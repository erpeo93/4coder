#if !defined(FCODER_LEX_GEN_HAND_WRITTEN)
#define FCODER_LEX_GEN_HAND_WRITTEN

internal u64
lexeme_hash(u64 seed, u8 *ptr, u64 size){
    u64 result = 0;
    for (u64 i = 0; i < size; i += 1, ptr += 1){
        result ^= ((*ptr) ^ result*59) + seed;
    }
    return(result);
}

internal Lexeme_Table_Lookup
lexeme_table_lookup(u64 *hash_array, String_Const_u8 *key_array, 
                    Lexeme_Table_Value *value_array, i32 slot_count, u64 seed,
                    u8 *ptr, u64 size){
    Lexeme_Table_Lookup result = {};
    u64 hash = lexeme_hash(seed, ptr, size);
    u64 comparison_hash = hash | 1;
    i32 first_index = (hash % slot_count);
    i32 index = first_index;
    for (;;){
        if (hash_array[index] == comparison_hash){
            if (string_match(SCu8(ptr, size), key_array[index])){
                result.found_match = true;
                result.base_kind = value_array[index].base_kind;
                result.sub_kind = value_array[index].sub_kind;
                break;
            }
        }
        else if (hash_array[index] == 0){
            break;
        }
        index += 1;
        if (index == slot_count){
            index = 0;
        }
        if (index == first_index){
            break;
        }
    }
    return(result);
}

#endif
u64 odin_main_keys_hash_array[333] = {
0x0000000000000000,0x0000000000000000,0x550285d10fa07091,0x0000000000000000,
0x872043768fe2db27,0x0955ed340cadcd57,0x58dcce371d5d6351,0x1d99427da3460593,
0x0000000000000000,0xca5ce863e90d9a41,0x0000000000000000,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0x550285d1105eb995,0x550285d163f74ccf,
0x6177dd8ca1311f59,0x1d99427da37122c1,0xcbcc8041c00e2eb7,0x0000000000000000,
0x0000000000000000,0x58dcce3791184055,0x872043768fe2fbc1,0x550285d10c3acfd9,
0xb32ed3ab49f8c80d,0x0000000000000000,0x0000000000000000,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0x1d99427da3b92d4d,0x0000000000000000,
0xa9f035df26eda933,0x0000000000000000,0x0000000000000000,0x58dcce38e1e5e581,
0x550285d10c82acdf,0x0000000000000000,0x0000000000000000,0x872043768fe15663,
0xcf7e2f98c8bec0a1,0x35dfabb7bfc7294d,0xcf7e2f98c8becef3,0x0000000000000000,
0x550285d1055f0831,0x872043768fe16dd3,0x0000000000000000,0x0000000000000000,
0xcf7e2f98c8bec0a9,0x550285d11144e86d,0x1d99427da3758e93,0x872043768fe2a0d3,
0x872043768fe1d885,0x0000000000000000,0x0000000000000000,0x0000000000000000,
0x0000000000000000,0x872043768fe2a0db,0x550285d10fa04c65,0x0000000000000000,
0x0000000000000000,0x58dcce3557d6f593,0x550285d11de7fc95,0x550285d117c2cc65,
0x872043768fe2b1cb,0x0000000000000000,0x0000000000000000,0xcc686de7ddf8c80d,
0x0000000000000000,0x0000000000000000,0x0000000000000000,0x9441776538af717d,
0x369a590e8df82eb7,0x58dcce390468c0a3,0x94549631fb573a41,0x098234bb28ae4a1f,
0x0000000000000000,0x3572eb469f479c5b,0x550285d11df357e5,0xe49bb706c1b9c741,
0xa928738007d7cddf,0x0000000000000000,0x872043768fe24499,0x872043768fe1a0b3,
0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,
0x0000000000000000,0xa9f035dbad80541f,0x1d99427da3b723eb,0x0000000000000000,
0x0000000000000000,0x58dcce38e1e5e855,0x0000000000000000,0x0000000000000000,
0x550285d11e4ca3e5,0x94421d09aabc7751,0x0000000000000000,0x0000000000000000,
0x0000000000000000,0xcf7e2f98c8bec22b,0x95ab120d002813f1,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0xf745e47fbde831e3,0x9455a7ebac5b0e51,
0x1d99427da3b8cd57,0x872043768fe16b79,0x58dcce370121f835,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0x550285d11e4ca691,0x0000000000000000,
0x0000000000000000,0x1d99427da38d3dc9,0x0000000000000000,0x58dcce3239d3781f,
0x64da1cec3c1cb523,0x58dcce35558fdac1,0x327ddb3316b30767,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0x1d99427da3b84df1,0xaec9aed2f713ea1f,
0x0000000000000000,0xa9f035049514ff51,0x1d99427da382db09,0x58dcce376b7768af,
0xd3efebdd5085ceb7,0x0000000000000000,0x1d99427da3b5be61,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0x550285d10fabd2e1,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0x0000000000000000,0x872043768fe24623,
0x0000000000000000,0x0000000000000000,0x0000000000000000,0x872043768fe1bc45,
0x0000000000000000,0x0cf5086569f8c80d,0x872043768fe193f5,0x0000000000000000,
0x0000000000000000,0xa9f034d5bc6bd5f5,0x0000000000000000,0x0000000000000000,
0x9cbfd275d678c80d,0xa9f0351b66f7cddf,0x94437672b5e74a63,0x1d99427da3817fd7,
0x0955b8c76d750a5b,0x0000000000000000,0x0000000000000000,0x0000000000000000,
0x0000000000000000,0x1d99427da34277ad,0x1d99427da369a601,0x3655b16deeb4e911,
0x9d7b3b6fad784a1f,0x1d99427da3825f9d,0x0000000000000000,0xcf7e2f98c8becf73,
0xcf7e2f98c8bece27,0x0000000000000000,0x1d99427da368ff89,0x0000000000000000,
0xaaacde4886c6ac11,0x0000000000000000,0x0000000000000000,0x0000000000000000,
0x1d99427da349d72b,0x0000000000000000,0xa9f035ad41796f29,0x95aa11593408ae1b,
0x0000000000000000,0x1d99427da35081cf,0x0000000000000000,0x0000000000000000,
0x872043768fe1d673,0x0000000000000000,0x0000000000000000,0x550285d10fabcc95,
0xb8c12a6d914e83a1,0x0000000000000000,0x1d99427da369eda7,0x872043768fe2d6bb,
0x0000000000000000,0x1d99427da36c4d21,0x35a60fb38ea87515,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0x0000000000000000,0x3596b7555a532b67,
0x0000000000000000,0x0000000000000000,0x872043768fe24515,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,
0x0000000000000000,0xa9f035204aa22225,0x58dcce3239d2b55f,0x3c422094dfe59d4d,
0x0000000000000000,0x58dcce36691bc669,0x0955e18f45ab3b13,0xa9f035c50f8b54a7,
0x0000000000000000,0x0000000000000000,0x1c8d5ead6ce28a1f,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0x58dcce35453aff71,0x0000000000000000,
0x366f5d6134d45aa1,0xa9f0355cdabf7441,0x0000000000000000,0x0000000000000000,
0x263b340189f8c80d,0x872043768fe16bf5,0x0000000000000000,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0x0000000000000000,0x1d99427da3b5b315,
0x94447063d28b92df,0x0000000000000000,0x872043768fe2a2e1,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0x0000000000000000,0x1d99427da38472a3,
0x58dcce35a8a14ecb,0x319c840d0bd70eb7,0x872043768fe15735,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0x1d99427da3739fc7,0x3572eb469f463b3d,
0x872043768fe2ed13,0x872043768fe1ba19,0x872043768fe1bcb3,0x0000000000000000,
0x58dcce371d5af2a9,0x327ddb3316b3d579,0x0000000000000000,0x550285d11df35751,
0x0955eb78eebda989,0x0000000000000000,0x0000000000000000,0x0000000000000000,
0x0000000000000000,0x1d99427da384716d,0x550285d10e37dd01,0x1d99427da38dc075,
0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0x58dcce37d91fc79d,0x0000000000000000,
0xec75cddcdb2c5aa1,0x9c168fe9e0deea1f,0x0000000000000000,0x0000000000000000,
0x1d99427da384717f,0x0955d50def9b3da1,0x0000000000000000,0x85d3e5b74c146a41,
0x550285d10fb84665,0xaaacde4886c7955b,0x550285d117c14d93,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0x0000000000000000,0xa9f0352e9c5d1225,
0xa51a59379ca5b205,0x1d99427da350afcb,0x0000000000000000,0x0000000000000000,
0x872043768fe158b9,0x0000000000000000,0x0000000000000000,0x0000000000000000,
0x1d99427da3b46e27,0x94437672b5e74d95,0x58dcce3791187581,0x0000000000000000,
0x943187911f563d4d,0x94521a509c33bac1,0x1d99427da369a695,0x0000000000000000,
0x0000000000000000,0x0000000000000000,0x550285d11de40ae1,0x0000000000000000,
0x0000000000000000,0xa9f0354aac9b28d1,0x9447efc39c716a41,0x550285d10fb847d1,
0xa9f035dcf36eabcb,
};
u8 odin_main_keys_key_array_2[] = {0x75,0x31,0x36,0x62,0x65,};
u8 odin_main_keys_key_array_4[] = {0x6e,0x69,0x6c,};
u8 odin_main_keys_key_array_5[] = {0x64,0x69,0x73,0x74,0x69,0x6e,0x63,0x74,};
u8 odin_main_keys_key_array_6[] = {0x72,0x65,0x73,0x69,0x7a,0x65,};
u8 odin_main_keys_key_array_7[] = {0x70,0x72,0x6f,0x63,};
u8 odin_main_keys_key_array_9[] = {0x61,0x70,0x70,0x65,0x6e,0x64,0x5f,0x65,0x6c,0x65,0x6d,};
u8 odin_main_keys_key_array_18[] = {0x64,0x65,0x66,0x65,0x72,};
u8 odin_main_keys_key_array_19[] = {0x62,0x72,0x65,0x61,0x6b,};
u8 odin_main_keys_key_array_20[] = {0x71,0x75,0x61,0x74,0x65,0x72,0x6e,0x69,0x6f,0x6e,};
u8 odin_main_keys_key_array_21[] = {0x72,0x75,0x6e,0x65,};
u8 odin_main_keys_key_array_22[] = {0x61,0x70,0x70,0x65,0x6e,0x64,0x5f,0x73,0x6f,0x61,0x5f,0x65,0x6c,0x65,0x6d,0x73,};
u8 odin_main_keys_key_array_25[] = {0x75,0x31,0x32,0x38,0x6c,0x65,};
u8 odin_main_keys_key_array_26[] = {0x6c,0x65,0x6e,};
u8 odin_main_keys_key_array_27[] = {0x75,0x6e,0x69,0x6f,0x6e,};
u8 odin_main_keys_key_array_28[] = {0x64,0x65,0x6c,0x65,0x74,0x65,0x5f,0x64,0x79,0x6e,0x61,0x6d,0x69,0x63,0x5f,0x61,0x72,0x72,0x61,0x79,};
u8 odin_main_keys_key_array_38[] = {0x65,0x6c,0x73,0x65,};
u8 odin_main_keys_key_array_40[] = {0x63,0x6f,0x6d,0x70,0x6c,0x65,0x78,};
u8 odin_main_keys_key_array_43[] = {0x69,0x31,0x32,0x38,0x62,0x65,};
u8 odin_main_keys_key_array_44[] = {0x75,0x73,0x69,0x6e,0x67,};
u8 odin_main_keys_key_array_47[] = {0x69,0x36,0x34,};
u8 odin_main_keys_key_array_48[] = {0x69,0x6e,};
u8 odin_main_keys_key_array_49[] = {0x63,0x6f,0x70,0x79,0x5f,0x73,0x6c,0x69,0x63,0x65,};
u8 odin_main_keys_key_array_50[] = {0x64,0x6f,};
u8 odin_main_keys_key_array_52[] = {0x6e,0x6f,0x74,0x69,0x6e,};
u8 odin_main_keys_key_array_53[] = {0x66,0x36,0x34,};
u8 odin_main_keys_key_array_56[] = {0x69,0x66,};
u8 odin_main_keys_key_array_57[] = {0x66,0x61,0x6c,0x73,0x65,};
u8 odin_main_keys_key_array_58[] = {0x75,0x69,0x6e,0x74,};
u8 odin_main_keys_key_array_59[] = {0x6d,0x61,0x78,};
u8 odin_main_keys_key_array_60[] = {0x61,0x6e,0x79,};
u8 odin_main_keys_key_array_65[] = {0x6d,0x61,0x70,};
u8 odin_main_keys_key_array_66[] = {0x75,0x31,0x36,0x6c,0x65,};
u8 odin_main_keys_key_array_69[] = {0x69,0x6d,0x70,0x6f,0x72,0x74,};
u8 odin_main_keys_key_array_70[] = {0x69,0x36,0x34,0x6c,0x65,};
u8 odin_main_keys_key_array_71[] = {0x63,0x6c,0x65,0x61,0x72,};
u8 odin_main_keys_key_array_72[] = {0x70,0x6f,0x70,};
u8 odin_main_keys_key_array_75[] = {0x72,0x65,0x73,0x69,0x7a,0x65,0x5f,0x64,0x79,0x6e,0x61,0x6d,0x69,0x63,0x5f,0x61,0x72,0x72,0x61,0x79,};
u8 odin_main_keys_key_array_79[] = {0x74,0x72,0x61,0x6e,0x73,0x6d,0x75,0x74,0x65,};
u8 odin_main_keys_key_array_80[] = {0x65,0x78,0x63,0x6c,0x5f,0x65,0x6c,0x65,0x6d,0x73,};
u8 odin_main_keys_key_array_81[] = {0x61,0x70,0x70,0x65,0x6e,0x64,};
u8 odin_main_keys_key_array_82[] = {0x69,0x6e,0x63,0x6c,0x5f,0x65,0x6c,0x65,0x6d,};
u8 odin_main_keys_key_array_83[] = {0x64,0x65,0x6c,0x65,0x74,0x65,0x5f,0x73,0x74,0x72,0x69,0x6e,0x67,};
u8 odin_main_keys_key_array_85[] = {0x64,0x65,0x6c,0x65,0x74,0x65,0x5f,0x6d,0x61,0x70,};
u8 odin_main_keys_key_array_86[] = {0x69,0x33,0x32,0x6c,0x65,};
u8 odin_main_keys_key_array_87[] = {0x6d,0x61,0x6b,0x65,0x5f,0x64,0x79,0x6e,0x61,0x6d,0x69,0x63,0x5f,0x61,0x72,0x72,0x61,0x79,0x5f,0x6c,0x65,0x6e,};
u8 odin_main_keys_key_array_88[] = {0x65,0x78,0x63,0x6c,0x5f,0x62,0x69,0x74,0x5f,0x73,0x65,0x74,};
u8 odin_main_keys_key_array_90[] = {0x75,0x31,0x36,};
u8 odin_main_keys_key_array_91[] = {0x63,0x61,0x70,};
u8 odin_main_keys_key_array_97[] = {0x63,0x73,0x74,0x72,0x69,0x6e,0x67,};
u8 odin_main_keys_key_array_98[] = {0x6a,0x6d,0x61,0x67,};
u8 odin_main_keys_key_array_101[] = {0x69,0x31,0x32,0x38,0x6c,0x65,};
u8 odin_main_keys_key_array_104[] = {0x69,0x31,0x36,0x6c,0x65,};
u8 odin_main_keys_key_array_105[] = {0x6f,0x66,0x66,0x73,0x65,0x74,0x5f,0x6f,0x66,};
u8 odin_main_keys_key_array_109[] = {0x75,0x38,};
u8 odin_main_keys_key_array_110[] = {0x6e,0x65,0x77,0x5f,0x63,0x6c,0x6f,0x6e,0x65,};
u8 odin_main_keys_key_array_114[] = {0x66,0x61,0x6c,0x6c,0x74,0x68,0x72,0x6f,0x75,0x67,0x68,};
u8 odin_main_keys_key_array_115[] = {0x74,0x79,0x70,0x65,0x69,0x64,0x5f,0x6f,0x66,};
u8 odin_main_keys_key_array_116[] = {0x65,0x78,0x63,0x6c,};
u8 odin_main_keys_key_array_117[] = {0x66,0x31,0x36,};
u8 odin_main_keys_key_array_118[] = {0x72,0x61,0x77,0x70,0x74,0x72,};
u8 odin_main_keys_key_array_122[] = {0x69,0x31,0x36,0x62,0x65,};
u8 odin_main_keys_key_array_125[] = {0x63,0x6f,0x70,0x79,};
u8 odin_main_keys_key_array_127[] = {0x73,0x74,0x72,0x69,0x6e,0x67,};
u8 odin_main_keys_key_array_128[] = {0x6d,0x61,0x6b,0x65,0x5f,0x64,0x79,0x6e,0x61,0x6d,0x69,0x63,0x5f,0x61,0x72,0x72,0x61,0x79,0x5f,0x6c,0x65,0x6e,0x5f,0x63,0x61,0x70,};
u8 odin_main_keys_key_array_129[] = {0x69,0x6e,0x6c,0x69,0x6e,0x65,};
u8 odin_main_keys_key_array_130[] = {0x71,0x75,0x61,0x74,0x65,0x72,0x6e,0x69,0x6f,0x6e,0x31,0x32,0x38,};
u8 odin_main_keys_key_array_134[] = {0x65,0x6e,0x75,0x6d,};
u8 odin_main_keys_key_array_135[] = {0x64,0x65,0x6c,0x65,0x74,0x65,0x5f,0x63,0x73,0x74,0x72,0x69,0x6e,0x67,};
u8 odin_main_keys_key_array_137[] = {0x73,0x69,0x7a,0x65,0x5f,0x6f,0x66,};
u8 odin_main_keys_key_array_138[] = {0x66,0x72,0x65,0x65,};
u8 odin_main_keys_key_array_139[] = {0x74,0x79,0x70,0x65,0x69,0x64,};
u8 odin_main_keys_key_array_140[] = {0x61,0x70,0x70,0x65,0x6e,0x64,0x5f,0x65,0x6c,0x65,0x6d,0x73,};
u8 odin_main_keys_key_array_142[] = {0x69,0x38,0x62,0x65,};
u8 odin_main_keys_key_array_146[] = {0x75,0x36,0x34,0x62,0x65,};
u8 odin_main_keys_key_array_151[] = {0x75,0x36,0x34,};
u8 odin_main_keys_key_array_155[] = {0x62,0x33,0x32,};
u8 odin_main_keys_key_array_157[] = {0x72,0x65,0x73,0x65,0x72,0x76,0x65,0x5f,0x64,0x79,0x6e,0x61,0x6d,0x69,0x63,0x5f,0x61,0x72,0x72,0x61,0x79,};
u8 odin_main_keys_key_array_158[] = {0x66,0x6f,0x72,};
u8 odin_main_keys_key_array_161[] = {0x75,0x69,0x6e,0x74,0x70,0x74,0x72,};
u8 odin_main_keys_key_array_164[] = {0x63,0x6c,0x65,0x61,0x72,0x5f,0x64,0x79,0x6e,0x61,0x6d,0x69,0x63,0x5f,0x61,0x72,0x72,0x61,0x79,};
u8 odin_main_keys_key_array_165[] = {0x62,0x69,0x74,0x5f,0x73,0x65,0x74,};
u8 odin_main_keys_key_array_166[] = {0x63,0x6f,0x6d,0x70,0x6c,0x65,0x78,0x36,0x34,};
u8 odin_main_keys_key_array_167[] = {0x62,0x6f,0x6f,0x6c,};
u8 odin_main_keys_key_array_168[] = {0x6d,0x61,0x6b,0x65,0x5f,0x6d,0x61,0x70,};
u8 odin_main_keys_key_array_173[] = {0x6d,0x61,0x6b,0x65,};
u8 odin_main_keys_key_array_174[] = {0x75,0x38,0x62,0x65,};
u8 odin_main_keys_key_array_175[] = {0x61,0x70,0x70,0x65,0x6e,0x64,0x5f,0x73,0x6f,0x61,};
u8 odin_main_keys_key_array_176[] = {0x61,0x70,0x70,0x65,0x6e,0x64,0x5f,0x73,0x74,0x72,0x69,0x6e,0x67,};
u8 odin_main_keys_key_array_177[] = {0x62,0x79,0x74,0x65,};
u8 odin_main_keys_key_array_179[] = {0x69,0x38,};
u8 odin_main_keys_key_array_180[] = {0x62,0x38,};
u8 odin_main_keys_key_array_182[] = {0x74,0x72,0x75,0x65,};
u8 odin_main_keys_key_array_184[] = {0x72,0x65,0x73,0x65,0x72,0x76,0x65,0x5f,0x73,0x6f,0x61,};
u8 odin_main_keys_key_array_188[] = {0x6b,0x6d,0x61,0x67,};
u8 odin_main_keys_key_array_190[] = {0x66,0x6f,0x72,0x65,0x69,0x67,0x6e,};
u8 odin_main_keys_key_array_191[] = {0x62,0x69,0x74,0x5f,0x66,0x69,0x65,0x6c,0x64,};
u8 odin_main_keys_key_array_193[] = {0x69,0x6e,0x63,0x6c,};
u8 odin_main_keys_key_array_196[] = {0x61,0x62,0x73,};
u8 odin_main_keys_key_array_199[] = {0x75,0x36,0x34,0x6c,0x65,};
u8 odin_main_keys_key_array_200[] = {0x74,0x79,0x70,0x65,0x5f,0x69,0x6e,0x66,0x6f,0x5f,0x6f,0x66,};
u8 odin_main_keys_key_array_202[] = {0x75,0x31,0x32,0x38,};
u8 odin_main_keys_key_array_203[] = {0x6e,0x65,0x77,};
u8 odin_main_keys_key_array_205[] = {0x77,0x68,0x65,0x6e,};
u8 odin_main_keys_key_array_206[] = {0x65,0x78,0x70,0x61,0x6e,0x64,0x5f,0x74,0x6f,0x5f,0x74,0x75,0x70,0x6c,0x65,};
u8 odin_main_keys_key_array_211[] = {0x63,0x6f,0x6d,0x70,0x6c,0x65,0x78,0x31,0x32,0x38,};
u8 odin_main_keys_key_array_214[] = {0x75,0x33,0x32,};
u8 odin_main_keys_key_array_221[] = {0x73,0x77,0x69,0x7a,0x7a,0x6c,0x65,};
u8 odin_main_keys_key_array_222[] = {0x73,0x74,0x72,0x75,0x63,0x74,};
u8 odin_main_keys_key_array_223[] = {0x6d,0x61,0x6b,0x65,0x5f,0x73,0x6c,0x69,0x63,0x65,};
u8 odin_main_keys_key_array_225[] = {0x6f,0x70,0x61,0x71,0x75,0x65,};
u8 odin_main_keys_key_array_226[] = {0x66,0x72,0x65,0x65,0x5f,0x61,0x6c,0x6c,};
u8 odin_main_keys_key_array_227[] = {0x64,0x79,0x6e,0x61,0x6d,0x69,0x63,};
u8 odin_main_keys_key_array_230[] = {0x63,0x6f,0x70,0x79,0x5f,0x66,0x72,0x6f,0x6d,0x5f,0x73,0x74,0x72,0x69,0x6e,0x67,};
u8 odin_main_keys_key_array_234[] = {0x6e,0x6f,0x74,0x5f,0x69,0x6e,};
u8 odin_main_keys_key_array_236[] = {0x75,0x6e,0x6f,0x72,0x65,0x64,0x65,0x72,0x65,0x64,0x5f,0x72,0x65,0x6d,0x6f,0x76,0x65,};
u8 odin_main_keys_key_array_237[] = {0x72,0x65,0x73,0x65,0x72,0x76,0x65,};
u8 odin_main_keys_key_array_240[] = {0x6d,0x61,0x6b,0x65,0x5f,0x64,0x79,0x6e,0x61,0x6d,0x69,0x63,0x5f,0x61,0x72,0x72,0x61,0x79,};
u8 odin_main_keys_key_array_241[] = {0x66,0x33,0x32,};
u8 odin_main_keys_key_array_247[] = {0x69,0x38,0x6c,0x65,};
u8 odin_main_keys_key_array_248[] = {0x61,0x75,0x74,0x6f,0x5f,0x63,0x61,0x73,0x74,};
u8 odin_main_keys_key_array_250[] = {0x6d,0x69,0x6e,};
u8 odin_main_keys_key_array_255[] = {0x63,0x61,0x72,0x64,};
u8 odin_main_keys_key_array_256[] = {0x73,0x77,0x69,0x74,0x63,0x68,};
u8 odin_main_keys_key_array_257[] = {0x69,0x6e,0x63,0x6c,0x5f,0x65,0x6c,0x65,0x6d,0x73,};
u8 odin_main_keys_key_array_258[] = {0x69,0x33,0x32,};
u8 odin_main_keys_key_array_262[] = {0x72,0x65,0x61,0x6c,};
u8 odin_main_keys_key_array_263[] = {0x64,0x65,0x6c,0x65,0x74,0x65,0x5f,0x6b,0x65,0x79,};
u8 odin_main_keys_key_array_264[] = {0x69,0x6e,0x74,};
u8 odin_main_keys_key_array_265[] = {0x62,0x31,0x36,};
u8 odin_main_keys_key_array_266[] = {0x62,0x36,0x34,};
u8 odin_main_keys_key_array_268[] = {0x72,0x65,0x74,0x75,0x72,0x6e,};
u8 odin_main_keys_key_array_269[] = {0x71,0x75,0x61,0x74,0x65,0x72,0x6e,0x69,0x6f,0x6e,0x32,0x35,0x36,};
u8 odin_main_keys_key_array_271[] = {0x69,0x33,0x32,0x62,0x65,};
u8 odin_main_keys_key_array_272[] = {0x63,0x6f,0x6e,0x74,0x69,0x6e,0x75,0x65,};
u8 odin_main_keys_key_array_277[] = {0x63,0x61,0x73,0x65,};
u8 odin_main_keys_key_array_278[] = {0x77,0x68,0x65,0x72,0x65,};
u8 odin_main_keys_key_array_279[] = {0x63,0x6f,0x6e,0x6a,};
u8 odin_main_keys_key_array_290[] = {0x64,0x65,0x6c,0x65,0x74,0x65,};
u8 odin_main_keys_key_array_292[] = {0x6f,0x72,0x64,0x65,0x72,0x65,0x64,0x5f,0x72,0x65,0x6d,0x6f,0x76,0x65,};
u8 odin_main_keys_key_array_293[] = {0x61,0x70,0x70,0x65,0x6e,0x64,0x5f,0x65,0x6c,0x65,0x6d,0x5f,0x73,0x74,0x72,0x69,0x6e,0x67,};
u8 odin_main_keys_key_array_296[] = {0x63,0x61,0x73,0x74,};
u8 odin_main_keys_key_array_297[] = {0x61,0x6c,0x69,0x67,0x6e,0x5f,0x6f,0x66,};
u8 odin_main_keys_key_array_299[] = {0x61,0x70,0x70,0x65,0x6e,0x64,0x5f,0x73,0x6f,0x61,0x5f,0x65,0x6c,0x65,0x6d,};
u8 odin_main_keys_key_array_300[] = {0x75,0x33,0x32,0x6c,0x65,};
u8 odin_main_keys_key_array_301[] = {0x72,0x65,0x73,0x65,0x72,0x76,0x65,0x5f,0x6d,0x61,0x70,};
u8 odin_main_keys_key_array_302[] = {0x63,0x6c,0x61,0x6d,0x70,};
u8 odin_main_keys_key_array_307[] = {0x70,0x61,0x63,0x6b,0x61,0x67,0x65,};
u8 odin_main_keys_key_array_308[] = {0x69,0x6e,0x69,0x74,0x5f,0x67,0x6c,0x6f,0x62,0x61,0x6c,0x5f,0x74,0x65,0x6d,0x70,0x6f,0x72,0x61,0x72,0x79,0x5f,0x61,0x6c,0x6c,0x6f,0x63,0x61,0x74,0x6f,0x72,};
u8 odin_main_keys_key_array_309[] = {0x69,0x6d,0x61,0x67,};
u8 odin_main_keys_key_array_312[] = {0x69,0x31,0x36,};
u8 odin_main_keys_key_array_316[] = {0x69,0x31,0x32,0x38,};
u8 odin_main_keys_key_array_317[] = {0x63,0x6f,0x6d,0x70,0x6c,0x65,0x78,0x33,0x32,};
u8 odin_main_keys_key_array_318[] = {0x75,0x31,0x32,0x38,0x62,0x65,};
u8 odin_main_keys_key_array_320[] = {0x64,0x65,0x6c,0x65,0x74,0x65,0x5f,0x73,0x6c,0x69,0x63,0x65,};
u8 odin_main_keys_key_array_321[] = {0x6e,0x6f,0x5f,0x69,0x6e,0x6c,0x69,0x6e,0x65,};
u8 odin_main_keys_key_array_322[] = {0x75,0x38,0x6c,0x65,};
u8 odin_main_keys_key_array_326[] = {0x69,0x36,0x34,0x62,0x65,};
u8 odin_main_keys_key_array_329[] = {0x74,0x79,0x70,0x65,0x5f,0x6f,0x66,};
u8 odin_main_keys_key_array_330[] = {0x65,0x78,0x63,0x6c,0x5f,0x65,0x6c,0x65,0x6d,};
u8 odin_main_keys_key_array_331[] = {0x75,0x33,0x32,0x62,0x65,};
u8 odin_main_keys_key_array_332[] = {0x63,0x6f,0x6e,0x74,0x65,0x78,0x74,};
String_Const_u8 odin_main_keys_key_array[333] = {
{0, 0},
{0, 0},
{odin_main_keys_key_array_2, 5},
{0, 0},
{odin_main_keys_key_array_4, 3},
{odin_main_keys_key_array_5, 8},
{odin_main_keys_key_array_6, 6},
{odin_main_keys_key_array_7, 4},
{0, 0},
{odin_main_keys_key_array_9, 11},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_18, 5},
{odin_main_keys_key_array_19, 5},
{odin_main_keys_key_array_20, 10},
{odin_main_keys_key_array_21, 4},
{odin_main_keys_key_array_22, 16},
{0, 0},
{0, 0},
{odin_main_keys_key_array_25, 6},
{odin_main_keys_key_array_26, 3},
{odin_main_keys_key_array_27, 5},
{odin_main_keys_key_array_28, 20},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_38, 4},
{0, 0},
{odin_main_keys_key_array_40, 7},
{0, 0},
{0, 0},
{odin_main_keys_key_array_43, 6},
{odin_main_keys_key_array_44, 5},
{0, 0},
{0, 0},
{odin_main_keys_key_array_47, 3},
{odin_main_keys_key_array_48, 2},
{odin_main_keys_key_array_49, 10},
{odin_main_keys_key_array_50, 2},
{0, 0},
{odin_main_keys_key_array_52, 5},
{odin_main_keys_key_array_53, 3},
{0, 0},
{0, 0},
{odin_main_keys_key_array_56, 2},
{odin_main_keys_key_array_57, 5},
{odin_main_keys_key_array_58, 4},
{odin_main_keys_key_array_59, 3},
{odin_main_keys_key_array_60, 3},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_65, 3},
{odin_main_keys_key_array_66, 5},
{0, 0},
{0, 0},
{odin_main_keys_key_array_69, 6},
{odin_main_keys_key_array_70, 5},
{odin_main_keys_key_array_71, 5},
{odin_main_keys_key_array_72, 3},
{0, 0},
{0, 0},
{odin_main_keys_key_array_75, 20},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_79, 9},
{odin_main_keys_key_array_80, 10},
{odin_main_keys_key_array_81, 6},
{odin_main_keys_key_array_82, 9},
{odin_main_keys_key_array_83, 13},
{0, 0},
{odin_main_keys_key_array_85, 10},
{odin_main_keys_key_array_86, 5},
{odin_main_keys_key_array_87, 22},
{odin_main_keys_key_array_88, 12},
{0, 0},
{odin_main_keys_key_array_90, 3},
{odin_main_keys_key_array_91, 3},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_97, 7},
{odin_main_keys_key_array_98, 4},
{0, 0},
{0, 0},
{odin_main_keys_key_array_101, 6},
{0, 0},
{0, 0},
{odin_main_keys_key_array_104, 5},
{odin_main_keys_key_array_105, 9},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_109, 2},
{odin_main_keys_key_array_110, 9},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_114, 11},
{odin_main_keys_key_array_115, 9},
{odin_main_keys_key_array_116, 4},
{odin_main_keys_key_array_117, 3},
{odin_main_keys_key_array_118, 6},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_122, 5},
{0, 0},
{0, 0},
{odin_main_keys_key_array_125, 4},
{0, 0},
{odin_main_keys_key_array_127, 6},
{odin_main_keys_key_array_128, 26},
{odin_main_keys_key_array_129, 6},
{odin_main_keys_key_array_130, 13},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_134, 4},
{odin_main_keys_key_array_135, 14},
{0, 0},
{odin_main_keys_key_array_137, 7},
{odin_main_keys_key_array_138, 4},
{odin_main_keys_key_array_139, 6},
{odin_main_keys_key_array_140, 12},
{0, 0},
{odin_main_keys_key_array_142, 4},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_146, 5},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_151, 3},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_155, 3},
{0, 0},
{odin_main_keys_key_array_157, 21},
{odin_main_keys_key_array_158, 3},
{0, 0},
{0, 0},
{odin_main_keys_key_array_161, 7},
{0, 0},
{0, 0},
{odin_main_keys_key_array_164, 19},
{odin_main_keys_key_array_165, 7},
{odin_main_keys_key_array_166, 9},
{odin_main_keys_key_array_167, 4},
{odin_main_keys_key_array_168, 8},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_173, 4},
{odin_main_keys_key_array_174, 4},
{odin_main_keys_key_array_175, 10},
{odin_main_keys_key_array_176, 13},
{odin_main_keys_key_array_177, 4},
{0, 0},
{odin_main_keys_key_array_179, 2},
{odin_main_keys_key_array_180, 2},
{0, 0},
{odin_main_keys_key_array_182, 4},
{0, 0},
{odin_main_keys_key_array_184, 11},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_188, 4},
{0, 0},
{odin_main_keys_key_array_190, 7},
{odin_main_keys_key_array_191, 9},
{0, 0},
{odin_main_keys_key_array_193, 4},
{0, 0},
{0, 0},
{odin_main_keys_key_array_196, 3},
{0, 0},
{0, 0},
{odin_main_keys_key_array_199, 5},
{odin_main_keys_key_array_200, 12},
{0, 0},
{odin_main_keys_key_array_202, 4},
{odin_main_keys_key_array_203, 3},
{0, 0},
{odin_main_keys_key_array_205, 4},
{odin_main_keys_key_array_206, 15},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_211, 10},
{0, 0},
{0, 0},
{odin_main_keys_key_array_214, 3},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_221, 7},
{odin_main_keys_key_array_222, 6},
{odin_main_keys_key_array_223, 10},
{0, 0},
{odin_main_keys_key_array_225, 6},
{odin_main_keys_key_array_226, 8},
{odin_main_keys_key_array_227, 7},
{0, 0},
{0, 0},
{odin_main_keys_key_array_230, 16},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_234, 6},
{0, 0},
{odin_main_keys_key_array_236, 17},
{odin_main_keys_key_array_237, 7},
{0, 0},
{0, 0},
{odin_main_keys_key_array_240, 18},
{odin_main_keys_key_array_241, 3},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_247, 4},
{odin_main_keys_key_array_248, 9},
{0, 0},
{odin_main_keys_key_array_250, 3},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_255, 4},
{odin_main_keys_key_array_256, 6},
{odin_main_keys_key_array_257, 10},
{odin_main_keys_key_array_258, 3},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_262, 4},
{odin_main_keys_key_array_263, 10},
{odin_main_keys_key_array_264, 3},
{odin_main_keys_key_array_265, 3},
{odin_main_keys_key_array_266, 3},
{0, 0},
{odin_main_keys_key_array_268, 6},
{odin_main_keys_key_array_269, 13},
{0, 0},
{odin_main_keys_key_array_271, 5},
{odin_main_keys_key_array_272, 8},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_277, 4},
{odin_main_keys_key_array_278, 5},
{odin_main_keys_key_array_279, 4},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_290, 6},
{0, 0},
{odin_main_keys_key_array_292, 14},
{odin_main_keys_key_array_293, 18},
{0, 0},
{0, 0},
{odin_main_keys_key_array_296, 4},
{odin_main_keys_key_array_297, 8},
{0, 0},
{odin_main_keys_key_array_299, 15},
{odin_main_keys_key_array_300, 5},
{odin_main_keys_key_array_301, 11},
{odin_main_keys_key_array_302, 5},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_307, 7},
{odin_main_keys_key_array_308, 31},
{odin_main_keys_key_array_309, 4},
{0, 0},
{0, 0},
{odin_main_keys_key_array_312, 3},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_316, 4},
{odin_main_keys_key_array_317, 9},
{odin_main_keys_key_array_318, 6},
{0, 0},
{odin_main_keys_key_array_320, 12},
{odin_main_keys_key_array_321, 9},
{odin_main_keys_key_array_322, 4},
{0, 0},
{0, 0},
{0, 0},
{odin_main_keys_key_array_326, 5},
{0, 0},
{0, 0},
{odin_main_keys_key_array_329, 7},
{odin_main_keys_key_array_330, 9},
{odin_main_keys_key_array_331, 5},
{odin_main_keys_key_array_332, 7},
};
Lexeme_Table_Value odin_main_keys_value_array[333] = {
{0, 0},
{0, 0},
{4, TokenOdinKind_u16be},
{0, 0},
{8, TokenOdinKind_LiteralNil},
{4, TokenOdinKind_distinct},
{4, TokenOdinKind_resize},
{4, TokenOdinKind_proc},
{0, 0},
{4, TokenOdinKind_append_elem},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_defer},
{4, TokenOdinKind_break},
{4, TokenOdinKind_quaternion},
{4, TokenOdinKind_rune},
{4, TokenOdinKind_append_soa_elems},
{0, 0},
{0, 0},
{4, TokenOdinKind_u128le},
{4, TokenOdinKind_len},
{4, TokenOdinKind_union},
{4, TokenOdinKind_delete_dynamic_array},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_else},
{0, 0},
{4, TokenOdinKind_complex},
{0, 0},
{0, 0},
{4, TokenOdinKind_i128be},
{4, TokenOdinKind_using},
{0, 0},
{0, 0},
{4, TokenOdinKind_i64},
{4, TokenOdinKind_in},
{4, TokenOdinKind_copy_slice},
{4, TokenOdinKind_do},
{0, 0},
{4, TokenOdinKind_notin},
{4, TokenOdinKind_f64},
{0, 0},
{0, 0},
{4, TokenOdinKind_if},
{8, TokenOdinKind_LiteralFalse},
{4, TokenOdinKind_uint},
{4, TokenOdinKind_max},
{4, TokenOdinKind_any},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_map},
{4, TokenOdinKind_u16le},
{0, 0},
{0, 0},
{4, TokenOdinKind_import},
{4, TokenOdinKind_i64le},
{4, TokenOdinKind_clear},
{4, TokenOdinKind_pop},
{0, 0},
{0, 0},
{4, TokenOdinKind_resize_dynamic_array},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_transmute},
{4, TokenOdinKind_excl_elems},
{4, TokenOdinKind_append},
{4, TokenOdinKind_incl_elem},
{4, TokenOdinKind_delete_string},
{0, 0},
{4, TokenOdinKind_delete_map},
{4, TokenOdinKind_i32le},
{4, TokenOdinKind_make_dynamic_array_len},
{4, TokenOdinKind_excl_bit_set},
{0, 0},
{4, TokenOdinKind_u16},
{4, TokenOdinKind_cap},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_cstring},
{4, TokenOdinKind_jmag},
{0, 0},
{0, 0},
{4, TokenOdinKind_i128le},
{0, 0},
{0, 0},
{4, TokenOdinKind_i16le},
{4, TokenOdinKind_offset_of},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_u8},
{4, TokenOdinKind_new_clone},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_fallthrough},
{4, TokenOdinKind_typeid_of},
{4, TokenOdinKind_excl},
{4, TokenOdinKind_f16},
{4, TokenOdinKind_rawptr},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_i16be},
{0, 0},
{0, 0},
{4, TokenOdinKind_copy},
{0, 0},
{4, TokenOdinKind_string},
{4, TokenOdinKind_make_dynamic_array_len_cap},
{4, TokenOdinKind_inline},
{4, TokenOdinKind_quaternion128},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_enum},
{4, TokenOdinKind_delete_cstring},
{0, 0},
{4, TokenOdinKind_size_of},
{4, TokenOdinKind_free},
{4, TokenOdinKind_typeid},
{4, TokenOdinKind_append_elems},
{0, 0},
{4, TokenOdinKind_i8be},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_u64be},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_u64},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_b32},
{0, 0},
{4, TokenOdinKind_reserve_dynamic_array},
{4, TokenOdinKind_for},
{0, 0},
{0, 0},
{4, TokenOdinKind_uintptr},
{0, 0},
{0, 0},
{4, TokenOdinKind_clear_dynamic_array},
{4, TokenOdinKind_bit_set},
{4, TokenOdinKind_complex64},
{4, TokenOdinKind_bool},
{4, TokenOdinKind_make_map},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_make},
{4, TokenOdinKind_u8be},
{4, TokenOdinKind_append_soa},
{4, TokenOdinKind_append_string},
{4, TokenOdinKind_byte},
{0, 0},
{4, TokenOdinKind_i8},
{4, TokenOdinKind_b8},
{0, 0},
{8, TokenOdinKind_LiteralTrue},
{0, 0},
{4, TokenOdinKind_reserve_soa},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_kmag},
{0, 0},
{4, TokenOdinKind_foreign},
{4, TokenOdinKind_bit_field},
{0, 0},
{4, TokenOdinKind_incl},
{0, 0},
{0, 0},
{4, TokenOdinKind_abs},
{0, 0},
{0, 0},
{4, TokenOdinKind_u64le},
{4, TokenOdinKind_type_info_of},
{0, 0},
{4, TokenOdinKind_u128},
{4, TokenOdinKind_new},
{0, 0},
{4, TokenOdinKind_when},
{4, TokenOdinKind_expand_to_tuple},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_complex128},
{0, 0},
{0, 0},
{4, TokenOdinKind_u32},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_swizzle},
{4, TokenOdinKind_struct},
{4, TokenOdinKind_make_slice},
{0, 0},
{4, TokenOdinKind_opaque},
{4, TokenOdinKind_free_all},
{4, TokenOdinKind_dynamic},
{0, 0},
{0, 0},
{4, TokenOdinKind_copy_from_string},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_not_in},
{0, 0},
{4, TokenOdinKind_unoredered_remove},
{4, TokenOdinKind_reserve},
{0, 0},
{0, 0},
{4, TokenOdinKind_make_dynamic_array},
{4, TokenOdinKind_f32},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_i8le},
{4, TokenOdinKind_auto_cast},
{0, 0},
{4, TokenOdinKind_min},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_card},
{4, TokenOdinKind_switch},
{4, TokenOdinKind_incl_elems},
{4, TokenOdinKind_i32},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_real},
{4, TokenOdinKind_delete_key},
{4, TokenOdinKind_int},
{4, TokenOdinKind_b16},
{4, TokenOdinKind_b64},
{0, 0},
{4, TokenOdinKind_return},
{4, TokenOdinKind_quaternion256},
{0, 0},
{4, TokenOdinKind_i32be},
{4, TokenOdinKind_continue},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_case},
{4, TokenOdinKind_where},
{4, TokenOdinKind_conj},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_delete},
{0, 0},
{4, TokenOdinKind_ordered_remove},
{4, TokenOdinKind_append_elem_string},
{0, 0},
{0, 0},
{4, TokenOdinKind_cast},
{4, TokenOdinKind_align_of},
{0, 0},
{4, TokenOdinKind_append_soa_elem},
{4, TokenOdinKind_u32le},
{4, TokenOdinKind_reserve_map},
{4, TokenOdinKind_clamp},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_package},
{4, TokenOdinKind_init_global_temporary_allocator},
{4, TokenOdinKind_imag},
{0, 0},
{0, 0},
{4, TokenOdinKind_i16},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_i128},
{4, TokenOdinKind_complex32},
{4, TokenOdinKind_u128be},
{0, 0},
{4, TokenOdinKind_delete_slice},
{4, TokenOdinKind_no_inline},
{4, TokenOdinKind_u8le},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_i64be},
{0, 0},
{0, 0},
{4, TokenOdinKind_type_of},
{4, TokenOdinKind_excl_elem},
{4, TokenOdinKind_u32be},
{4, TokenOdinKind_context},
};
i32 odin_main_keys_slot_count = 333;
u64 odin_main_keys_seed = 0x764974b80365c843;
u64 odin_directives_hash_array[33] = {
0xe1c8ed6933f72427,0x0000000000000000,0x0000000000000000,0x2a536f2d4177a0b3,
0x0000000000000000,0x77e8148c555615a9,0x07592e05ff820e3b,0x2a536f2d7f90c8bd,
0xec7d4e7e8bfe177d,0x0000000000000000,0x0000000000000000,0x0000000000000000,
0xf739723db0d63497,0xca31c48ceba268bd,0x743ab7316968f433,0xec7d4febec7e7c31,
0x0000000000000000,0x645db2d85b0fcfb7,0xca31c48e467d4079,0x0000000000000000,
0x0000000000000000,0xe1c8da0bc5a6c0c3,0xe1c8e94c062c5f8d,0x0000000000000000,
0x77d6e099a3b5e817,0x0000000000000000,0x2a536f2d7f829313,0x2a536f2d7fbc6dc3,
0x0000000000000000,0x5c035e43a1ca0e3b,0x0000000000000000,0xca31c48e907c9033,
0x0000000000000000,
};
u8 odin_directives_key_array_0[] = {0x6e,0x6f,0x5f,0x61,0x6c,0x69,0x61,0x73,};
u8 odin_directives_key_array_3[] = {0x74,0x79,0x70,0x65,};
u8 odin_directives_key_array_5[] = {0x6c,0x6f,0x63,0x61,0x74,0x69,0x6f,0x6e,0x73,};
u8 odin_directives_key_array_6[] = {0x6e,0x6f,0x5f,0x62,0x6f,0x75,0x6e,0x64,0x73,0x5f,0x63,0x68,0x65,0x63,0x6b,};
u8 odin_directives_key_array_7[] = {0x6c,0x6f,0x61,0x64,};
u8 odin_directives_key_array_8[] = {0x70,0x61,0x72,0x74,0x69,0x61,0x6c,};
u8 odin_directives_key_array_12[] = {0x63,0x61,0x6c,0x6c,0x65,0x72,0x5f,0x6c,0x6f,0x63,0x61,0x74,0x69,0x6f,0x6e,};
u8 odin_directives_key_array_13[] = {0x70,0x61,0x63,0x6b,0x65,0x64,};
u8 odin_directives_key_array_14[] = {0x70,0x72,0x6f,0x63,0x65,0x64,0x75,0x72,0x65,};
u8 odin_directives_key_array_15[] = {0x64,0x65,0x66,0x69,0x6e,0x65,0x64,};
u8 odin_directives_key_array_17[] = {0x61,0x6c,0x69,0x67,0x6e,};
u8 odin_directives_key_array_18[] = {0x6e,0x6f,0x5f,0x6e,0x69,0x6c,};
u8 odin_directives_key_array_21[] = {0x63,0x6f,0x6d,0x70,0x6c,0x65,0x74,0x65,};
u8 odin_directives_key_array_22[] = {0x63,0x5f,0x76,0x61,0x72,0x61,0x72,0x67,};
u8 odin_directives_key_array_24[] = {0x72,0x61,0x77,0x5f,0x75,0x6e,0x69,0x6f,0x6e,};
u8 odin_directives_key_array_26[] = {0x66,0x69,0x6c,0x65,};
u8 odin_directives_key_array_27[] = {0x6c,0x69,0x6e,0x65,};
u8 odin_directives_key_array_29[] = {0x62,0x6f,0x75,0x6e,0x64,0x73,0x5f,0x63,0x68,0x65,0x63,0x6b,};
u8 odin_directives_key_array_31[] = {0x61,0x73,0x73,0x65,0x72,0x74,};
String_Const_u8 odin_directives_key_array[33] = {
{odin_directives_key_array_0, 8},
{0, 0},
{0, 0},
{odin_directives_key_array_3, 4},
{0, 0},
{odin_directives_key_array_5, 9},
{odin_directives_key_array_6, 15},
{odin_directives_key_array_7, 4},
{odin_directives_key_array_8, 7},
{0, 0},
{0, 0},
{0, 0},
{odin_directives_key_array_12, 15},
{odin_directives_key_array_13, 6},
{odin_directives_key_array_14, 9},
{odin_directives_key_array_15, 7},
{0, 0},
{odin_directives_key_array_17, 5},
{odin_directives_key_array_18, 6},
{0, 0},
{0, 0},
{odin_directives_key_array_21, 8},
{odin_directives_key_array_22, 8},
{0, 0},
{odin_directives_key_array_24, 9},
{0, 0},
{odin_directives_key_array_26, 4},
{odin_directives_key_array_27, 4},
{0, 0},
{odin_directives_key_array_29, 12},
{0, 0},
{odin_directives_key_array_31, 6},
{0, 0},
};
Lexeme_Table_Value odin_directives_value_array[33] = {
{4, TokenOdinKind_no_alias},
{0, 0},
{0, 0},
{4, TokenOdinKind_type},
{0, 0},
{4, TokenOdinKind_locations},
{4, TokenOdinKind_no_bounds_check},
{4, TokenOdinKind_load},
{4, TokenOdinKind_partial},
{0, 0},
{0, 0},
{0, 0},
{4, TokenOdinKind_caller_location},
{4, TokenOdinKind_packed},
{4, TokenOdinKind_procedure},
{4, TokenOdinKind_defined},
{0, 0},
{4, TokenOdinKind_align},
{4, TokenOdinKind_no_nil},
{0, 0},
{0, 0},
{4, TokenOdinKind_complete},
{4, TokenOdinKind_c_vararg},
{0, 0},
{4, TokenOdinKind_raw_union},
{0, 0},
{4, TokenOdinKind_file},
{4, TokenOdinKind_line},
{0, 0},
{4, TokenOdinKind_bounds_check},
{0, 0},
{4, TokenOdinKind_assert},
{0, 0},
};
i32 odin_directives_slot_count = 33;
u64 odin_directives_seed = 0x8cd43e78b879825e;
u64 odin_attributes_hash_array[21] = {
0x0000000000000000,0x67a25fc87cd6ab79,0x0000000000000000,0x4391ffd7a544cfc1,
0x7df5536f20f3787b,0x0000000000000000,0x49cabc3b0846527d,0xd85a3487e9be0bb5,
0x0000000000000000,0x52c4ede8006450af,0xd6b94740380ce861,0x0000000000000000,
0x0000000000000000,0x49cabc0e63a01e91,0xd85a348293df3d71,0x0000000000000000,
0xf738dc64daabbd0f,0xbf838fd391f67a0b,0x0000000000000000,0xf090de02eed1b883,
0x5c3b1b2018c8edc3,
};
u8 odin_attributes_key_array_1[] = {0x64,0x65,0x66,0x65,0x72,0x72,0x65,0x64,0x5f,0x69,0x6e,};
u8 odin_attributes_key_array_3[] = {0x64,0x65,0x66,0x61,0x75,0x6c,0x74,0x5f,0x63,0x61,0x6c,0x6c,0x69,0x6e,0x67,0x5f,0x63,0x6f,0x6e,0x76,0x65,0x6e,0x74,0x69,0x6f,0x6e,};
u8 odin_attributes_key_array_4[] = {0x74,0x68,0x72,0x65,0x61,0x64,0x5f,0x6c,0x6f,0x63,0x61,0x6c,};
u8 odin_attributes_key_array_6[] = {0x70,0x72,0x69,0x76,0x61,0x74,0x65,};
u8 odin_attributes_key_array_7[] = {0x73,0x74,0x61,0x74,0x69,0x63,};
u8 odin_attributes_key_array_9[] = {0x6c,0x69,0x6e,0x6b,0x5f,0x70,0x72,0x65,0x66,0x69,0x78,};
u8 odin_attributes_key_array_10[] = {0x64,0x65,0x66,0x65,0x72,0x72,0x65,0x64,0x5f,0x6e,0x6f,0x6e,0x65,};
u8 odin_attributes_key_array_13[] = {0x62,0x75,0x69,0x6c,0x74,0x69,0x6e,};
u8 odin_attributes_key_array_14[] = {0x65,0x78,0x70,0x6f,0x72,0x74,};
u8 odin_attributes_key_array_16[] = {0x72,0x65,0x71,0x75,0x69,0x72,0x65,0x5f,0x72,0x65,0x73,0x75,0x6c,0x74,0x73,};
u8 odin_attributes_key_array_17[] = {0x64,0x65,0x70,0x72,0x65,0x63,0x61,0x74,0x65,0x64,};
u8 odin_attributes_key_array_19[] = {0x64,0x65,0x66,0x65,0x72,0x72,0x65,0x64,0x5f,0x6f,0x75,0x74,};
u8 odin_attributes_key_array_20[] = {0x6c,0x69,0x6e,0x6b,0x5f,0x6e,0x61,0x6d,0x65,};
String_Const_u8 odin_attributes_key_array[21] = {
{0, 0},
{odin_attributes_key_array_1, 11},
{0, 0},
{odin_attributes_key_array_3, 26},
{odin_attributes_key_array_4, 12},
{0, 0},
{odin_attributes_key_array_6, 7},
{odin_attributes_key_array_7, 6},
{0, 0},
{odin_attributes_key_array_9, 11},
{odin_attributes_key_array_10, 13},
{0, 0},
{0, 0},
{odin_attributes_key_array_13, 7},
{odin_attributes_key_array_14, 6},
{0, 0},
{odin_attributes_key_array_16, 15},
{odin_attributes_key_array_17, 10},
{0, 0},
{odin_attributes_key_array_19, 12},
{odin_attributes_key_array_20, 9},
};
Lexeme_Table_Value odin_attributes_value_array[21] = {
{0, 0},
{4, TokenOdinKind_deferred_in},
{0, 0},
{4, TokenOdinKind_default_calling_convention},
{4, TokenOdinKind_thread_local},
{0, 0},
{4, TokenOdinKind_private},
{4, TokenOdinKind_static},
{0, 0},
{4, TokenOdinKind_link_prefix},
{4, TokenOdinKind_deferred_none},
{0, 0},
{0, 0},
{4, TokenOdinKind_builtin},
{4, TokenOdinKind_export},
{0, 0},
{4, TokenOdinKind_require_results},
{4, TokenOdinKind_deprecated},
{0, 0},
{4, TokenOdinKind_deferred_out},
{4, TokenOdinKind_link_name},
};
i32 odin_attributes_slot_count = 21;
u64 odin_attributes_seed = 0xb4c66e95cc8c9e4c;
struct Lex_State_Odin{
u32 flags_ZF0;
u32 flags_KF0;
u16 flags_KB0;
u8 *base;
u8 *delim_first;
u8 *delim_one_past_last;
u8 *emit_ptr;
u8 *ptr;
u8 *opl_ptr;
};
internal void
lex_full_input_odin_init(Lex_State_Odin *state_ptr, String_Const_u8 input){
state_ptr->flags_ZF0 = 0;
state_ptr->flags_KF0 = 0;
state_ptr->flags_KB0 = 0;
state_ptr->base = input.str;
state_ptr->delim_first = input.str;
state_ptr->delim_one_past_last = input.str;
state_ptr->emit_ptr = input.str;
state_ptr->ptr = input.str;
state_ptr->opl_ptr = input.str + input.size;
}
internal b32
lex_full_input_odin_breaks(Arena *arena, Token_List *list, Lex_State_Odin *state_ptr, u64 max){
b32 result = false;
u64 emit_counter = 0;
Lex_State_Odin state;
block_copy_struct(&state, state_ptr);
{
state_label_1: // root
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_EOF;
token.kind = 0;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
result = true;
goto end;
}
}
switch (*state.ptr){
case 0x00:case 0x01:case 0x02:case 0x03:case 0x04:case 0x05:case 0x06:
case 0x07:case 0x08:case 0x0e:case 0x0f:case 0x10:case 0x11:case 0x12:
case 0x13:case 0x14:case 0x15:case 0x16:case 0x17:case 0x18:case 0x19:
case 0x1a:case 0x1b:case 0x1c:case 0x1d:case 0x1e:case 0x1f:case 0x5c:
case 0x7f:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_LexError;
token.kind = 2;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x09:case 0x0a:case 0x0b:case 0x0c:case 0x0d:case 0x20:
{
state.ptr += 1;
goto state_label_3; // whitespace
}break;
case 0x21:
{
state.ptr += 1;
goto state_label_31; // op stage
}break;
case 0x22:
{
state.ptr += 1;
goto state_label_19; // string
}break;
case 0x23:
{
state.ptr += 1;
state.delim_first = state.ptr;
goto state_label_26; // directive
}break;
default:
{
state.ptr += 1;
goto state_label_2; // identifier
}break;
case 0x25:
{
state.ptr += 1;
goto state_label_37; // op stage
}break;
case 0x26:
{
state.ptr += 1;
goto state_label_32; // op stage
}break;
case 0x27:
{
state.ptr += 1;
state.flags_ZF0 |= 0x10;
goto state_label_19; // string
}break;
case 0x28:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_ParenOp;
token.kind = 13;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x29:
{
if ((HasFlag(state.flags_KB0, 0x1))){
state.ptr += 1;
state.flags_KB0 &= ~(0x1);
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_AttributeClose;
token.kind = 14;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_ParenCl;
token.kind = 14;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x2a:
{
state.ptr += 1;
goto state_label_36; // op stage
}break;
case 0x2b:
{
state.ptr += 1;
goto state_label_34; // op stage
}break;
case 0x2c:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_Comma;
token.kind = 15;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x2d:
{
state.ptr += 1;
goto state_label_35; // op stage
}break;
case 0x2e:
{
state.ptr += 1;
goto state_label_4; // operator_or_fnumber_dot
}break;
case 0x2f:
{
state.ptr += 1;
goto state_label_5; // operator_or_comment_slash
}break;
case 0x30:
{
state.ptr += 1;
goto state_label_7; // znumber
}break;
case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:case 0x37:
case 0x38:case 0x39:
{
state.ptr += 1;
goto state_label_6; // number
}break;
case 0x3a:
{
state.ptr += 1;
goto state_label_27; // op stage
}break;
case 0x3b:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_Semicolon;
token.kind = 15;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x3c:
{
state.ptr += 1;
goto state_label_28; // op stage
}break;
case 0x3d:
{
state.ptr += 1;
goto state_label_30; // op stage
}break;
case 0x3e:
{
state.ptr += 1;
goto state_label_29; // op stage
}break;
case 0x3f:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_Ternary;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x40:
{
state.ptr += 1;
state.delim_first = state.ptr;
goto state_label_24; // attribute_first
}break;
case 0x5b:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_BrackOp;
token.kind = 13;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x5d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_BrackCl;
token.kind = 14;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x5e:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_Carrot;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x60:
{
state.ptr += 1;
state.flags_ZF0 |= 0x20;
goto state_label_19; // string
}break;
case 0x7b:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_BraceOp;
token.kind = 11;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x7c:
{
state.ptr += 1;
goto state_label_33; // op stage
}break;
case 0x7d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_BraceCl;
token.kind = 12;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x7e:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_Tilde;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_2: // identifier
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
if (HasFlag(state.flags_KB0, 0x1)){
Lexeme_Table_Lookup lookup = lexeme_table_lookup(odin_attributes_hash_array, odin_attributes_key_array, odin_attributes_value_array, odin_attributes_slot_count, odin_attributes_seed, state.emit_ptr, token.size);
if (lookup.found_match){
token.kind = lookup.base_kind;
token.sub_kind = lookup.sub_kind;
break;
}
}
Lexeme_Table_Lookup lookup = lexeme_table_lookup(odin_main_keys_hash_array, odin_main_keys_key_array, odin_main_keys_value_array, odin_main_keys_slot_count, odin_main_keys_seed, state.emit_ptr, token.size);
if (lookup.found_match){
token.kind = lookup.base_kind;
token.sub_kind = lookup.sub_kind;
break;
}
token.sub_kind = TokenOdinKind_Identifier;
token.kind = 6;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
case 0x00:case 0x01:case 0x02:case 0x03:case 0x04:case 0x05:case 0x06:
case 0x07:case 0x08:case 0x09:case 0x0a:case 0x0b:case 0x0c:case 0x0d:
case 0x0e:case 0x0f:case 0x10:case 0x11:case 0x12:case 0x13:case 0x14:
case 0x15:case 0x16:case 0x17:case 0x18:case 0x19:case 0x1a:case 0x1b:
case 0x1c:case 0x1d:case 0x1e:case 0x1f:case 0x20:case 0x21:case 0x22:
case 0x23:case 0x25:case 0x26:case 0x27:case 0x28:case 0x29:case 0x2a:
case 0x2b:case 0x2c:case 0x2d:case 0x2e:case 0x2f:case 0x3a:case 0x3b:
case 0x3c:case 0x3d:case 0x3e:case 0x3f:case 0x40:case 0x5b:case 0x5c:
case 0x5d:case 0x5e:case 0x60:case 0x7b:case 0x7c:case 0x7d:case 0x7e:
case 0x7f:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
if (HasFlag(state.flags_KB0, 0x1)){
Lexeme_Table_Lookup lookup = lexeme_table_lookup(odin_attributes_hash_array, odin_attributes_key_array, odin_attributes_value_array, odin_attributes_slot_count, odin_attributes_seed, state.emit_ptr, token.size);
if (lookup.found_match){
token.kind = lookup.base_kind;
token.sub_kind = lookup.sub_kind;
break;
}
}
Lexeme_Table_Lookup lookup = lexeme_table_lookup(odin_main_keys_hash_array, odin_main_keys_key_array, odin_main_keys_value_array, odin_main_keys_slot_count, odin_main_keys_seed, state.emit_ptr, token.size);
if (lookup.found_match){
token.kind = lookup.base_kind;
token.sub_kind = lookup.sub_kind;
break;
}
token.sub_kind = TokenOdinKind_Identifier;
token.kind = 6;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
default:
{
state.ptr += 1;
goto state_label_2; // identifier
}break;
}
}
{
state_label_3: // whitespace
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_Whitespace;
token.kind = 1;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_Whitespace;
token.kind = 1;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x09:case 0x0a:case 0x0b:case 0x0c:case 0x0d:case 0x20:
{
state.ptr += 1;
goto state_label_3; // whitespace
}break;
}
}
{
state_label_4: // operator_or_fnumber_dot
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_Dot;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_Dot;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x2e:
{
state.ptr += 1;
goto state_label_40; // op stage
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:
{
state.ptr += 1;
goto state_label_8; // fnumber_decimal
}break;
}
}
{
state_label_5: // operator_or_comment_slash
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_Div;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_Div;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x2a:
{
state.ptr += 1;
goto state_label_21; // comment_block
}break;
case 0x2f:
{
state.ptr += 1;
goto state_label_23; // comment_line
}break;
case 0x3d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_DivEq;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_6: // number
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_LiteralInteger;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_LiteralInteger;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x2e:
{
state.ptr += 1;
goto state_label_8; // fnumber_decimal
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:
{
state.ptr += 1;
goto state_label_6; // number
}break;
case 0x45:case 0x65:
{
state.ptr += 1;
goto state_label_9; // fnumber_exponent
}break;
}
}
{
state_label_7: // znumber
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_LiteralInteger;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_LiteralInteger;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x2e:
{
state.ptr += 1;
goto state_label_8; // fnumber_decimal
}break;
case 0x42:case 0x62:
{
state.ptr += 1;
state.flags_ZF0 |= 0x8;
goto state_label_14; // number_bin_first
}break;
case 0x45:case 0x65:
{
state.ptr += 1;
goto state_label_9; // fnumber_exponent
}break;
case 0x4f:case 0x6f:
{
state.ptr += 1;
state.flags_ZF0 |= 0x2;
goto state_label_16; // number_oct
}break;
case 0x58:case 0x78:
{
state.ptr += 1;
state.flags_ZF0 |= 0x1;
goto state_label_12; // number_hex_first
}break;
case 0x5a:case 0x7a:
{
state.ptr += 1;
state.flags_ZF0 |= 0x4;
goto state_label_13; // number_doz_first
}break;
}
}
{
state_label_8: // fnumber_decimal
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_LiteralFloat;
token.kind = 9;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_LiteralFloat;
token.kind = 9;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:
{
state.ptr += 1;
goto state_label_8; // fnumber_decimal
}break;
case 0x45:case 0x65:
{
state.ptr += 1;
goto state_label_9; // fnumber_exponent
}break;
}
}
{
state_label_9: // fnumber_exponent
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_LiteralFloat;
token.kind = 9;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_LiteralFloat;
token.kind = 9;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x2b:case 0x2d:
{
state.ptr += 1;
goto state_label_10; // fnumber_exponent_sign
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:
{
state.ptr += 1;
goto state_label_11; // fnumber_exponent_digits
}break;
}
}
{
state_label_10: // fnumber_exponent_sign
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_LiteralFloat;
token.kind = 9;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_LiteralFloat;
token.kind = 9;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:
{
state.ptr += 1;
goto state_label_11; // fnumber_exponent_digits
}break;
}
}
{
state_label_11: // fnumber_exponent_digits
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_LiteralFloat;
token.kind = 9;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_LiteralFloat;
token.kind = 9;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:
{
state.ptr += 1;
goto state_label_11; // fnumber_exponent_digits
}break;
}
}
{
state_label_12: // number_hex_first
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_LexError;
token.kind = 2;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_LexError;
token.kind = 2;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
case 0x66:
{
state.ptr += 1;
goto state_label_15; // number_hex
}break;
}
}
{
state_label_13: // number_doz_first
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_LexError;
token.kind = 2;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_LexError;
token.kind = 2;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x61:case 0x62:
{
state.ptr += 1;
goto state_label_17; // number_doz
}break;
}
}
{
state_label_14: // number_bin_first
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_LexError;
token.kind = 2;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_LexError;
token.kind = 2;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x30:case 0x31:
{
state.ptr += 1;
goto state_label_18; // number_bin
}break;
case 0x5f:
{
state.ptr += 1;
state.flags_ZF0 |= 0x8;
goto state_label_14; // number_bin_first
}break;
}
}
{
state_label_15: // number_hex
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_LiteralIntegerHex;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_LiteralIntegerHex;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
case 0x66:
{
state.ptr += 1;
goto state_label_15; // number_hex
}break;
}
}
{
state_label_16: // number_oct
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_LiteralIntegerOct;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_LiteralIntegerOct;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:
{
state.ptr += 1;
state.flags_ZF0 |= 0x2;
goto state_label_16; // number_oct
}break;
}
}
{
state_label_17: // number_doz
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_LiteralIntegerDoz;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_LiteralIntegerDoz;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
case 0x66:
{
state.ptr += 1;
goto state_label_17; // number_doz
}break;
}
}
{
state_label_18: // number_bin
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_LiteralIntegerBin;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_LiteralIntegerBin;
token.kind = 8;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x30:case 0x31:case 0x5f:
{
state.ptr += 1;
goto state_label_18; // number_bin
}break;
}
}
{
state_label_19: // string
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_LexError;
token.kind = 2;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
state.ptr += 1;
goto state_label_19; // string
}break;
case 0x0a:
{
if ((!HasFlag(state.flags_ZF0, 0x20))){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_LexError;
token.kind = 2;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}
state.ptr += 1;
goto state_label_19; // string
}break;
case 0x22:
{
if ((!HasFlag(state.flags_ZF0, 0x10))){
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_LiteralString;
token.kind = 10;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}
state.ptr += 1;
goto state_label_19; // string
}break;
case 0x27:
{
if ((HasFlag(state.flags_ZF0, 0x10))){
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_LiteralCharacter;
token.kind = 10;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}
if ((!HasFlag(state.flags_ZF0, 0x20) && !HasFlag(state.flags_ZF0, 0x10))){
state.ptr += 1;
goto state_label_19; // string
}
state.ptr += 1;
goto state_label_19; // string
}break;
case 0x5c:
{
if ((!HasFlag(state.flags_ZF0, 0x20))){
state.ptr += 1;
goto state_label_20; // string_esc
}
state.ptr += 1;
goto state_label_19; // string
}break;
case 0x60:
{
if ((HasFlag(state.flags_ZF0, 0x20))){
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_LiteralStringRaw;
token.kind = 10;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}
state.ptr += 1;
goto state_label_19; // string
}break;
}
}
{
state_label_20: // string_esc
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_LexError;
token.kind = 2;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_EOF;
token.kind = 0;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
result = true;
goto end;
}
        }
        
        state.ptr += 1;
        goto state_label_19; // string
}
{
state_label_21: // comment_block
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_BlockComment;
token.kind = 3;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_EOF;
token.kind = 0;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
result = true;
goto end;
}
}
switch (*state.ptr){
default:
{
state.ptr += 1;
goto state_label_21; // comment_block
}break;
case 0x2a:
{
state.ptr += 1;
goto state_label_22; // comment_block_try_close
}break;
}
}
{
state_label_22: // comment_block_try_close
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_BlockComment;
token.kind = 3;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_EOF;
token.kind = 0;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
result = true;
goto end;
}
}
switch (*state.ptr){
default:
{
state.ptr += 1;
goto state_label_21; // comment_block
}break;
case 0x2a:
{
state.ptr += 1;
goto state_label_22; // comment_block_try_close
}break;
case 0x2f:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_BlockComment;
token.kind = 3;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_23: // comment_line
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_LineComment;
token.kind = 3;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
state.ptr += 1;
goto state_label_23; // comment_line
}break;
case 0x0a:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_LineComment;
token.kind = 3;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_24: // attribute_first
if (state.ptr == state.opl_ptr){
if ((true)){
goto state_label_25; // attribute
}
}
switch (*state.ptr){
default:
{
goto state_label_25; // attribute
}break;
case 0x28:
{
state.ptr += 1;
state.flags_KB0 |= 0x1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_AttributeOpen;
token.kind = 13;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_25: // attribute
if (state.ptr == state.opl_ptr){
if ((true)){
state.delim_one_past_last = state.ptr;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
Lexeme_Table_Lookup lookup = lexeme_table_lookup(odin_attributes_hash_array, odin_attributes_key_array, odin_attributes_value_array, odin_attributes_slot_count, odin_attributes_seed, state.delim_first, (state.delim_one_past_last - state.delim_first));
if (lookup.found_match){
token.kind = lookup.base_kind;
token.sub_kind = lookup.sub_kind;
break;
}
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
state.delim_one_past_last = state.ptr;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
Lexeme_Table_Lookup lookup = lexeme_table_lookup(odin_attributes_hash_array, odin_attributes_key_array, odin_attributes_value_array, odin_attributes_slot_count, odin_attributes_seed, state.delim_first, (state.delim_one_past_last - state.delim_first));
if (lookup.found_match){
token.kind = lookup.base_kind;
token.sub_kind = lookup.sub_kind;
break;
}
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x41:case 0x42:case 0x43:case 0x44:case 0x45:case 0x46:case 0x47:
case 0x48:case 0x49:case 0x4a:case 0x4b:case 0x4c:case 0x4d:case 0x4e:
case 0x4f:case 0x50:case 0x51:case 0x52:case 0x53:case 0x54:case 0x55:
case 0x56:case 0x57:case 0x58:case 0x59:case 0x5a:case 0x5f:case 0x61:
case 0x62:case 0x63:case 0x64:case 0x65:case 0x66:case 0x67:case 0x68:
case 0x69:case 0x6a:case 0x6b:case 0x6c:case 0x6d:case 0x6e:case 0x6f:
case 0x70:case 0x71:case 0x72:case 0x73:case 0x74:case 0x75:case 0x76:
case 0x77:case 0x78:case 0x79:case 0x7a:
{
state.ptr += 1;
goto state_label_25; // attribute
}break;
}
}
{
state_label_26: // directive
if (state.ptr == state.opl_ptr){
if ((true)){
state.delim_one_past_last = state.ptr;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
Lexeme_Table_Lookup lookup = lexeme_table_lookup(odin_directives_hash_array, odin_directives_key_array, odin_directives_value_array, odin_directives_slot_count, odin_directives_seed, state.delim_first, (state.delim_one_past_last - state.delim_first));
if (lookup.found_match){
token.kind = lookup.base_kind;
token.sub_kind = lookup.sub_kind;
break;
}
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
state.delim_one_past_last = state.ptr;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
Lexeme_Table_Lookup lookup = lexeme_table_lookup(odin_directives_hash_array, odin_directives_key_array, odin_directives_value_array, odin_directives_slot_count, odin_directives_seed, state.delim_first, (state.delim_one_past_last - state.delim_first));
if (lookup.found_match){
token.kind = lookup.base_kind;
token.sub_kind = lookup.sub_kind;
break;
}
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x41:case 0x42:case 0x43:case 0x44:case 0x45:case 0x46:case 0x47:
case 0x48:case 0x49:case 0x4a:case 0x4b:case 0x4c:case 0x4d:case 0x4e:
case 0x4f:case 0x50:case 0x51:case 0x52:case 0x53:case 0x54:case 0x55:
case 0x56:case 0x57:case 0x58:case 0x59:case 0x5a:case 0x5f:case 0x61:
case 0x62:case 0x63:case 0x64:case 0x65:case 0x66:case 0x67:case 0x68:
case 0x69:case 0x6a:case 0x6b:case 0x6c:case 0x6d:case 0x6e:case 0x6f:
case 0x70:case 0x71:case 0x72:case 0x73:case 0x74:case 0x75:case 0x76:
case 0x77:case 0x78:case 0x79:case 0x7a:
{
state.ptr += 1;
goto state_label_26; // directive
}break;
}
}
{
state_label_27: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_Colon;
token.kind = 15;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_Colon;
token.kind = 15;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x3a:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_ColonColon;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x3d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_ColonEq;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_28: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_Less;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_Less;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x3c:
{
state.ptr += 1;
goto state_label_38; // op stage
}break;
case 0x3d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_LessEq;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_29: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_Grtr;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_Grtr;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x3d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_GrtrEq;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x3e:
{
state.ptr += 1;
goto state_label_39; // op stage
}break;
}
}
{
state_label_30: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_Eq;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_Eq;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x3d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_EqEq;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_31: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_Not;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_Not;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x3d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_NotEq;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_32: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_And;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_And;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x26:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_AndAnd;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_33: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_Or;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_Or;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x7c:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_OrOr;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_34: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_Plus;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_Plus;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x3d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_PlusEq;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_35: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_Minus;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_Minus;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x3d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_MinusEq;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_36: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_Star;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_Star;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x3d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_StarEq;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_37: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_Mod;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_Mod;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x3d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_ModEq;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_38: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_LeftLeft;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_LeftLeft;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x3d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_LeftLeftEq;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_39: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_RightRight;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_RightRight;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x3d:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_RightRightEq;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
}
}
{
state_label_40: // op stage
if (state.ptr == state.opl_ptr){
if ((true)){
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_DotDot;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}
}
switch (*state.ptr){
default:
{
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_DotDot;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
case 0x3c:
{
state.ptr += 1;
{
Token token = {};
token.pos = (i64)(state.emit_ptr - state.base);
token.size = (i64)(state.ptr - state.emit_ptr);
token.flags = state.flags_KB0;
do{
token.sub_kind = TokenOdinKind_DotDotLess;
token.kind = 7;
}while(0);
token_list_push(arena, list, &token);
emit_counter += 1;
state.emit_ptr = state.ptr;
if (emit_counter == max){
goto end;
}
}
state.flags_KF0 |= 0x1;
state.flags_ZF0 = 0;
goto state_label_1; // root
}break;
}
}
end:;
block_copy_struct(state_ptr, &state);
return(result);
}
internal Token_List
lex_full_input_odin(Arena *arena, String_Const_u8 input){
Lex_State_Odin state = {};
lex_full_input_odin_init(&state, input);
Token_List list = {};
lex_full_input_odin_breaks(arena, &list, &state, max_u64);
return(list);
}
