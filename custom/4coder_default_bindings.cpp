/*4coder_default_bidings.cpp - Supplies the default bindings used for default 4coder behavior.
*/

// TOP


// BOTTOM

#if !defined(FCODER_DEFAULT_BINDINGS_CPP)
#define FCODER_DEFAULT_BINDINGS_CPP

#include "4coder_default_include.cpp"

// NOTE(allen): Users can declare their own managed IDs here.

#if !defined(META_PASS)
#include "generated/managed_id_metadata.cpp"
#endif

CUSTOM_COMMAND_SIG(move_to_line_boundary_backward)
{
    View_ID view = get_active_view(app, Access_ReadVisible);
    while(true)
    {
        i64 oldPos = view_get_cursor_pos(app, view);
        seek_beginning_of_line(app);
        i64 currentPos = view_get_cursor_pos(app, view);
        
        if(oldPos == currentPos)
        {
            move_up(app);
            seek_end_of_line(app);
        }
        else
        {
            break;
        }
    }
}

CUSTOM_COMMAND_SIG(move_to_line_boundary_forward)
{
    View_ID view = get_active_view(app, Access_ReadVisible);
    while(true)
    {
        i64 oldPos = view_get_cursor_pos(app, view);
        seek_end_of_line(app);
        i64 currentPos = view_get_cursor_pos(app, view);
        
        if(oldPos == currentPos)
        {
            move_down(app);
            seek_beginning_of_line(app);
        }
        else
        {
            break;
        }
    }
}

CUSTOM_COMMAND_SIG(delete_next_line)
{
    View_ID view = get_active_view(app, Access_ReadVisible);
    i64 pos = view_get_cursor_pos(app, view);
    
    move_down(app);
    delete_line(app);
    
    view_set_cursor(app, view, seek_pos(pos));
}

CUSTOM_COMMAND_SIG(delete_to_end_of_line_and_terminate)
{
    Scratch_Block scratch(app);
    set_mark(app);
    seek_end_of_line(app);
    delete_range(app);
    String_Const_u8 str = push_u8_stringf(scratch, ";");
    write_string(app, str);
}

CUSTOM_COMMAND_SIG(copy_current_line)
{
    seek_beginning_of_line(app);
    set_mark(app);
    seek_end_of_line(app);
    copy(app);
}

function b32
query_replace_custom(Application_Links *app, View_ID view, Buffer_ID buffer_id, i64 pos, String_Const_u8 r, String_Const_u8 w){
    b32 result = false;
    
    i64 new_pos = 0;
    seek_string_forward(app, buffer_id, pos - 1, 0, r, &new_pos);
    
    User_Input in = {};
    for (;;){
        if(new_pos == buffer_get_size(app, buffer_id))
        {
            break;
        }
        
        Range_i64 match = Ii64(new_pos, new_pos + r.size);
        isearch__update_highlight(app, view, match);
        
        in = get_next_input(app, EventProperty_AnyKey, EventProperty_MouseButton);
        if (in.abort || match_key_code(&in, KeyCode_Escape) || !is_unmodified_key(&in.event)){
            result = true;
            break;
        }
        
        i64 size = buffer_get_size(app, buffer_id);
        if (match.max <= size &&
            (match_key_code(&in, KeyCode_Y) ||
             match_key_code(&in, KeyCode_Return) ||
             match_key_code(&in, KeyCode_Tab))){
            buffer_replace_range(app, buffer_id, match, w);
            pos = match.start + w.size;
        }
        else{
            pos = match.max;
        }
        
        seek_string_forward(app, buffer_id, pos, 0, r, &new_pos);
    }
    
    view_disable_highlight_range(app, view);
    
    if (in.abort){
        result = true;
    }
    
    view_set_cursor_and_preferred_x(app, view, seek_pos(pos));
    return result;
}

function void
query_replace_all_buffers__(Application_Links *app, String_Const_u8 replace_str, Buffer_ID starting_buffer){
    Query_Bar_Group group(app);
    
    View_ID view = get_active_view(app, Access_ReadWriteVisible);
    Query_Bar with = {};
    u8 with_space[1024];
    with.prompt = string_u8_litexpr("With: ");
    with.string = SCu8(with_space, (u64)0);
    with.string_capacity = sizeof(with_space);
    
    if (query_user_string(app, &with)){
        String_Const_u8 r = replace_str;
        String_Const_u8 w = with.string;
        
        Query_Bar bar = {};
        bar.prompt = string_u8_litexpr("Replace? (y)es, (n)ext, (esc)\n");
        start_query_bar(app, &bar, 0);
        
        for (Buffer_ID buffer = get_buffer_next(app, 0, Access_ReadWriteVisible);
             buffer != 0;
             buffer = get_buffer_next(app, buffer, Access_ReadWriteVisible))
        {
            view_set_buffer(app, view, buffer, SetBuffer_DontUpdateTouchList);
            
            i64 pos = 0;
            i64 new_pos = 0;
            seek_string_forward(app, buffer,pos, 0, r, &new_pos);
            
            User_Input in = {};
            for (;;){
                if(new_pos >= buffer_get_size(app, buffer))
                {
                    break;
                }
                Range_i64 match = Ii64(new_pos, new_pos + r.size);
                isearch__update_highlight(app, view, match);
                
                in = get_next_input(app, EventProperty_AnyKey, EventProperty_MouseButton);
                if (in.abort || match_key_code(&in, KeyCode_Escape) || !is_unmodified_key(&in.event)){
                    break;
                }
                
                i64 size = buffer_get_size(app, buffer);
                if (match.max <= size &&
                    (match_key_code(&in, KeyCode_Y) ||
                     match_key_code(&in, KeyCode_Return) ||
                     match_key_code(&in, KeyCode_Tab))){
                    buffer_replace_range(app, buffer, match, w);
                    pos = match.start + w.size;
                }
                else{
                    pos = match.max;
                }
                
                seek_string_forward(app, buffer, pos, 0, r, &new_pos);
            }
            
            view_disable_highlight_range(app, view);
            if (in.abort || match_key_code(&in, KeyCode_Escape)){
                return;
            }
            
            view_set_cursor_and_preferred_x(app, view, seek_pos(pos));
        }
    }
}

CUSTOM_COMMAND_SIG(query_replace_in_all_buffers)
CUSTOM_DOC("Queries the user for two strings, and incrementally replaces every occurence of the first string with the second string in all loaded buffers.")
{
    
    View_ID view = get_active_view(app, Access_ReadWriteVisible);
    Buffer_ID activeBuffer = view_get_buffer(app, view, Access_ReadWriteVisible);
    i64 mark_pos = view_get_mark_pos(app, view);
    i64 cursor_pos = view_get_cursor_pos(app, view);
    
    Query_Bar_Group group(app);
    Query_Bar replace = {};
    u8 replace_space[1024];
    replace.prompt = string_u8_litexpr("Interactive Replace All: ");
    replace.string = SCu8(replace_space, (u64)0);
    replace.string_capacity = sizeof(replace_space);
    if (query_user_string(app, &replace)){
        if (replace.string.size > 0){
            query_replace_all_buffers__(app, replace.string, activeBuffer);
            
            view_set_buffer(app, view, activeBuffer, 0);
            view_set_cursor_and_preferred_x(app, view, seek_pos(cursor_pos));
            view_set_mark(app, view, seek_pos(mark_pos));
        }
    }
}

CUSTOM_COMMAND_SIG(custom_move_up)
{
    Input_Event event  = {};
    event.virtual_event = true;
    event.kind = InputEventKind_KeyStroke;
    event.key.code = KeyCode_Up;
    enqueue_virtual_event(app, &event);
}


CUSTOM_COMMAND_SIG(custom_move_down)
{
    Input_Event event  = {};
    event.virtual_event = true;
    event.kind = InputEventKind_KeyStroke;
    event.key.code = KeyCode_Down;
    enqueue_virtual_event(app, &event);
}

CUSTOM_COMMAND_SIG(custom_move_left)
{
    Input_Event event  = {};
    event.virtual_event = true;
    event.kind = InputEventKind_KeyStroke;
    event.key.code = KeyCode_Left;
    enqueue_virtual_event(app, &event);
}

CUSTOM_COMMAND_SIG(custom_move_right)
{
    Input_Event event  = {};
    event.virtual_event = true;
    event.kind = InputEventKind_KeyStroke;
    event.key.code = KeyCode_Right;
    enqueue_virtual_event(app, &event);
}

CUSTOM_COMMAND_SIG(comment_block)
{
    place_begin_and_end_on_own_lines(app, "/* ", " //*/");
}

CUSTOM_COMMAND_SIG(place_line_in_scope)
{
    seek_beginning_of_line(app);
    set_mark(app);
    seek_end_of_line(app);
    place_in_scope(app);
    
}

CUSTOM_COMMAND_SIG(place_line_in_scope_and_semicolon)
{
    seek_beginning_of_line(app);
    set_mark(app);
    seek_end_of_line(app);
    place_begin_and_end_on_own_lines(app, "{", "};");
}

CUSTOM_COMMAND_SIG(place_line_after_scope_in_scope)
{
    select_surrounding_scope(app);
    cursor_mark_swap(app);
    move_down(app);
    move_line_up(app);
}

CUSTOM_COMMAND_SIG(place_line_before_scope_in_scope)
{
    select_surrounding_scope(app);
    move_up(app);
    move_line_down(app);
}

CUSTOM_COMMAND_SIG(delete_current_scope_custom)
{
    select_surrounding_scope(app);
    delete_range(app);
} 

CUSTOM_COMMAND_SIG(select_next_top_most_scope)
{
    View_ID view = get_active_view(app, Access_ReadVisible);
    
    i64 oldPos = view_get_cursor_pos(app, view);
    select_next_scope_absolute(app);
    select_surrounding_scope_maximal(app);
    i64 currentPos = view_get_cursor_pos(app, view);
    
    if(oldPos == currentPos)
    {
        cursor_mark_swap(app);
        select_next_scope_absolute(app);
        select_surrounding_scope_maximal(app);
    }
}


CUSTOM_COMMAND_SIG(goto_prev_odin_function)
{
    View_ID view = get_active_view(app, Access_ReadVisible);
    Buffer_ID buffer = view_get_buffer(app, view, Access_ReadVisible);
    i64 pos = view_get_cursor_pos(app, view);
    
    move_up(app);
    
    i64 searchPos = view_get_cursor_pos(app, view);
    i64 new_pos;
    String_Const_u8 str = string_u8_litexpr("proc(");
    seek_string_insensitive_backward(app, buffer, searchPos, 0, str, &new_pos);
    
    b32 found = (new_pos < buffer_get_size(app, buffer) && new_pos > 0);
    if(!found)
    {
        new_pos = pos;
    }
    
    view_set_cursor(app, view, seek_pos(new_pos));
    
    if(found)
    {
        seek_beginning_of_line(app);
    }
}

CUSTOM_COMMAND_SIG(goto_next_odin_function)
{
    View_ID view = get_active_view(app, Access_ReadVisible);
    Buffer_ID buffer = view_get_buffer(app, view, Access_ReadVisible);
    i64 pos = view_get_cursor_pos(app, view);
    move_down(app);
    
    i64 searchPos = view_get_cursor_pos(app, view);
    
    i64 new_pos;
    String_Const_u8 str = string_u8_litexpr("proc(");
    seek_string_insensitive_forward(app, buffer, searchPos, 0, str, &new_pos);
    
    b32 found = (new_pos < buffer_get_size(app, buffer) && new_pos > 0);
    if(!found)
    {
        new_pos = pos;
    }
    
    view_set_cursor(app, view, seek_pos(new_pos));
    
    if(found)
    {
        seek_beginning_of_line(app);
    }
    
}

static Buffer_ID global_buffer_hot_reload_theme;

CUSTOM_COMMAND_SIG(toggle_theme_hot_reload)
{
    View_ID active_view = get_active_view(app, Access_Always);
    Buffer_ID buffer = view_get_buffer(app, active_view, Access_Always);
    
    if(buffer == global_buffer_hot_reload_theme)
    {
        global_buffer_hot_reload_theme = {};
    }
    else
    {
        //load_theme_current_buffer(app);
        global_buffer_hot_reload_theme = buffer;
    }
}

CUSTOM_COMMAND_SIG(pick_color)
{
    View_ID view = get_this_ctx_view(app, Access_Always);
#if 0
    View_Context ctx = view_current_context(app, view);
    ctx.render_caller = lister_render;
    ctx.hides_buffer = true;
    View_Context_Block ctx_block(app, view, &ctx);
#endif
    
    for (;;)
    {
        String_Const_u8 color = string_u8_litexpr("invalid");
        User_Input in = get_next_input(app, EventPropertyGroup_Any, EventProperty_Escape);
        if (in.abort){
            break;
        }
        switch(in.event.kind)
        {
            case InputEventKind_KeyStroke:
            {
                switch(in.event.key.code)
                {
                    case KeyCode_R:
                    {
                        color = string_u8_litexpr("0xFFFF0000;");
                    } break;
                    
                    case KeyCode_G:
                    {
                        color = string_u8_litexpr("0xFF00FF00;");
                    } break;
                    
                    case KeyCode_B:
                    {
                        color = string_u8_litexpr("0xFF0000FF;");
                    } break;
                }
            }
        }
        
        if(!string_match(color, string_u8_litexpr("invalid")))
        {
            i64 pos = view_get_cursor_pos(app, view);
            move_left_alpha_numeric_boundary(app);
            i64 markPos = view_get_cursor_pos(app, view);
            view_set_mark(app, view, seek_pos(markPos));
            seek_end_of_line(app);
            delete_range(app);
            write_string(app, color);
            view_set_cursor(app, view, seek_pos(pos));
            color = string_u8_litexpr("invalid");
        }
    }
#if 0
    switch (in.event.kind){
        case InputEventKind_TextInsert:
        {
            if (lister->handlers.write_character != 0){
                result = lister->handlers.write_character(app);
            }
        }break;
        
        case InputEventKind_KeyStroke:
        {
            switch (in.event.key.code){
                case KeyCode_Return:
                case KeyCode_Tab:
                {
                    void *user_data = 0;
                    if (0 <= lister->raw_item_index &&
                        lister->raw_item_index < lister->options.count){
                        user_data = lister_get_user_data(lister, lister->raw_item_index);
                    }
                    lister_activate(app, lister, user_data, false);
                    result = ListerActivation_Finished;
                }break;
                
                case KeyCode_Backspace:
                {
                    if (lister->handlers.backspace != 0){
                        lister->handlers.backspace(app);
                    }
                    else if (lister->handlers.key_stroke != 0){
                        result = lister->handlers.key_stroke(app);
                    }
                    else{
                        handled = false;
                    }
                }break;
                
                case KeyCode_Up:
                {
                    if (lister->handlers.navigate != 0){
                        lister->handlers.navigate(app, view, lister, -1);
                    }
                    else if (lister->handlers.key_stroke != 0){
                        result = lister->handlers.key_stroke(app);
                    }
                    else{
                        handled = false;
                    }
                }break;
                
                case KeyCode_Down:
                {
                    if (lister->handlers.navigate != 0){
                        lister->handlers.navigate(app, view, lister, 1);
                    }
                    else if (lister->handlers.key_stroke != 0){
                        result = lister->handlers.key_stroke(app);
                    }
                    else{
                        handled = false;
                    }
                }break;
                
                case KeyCode_PageUp:
                {
                    if (lister->handlers.navigate != 0){
                        lister->handlers.navigate(app, view, lister,
                                                  -lister->visible_count);
                    }
                    else if (lister->handlers.key_stroke != 0){
                        result = lister->handlers.key_stroke(app);
                    }
                    else{
                        handled = false;
                    }
                }break;
                
                case KeyCode_PageDown:
                {
                    if (lister->handlers.navigate != 0){
                        lister->handlers.navigate(app, view, lister,
                                                  lister->visible_count);
                    }
                    else if (lister->handlers.key_stroke != 0){
                        result = lister->handlers.key_stroke(app);
                    }
                    else{
                        handled = false;
                    }
                }break;
                
                default:
                {
                    if (lister->handlers.key_stroke != 0){
                        result = lister->handlers.key_stroke(app);
                    }
                    else{
                        handled = false;
                    }
                }break;
            }
        }break;
        
        case InputEventKind_MouseButton:
        {
            switch (in.event.mouse.code){
                case MouseCode_Left:
                {
                    Vec2_f32 p = V2f32(in.event.mouse.p);
                    void *clicked = lister_user_data_at_p(app, view, lister, p);
                    lister->hot_user_data = clicked;
                }break;
                
                default:
                {
                    handled = false;
                }break;
            }
        }break;
        
        case InputEventKind_MouseButtonRelease:
        {
            switch (in.event.mouse.code){
                case MouseCode_Left:
                {
                    if (lister->hot_user_data != 0){
                        Vec2_f32 p = V2f32(in.event.mouse.p);
                        void *clicked = lister_user_data_at_p(app, view, lister, p);
                        if (lister->hot_user_data == clicked){
                            lister_activate(app, lister, clicked, true);
                            result = ListerActivation_Finished;
                        }
                    }
                    lister->hot_user_data = 0;
                }break;
                
                default:
                {
                    handled = false;
                }break;
            }
        }break;
        
        case InputEventKind_MouseWheel:
        {
            Mouse_State mouse = get_mouse_state(app);
            lister->scroll.target.y += mouse.wheel;
            lister_update_filtered_list(app, lister);
        }break;
        
        case InputEventKind_MouseMove:
        {
            lister_update_filtered_list(app, lister);
        }break;
        
        case InputEventKind_Core:
        {
            switch (in.event.core.code){
                case CoreCode_Animate:
                {
                    lister_update_filtered_list(app, lister);
                }break;
                
                default:
                {
                    handled = false;
                }break;
            }
        }break;
        
        default:
        {
            handled = false;
        }break;
    }
    
    if (result == ListerActivation_Finished){
        break;
    }
    
    if (!handled){
        Mapping *mapping = lister->mapping;
        Command_Map *map = lister->map;
        
        Fallback_Dispatch_Result disp_result =
            fallback_command_dispatch(app, mapping, map, &in);
        if (disp_result.code == FallbackDispatch_DelayedUICall){
            call_after_ctx_shutdown(app, view, disp_result.func);
            break;
        }
        
        if (disp_result.code == FallbackDispatch_Unhandled){
            leave_current_input_unhandled(app);
        }
        else{
            lister_call_refresh_handler(app, lister);
        }
    }
}
#endif
}


CUSTOM_COMMAND_SIG(keyboard_macro_start_stop_recording)
{
    if (global_keyboard_macro_is_recording ||
        get_current_input_is_virtual(app))
    {
        keyboard_macro_finish_recording(app);
    }
    else
    {
        keyboard_macro_start_recording(app);
    }
}

CUSTOM_COMMAND_SIG(save_all_dirty_and_build_in_build_panel)
{
    save_all_dirty_buffers(app);
    build_in_build_panel(app);
}

CUSTOM_COMMAND_SIG(view_jump_list_with_lister_and_close_jump_list)
{
    Heap *heap = &global_heap;
    View_ID view = get_active_view(app, Access_Always);
    Buffer_ID buffer = view_get_buffer(app, view, Access_Always);
    Marker_List *list = get_or_make_list_for_buffer(app, heap, buffer);
    if (list != 0){
        Jump_Lister_Result jump = get_jump_index_from_user(app, list, "Jump:");
        jump_to_jump_lister_result(app, view, list, &jump);
        delete_marker_list(list);
    }
}

CUSTOM_COMMAND_SIG(copy_line)
{
    View_ID view = get_active_view(app, Access_ReadVisible);
    Buffer_ID buffer = view_get_buffer(app, view, Access_ReadVisible);
    i64 line_number = get_line_number_from_pos(app, buffer, view_get_cursor_pos(app, view));
    Range_i64 range = get_line_pos_range(app, buffer, line_number);
    clipboard_post_buffer_range(app, 0, buffer, range);
}

CUSTOM_COMMAND_SIG(copy_token)
{
    View_ID view = get_active_view(app, Access_ReadVisible);
    Buffer_ID buffer = view_get_buffer(app, view, Access_ReadVisible);
    Range_i64 token_range = enclose_pos_tokens(app, buffer, view_get_cursor_pos(app, view));
    clipboard_post_buffer_range(app, 0, buffer, token_range);
}

CUSTOM_COMMAND_SIG(cut_token)
{
    View_ID view = get_active_view(app, Access_ReadVisible);
    Buffer_ID buffer = view_get_buffer(app, view, Access_ReadVisible);
    Range_i64 token_range = enclose_pos_tokens(app, buffer, view_get_cursor_pos(app, view));
    clipboard_post_buffer_range(app, 0, buffer, token_range);
    buffer_replace_range(app, buffer, token_range, string_u8_empty);
}

CUSTOM_COMMAND_SIG(cut_line)
{
    copy_line(app);
    delete_line(app);
}


CUSTOM_COMMAND_SIG(move_range_up)
{
    View_ID view = get_active_view(app, Access_ReadVisible);
    Buffer_ID buffer = view_get_buffer(app, view, Access_ReadVisible);
    
    i64 mark_pos = view_get_mark_pos(app, view);
    i64 cursor_pos = view_get_cursor_pos(app, view);
    
    if(mark_pos != cursor_pos)
    {
        Scratch_Block scratch(app);
        
        Range_i64 range = get_view_range(app, view);
        String_Const_u8 text = push_buffer_range(app, scratch, buffer, range);
        delete_range(app);
        move_up(app);
        seek_beginning_of_line(app);
        
        i64 pos = view_get_cursor_pos(app, view);
        buffer_replace_range(app, buffer, Ii64(pos), text);
        
        if(mark_pos < cursor_pos)
        {
            view_set_mark(app, view, seek_pos(pos));
            view_set_cursor_and_preferred_x(app, view, seek_pos(pos + (i32)text.size));
        }
        else
        {
            view_set_mark(app, view, seek_pos(pos + (i32) text.size));
            view_set_cursor_and_preferred_x(app, view, seek_pos(pos));
        }
        
    }
}

CUSTOM_COMMAND_SIG(move_range_down)
{
    View_ID view = get_active_view(app, Access_ReadVisible);
    Buffer_ID buffer = view_get_buffer(app, view, Access_ReadVisible);
    
    i64 mark_pos = view_get_mark_pos(app, view);
    i64 cursor_pos = view_get_cursor_pos(app, view);
    
    if(mark_pos != cursor_pos)
    {
        Scratch_Block scratch(app);
        
        Range_i64 range = get_view_range(app, view);
        String_Const_u8 text = push_buffer_range(app, scratch, buffer, range);
        delete_range(app);
        move_down(app);
        seek_beginning_of_line(app);
        
        i64 pos = view_get_cursor_pos(app, view);
        buffer_replace_range(app, buffer, Ii64(pos), text);
        
        if(mark_pos < cursor_pos)
        {
            view_set_mark(app, view, seek_pos(pos));
            view_set_cursor_and_preferred_x(app, view, seek_pos(pos + (i32)text.size));
        }
        else
        {
            view_set_mark(app, view, seek_pos(pos + (i32) text.size));
            view_set_cursor_and_preferred_x(app, view, seek_pos(pos));
        }
    }
}

CUSTOM_COMMAND_SIG(duplicate_range)
{
    View_ID view = get_active_view(app, Access_ReadVisible);
    Buffer_ID buffer = view_get_buffer(app, view, Access_ReadVisible);
    
    i64 mark_pos = view_get_mark_pos(app, view);
    i64 cursor_pos = view_get_cursor_pos(app, view);
    
    if(mark_pos != cursor_pos)
    {
        Scratch_Block scratch(app);
        Range_i64 range = get_view_range(app, view);
        String_Const_u8 text = push_buffer_range(app, scratch, buffer, range);
        text = push_u8_stringf(scratch, "%.*s", string_expand(text));
        
        i64 pos = mark_pos;
        if(cursor_pos < mark_pos)
        {
            pos = cursor_pos;
        }
        
        buffer_replace_range(app, buffer, Ii64(pos), text);
        
        if(mark_pos < cursor_pos)
        {
            view_set_mark(app, view, seek_pos(pos));
            view_set_cursor_and_preferred_x(app, view, seek_pos(pos + (i32)text.size));
        }
        else
        {
            view_set_mark(app, view, seek_pos(pos + (i32) text.size));
            view_set_cursor_and_preferred_x(app, view, seek_pos(pos));
        }
    }
}

CUSTOM_COMMAND_SIG(delete_from_beginning_of_line)
{
    set_mark(app);
    seek_beginning_of_line(app);
    delete_range(app);
}


CUSTOM_COMMAND_SIG(delete_line_add_to_clip)
{
    View_ID view = get_active_view(app, Access_ReadVisible);
    Buffer_ID buffer = view_get_buffer(app, view, Access_ReadVisible);
    
    seek_beginning_of_line(app);
    set_mark(app);
    seek_end_of_line(app);
    
    Scratch_Block scratch(app);
    
    Range_i64 range = get_view_range(app, view);
    
    String_Const_u8 line = push_buffer_range(app, scratch, buffer, range);
    delete_line(app);
    
    String_Const_u8 to_copy = {};
    if(clipboard_count(0) != 0)
    {
        String_Const_u8 clipboard = push_clipboard_index(scratch, 0, 0);
        to_copy = push_stringf(scratch, "%.*s%.*s\n", clipboard.size, clipboard.str, line.size, line.str);
    }
    else
    {
        to_copy = push_stringf(scratch, "%.*s\n", line.size, line.str);
    }
    
    if (to_copy.size > 0){
        clipboard_post(0, to_copy);
    }
}

CUSTOM_COMMAND_SIG(cut_add_to_clip)
{
    View_ID view = get_active_view(app, Access_ReadVisible);
    Buffer_ID buffer = view_get_buffer(app, view, Access_ReadVisible);
    
    Scratch_Block scratch(app);
    
    Range_i64 range = get_view_range(app, view);
    
    String_Const_u8 range_buffer = push_buffer_range(app, scratch, buffer, range);
    delete_range(app);
    
    String_Const_u8 to_copy = {};
    if(clipboard_count(0) != 0)
    {
        String_Const_u8 clipboard = push_clipboard_index(scratch, 0, 0);
        to_copy = push_stringf(scratch, "%.*s%.*s", clipboard.size, clipboard.str, range_buffer.size, range_buffer.str);
    }
    else
    {
        to_copy = push_stringf(scratch, "%.*s", range_buffer.size, range_buffer.str);
    }
    
    if (to_copy.size > 0){
        clipboard_post(0, to_copy);
    }
}

CUSTOM_COMMAND_SIG(quick_peel_buffer)
{
    View_ID view = get_active_view(app, Access_ReadVisible);
    Buffer_ID buffer = view_get_buffer(app, view, Access_ReadVisible);
    Buffer_ID next_buffer = get_buffer_next(app, buffer, Access_ReadVisible);
    view_set_buffer(app, view, next_buffer, SetBuffer_DontUpdateTouchList);
}

CUSTOM_COMMAND_SIG(view_buffer_other_panel_switch_back)
{
    view_buffer_other_panel(app);
    change_active_panel(app);
}

CUSTOM_COMMAND_SIG(quick_goto_next_buffer_in_stack)
{
    View_ID view = get_active_view(app, Access_ReadVisible);
    Buffer_ID buffer = view_get_buffer(app, view, Access_ReadVisible);
    Buffer_ID next_buffer = get_buffer_prev(app, buffer, Access_ReadVisible);
    view_set_buffer(app, view, next_buffer, SetBuffer_DontUpdateTouchList);
}

CUSTOM_COMMAND_SIG(list_all_type_definitions_current_buffer_lister)
{
    String_Const_u8 decls_name = string_u8_litexpr("*decls*");
    Buffer_ID decls_buffer = get_buffer_by_name(app, decls_name, Access_Always);
    if (!buffer_exists(app, decls_buffer)){
        decls_buffer = create_buffer(app, decls_name, BufferCreate_AlwaysNew);
        buffer_set_setting(app, decls_buffer, BufferSetting_Unimportant, true);
        buffer_set_setting(app, decls_buffer, BufferSetting_ReadOnly, true);
        //buffer_set_setting(app, decls_buffer, BufferSetting_WrapLine, false);
    }
    else{
        clear_buffer(app, decls_buffer);
        buffer_send_end_signal(app, decls_buffer);
    }
    
    Scratch_Block scratch(app);
    
    String_Const_u8_Array array = {};
    array.count = 3;
    array.vals = push_array(scratch, String_Const_u8, array.count);
    i32 i = 0;
    array.vals[i++] = (push_u8_stringf(scratch, "\nstruct"));
    array.vals[i++] = (push_u8_stringf(scratch, "\nunion "));
    array.vals[i++] = (push_u8_stringf(scratch, "\nenum "));
    Assert(i == array.count);
    
    View_ID view = get_active_view(app, Access_Always);
    Buffer_ID buffer = view_get_buffer(app, view, Access_Always);
    
    list_all_locations_in_buffer__generic_buffer(app, buffer, array, ListAllLocationsFlag_CaseSensitive|ListAllLocationsFlag_MatchSubstring, decls_buffer, 1);
    
    Heap *heap = &global_heap;
    view = get_active_view(app, Access_Always);
    view_set_buffer(app, view, decls_buffer, 0);
    buffer = view_get_buffer(app, view, Access_Always);
    
    lock_jump_buffer(app, decls_name);
    
    Marker_List *list = get_or_make_list_for_buffer(app, heap, buffer);
    if (list != 0){
        Jump_Lister_Result jump = get_jump_index_from_user(app, list, "Definition:");
        jump_to_jump_lister_result(app, view, list, &jump);
        try_buffer_kill(app, decls_buffer, view, 0);
        
        buffer = view_get_buffer(app, view, Access_ReadVisible);
        i64 read_only = 0;
        if(buffer_get_setting(app, buffer, BufferSetting_ReadOnly, &read_only) && read_only > 0)
        {
            quick_peel_buffer(app);
        }
    }
}

CUSTOM_COMMAND_SIG(interactive_search_type_definition)
{
    String_Const_u8 decls_name = string_u8_litexpr("*decls*");
    Buffer_ID decls_buffer = get_buffer_by_name(app, decls_name, Access_Always);
    if (!buffer_exists(app, decls_buffer)){
        decls_buffer = create_buffer(app, decls_name, BufferCreate_AlwaysNew);
        buffer_set_setting(app, decls_buffer, BufferSetting_Unimportant, true);
        buffer_set_setting(app, decls_buffer, BufferSetting_ReadOnly, true);
        //buffer_set_setting(app, decls_buffer, BufferSetting_WrapLine, false);
    }
    else{
        clear_buffer(app, decls_buffer);
        buffer_send_end_signal(app, decls_buffer);
    }
    
    Scratch_Block scratch(app);
    String_Const_u8_Array array = {};
    array.count = 3;
    array.vals = push_array(scratch, String_Const_u8, array.count);
    i32 i = 0;
    array.vals[i++] = (push_u8_stringf(scratch, "\nstruct "));
    array.vals[i++] = (push_u8_stringf(scratch, "\nunion "));
    array.vals[i++] = (push_u8_stringf(scratch, "\nenum "));
    Assert(i == array.count);
    
    list_all_locations__generic_buffer_offset(app, array, ListAllLocationsFlag_CaseSensitive|ListAllLocationsFlag_MatchSubstring, decls_buffer, 1);
    
    Heap *heap = &global_heap;
    View_ID view = get_active_view(app, Access_Always);
    view_set_buffer(app, view, decls_buffer, 0);
    Buffer_ID buffer = view_get_buffer(app, view, Access_Always);
    
    lock_jump_buffer(app, decls_name);
    
    Marker_List *list = get_or_make_list_for_buffer(app, heap, buffer);
    if (list != 0){
        Jump_Lister_Result jump = get_jump_index_from_user(app, list, "Definition:");
        jump_to_jump_lister_result(app, view, list, &jump);
        try_buffer_kill(app, decls_buffer, view, 0);
        
        buffer = view_get_buffer(app, view, Access_ReadVisible);
        i64 read_only = 0;
        if(buffer_get_setting(app, buffer, BufferSetting_ReadOnly, &read_only) && read_only > 0)
        {
            quick_peel_buffer(app);
        }
    }
}

CUSTOM_COMMAND_SIG(custom_list_all_functions_current_buffer_lister)
{
    list_all_functions_current_buffer_lister(app);
    String_Const_u8 decls_name = string_u8_litexpr("*decls*");
    Buffer_ID decls_buffer = get_buffer_by_name(app, decls_name, Access_Always);
    View_ID view = get_active_view(app, Access_Always);
    try_buffer_kill(app, decls_buffer, view, 0);
    
    Buffer_ID buffer = view_get_buffer(app, view, Access_ReadVisible);
    i64 read_only = 0;
    if(buffer_get_setting(app, buffer, BufferSetting_ReadOnly, &read_only) && read_only > 0)
    {
        quick_peel_buffer(app);
    }
}

CUSTOM_COMMAND_SIG(custom_list_all_functions_all_buffers_lister)
{
    list_all_functions_all_buffers_lister(app);
    String_Const_u8 decls_name = string_u8_litexpr("*decls*");
    Buffer_ID decls_buffer = get_buffer_by_name(app, decls_name, Access_Always);
    View_ID view = get_active_view(app, Access_Always);
    try_buffer_kill(app, decls_buffer, view, 0);
    
    Buffer_ID buffer = view_get_buffer(app, view, Access_ReadVisible);
    i64 read_only = 0;
    if(buffer_get_setting(app, buffer, BufferSetting_ReadOnly, &read_only) && read_only > 0)
    {
        quick_peel_buffer(app);
    }
}




CUSTOM_COMMAND_SIG(swap_token_right)
{
    View_ID view = get_active_view(app, Access_ReadVisible);
    Buffer_ID buffer = view_get_buffer(app, view, Access_ReadVisible);
    
    Range_i64 range_1 = enclose_pos_tokens(app, buffer, view_get_cursor_pos(app, view));
    
    move_right_alpha_numeric_underscore_boundary(app);
    
    i64 pos = view_get_cursor_pos(app, view);
    if(pos == range_1.end)
    {
        move_right_alpha_numeric_underscore_boundary(app);
    }
    move_left(app);
    
    Range_i64 range_2 = enclose_pos_tokens(app, buffer, view_get_cursor_pos(app, view));
    
    Scratch_Block scratch(app);
    
    String_Const_u8 text_1 = push_buffer_range(app, scratch, buffer, range_1);
    String_Const_u8 text_2 = push_buffer_range(app, scratch, buffer, range_2);
    
    History_Group group = history_group_begin(app, buffer);
    buffer_replace_range(app, buffer, range_2, text_1);
    buffer_replace_range(app, buffer, range_1, text_2);
    history_group_end(group);
    
    replace_range_shift(range_1, text_2.size);
}

CUSTOM_COMMAND_SIG(swap_token_left)
{
    View_ID view = get_active_view(app, Access_ReadVisible);
    Buffer_ID buffer = view_get_buffer(app, view, Access_ReadVisible);
    
    Range_i64 range_1 = enclose_pos_tokens(app, buffer, view_get_cursor_pos(app, view));
    
    move_left_alpha_numeric_underscore_boundary(app);
    
    i64 pos = view_get_cursor_pos(app, view);
    if(pos == range_1.start)
    {
        move_left_alpha_numeric_underscore_boundary(app);
    }
    move_right(app);
    
    Range_i64 range_2 = enclose_pos_tokens(app, buffer, view_get_cursor_pos(app, view));
    
    Scratch_Block scratch(app);
    
    String_Const_u8 text_1 = push_buffer_range(app, scratch, buffer, range_1);
    String_Const_u8 text_2 = push_buffer_range(app, scratch, buffer, range_2);
    
    History_Group group = history_group_begin(app, buffer);
    buffer_replace_range(app, buffer, range_1, text_2);
    buffer_replace_range(app, buffer, range_2, text_1);
    history_group_end(group);
    
    replace_range_shift(range_2, text_1.size);
}

CUSTOM_COMMAND_SIG(goto_prev_function)
{
    select_prev_top_most_scope(app);
}

CUSTOM_COMMAND_SIG(goto_next_function)
{
    select_next_top_most_scope(app);
}

CUSTOM_COMMAND_SIG(scan_prev_brace_or_open_paren)
{
    View_ID view = get_active_view(app, Access_ReadVisible);
    Buffer_ID buffer = view_get_buffer(app, view, Access_ReadVisible);
    i64 pos = view_get_cursor_pos(app, view);
    
    i64 brace_pos;
    i64 parent_pos;
    
    String_Const_u8 str = string_u8_litexpr("{");
    seek_string_insensitive_backward(app, buffer, pos, 0, str, &brace_pos);
    
    str = string_u8_litexpr("(");
    seek_string_insensitive_backward(app, buffer, pos, 0, str, &parent_pos);
    
    i64 new_pos = Max(brace_pos, parent_pos);
    b32 found = (new_pos < buffer_get_size(app, buffer) && new_pos > 0);
    if(!found)
    {
        new_pos = pos;
    }
    view_set_cursor(app, view, seek_pos(new_pos));
}

CUSTOM_COMMAND_SIG(scan_next_brace_or_close_paren)
{
    View_ID view = get_active_view(app, Access_ReadVisible);
    Buffer_ID buffer = view_get_buffer(app, view, Access_ReadVisible);
    i64 pos = view_get_cursor_pos(app, view);
    i64 brace_pos;
    i64 parent_pos;
    
    String_Const_u8 str = string_u8_litexpr("}");
    seek_string_insensitive_forward(app, buffer, pos, 0, str, &brace_pos);
    
    str = string_u8_litexpr(")");
    seek_string_insensitive_forward(app, buffer, pos, 0, str, &parent_pos);
    
    i64 new_pos = Min(brace_pos, parent_pos);
    b32 found = (new_pos < buffer_get_size(app, buffer) && new_pos > 0);
    if(!found)
    {
        new_pos = pos;
    }
    view_set_cursor(app, view, seek_pos(new_pos));
}

CUSTOM_COMMAND_SIG(paste_and_indent_invert_mark_cursor)
{
    paste_and_indent(app);
    cursor_mark_swap(app);
}

i64 smart_copied_token_cursor_pos = -1;
i64 smart_copied_token_mark_pos = -1;

i64 smart_copied_line_cursor_pos = -1;
i64 smart_copied_line_mark_pos = -1;

CUSTOM_COMMAND_SIG(custom_smart_copy)
{
    View_ID view = get_active_view(app, Access_ReadVisible);
    Buffer_ID buffer = view_get_buffer(app, view, Access_ReadVisible);
    
    i64 cursor_pos = view_get_cursor_pos(app, view);
    i64 mark_pos = view_get_mark_pos(app, view);
    
    if(smart_copied_line_cursor_pos == cursor_pos && smart_copied_line_mark_pos == mark_pos)
    {
        i64 prev_blank = get_pos_of_blank_line_grouped(app, buffer, Scan_Backward, cursor_pos);
        prev_blank = view_get_character_legal_pos_from_pos(app, view, prev_blank);
        
        i64 next_blank = get_pos_of_blank_line_grouped(app, buffer, Scan_Forward, cursor_pos);
        next_blank = view_get_character_legal_pos_from_pos(app, view, next_blank);
        
        Range_i64 range = {prev_blank, next_blank + 1};
        
        Range_i64 scope_range = {};
        if (find_surrounding_nest(app, buffer, cursor_pos, FindNest_Scope, &scope_range)){
            
            i64 min = Min(cursor_pos, mark_pos);
            i64 max = Max(cursor_pos, mark_pos);
            
            i64 blank_delta = (min - range.start) + (range.end - max);
            i64 scope_delta = (min - scope_range.start) + (scope_range.end - max);
            
            if(scope_delta < blank_delta)
            {
                range = scope_range;
            }
        }
        
        view_set_cursor_and_preferred_x(app, view, seek_pos(range.end));
        view_set_mark(app, view, seek_pos(range.start));
    }
    else if(smart_copied_token_cursor_pos == cursor_pos && smart_copied_token_mark_pos == mark_pos)
    {
        seek_beginning_of_line(app);
        set_mark(app);
        seek_end_of_line(app);
        
        smart_copied_line_cursor_pos = view_get_cursor_pos(app, view);
        smart_copied_line_mark_pos = view_get_mark_pos(app, view);
    }
    else
    {
        smart_copied_token_cursor_pos = -1;
        smart_copied_token_mark_pos = -1;
        
        smart_copied_line_cursor_pos = -1;
        smart_copied_line_mark_pos = -1;
        
        if(cursor_pos == mark_pos)
        {
            Range_i64 token_range = enclose_pos_tokens(app, buffer, view_get_cursor_pos(app, view));
            view_set_cursor_and_preferred_x(app, view, seek_pos(token_range.end));
            view_set_mark(app, view, seek_pos(token_range.start));
            
            smart_copied_token_cursor_pos = view_get_cursor_pos(app, view);
            smart_copied_token_mark_pos = view_get_mark_pos(app, view);
        }
    }
    
    copy(app);
}

CUSTOM_COMMAND_SIG(add_blank_line_after_cursor)
{
    View_ID view = get_active_view(app, Access_ReadVisible);
    Buffer_ID buffer = view_get_buffer(app, view, Access_ReadVisible);
    
    move_down(app);
    seek_beginning_of_line(app);
    i64 pos = view_get_cursor_pos(app, view);
    buffer_replace_range(app, buffer, Ii64(pos), SCu8("\n"));
}

function void setup_all_mappings(Mapping *mapping, i64 scopeid)
{
    MappingScope();
    SelectMapping(mapping);
    SelectMap(scopeid);
    
    // I/J/K/L
    
    Bind(scan_prev_brace_or_open_paren,                KeyCode_I, KeyCode_Control);
    Bind(scan_next_brace_or_close_paren,              KeyCode_K, KeyCode_Control);
    Bind(custom_move_left,                         KeyCode_J, KeyCode_Control);
    Bind(custom_move_right,                        KeyCode_L, KeyCode_Control);
    
    Bind(custom_move_up,                           KeyCode_I, KeyCode_Alt);
    Bind(custom_move_down,                         KeyCode_K, KeyCode_Alt);
    Bind(move_left_alpha_numeric_boundary,         KeyCode_J, KeyCode_Alt);
    Bind(move_right_alpha_numeric_boundary,        KeyCode_L, KeyCode_Alt);
    
    Bind(move_up_to_blank_line_end,                KeyCode_I, KeyCode_Alt, KeyCode_Shift);
    Bind(move_down_to_blank_line_end,              KeyCode_K, KeyCode_Alt, KeyCode_Shift);
    Bind(move_left_whitespace_boundary,            KeyCode_J, KeyCode_Alt, KeyCode_Shift);
    Bind(move_right_whitespace_boundary,           KeyCode_L, KeyCode_Alt, KeyCode_Shift);
    
    Bind(move_up_to_blank_line_end,            KeyCode_I, KeyCode_Alt, KeyCode_Control);
    Bind(move_down_to_blank_line_end,           KeyCode_K, KeyCode_Alt, KeyCode_Control);
    Bind(move_to_line_boundary_backward,           KeyCode_J, KeyCode_Alt, KeyCode_Control);
    Bind(move_to_line_boundary_forward,            KeyCode_L, KeyCode_Alt, KeyCode_Control);
    
    Bind(move_line_up,                             KeyCode_I, KeyCode_Control, KeyCode_Shift);
    Bind(move_line_down,                           KeyCode_K,KeyCode_Control,KeyCode_Shift);
    Bind(swap_token_right,                         KeyCode_L, KeyCode_Control, KeyCode_Shift);
    Bind(swap_token_left,                          KeyCode_J, KeyCode_Control, KeyCode_Shift);
    
    // Other navigation commands
    
    Bind(goto_prev_function, KeyCode_9, KeyCode_Alt);
    Bind(goto_next_function, KeyCode_0, KeyCode_Alt);
    
    Bind(goto_beginning_of_file, KeyCode_9, KeyCode_Alt, KeyCode_Shift);
    Bind(goto_end_of_file, KeyCode_0, KeyCode_Alt, KeyCode_Shift);
    
    Bind(select_prev_scope_absolute, KeyCode_Minus, KeyCode_Alt);
    Bind(select_next_scope_absolute, KeyCode_Equal, KeyCode_Alt);
    
    Bind(select_prev_top_most_scope, KeyCode_Minus, KeyCode_Alt, KeyCode_Shift);
    Bind(select_next_top_most_scope, KeyCode_Equal, KeyCode_Alt, KeyCode_Shift);
    
    
    // Arrows
    
    Bind(move_range_up,          KeyCode_Up, KeyCode_Shift, KeyCode_Control);
    Bind(move_range_down,         KeyCode_Down, KeyCode_Shift, KeyCode_Control);
    
    // General Purpouse Commands
    
    Bind(change_active_panel,           KeyCode_Semicolon, KeyCode_Alt);
    Bind(view_buffer_other_panel_switch_back, KeyCode_Semicolon, KeyCode_Alt, KeyCode_Shift);
    
    Bind(quick_peel_buffer, KeyCode_B, KeyCode_Alt);
    Bind(quick_goto_next_buffer_in_stack, KeyCode_B, KeyCode_Alt, KeyCode_Shift);
    
    Bind(interactive_open_or_new,       KeyCode_O, KeyCode_Alt);
    Bind(open_in_other,                 KeyCode_O, KeyCode_Alt, KeyCode_Control);
    
    Bind(redo,                        KeyCode_Y, KeyCode_Alt);
    Bind(undo,                        KeyCode_U, KeyCode_Alt);
    
    Bind(set_mark,                    KeyCode_Space, KeyCode_Alt);
    Bind(cursor_mark_swap,            KeyCode_Space, KeyCode_Alt, KeyCode_Shift);
    
    // copy and paste
    
    Bind(custom_smart_copy,                        KeyCode_C, KeyCode_Alt);
    Bind(copy_line,                   KeyCode_C, KeyCode_Alt, KeyCode_Control);
    Bind(copy_token,                   KeyCode_C, KeyCode_Control, KeyCode_Shift);
    
    Bind(paste_and_indent,            KeyCode_V, KeyCode_Alt);
    Bind(paste_and_indent_invert_mark_cursor, KeyCode_V, KeyCode_Alt, KeyCode_Control);
    Bind(paste_next_and_indent,       KeyCode_V, KeyCode_Alt, KeyCode_Shift);
    
    Bind(cut,                         KeyCode_X, KeyCode_Alt);
    Bind(delete_range,                KeyCode_X, KeyCode_Alt, KeyCode_Shift);
    Bind(cut_line,                    KeyCode_X, KeyCode_Alt, KeyCode_Control);
    Bind(cut_token,                    KeyCode_X, KeyCode_Shift, KeyCode_Control);
    
    Bind(cut_add_to_clip,             KeyCode_Z, KeyCode_Alt);
    Bind(delete_line_add_to_clip,     KeyCode_Z, KeyCode_Alt, KeyCode_Control);
    
    Bind(add_blank_line_after_cursor,              KeyCode_H, KeyCode_Alt);
    Bind(duplicate_line,              KeyCode_H, KeyCode_Alt, KeyCode_Control);
    Bind(duplicate_range,              KeyCode_H, KeyCode_Alt, KeyCode_Shift);
    
    Bind(delete_line,                 KeyCode_Backspace, KeyCode_Alt, KeyCode_Control);
    Bind(delete_next_line,            KeyCode_Delete, KeyCode_Alt, KeyCode_Control);
    
    // Delete Text Commands
    
    Bind(backspace_alpha_numeric_boundary, KeyCode_Backspace, KeyCode_Alt);
    Bind(snipe_backward_whitespace_or_token_boundary, KeyCode_Backspace, KeyCode_Alt, KeyCode_Shift);
    Bind(snipe_forward_whitespace_or_token_boundary,  KeyCode_Delete, KeyCode_Alt);
    
    // Search Commands
    
    Bind(search,                      KeyCode_S, KeyCode_Alt);
    Bind(reverse_search,              KeyCode_S, KeyCode_Alt, KeyCode_Shift);
    Bind(list_all_substring_locations_case_insensitive, KeyCode_S, KeyCode_Alt, KeyCode_Control);
    
    Bind(custom_list_all_functions_current_buffer_lister, KeyCode_F, KeyCode_Alt);
    Bind(custom_list_all_functions_all_buffers_lister, KeyCode_F, KeyCode_Alt, KeyCode_Shift);
    
    Bind(list_all_type_definitions_current_buffer_lister, KeyCode_D, KeyCode_Alt);
    Bind(interactive_search_type_definition, KeyCode_D, KeyCode_Alt, KeyCode_Shift);
    
    Bind(goto_line,                   KeyCode_G, KeyCode_Alt, KeyCode_Shift);
    Bind(jump_to_definition_at_cursor, KeyCode_G, KeyCode_Alt);
    
    Bind(replace_in_buffer, KeyCode_R, KeyCode_Alt);
    Bind(replace_in_range,            KeyCode_R, KeyCode_Alt, KeyCode_Shift);
    Bind(replace_in_all_buffers,   KeyCode_R, KeyCode_Alt, KeyCode_Control);
    
    Bind(query_replace,               KeyCode_Q, KeyCode_Alt);
    Bind(query_replace_in_all_buffers,   KeyCode_Q, KeyCode_Alt, KeyCode_Shift);
    
    // Misc
    
    //Bind(exit_4coder, KeyCode_Q, KeyCode_Alt);
    
    Bind(goto_next_jump,                KeyCode_N, KeyCode_Alt);
    Bind(goto_prev_jump,                KeyCode_N, KeyCode_Alt, KeyCode_Shift);
    
    Bind(write_todo,                 KeyCode_T, KeyCode_Alt);
    Bind(write_note,                 KeyCode_T, KeyCode_Alt, KeyCode_Shift);
    Bind(write_hack,                 KeyCode_T, KeyCode_Alt, KeyCode_Control);
    
    Bind(keyboard_macro_start_stop_recording , KeyCode_M, KeyCode_Alt);
    Bind(keyboard_macro_replay,           KeyCode_M, KeyCode_Alt, KeyCode_Shift);
    
    Bind(command_lister,                KeyCode_Comma, KeyCode_Alt);
    Bind(snippet_lister,              KeyCode_Period, KeyCode_Alt);
    
    Bind(save_all_dirty_and_build_in_build_panel,          KeyCode_Return, KeyCode_Alt);
    Bind(close_build_panel,             KeyCode_Return, KeyCode_Alt, KeyCode_Shift);
    
    Bind(comment_line_toggle,        KeyCode_ForwardSlash, KeyCode_Alt);
    Bind(comment_block, KeyCode_ForwardSlash, KeyCode_Shift, KeyCode_Alt);
    Bind(if0_off,                KeyCode_ForwardSlash, KeyCode_Alt, KeyCode_Control);
    
    Bind(delete_to_end_of_line_and_terminate, KeyCode_Quote, KeyCode_Alt);
    Bind(delete_from_beginning_of_line, KeyCode_Quote, KeyCode_Alt, KeyCode_Shift);
    
    // Scope Commands
    
    Bind(place_line_in_scope,               KeyCode_LeftBracket, KeyCode_Alt);
    Bind(place_line_in_scope_and_semicolon, KeyCode_RightBracket, KeyCode_Alt);
    
    Bind(place_line_before_scope_in_scope, KeyCode_LeftBracket, KeyCode_Alt, KeyCode_Shift);
    Bind(place_line_after_scope_in_scope, KeyCode_RightBracket, KeyCode_Alt, KeyCode_Shift);
    
    // NOTE(Leonardo): currently unused commands
#if 0
    //Bind(view_jump_list_with_lister_and_close_jump_list,  KeyCode_Period, KeyCode_Alt);
    Bind(place_in_scope,             KeyCode_LeftBracket, KeyCode_Alt, KeyCode_Shift);
    Bind(delete_current_scope_custom,       KeyCode_RightBracket, KeyCode_Control);
    
    Bind(change_to_build_panel,         KeyCode_Comma, KeyCode_Alt);
    Bind(query_replace_selection,     KeyCode_R, KeyCode_Alt, KeyCode_Shift);
    Bind(search_identifier,           KeyCode_T, KeyCode_Control);
    Bind(list_all_locations_of_identifier, KeyCode_T, KeyCode_Control, KeyCode_Shift);
    Bind(replace_in_range,       KeyCode_Quote, KeyCode_Alt);
    Bind(query_replace_identifier,    KeyCode_R, KeyCode_Alt, KeyCode_Control);
    Bind(replace_in_buffer,      KeyCode_Quote, KeyCode_Alt, KeyCode_Shift);
    Bind(replace_in_all_buffers, KeyCode_Quote, KeyCode_Alt, KeyCode_Shift, KeyCode_Control);
    Bind(word_complete_drop_down,    KeyCode_Tab, KeyCode_Shift);
    Bind(reopen,                      KeyCode_O, KeyCode_Control);
#endif
    
    //Bind(list_all_locations_of_type_definition, KeyCode_D, KeyCode_Control);
    
    //Misc Commands
    //Bind(toggle_theme_hot_reload,                 KeyCode_4, KeyCode_Alt);
    //Bind(pick_color, KeyCode_W, KeyCode_Alt);
    
    //Bind(kill_buffer,                 KeyCode_K, KeyCode_Control, KeyCode_Shift);
    
    //Bind(place_in_scope_for,             KeyCode_LeftBracket, KeyCode_Alt, KeyCode_Shift);
    //Bind(place_in_scope_if,             KeyCode_LeftBracket, KeyCode_Alt, KeyCode_Shift);
    //Bind(place_in_scope_else,             KeyCode_LeftBracket, KeyCode_Alt, KeyCode_Shift);
    //Bind(place_in_scope_if_else_if,             KeyCode_LeftBracket, KeyCode_Alt, KeyCode_Shift);
    //Bind(place_in_scope_if_else_else,             KeyCode_LeftBracket, KeyCode_Alt, KeyCode_Shift);
    //Bind(if0_off,                    KeyCode_I, KeyCode_Alt);
    //Bind(write_zero_struct,          KeyCode_0, KeyCode_Control);
    //Bind(open_long_braces_semicolon, KeyCode_LeftBracket, KeyCode_Control, KeyCode_Shift);
    
    //Bind(center_view,                 KeyCode_E, KeyCode_Control);
    //Bind(left_adjust_view,            KeyCode_E, KeyCode_Control, KeyCode_Shift);
}

function void
setup_custom_mappings(Mapping *mapping, i64 global_id, i64 file_id, i64 code_id){
    MappingScope();
    SelectMapping(mapping);
    
    SelectMap(global_id);
    SelectMap(file_id);
    ParentMap(global_id);
    SelectMap(code_id);
    ParentMap(file_id);
    
    setup_all_mappings(mapping, global_id);
    setup_all_mappings(mapping, file_id);
    setup_all_mappings(mapping, code_id);
}

void LoadThemeFromBuffer(Application_Links* app, Buffer_ID buffer)
{
    Scratch_Block scratch(app);
    String_Const_u8 file_name = push_buffer_file_name(app, scratch, buffer);
    if (file_name.size > 0){
        Arena *arena = &global_theme_arena;
        Color_Table color_table = make_color_table(app, arena);
        Config *config = theme_parse__buffer(app, scratch, buffer, arena, &color_table);
        String_Const_u8 error_text = config_stringize_errors(app, scratch, config);
        print_message(app, error_text);
        
        u64 problem_score = 0;
        if (color_table.count < defcolor_line_numbers_text){
            problem_score = defcolor_line_numbers_text - color_table.count;
        }
        for (i32 i = 0; i < color_table.count; i += 1){
            if (color_table.arrays[i].count == 0){
                problem_score += 1;
            }
        }
        
        if (error_text.size > 0 || problem_score >= 10){
            String_Const_u8 string = push_u8_stringf(scratch, "There appears to be a problem parsing %.*s; no theme change applied\n", string_expand(file_name));
            print_message(app, string);
        }
        else{
            String_Const_u8 name = string_front_of_path(file_name);
            if (string_match(string_postfix(name, 7), string_u8_litexpr(".4coder"))){
                name = string_chop(name, 7);
            }
            save_theme(color_table, name);
            
            Color_Table_Node *node = global_theme_list.last;
            if (node != 0 && string_match(node->name, name)){
                active_color_table = node->table;
            }
        }
    }
}

enum Seek_Dir
{
    Seek_Left,
    Seek_Right,
    Seek_Up,
    Seek_Down,
};

i64 seek_line_begin_pos(Application_Links* app, i64 pos)
{
    View_ID view = get_active_view(app, Access_ReadVisible);
    Buffer_Cursor cursor = view_compute_cursor(app, view, seek_pos(pos));
    Vec2_f32 p = view_relative_xy_of_pos(app, view, cursor.line, pos);
    p.x = 0.f;
    i64 result = view_pos_at_relative_xy(app, view, cursor.line, p);
    return result;
}

i64 seek_line_end_pos(Application_Links* app, i64 pos)
{
    View_ID view = get_active_view(app, Access_ReadVisible);
    Buffer_Cursor cursor = view_compute_cursor(app, view, seek_pos(pos));
    Vec2_f32 p = view_relative_xy_of_pos(app, view, cursor.line, pos);
    p.x = max_f32;
    i64 result = view_pos_at_relative_xy(app, view, cursor.line, p);
    return result;
}

i64 seek_upper_line_pos(Application_Links* app, i64 pos)
{
    View_ID view = get_active_view(app, Access_ReadVisible);
    Buffer_Cursor cursor = view_compute_cursor(app, view, seek_pos(pos));
    Rect_f32 r = view_padded_box_of_pos(app, view, cursor.line, pos);
    Vec2_f32 p = {};
    p.x = view_get_preferred_x(app, view);
    p.y = r.y0 - 1.0f;
    i64 result = view_pos_at_relative_xy(app, view, cursor.line, p);
    return result;
}

i64 seek_under_line_pos(Application_Links* app, i64 pos)
{
    View_ID view = get_active_view(app, Access_ReadVisible);
    Buffer_Cursor cursor = view_compute_cursor(app, view, seek_pos(pos));
    Rect_f32 r = view_padded_box_of_pos(app, view, cursor.line, pos);
    Vec2_f32 p = {};
    p.x = view_get_preferred_x(app, view);
    p.y = r.y1 + 1.0f;
    i64 result = view_pos_at_relative_xy(app, view, cursor.line, p);
    return result;
}

void
custom_layer_init(Application_Links *app){
    Thread_Context *tctx = get_thread_context(app);
    
    // NOTE(allen): setup for default framework
    default_framework_init(app);
    
    // NOTE(allen): default hooks and command maps
    set_all_default_hooks(app);
    mapping_init(tctx, &framework_mapping);
    String_ID global_map_id = vars_save_string_lit("keys_global");
    String_ID file_map_id = vars_save_string_lit("keys_file");
    String_ID code_map_id = vars_save_string_lit("keys_code");
    
#if OS_MAC
    setup_mac_mapping(&framework_mapping, global_map_id, file_map_id, code_map_id);
#else
    setup_default_mapping(&framework_mapping, global_map_id, file_map_id, code_map_id);
#endif
    
    setup_essential_mapping(&framework_mapping, global_map_id, file_map_id, code_map_id);
    setup_custom_mappings(&framework_mapping, global_map_id, file_map_id, code_map_id);
}

#endif //FCODER_DEFAULT_BINDINGS

// BOTTOM
