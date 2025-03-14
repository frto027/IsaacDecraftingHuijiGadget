
struct ItemPoolDataItem{
    int id;float weight;
};
struct ItemPoolMetaData{
    int index, length;
};
struct ItemPoolData{
    struct ItemPoolDataItem * datas;
    int length;
};

struct ItemConfigData{
    int aid,quality,is_active,tags;
};

#define TAG_LAZARUSSHARED       (1<<1)
#define TAG_NODAILY             (1<<2)
#define TAG_OFFENSIVE           (1<<3)
#define TAG_NOLOSTBR            (1<<4)
#define TAG_NOKEEPER            (1<<5)
#define TAG_NOGREED             (1<<6)
#define TAG_NOCHALLENGE         (1<<7)
ItemPoolDataItem item_pool_datas[] = {
    {1,1},
    {2,1},
    {3,1},
    {4,1},
    {5,1},
    {6,1},
    {7,1},
    {8,1},
    {10,1},
    {12,0.5},
    {13,1},
    {14,1},
    {15,1},
    {17,0.1},
    {19,1},
    {36,1},
    {37,1},
    {38,1},
    {39,1},
    {40,1},
    {41,1},
    {42,1},
    {44,1},
    {45,1},
    {46,1},
    {47,1},
    {48,1},
    {49,1},
    {52,1},
    {53,1},
    {55,1},
    {56,1},
    {57,1},
    {58,1},
    {62,1},
    {65,1},
    {66,1},
    {67,1},
    {68,1},
    {69,1},
    {71,1},
    {72,1},
    {75,1},
    {76,1},
    {77,1},
    {78,1},
    {85,1},
    {86,1},
    {87,1},
    {88,1},
    {89,1},
    {91,1},
    {92,1},
    {93,1},
    {94,1},
    {95,1},
    {96,1},
    {97,1},
    {98,0.2},
    {99,1},
    {100,1},
    {101,0.5},
    {102,1},
    {103,1},
    {104,1},
    {105,1},
    {106,1},
    {107,1},
    {108,1},
    {109,1},
    {110,1},
    {111,1},
    {113,1},
    {114,0.2},
    {115,1},
    {117,1},
    {120,1},
    {121,1},
    {123,1},
    {124,1},
    {125,1},
    {126,1},
    {127,1},
    {128,1},
    {129,1},
    {131,1},
    {136,1},
    {137,1},
    {138,1},
    {140,1},
    {142,1},
    {143,1},
    {144,1},
    {146,1},
    {148,1},
    {149,1},
    {150,1},
    {151,1},
    {152,1},
    {153,1},
    {154,1},
    {155,1},
    {157,1},
    {160,1},
    {161,1},
    {162,1},
    {163,1},
    {166,1},
    {167,1},
    {168,0.1},
    {169,1},
    {170,1},
    {171,1},
    {172,1},
    {173,1},
    {174,1},
    {175,1},
    {176,1},
    {178,1},
    {180,1},
    {186,1},
    {188,1},
    {189,1},
    {190,0.1},
    {191,1},
    {192,1},
    {200,1},
    {201,1},
    {202,1},
    {206,1},
    {209,1},
    {210,1},
    {211,1},
    {213,1},
    {214,1},
    {217,1},
    {220,1},
    {221,1},
    {222,1},
    {223,1},
    {224,1},
    {225,1},
    {227,1},
    {228,1},
    {229,1},
    {231,1},
    {233,1},
    {234,1},
    {236,1},
    {237,0.2},
    {240,1},
    {242,1},
    {244,1},
    {245,1},
    {256,1},
    {257,1},
    {261,1},
    {264,1},
    {265,1},
    {266,1},
    {267,1},
    {268,1},
    {269,1},
    {270,1},
    {271,1},
    {272,1},
    {273,1},
    {274,1},
    {275,1},
    {276,1},
    {277,1},
    {278,1},
    {279,1},
    {280,1},
    {281,1},
    {282,1},
    {283,1},
    {284,1},
    {285,1},
    {287,1},
    {288,1},
    {291,1},
    {292,1},
    {294,1},
    {295,1},
    {298,1},
    {299,1},
    {300,1},
    {301,1},
    {302,1},
    {303,1},
    {304,1},
    {305,1},
    {306,1},
    {307,1},
    {308,1},
    {309,1},
    {310,1},
    {312,1},
    {313,0.2},
    {314,1},
    {315,1},
    {316,1},
    {317,1},
    {318,1},
    {319,1},
    {320,1},
    {321,1},
    {322,1},
    {323,1},
    {324,1},
    {325,1},
    {329,1},
    {330,1},
    {332,1},
    {333,0.2},
    {334,0.2},
    {335,0.2},
    {336,1},
    {350,1},
    {351,1},
    {352,1},
    {353,1},
    {358,1},
    {359,1},
    {361,1},
    {362,1},
    {364,1},
    {365,1},
    {366,1},
    {367,1},
    {368,1},
    {369,1},
    {371,1},
    {373,1},
    {374,0.2},
    {375,1},
    {377,1},
    {378,1},
    {379,1},
    {381,1},
    {382,1},
    {384,1},
    {385,1},
    {386,1},
    {388,1},
    {389,1},
    {390,1},
    {391,1},
    {392,1},
    {393,1},
    {394,1},
    {395,1},
    {397,1},
    {398,1},
    {401,1},
    {404,1},
    {405,1},
    {406,1},
    {407,1},
    {410,1},
    {411,1},
    {418,1},
    {419,1},
    {421,1},
    {422,1},
    {426,1},
    {427,1},
    {430,1},
    {431,1},
    {432,1},
    {435,1},
    {436,1},
    {437,1},
    {440,1},
    {443,1},
    {444,1},
    {445,1},
    {446,1},
    {447,1},
    {448,1},
    {449,1},
    {452,1},
    {453,1},
    {454,1},
    {457,1},
    {458,1},
    {459,1},
    {460,1},
    {461,1},
    {463,1},
    {465,1},
    {466,1},
    {467,1},
    {469,1},
    {470,1},
    {471,1},
    {473,1},
    {476,1},
    {478,1},
    {481,1},
    {482,1},
    {485,1},
    {488,1},
    {491,1},
    {492,1},
    {493,1},
    {494,1},
    {495,1},
    {496,1},
    {497,1},
    {502,1},
    {504,1},
    {506,1},
    {507,1},
    {508,1},
    {509,1},
    {511,1},
    {512,1},
    {513,1},
    {516,1},
    {517,1},
    {522,1},
    {524,1},
    {525,1},
    {529,1},
    {531,1},
    {532,1},
    {537,1},
    {539,1},
    {540,1},
    {542,1},
    {543,1},
    {544,1},
    {545,1},
    {548,1},
    {549,1},
    {553,1},
    {555,1},
    {557,1},
    {558,1},
    {559,1},
    {560,1},
    {561,1},
    {563,1},
    {565,1},
    {570,1},
    {575,1},
    {576,1},
    {578,1},
    {581,1},
    {583,1},
    {605,1},
    {607,1},
    {608,1},
    {609,0.5},
    {610,1},
    {611,1},
    {612,1},
    {614,1},
    {615,1},
    {616,1},
    {617,1},
    {618,1},
    {625,0.1},
    {629,1},
    {631,1},
    {635,1},
    {637,1},
    {639,1},
    {641,1},
    {645,1},
    {649,1},
    {650,0.5},
    {652,1},
    {655,1},
    {657,1},
    {658,1},
    {661,1},
    {663,1},
    {671,1},
    {675,1},
    {676,1},
    {677,0.2},
    {678,1},
    {680,1},
    {681,1},
    {682,1},
    {683,1},
    {687,1},
    {690,1},
    {693,1},
    {695,1},
    {703,0.5},
    {709,1},
    {710,1},
    {713,1},
    {717,1},
    {720,1},
    {722,1},
    {723,0.1},
    {724,1},
    {725,1},
    {726,1},
    {727,1},
    {728,0.5},
    {729,1},
    {21,1},
    {33,1},
    {54,1},
    {60,1},
    {63,1},
    {64,1},
    {75,1},
    {85,1},
    {102,1},
    {116,1},
    {137,1},
    {139,1},
    {147,1},
    {156,1},
    {164,1},
    {195,1},
    {199,1},
    {203,1},
    {204,1},
    {205,1},
    {208,1},
    {227,1},
    {232,1},
    {246,1},
    {247,1},
    {248,1},
    {249,1},
    {250,1},
    {251,1},
    {252,1},
    {260,1},
    {286,0.5},
    {289,1},
    {290,1},
    {295,1},
    {296,1},
    {297,1},
    {337,1},
    {338,1},
    {347,1},
    {348,1},
    {349,1},
    {356,1},
    {357,1},
    {372,1},
    {376,1},
    {380,1},
    {383,1},
    {396,1},
    {402,0.5},
    {403,1},
    {414,1},
    {416,1},
    {422,1},
    {424,0.5},
    {425,1},
    {434,1},
    {439,1},
    {451,1},
    {472,1},
    {475,0.2},
    {479,1},
    {480,1},
    {483,0.5},
    {485,0.5},
    {486,1},
    {487,1},
    {505,1},
    {514,1},
    {515,1},
    {518,1},
    {520,1},
    {521,1},
    {523,1},
    {527,1},
    {534,1},
    {535,1},
    {566,1},
    {585,1},
    {599,1},
    {602,1},
    {603,1},
    {604,1},
    {619,1},
    {621,1},
    {623,1},
    {624,1},
    {638,1},
    {642,0.1},
    {647,1},
    {660,0.5},
    {670,1},
    {716,1},
    {719,0.5},
    {14,1},
    {22,1},
    {23,1},
    {24,1},
    {25,1},
    {26,1},
    {27,1},
    {28,1},
    {29,1},
    {30,1},
    {31,1},
    {32,1},
    {51,1},
    {70,1},
    {92,0.5},
    {141,1},
    {143,1},
    {165,1},
    {176,1},
    {183,1},
    {193,1},
    {194,1},
    {195,1},
    {196,1},
    {197,1},
    {198,1},
    {218,1},
    {219,1},
    {240,1},
    {253,1},
    {254,1},
    {255,1},
    {339,1},
    {340,1},
    {341,1},
    {342,1},
    {343,1},
    {344,1},
    {345,1},
    {346,1},
    {354,1},
    {355,1},
    {370,1},
    {428,0.5},
    {438,1},
    {455,1},
    {456,1},
    {538,1},
    {541,1},
    {547,1},
    {564,1},
    {600,1},
    {624,1},
    {644,1},
    {659,1},
    {707,1},
    {708,1},
    {730,1},
    {731,1},
    {8,1},
    {34,1},
    {35,1},
    {51,1},
    {67,1},
    {74,1},
    {79,1},
    {80,1},
    {81,1},
    {82,1},
    {83,1},
    {84,1},
    {97,1},
    {109,1},
    {113,1},
    {114,1},
    {115,1},
    {118,1},
    {122,1},
    {123,1},
    {127,0.2},
    {133,1},
    {134,1},
    {145,1},
    {157,1},
    {159,1},
    {163,1},
    {172,1},
    {186,1},
    {187,1},
    {212,1},
    {215,1},
    {216,1},
    {225,1},
    {230,1},
    {237,1},
    {241,1},
    {259,1},
    {262,1},
    {268,1},
    {269,1},
    {275,1},
    {278,1},
    {292,1},
    {311,1},
    {360,1},
    {391,1},
    {399,1},
    {408,1},
    {409,1},
    {411,1},
    {412,1},
    {417,1},
    {420,1},
    {431,1},
    {433,1},
    {441,0.2},
    {442,1},
    {462,1},
    {468,1},
    {475,0.2},
    {477,0.5},
    {498,1},
    {503,1},
    {506,1},
    {519,1},
    {526,1},
    {530,1},
    {536,1},
    {545,1},
    {554,1},
    {556,1},
    {569,1},
    {572,1},
    {577,1},
    {606,1},
    {634,1},
    {646,1},
    {654,1},
    {665,1},
    {672,1},
    {679,1},
    {684,1},
    {692,1},
    {694,0.5},
    {695,1},
    {698,1},
    {699,1},
    {702,1},
    {704,0.5},
    {705,0.5},
    {706,0.5},
    {712,0.5},
    {728,1},
    {7,1},
    {33,1},
    {72,1},
    {78,1},
    {98,1},
    {101,1},
    {108,1},
    {112,1},
    {124,1},
    {138,1},
    {142,1},
    {146,1},
    {156,1},
    {162,1},
    {173,1},
    {178,1},
    {182,1},
    {184,1},
    {185,1},
    {197,1},
    {243,1},
    {313,1},
    {326,1},
    {331,1},
    {332,1},
    {333,1},
    {334,1},
    {335,1},
    {363,1},
    {374,1},
    {387,1},
    {390,1},
    {400,1},
    {407,1},
    {413,1},
    {415,1},
    {423,1},
    {464,1},
    {477,0.5},
    {490,1},
    {498,1},
    {499,1},
    {510,0.4},
    {519,1},
    {526,1},
    {528,1},
    {533,1},
    {543,1},
    {567,1},
    {568,1},
    {573,1},
    {574,1},
    {579,1},
    {584,0.5},
    {586,1},
    {601,1},
    {622,1},
    {634,1},
    {640,1},
    {643,1},
    {651,1},
    {653,1},
    {685,1},
    {686,1},
    {691,0.5},
    {696,1},
    {11,1},
    {16,1},
    {17,1},
    {20,1},
    {35,1},
    {84,1},
    {120,1},
    {121,1},
    {127,1},
    {168,1},
    {190,1},
    {213,1},
    {226,1},
    {242,1},
    {258,1},
    {262,1},
    {263,1},
    {271,1},
    {286,1},
    {287,1},
    {316,1},
    {321,1},
    {348,1},
    {388,1},
    {389,1},
    {402,1},
    {405,1},
    {424,1},
    {450,1},
    {489,1},
    {500,1},
    {501,1},
    {546,1},
    {562,1},
    {571,1},
    {580,1},
    {582,1},
    {609,1},
    {612,1},
    {625,1},
    {628,1},
    {632,1},
    {636,1},
    {664,1},
    {667,1},
    {669,1},
    {674,1},
    {675,1},
    {677,1},
    {688,1},
    {689,1},
    {691,0.5},
    {697,0.5},
    {700,1},
    {701,1},
    {703,1},
    {711,1},
    {716,1},
    {717,1},
    {719,1},
    {721,1},
    {723,1},
    {9,1},
    {36,1},
    {209,1},
    {378,1},
    {504,1},
    {576,1},
    {28,1},
    {29,1},
    {32,1},
    {74,1},
    {179,0.5},
    {194,1},
    {196,1},
    {255,1},
    {341,1},
    {343,1},
    {344,1},
    {354,1},
    {355,1},
    {370,1},
    {428,0.5},
    {438,1},
    {444,0.1},
    {455,1},
    {456,1},
    {534,0.5},
    {571,0.1},
    {644,1},
    {708,1},
    {730,1},
    {732,1},
    {81,1},
    {133,1},
    {134,1},
    {140,1},
    {145,1},
    {212,1},
    {297,1},
    {316,1},
    {371,1},
    {475,0.1},
    {565,0.5},
    {580,0.1},
    {642,1},
    {654,0.2},
    {665,1},
    {51,1},
    {79,1},
    {80,1},
    {81,1},
    {126,1},
    {133,1},
    {134,1},
    {145,1},
    {212,1},
    {215,1},
    {216,1},
    {225,1},
    {241,1},
    {260,1},
    {371,1},
    {408,1},
    {442,1},
    {451,1},
    {468,1},
    {475,0.2},
    {496,1},
    {503,1},
    {536,1},
    {565,1},
    {569,1},
    {580,1},
    {642,1},
    {654,0.5},
    {665,1},
    {692,1},
    {694,0.5},
    {697,0.5},
    {702,1},
    {711,1},
    {588,1},
    {589,1},
    {590,1},
    {591,1},
    {592,1},
    {593,1},
    {594,1},
    {595,1},
    {596,1},
    {597,1},
    {598,1},
};

ItemPoolMetaData item_pool_metadata[] = {
    {0,407},
    {407,94},
    {501,59},
    {560,94},
    {654,66},
    {720,62},
    {-1,-1},
    {782,6},
    {788,25},
    {813,15},
    {-1,-1},
    {-1,-1},
    {828,34},
    {-1,-1},
    {-1,-1},
    {-1,-1},
    {-1,-1},
    {-1,-1},
    {-1,-1},
    {-1,-1},
    {-1,-1},
    {-1,-1},
    {-1,-1},
    {-1,-1},
    {-1,-1},
    {-1,-1},
    {862,11},
};


ItemPoolData GetItemPoolData(int item_pool_id){
    int index = item_pool_metadata[item_pool_id].index;
    if(index < 0){
        return {NULL, 0};
    }else{
        return {&item_pool_datas[index], item_pool_metadata[item_pool_id].length};
    }
}

struct ItemConfigData item_config_datas[] = {
    {-1,-1,0,0},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,4,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,0,0,(TAG_OFFENSIVE)},
    {-1,2,0,0},
    {-1,2,0,0},
    {-1,4,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_NOLOSTBR)},
    {-1,2,0,(TAG_NOLOSTBR)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,0,0,(TAG_OFFENSIVE)},
    {8,2,0,(TAG_NOLOSTBR)},
    {-1,1,0,(TAG_OFFENSIVE|TAG_NOGREED)},
    {-1,1,0,(TAG_NOLOSTBR)},
    {-1,1,0,(TAG_NOLOSTBR)},
    {-1,1,0,(TAG_NOLOSTBR)},
    {-1,1,0,(TAG_NOLOSTBR)},
    {-1,1,0,(TAG_NOLOSTBR)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {139,3,0,(TAG_OFFENSIVE)},
    {-1,1,1,(TAG_NOLOSTBR)},
    {-1,2,1,(TAG_OFFENSIVE)},
    {36,0,1,(TAG_OFFENSIVE)},
    {-1,0,1,0},
    {-1,1,1,(TAG_OFFENSIVE)},
    {-1,1,1,(TAG_OFFENSIVE)},
    {-1,0,1,(TAG_OFFENSIVE)},
    {-1,0,1,(TAG_NOLOSTBR)},
    {-1,0,1,(TAG_OFFENSIVE)},
    {-1,1,1,(TAG_OFFENSIVE)},
    {-1,-1,0,0},
    {-1,0,1,(TAG_OFFENSIVE)},
    {-1,1,1,(TAG_NOLOSTBR)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,1,1,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,2,1,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {11,4,0,(TAG_OFFENSIVE)},
    {-1,1,0,0},
    {-1,1,0,(TAG_OFFENSIVE|TAG_NOGREED)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,0,1,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,2,1,(TAG_OFFENSIVE)},
    {-1,0,0,0},
    {-1,1,0,(TAG_NOLOSTBR)},
    {-1,-1,0,0},
    {-1,2,0,(TAG_NOLOSTBR)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,0,1,(TAG_OFFENSIVE)},
    {-1,0,1,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {6,1,0,0},
    {10,0,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,1,1,(TAG_OFFENSIVE)},
    {7,3,1,(TAG_NOLOSTBR)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,2,0,0},
    {-1,3,0,(TAG_NOLOSTBR)},
    {9,2,1,0},
    {-1,2,1,(TAG_OFFENSIVE)},
    {-1,2,1,(TAG_OFFENSIVE)},
    {13,0,1,(TAG_OFFENSIVE)},
    {15,1,0,(TAG_OFFENSIVE)},
    {14,1,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {12,3,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {19,2,0,(TAG_NOLOSTBR)},
    {26,1,1,(TAG_OFFENSIVE)},
    {21,1,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {25,2,0,(TAG_NOLOSTBR)},
    {22,1,1,(TAG_OFFENSIVE)},
    {20,3,0,(TAG_NOLOSTBR)},
    {23,1,0,(TAG_OFFENSIVE)},
    {24,2,0,(TAG_OFFENSIVE)},
    {27,3,0,(TAG_OFFENSIVE)},
    {-1,1,1,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {31,3,0,(TAG_OFFENSIVE)},
    {29,4,1,(TAG_OFFENSIVE)},
    {28,2,0,(TAG_OFFENSIVE)},
    {-1,2,1,(TAG_OFFENSIVE)},
    {-1,4,0,(TAG_NOLOSTBR)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {35,3,0,(TAG_OFFENSIVE)},
    {-1,0,1,(TAG_OFFENSIVE)},
    {45,1,0,0},
    {47,1,0,(TAG_OFFENSIVE)},
    {43,4,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,0,0,(TAG_NOLOSTBR)},
    {-1,4,0,(TAG_OFFENSIVE)},
    {147,2,0,(TAG_NOLOSTBR)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,1,1,(TAG_OFFENSIVE)},
    {-1,1,1,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {44,0,1,(TAG_NOLOSTBR)},
    {48,3,1,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_NOLOSTBR)},
    {-1,2,1,(TAG_OFFENSIVE)},
    {46,1,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,2,1,(TAG_NOLOSTBR)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,2,1,(TAG_NOLOSTBR)},
    {-1,0,1,(TAG_OFFENSIVE)},
    {-1,0,1,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_NOLOSTBR)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,0,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_NOLOSTBR)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,2,1,(TAG_OFFENSIVE)},
    {-1,3,1,(TAG_NOLOSTBR)},
    {-1,1,1,(TAG_OFFENSIVE)},
    {-1,0,0,(TAG_NOLOSTBR)},
    {140,4,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_NOLOSTBR)},
    {54,2,0,(TAG_NOLOSTBR)},
    {-1,3,1,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_NOLOSTBR)},
    {-1,1,1,(TAG_OFFENSIVE)},
    {-1,0,0,(TAG_NOLOSTBR|TAG_NOCHALLENGE)},
    {50,1,0,(TAG_NOLOSTBR)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {59,2,1,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {49,2,1,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {62,4,0,(TAG_OFFENSIVE)},
    {-1,4,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,1,1,(TAG_OFFENSIVE)},
    {53,2,0,0},
    {-1,3,0,0},
    {-1,1,0,(TAG_OFFENSIVE)},
    {58,2,1,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_NOLOSTBR)},
    {-1,0,1,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {113,3,0,(TAG_NOLOSTBR)},
    {-1,0,0,(TAG_NOLOSTBR)},
    {-1,3,1,(TAG_OFFENSIVE)},
    {-1,4,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_NOLOSTBR)},
    {-1,3,0,(TAG_NOLOSTBR)},
    {56,0,1,(TAG_NOLOSTBR)},
    {65,1,0,(TAG_OFFENSIVE)},
    {51,0,0,(TAG_OFFENSIVE)},
    {63,3,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,1,1,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_NOLOSTBR)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,0,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,0,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_NOLOSTBR)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_NOLOSTBR)},
    {-1,2,0,(TAG_NOLOSTBR)},
    {107,1,0,(TAG_OFFENSIVE)},
    {6,1,0,0},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,1,0,0},
    {-1,0,0,(TAG_NOLOSTBR)},
    {-1,1,0,0},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_NOLOSTBR)},
    {-1,3,0,(TAG_OFFENSIVE|TAG_NOGREED)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_NOLOSTBR)},
    {-1,2,0,(TAG_NOLOSTBR)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {150,3,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,4,0,0},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_NOLOSTBR)},
    {-1,2,0,(TAG_NOLOSTBR)},
    {-1,1,0,(TAG_NOLOSTBR)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {128,3,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {138,4,0,0},
    {-1,0,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,-1,0,0},
    {-1,0,0,(TAG_NOLOSTBR)},
    {103,3,0,(TAG_OFFENSIVE)},
    {-1,0,0,(TAG_OFFENSIVE|TAG_LAZARUSSHARED)},
    {-1,0,0,(TAG_OFFENSIVE|TAG_LAZARUSSHARED)},
    {141,1,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE|TAG_NOGREED)},
    {-1,2,0,0},
    {-1,2,0,0},
    {104,3,0,(TAG_OFFENSIVE)},
    {-1,4,0,(TAG_OFFENSIVE)},
    {134,1,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {135,3,0,(TAG_OFFENSIVE|TAG_NOGREED)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {146,0,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_NOLOSTBR)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {105,0,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {136,3,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,0,0,(TAG_NOLOSTBR)},
    {233,2,1,(TAG_OFFENSIVE)},
    {-1,1,0,0},
    {-1,3,0,0},
    {-1,2,0,(TAG_OFFENSIVE)},
    {102,1,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {124,2,0,(TAG_OFFENSIVE)},
    {-1,0,0,(TAG_OFFENSIVE)},
    {-1,0,0,(TAG_OFFENSIVE)},
    {-1,0,0,(TAG_NOLOSTBR)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {129,0,0,(TAG_NOLOSTBR)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,1,0,0},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,1,0,0},
    {-1,1,1,(TAG_NOLOSTBR)},
    {133,2,1,(TAG_OFFENSIVE)},
    {148,2,1,(TAG_OFFENSIVE)},
    {-1,1,1,(TAG_OFFENSIVE)},
    {121,2,1,(TAG_OFFENSIVE)},
    {122,0,1,(TAG_OFFENSIVE)},
    {-1,1,1,(TAG_OFFENSIVE)},
    {137,1,1,(TAG_OFFENSIVE)},
    {-1,0,1,(TAG_NOLOSTBR)},
    {-1,1,1,(TAG_OFFENSIVE)},
    {126,3,1,(TAG_OFFENSIVE)},
    {143,1,1,(TAG_OFFENSIVE)},
    {145,0,1,(TAG_OFFENSIVE)},
    {-1,0,1,(TAG_OFFENSIVE)},
    {-1,2,1,(TAG_NOLOSTBR)},
    {119,2,1,(TAG_OFFENSIVE)},
    {-1,1,1,0},
    {-1,1,0,0},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_NOLOSTBR)},
    {-1,1,0,0},
    {-1,2,0,0},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {112,3,0,(TAG_OFFENSIVE)},
    {108,3,0,(TAG_NOLOSTBR|TAG_NOCHALLENGE)},
    {109,2,0,(TAG_NOLOSTBR)},
    {-1,4,0,0},
    {-1,1,0,(TAG_NOLOSTBR)},
    {-1,0,0,(TAG_OFFENSIVE)},
    {-1,0,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {110,2,0,(TAG_OFFENSIVE)},
    {114,1,0,(TAG_OFFENSIVE)},
    {115,1,0,0},
    {-1,2,0,(TAG_OFFENSIVE)},
    {106,1,1,(TAG_OFFENSIVE)},
    {125,1,1,(TAG_OFFENSIVE)},
    {30,0,1,(TAG_OFFENSIVE)},
    {-1,1,1,(TAG_NOLOSTBR)},
    {57,2,0,(TAG_OFFENSIVE|TAG_LAZARUSSHARED)},
    {78,2,0,(TAG_OFFENSIVE|TAG_LAZARUSSHARED)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {156,4,0,(TAG_OFFENSIVE)},
    {116,1,0,(TAG_NOLOSTBR|TAG_NOCHALLENGE)},
    {130,3,0,(TAG_OFFENSIVE)},
    {131,3,0,(TAG_NOLOSTBR)},
    {132,3,0,0},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,1,0,0},
    {-1,1,1,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_NOLOSTBR)},
    {-1,3,1,(TAG_OFFENSIVE)},
    {-1,1,1,(TAG_OFFENSIVE)},
    {244,1,1,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,1,1,(TAG_OFFENSIVE)},
    {-1,1,1,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_NOLOSTBR)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {203,1,1,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {190,4,0,(TAG_OFFENSIVE)},
    {183,2,0,(TAG_OFFENSIVE)},
    {192,2,0,(TAG_OFFENSIVE)},
    {189,2,0,0},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,0,0,(TAG_NOLOSTBR)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,3,0,0},
    {-1,2,0,(TAG_OFFENSIVE|TAG_NOGREED)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {188,3,0,(TAG_OFFENSIVE)},
    {-1,1,1,(TAG_OFFENSIVE)},
    {-1,1,1,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {181,1,1,(TAG_OFFENSIVE)},
    {193,2,0,0},
    {200,0,0,(TAG_OFFENSIVE)},
    {218,3,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {182,1,0,(TAG_OFFENSIVE)},
    {202,1,0,(TAG_OFFENSIVE)},
    {220,2,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,4,0,(TAG_OFFENSIVE)},
    {-1,0,1,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {186,3,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {179,1,0,0},
    {201,1,0,(TAG_OFFENSIVE)},
    {231,1,1,(TAG_OFFENSIVE)},
    {180,3,0,(TAG_OFFENSIVE)},
    {184,3,0,(TAG_OFFENSIVE)},
    {187,2,0,0},
    {194,2,0,(TAG_OFFENSIVE)},
    {198,3,0,(TAG_OFFENSIVE)},
    {219,1,0,(TAG_NOLOSTBR)},
    {222,1,0,(TAG_NOLOSTBR)},
    {135,3,0,(TAG_OFFENSIVE)},
    {-1,4,0,(TAG_OFFENSIVE)},
    {238,2,0,(TAG_OFFENSIVE)},
    {221,3,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,3,1,(TAG_OFFENSIVE)},
    {-1,0,0,(TAG_OFFENSIVE)},
    {-1,0,1,(TAG_OFFENSIVE)},
    {-1,-1,1,(TAG_OFFENSIVE)},
    {-1,2,0,0},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,1,0,0},
    {-1,0,0,(TAG_OFFENSIVE)},
    {-1,1,1,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_NOLOSTBR)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {195,1,0,(TAG_OFFENSIVE)},
    {-1,2,1,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_NOLOSTBR)},
    {-1,1,1,(TAG_OFFENSIVE|TAG_NOGREED)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,2,1,(TAG_OFFENSIVE)},
    {232,2,0,(TAG_OFFENSIVE)},
    {276,4,1,(TAG_OFFENSIVE)},
    {290,1,0,(TAG_NOLOSTBR)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,0,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_NOLOSTBR)},
    {-1,1,0,0},
    {308,2,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,0,0,(TAG_NOLOSTBR)},
    {291,3,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {307,2,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_NOLOSTBR)},
    {-1,2,0,0},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {299,3,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {297,2,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {285,0,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {315,0,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {286,1,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,0,1,0},
    {305,0,1,(TAG_OFFENSIVE)},
    {296,2,1,(TAG_OFFENSIVE)},
    {295,3,1,(TAG_OFFENSIVE)},
    {-1,0,1,(TAG_OFFENSIVE)},
    {318,2,1,(TAG_OFFENSIVE)},
    {-1,0,1,(TAG_OFFENSIVE)},
    {-1,0,1,(TAG_OFFENSIVE)},
    {-1,0,1,(TAG_NOLOSTBR|TAG_NOCHALLENGE)},
    {-1,3,1,(TAG_OFFENSIVE)},
    {-1,1,1,(TAG_OFFENSIVE)},
    {294,2,1,(TAG_OFFENSIVE)},
    {288,0,1,0},
    {-1,2,1,(TAG_NOLOSTBR)},
    {303,1,1,(TAG_OFFENSIVE)},
    {282,4,1,(TAG_OFFENSIVE)},
    {289,2,1,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_NOLOSTBR)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {292,3,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {306,1,0,(TAG_OFFENSIVE)},
    {283,3,0,(TAG_OFFENSIVE)},
    {298,2,0,(TAG_OFFENSIVE)},
    {335,1,0,(TAG_NOLOSTBR)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {316,0,1,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE|TAG_NOGREED)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,2,1,(TAG_OFFENSIVE)},
    {-1,1,0,0},
    {-1,1,0,0},
    {338,1,1,(TAG_OFFENSIVE)},
    {352,1,0,(TAG_OFFENSIVE)},
    {349,1,1,(TAG_OFFENSIVE)},
    {353,2,0,(TAG_NOLOSTBR)},
    {354,3,0,0},
    {350,3,1,(TAG_OFFENSIVE)},
    {351,1,1,(TAG_OFFENSIVE)},
    {356,1,0,(TAG_OFFENSIVE)},
    {355,2,0,(TAG_OFFENSIVE)},
    {357,1,0,(TAG_OFFENSIVE)},
    {367,2,0,(TAG_OFFENSIVE)},
    {364,2,1,(TAG_OFFENSIVE)},
    {365,1,1,(TAG_OFFENSIVE)},
    {366,1,1,(TAG_OFFENSIVE)},
    {369,3,0,(TAG_OFFENSIVE)},
    {368,0,0,(TAG_NOLOSTBR)},
    {372,2,0,(TAG_OFFENSIVE)},
    {371,3,1,(TAG_OFFENSIVE)},
    {373,3,0,(TAG_OFFENSIVE)},
    {374,1,0,(TAG_OFFENSIVE)},
    {376,1,0,(TAG_OFFENSIVE|TAG_LAZARUSSHARED)},
    {377,4,0,(TAG_OFFENSIVE)},
    {378,3,0,(TAG_OFFENSIVE)},
    {380,3,0,(TAG_OFFENSIVE)},
    {379,3,0,(TAG_OFFENSIVE)},
    {385,2,0,0},
    {383,1,1,(TAG_OFFENSIVE)},
    {384,1,0,(TAG_OFFENSIVE)},
    {386,2,0,0},
    {387,0,0,(TAG_NOLOSTBR)},
    {382,2,0,(TAG_OFFENSIVE)},
    {392,1,0,(TAG_NOLOSTBR)},
    {393,1,0,0},
    {398,1,0,(TAG_NOLOSTBR)},
    {394,1,0,(TAG_OFFENSIVE)},
    {401,2,1,(TAG_OFFENSIVE)},
    {400,2,0,0},
    {397,3,0,(TAG_OFFENSIVE)},
    {395,1,0,(TAG_OFFENSIVE)},
    {396,3,0,(TAG_OFFENSIVE)},
    {-1,4,1,(TAG_OFFENSIVE)},
    {-1,4,0,(TAG_OFFENSIVE)},
    {-1,4,1,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,1,0,0},
    {583,0,1,(TAG_OFFENSIVE)},
    {-1,2,1,(TAG_OFFENSIVE)},
    {-1,2,1,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_NOLOSTBR)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {433,4,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {462,1,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {423,1,0,0},
    {-1,1,0,(TAG_NOLOSTBR)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_NOLOSTBR)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {517,1,0,(TAG_OFFENSIVE)},
    {432,2,1,(TAG_OFFENSIVE)},
    {-1,0,1,(TAG_OFFENSIVE)},
    {520,3,0,(TAG_OFFENSIVE)},
    {415,3,1,(TAG_OFFENSIVE|TAG_NOGREED)},
    {-1,4,0,0},
    {-1,0,1,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {417,3,0,(TAG_OFFENSIVE)},
    {420,1,1,(TAG_OFFENSIVE)},
    {429,3,0,(TAG_OFFENSIVE)},
    {-1,-1,0,0},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE|TAG_NOGREED)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {582,2,0,(TAG_OFFENSIVE)},
    {-1,0,0,(TAG_OFFENSIVE)},
    {-1,1,1,(TAG_OFFENSIVE)},
    {-1,0,1,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {448,3,1,(TAG_OFFENSIVE)},
    {450,0,0,(TAG_NOLOSTBR)},
    {497,2,1,(TAG_OFFENSIVE)},
    {460,1,0,0},
    {-1,-1,0,0},
    {-1,2,0,(TAG_NOLOSTBR)},
    {-1,3,0,0},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {431,3,0,(TAG_OFFENSIVE)},
    {-1,-1,0,0},
    {430,2,0,(TAG_OFFENSIVE)},
    {436,3,1,(TAG_OFFENSIVE)},
    {-1,1,1,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {547,4,1,(TAG_OFFENSIVE)},
    {-1,0,0,(TAG_LAZARUSSHARED)},
    {-1,0,0,(TAG_LAZARUSSHARED)},
    {636,4,1,(TAG_OFFENSIVE)},
    {-1,3,0,0},
    {-1,-1,0,0},
    {440,0,1,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_LAZARUSSHARED)},
    {519,1,0,(TAG_OFFENSIVE)},
    {-1,1,1,(TAG_OFFENSIVE)},
    {-1,4,1,(TAG_OFFENSIVE|TAG_NOCHALLENGE|TAG_NODAILY)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,1,1,(TAG_OFFENSIVE)},
    {442,1,1,(TAG_NOLOSTBR)},
    {418,3,1,(TAG_OFFENSIVE)},
    {446,1,0,(TAG_OFFENSIVE)},
    {472,2,1,(TAG_OFFENSIVE)},
    {470,4,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {456,1,0,0},
    {546,2,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,-1,0,0},
    {409,1,0,(TAG_OFFENSIVE)},
    {410,0,1,(TAG_OFFENSIVE)},
    {425,3,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {424,1,1,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,0,1,0},
    {432,2,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_NOLOSTBR)},
    {-1,1,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE|TAG_NOGREED)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,-1,0,0},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,4,0,(TAG_NOLOSTBR)},
    {444,2,0,(TAG_OFFENSIVE)},
    {-1,-1,0,0},
    {503,2,0,(TAG_OFFENSIVE)},
    {-1,0,0,(TAG_LAZARUSSHARED)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {441,2,0,(TAG_OFFENSIVE|TAG_NOGREED)},
    {443,1,0,(TAG_NOLOSTBR)},
    {445,0,0,(TAG_NOKEEPER|TAG_NOGREED)},
    {447,2,0,(TAG_OFFENSIVE|TAG_LAZARUSSHARED)},
    {469,1,0,0},
    {451,1,0,(TAG_NOLOSTBR)},
    {453,1,0,(TAG_NOLOSTBR)},
    {457,1,0,(TAG_NOLOSTBR)},
    {463,4,0,(TAG_OFFENSIVE)},
    {455,2,0,(TAG_OFFENSIVE)},
    {449,2,0,(TAG_OFFENSIVE)},
    {466,0,0,(TAG_OFFENSIVE)},
    {467,3,0,(TAG_OFFENSIVE)},
    {468,2,0,(TAG_OFFENSIVE)},
    {461,2,0,(TAG_OFFENSIVE)},
    {471,1,1,(TAG_OFFENSIVE)},
    {422,1,0,(TAG_OFFENSIVE)},
    {473,2,1,(TAG_OFFENSIVE)},
    {434,2,0,0},
    {491,4,0,(TAG_OFFENSIVE)},
    {492,3,0,0},
    {501,4,0,(TAG_OFFENSIVE)},
    {494,1,0,(TAG_NOLOSTBR)},
    {495,2,0,0},
    {496,3,0,0},
    {452,2,0,(TAG_NOLOSTBR)},
    {499,3,0,(TAG_OFFENSIVE)},
    {435,1,0,(TAG_OFFENSIVE|TAG_LAZARUSSHARED|TAG_NOGREED)},
    {502,4,0,(TAG_OFFENSIVE)},
    {498,2,0,(TAG_OFFENSIVE)},
    {504,3,0,(TAG_OFFENSIVE)},
    {505,2,0,(TAG_OFFENSIVE)},
    {506,1,0,(TAG_NOLOSTBR)},
    {507,2,1,(TAG_OFFENSIVE)},
    {590,1,1,(TAG_OFFENSIVE)},
    {587,1,1,(TAG_OFFENSIVE)},
    {597,3,1,(TAG_OFFENSIVE)},
    {-1,1,0,(TAG_NOLOSTBR)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {437,1,1,(TAG_OFFENSIVE)},
    {586,-1,1,(TAG_OFFENSIVE)},
    {592,4,1,(TAG_OFFENSIVE)},
    {599,3,1,(TAG_OFFENSIVE)},
    {589,3,1,(TAG_NOLOSTBR)},
    {-1,0,1,0},
    {-1,0,1,0},
    {464,3,0,(TAG_OFFENSIVE)},
    {596,2,0,(TAG_OFFENSIVE)},
    {-1,-1,0,0},
    {465,1,1,(TAG_OFFENSIVE)},
    {459,2,1,(TAG_OFFENSIVE)},
    {500,0,0,(TAG_OFFENSIVE)},
    {600,2,1,(TAG_OFFENSIVE)},
    {584,4,1,(TAG_OFFENSIVE)},
    {585,2,0,(TAG_NOLOSTBR)},
    {588,0,0,(TAG_OFFENSIVE)},
    {591,1,0,(TAG_OFFENSIVE)},
    {594,1,0,(TAG_OFFENSIVE)},
    {595,3,1,(TAG_OFFENSIVE)},
    {598,1,1,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,2,0,(TAG_OFFENSIVE)},
    {-1,3,0,(TAG_OFFENSIVE)},
    {-1,-1,0,0},
};


struct ItemConfigData* GetItemConfig(int item_id){
    return &item_config_datas[item_id];
}

