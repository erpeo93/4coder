/*
4coder_default_include.cpp - Default set of commands and setup used in 4coder.
*/

// TOP

#if !defined(FCODER_DEFAULT_INCLUDE_CPP)
#define FCODER_DEFAULT_INCLUDE_CPP

#include "4coder_base_types.h"
#include "4coder_version.h"
#include "4coder_events.h"
#include "4coder_default_colors.h"
#include "4coder_types.h"
#define DYNAMIC_LINK_API
#include "generated/custom_api.h"
#include "4coder_system_types.h"
#define DYNAMIC_LINK_API
#include "generated/system_api.h"
#include "generated/command_metadata.h"

#include "4coder_base_types.cpp"
#include "4coder_stringf.cpp"
#include "4coder_app_links_allocator.cpp"

#include "4coder_table.h"
#include "4coder_token.h"

#include "generated/lexer_cpp.h"
#include "4coder_string_match.h"
#include "4coder_helper.h"
#include "4coder_insertion.h"
#include "4coder_fancy.h"
#include "4coder_ui_helper.h"
#include "4coder_default_framework.h"
#include "4coder_config.h"
#include "4coder_auto_indent.h"
#include "4coder_search.h"
#include "4coder_build_commands.h"
#include "4coder_jumping.h"
#include "4coder_jump_sticky.h"
#include "4coder_jump_lister.h"
#include "4coder_project_commands.h"
#include "4coder_function_list.h"
#include "4coder_scope_commands.h"
#include "4coder_combined_write_commands.h"
#include "4coder_log_parser.h"

////////////////////////////////

#define DYNAMIC_LINK_API
#include "generated/custom_api.cpp"
#define DYNAMIC_LINK_API
#include "generated/system_api.cpp"
#include "4coder_system_helpers.cpp"
#include "4coder_events.cpp"
#include "4coder_custom.cpp"
#include "4coder_log.cpp"
#include "4coder_hash_functions.cpp"
#include "4coder_table.cpp"
#include "4coder_string_match.cpp"
#include "4coder_buffer_seek_constructors.cpp"

#include "4coder_token.cpp"
#include "generated/lexer_cpp.cpp"
#include "4coder_default_framework_variables.cpp"
#include "4coder_helper.cpp"
#include "4coder_fancy.cpp"
#include "4coder_ui_helper.cpp"
#include "4coder_font_helper.cpp"
#include "4coder_config.cpp"
#include "4coder_default_framework.cpp"
#include "4coder_insertion.cpp"
#include "4coder_base_commands.cpp"
#include "4coder_lists.cpp"
#include "4coder_auto_indent.cpp"
#include "4coder_search.cpp"
#include "4coder_jumping.cpp"
#include "4coder_jump_sticky.cpp"
#include "4coder_jump_lister.cpp"
#include "4coder_log_parser.cpp"
#include "4coder_clipboard.cpp"
#include "4coder_cli_command.cpp"
#include "4coder_build_commands.cpp"
#include "4coder_project_commands.cpp"
#include "4coder_function_list.cpp"
#include "4coder_scope_commands.cpp"
#include "4coder_combined_write_commands.cpp"
#include "4coder_miblo_numbers.cpp"

#include "4coder_default_hooks.cpp"
#include "4coder_remapping_commands.cpp"

#endif

// BOTTOM

