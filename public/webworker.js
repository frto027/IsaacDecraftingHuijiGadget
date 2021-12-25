//对item_array进行桶排序
function bucket_sort_list_toint64(item_array) {
    //@debug-only
    console.assert(item_array.length == 8);

    let item_count = [];

    //initial value
    for (let i = 0; i < 0x1f; i++) {
        item_count[i] = 0;
    }

    item_count[item_array[0]]++;
    item_count[item_array[1]]++;
    item_count[item_array[2]]++;
    item_count[item_array[3]]++;
    item_count[item_array[4]]++;
    item_count[item_array[5]]++;
    item_count[item_array[6]]++;
    item_count[item_array[7]]++;

    let offset = BigInt(0);

    let v12 = BigInt(0); // v12 is 64 bit
    for (let i = BigInt(0); i < BigInt(0x1f); i++) {
        for (let j = 0; j < item_count[i]; j++) {
            //此代码一定会执行8遍
            v12 |= i << offset;
            offset += BigInt(8);
        }
    }
    //v12 = 0x08 07 06 05 04 03 02 01
    return v12;
}

//游戏中的随机数字生成器
let rng_offsets = [
    0x00000001, 0x00000005, 0x00000010, 0x00000001, 0x00000005, 0x00000013,
    0x00000001, 0x00000009, 0x0000001d, 0x00000001, 0x0000000b, 0x00000006,
    0x00000001, 0x0000000b, 0x00000010, 0x00000001, 0x00000013, 0x00000003,
    0x00000001, 0x00000015, 0x00000014, 0x00000001, 0x0000001b, 0x0000001b,
    0x00000002, 0x00000005, 0x0000000f, 0x00000002, 0x00000005, 0x00000015,
    0x00000002, 0x00000007, 0x00000007, 0x00000002, 0x00000007, 0x00000009,
    0x00000002, 0x00000007, 0x00000019, 0x00000002, 0x00000009, 0x0000000f,
    0x00000002, 0x0000000f, 0x00000011, 0x00000002, 0x0000000f, 0x00000019,
    0x00000002, 0x00000015, 0x00000009, 0x00000003, 0x00000001, 0x0000000e,
    0x00000003, 0x00000003, 0x0000001a, 0x00000003, 0x00000003, 0x0000001c,
    0x00000003, 0x00000003, 0x0000001d, 0x00000003, 0x00000005, 0x00000014,
    0x00000003, 0x00000005, 0x00000016, 0x00000003, 0x00000005, 0x00000019,
    0x00000003, 0x00000007, 0x0000001d, 0x00000003, 0x0000000d, 0x00000007,
    0x00000003, 0x00000017, 0x00000019, 0x00000003, 0x00000019, 0x00000018,
    0x00000003, 0x0000001b, 0x0000000b, 0x00000004, 0x00000003, 0x00000011,
    0x00000004, 0x00000003, 0x0000001b, 0x00000004, 0x00000005, 0x0000000f,
    0x00000005, 0x00000003, 0x00000015, 0x00000005, 0x00000007, 0x00000016,
    0x00000005, 0x00000009, 0x00000007, 0x00000005, 0x00000009, 0x0000001c,
    0x00000005, 0x00000009, 0x0000001f, 0x00000005, 0x0000000d, 0x00000006,
    0x00000005, 0x0000000f, 0x00000011, 0x00000005, 0x00000011, 0x0000000d,
    0x00000005, 0x00000015, 0x0000000c, 0x00000005, 0x0000001b, 0x00000008,
    0x00000005, 0x0000001b, 0x00000015, 0x00000005, 0x0000001b, 0x00000019,
    0x00000005, 0x0000001b, 0x0000001c, 0x00000006, 0x00000001, 0x0000000b,
    0x00000006, 0x00000003, 0x00000011, 0x00000006, 0x00000011, 0x00000009,
    0x00000006, 0x00000015, 0x00000007, 0x00000006, 0x00000015, 0x0000000d,
    0x00000007, 0x00000001, 0x00000009, 0x00000007, 0x00000001, 0x00000012,
    0x00000007, 0x00000001, 0x00000019, 0x00000007, 0x0000000d, 0x00000019,
    0x00000007, 0x00000011, 0x00000015, 0x00000007, 0x00000019, 0x0000000c,
    0x00000007, 0x00000019, 0x00000014, 0x00000008, 0x00000007, 0x00000017,
    0x00000008, 0x00000009, 0x00000017, 0x00000009, 0x00000005, 0x0000000e,
    0x00000009, 0x00000005, 0x00000019, 0x00000009, 0x0000000b, 0x00000013,
    0x00000009, 0x00000015, 0x00000010, 0x0000000a, 0x00000009, 0x00000015,
    0x0000000a, 0x00000009, 0x00000019, 0x0000000b, 0x00000007, 0x0000000c,
    0x0000000b, 0x00000007, 0x00000010, 0x0000000b, 0x00000011, 0x0000000d,
    0x0000000b, 0x00000015, 0x0000000d, 0x0000000c, 0x00000009, 0x00000017,
    0x0000000d, 0x00000003, 0x00000011, 0x0000000d, 0x00000003, 0x0000001b,
    0x0000000d, 0x00000005, 0x00000013, 0x0000000d, 0x00000011, 0x0000000f,
    0x0000000e, 0x00000001, 0x0000000f, 0x0000000e, 0x0000000d, 0x0000000f,
    0x0000000f, 0x00000001, 0x0000001d, 0x00000011, 0x0000000f, 0x00000014,
    0x00000011, 0x0000000f, 0x00000017, 0x00000011, 0x0000000f, 0x0000001a,
];

function RNG_Next(num, offset_id) {
    let offset_a = rng_offsets[offset_id * 3];
    let offset_b = rng_offsets[offset_id * 3 + 1];
    let offset_c = rng_offsets[offset_id * 3 + 2];
    num = num ^ ((num >>> offset_a) & 0xffffffff);
    num = num ^ ((num << offset_b) & 0xffffffff);
    num = num ^ ((num >>> offset_c) & 0xffffffff);
    return num >>> 0; /* to unsigned */
}

/* 道具池和品质的数据经过压缩，压缩算法参考github文件compress.js */
let item_pool_data = [];
let item_config_data = {};

/* 解压缩 */
var compressed =
    '{"item_pool_data_compressed":[{"1":[1,2,3,4,5,6,7,8,10,13,14,15,19,36,37,38,39,40,41,42,44,45,46,47,48,49,52,53,55,56,57,58,62,65,66,67,68,69,71,72,75,76,77,78,85,86,87,88,89,91,92,93,94,95,96,97,99,100,102,103,104,105,106,107,108,109,110,111,113,115,117,120,121,123,124,125,127,128,129,131,136,137,138,140,142,143,144,146,148,149,150,151,152,153,154,155,157,160,161,162,163,166,167,169,170,171,172,173,174,175,176,178,180,186,188,189,191,192,200,201,202,206,209,210,211,213,214,217,220,221,222,224,225,227,228,229,231,233,234,236,240,242,244,245,256,257,261,264,265,266,267,268,269,270,271,272,273,274,275,276,277,278,279,280,281,282,283,284,285,287,288,291,292,294,295,298,299,300,301,302,303,304,305,306,307,308,309,310,312,314,315,316,317,318,319,320,321,322,323,324,325,329,330,332,336,350,351,352,353,358,359,361,362,364,365,366,367,368,369,371,373,375,377,378,379,381,382,384,385,386,388,389,390,391,392,393,394,395,397,398,401,404,405,406,407,410,411,418,419,421,422,426,427,430,431,432,435,436,437,440,443,444,445,446,447,448,449,452,453,454,457,458,459,460,461,463,465,466,467,469,470,471,473,476,478,481,482,485,488,491,492,493,494,495,496,497,502,504,506,507,508,509,511,512,513,516,517,522,524,525,529,531,532,537,539,540,542,543,544,545,548,549,553,555,557,558,559,560,561,563,565,570,575,576,578,581,583,605,607,608,610,611,612,614,615,616,617,618,629,631,635,637,639,641,645,649,652,655,657,658,661,663,671,675,676,678,680,681,682,683,687,690,693,695,709,710,713,717,720,722,724,725,726,727,729],"0.5":[12,101,223,609,650,703,728],"0.1":[17,190,625,723],"0.2":[98,114,237,313,333,334,335,374,677]},{"1":[21,33,54,60,63,64,75,85,102,116,137,139,147,156,164,177,195,199,203,204,205,208,227,232,246,247,248,249,250,251,252,260,289,290,295,296,297,337,338,347,348,349,356,357,372,376,380,383,396,403,414,416,422,425,434,439,451,472,479,480,486,487,505,514,515,518,520,521,523,527,534,535,566,585,599,602,603,604,619,621,623,624,638,647,670,716],"0.2":[286,475],"0.5":[402,424,483,485,660,719],"0.1":[642]},{"1":[14,22,23,24,25,26,27,28,29,30,31,32,51,70,141,143,165,176,183,193,194,195,196,197,198,218,219,240,253,254,255,339,340,341,342,343,344,345,346,354,355,370,438,455,456,538,541,547,564,600,624,644,659,707,708,730,731],"0.5":[92,428]},{"1":[8,34,35,51,67,74,79,80,81,82,83,84,97,109,113,114,115,118,122,123,126,133,134,145,157,159,163,172,187,212,215,216,225,230,237,241,259,262,268,269,275,278,292,311,360,391,399,408,409,411,412,417,420,431,433,442,462,468,498,519,526,530,536,545,554,556,569,572,577,606,634,646,654,665,672,679,684,692,695,698,699,702,728],"0.2":[127,441,475],"0.5":[477,694,704,705,706,712]},{"1":[7,33,72,98,101,108,112,124,142,146,156,162,173,178,182,184,185,243,313,326,331,332,333,334,335,363,374,387,390,400,413,415,423,464,490,498,499,519,526,528,533,543,567,568,573,574,579,586,601,622,634,640,643,651,653,685,686,696],"0.5":[477,584,691],"0.4":[510]},{"1":[11,16,17,20,35,84,120,121,127,168,190,213,226,242,258,262,263,271,286,287,316,321,348,388,389,402,405,424,450,489,500,501,546,562,571,580,582,609,612,625,628,632,636,664,667,669,674,675,677,688,689,700,701,703,711,716,717,719,721,723],"0.5":[691,697]},null,{"1":[9,36,209,378,504,576]},{"1":[28,29,32,74,194,196,255,341,343,344,354,355,370,438,455,456,644,708,730,732],"0.5":[179,428,534],"0.1":[444,571]},{"1":[81,133,134,140,145,212,297,316,371,642,665],"0.1":[475,580],"0.5":[565],"0.2":[654]},null,null,{"1":[51,79,80,81,133,134,145,212,215,216,225,241,260,371,408,442,451,468,496,503,508,536,565,569,580,642,692,702,711],"0.2":[475],"0.5":[654,694,697]},null,null,null,null,null,null,null,null,null,null,null,null,null,{"1":[588,589,590,591,592,593,594,595,596,597,598]}],"item_config_data_compressed":{"0":[5,9,19,36,40,41,44,59,84,111,117,126,141,144,148,177,180,186,188,233,238,239,262,274,276,285,287,290,315,316,319,323,326,386,388,391,426,433,447,468,470,474,475,481,482,497,504,508,605,615,626,627,633,668,714,715],"1":[8,22,23,24,25,26,27,28,29,30,31,33,35,37,39,42,45,47,53,55,56,60,62,65,66,67,74,77,86,87,88,94,95,100,102,103,123,124,128,129,135,136,137,140,147,161,162,163,167,171,174,175,176,187,192,194,195,198,200,204,205,210,211,214,227,236,240,250,252,256,258,267,269,270,272,273,277,280,281,282,288,291,294,295,298,299,302,304,308,314,318,321,325,332,337,339,340,344,346,349,351,352,357,358,364,365,366,367,368,371,377,383,385,392,394,396,398,400,403,404,405,408,413,420,421,427,430,435,436,437,442,445,446,448,449,456,467,469,472,473,478,484,485,486,488,493,498,501,502,505,506,509,510,511,512,517,522,523,525,537,539,541,543,548,560,561,563,565,578,582,599,602,603,607,610,623,624,631,635,644,645,649,652,655,658,659,672,675,681,692,707],"2":[2,6,10,11,13,14,15,16,21,34,38,46,49,54,57,63,64,71,72,73,75,76,85,89,91,92,93,96,97,99,101,106,107,112,113,115,116,119,120,121,122,125,130,131,134,138,142,143,152,154,155,156,160,164,166,172,181,191,193,197,202,206,207,209,212,213,218,219,220,222,225,226,228,229,231,242,246,247,248,251,253,254,257,263,264,266,271,279,286,289,293,296,297,300,303,309,310,312,320,322,324,327,328,329,330,338,343,348,353,354,355,361,362,369,376,378,379,380,382,384,393,401,406,407,409,410,412,416,418,423,425,428,429,431,432,434,440,450,452,453,454,455,457,460,463,464,465,466,471,480,487,491,492,507,513,514,516,518,519,521,526,529,530,532,533,535,536,538,540,542,544,554,555,557,558,559,566,568,569,571,574,576,577,583,585,588,589,591,593,594,595,604,608,611,612,614,618,621,622,632,634,638,639,641,642,647,650,654,656,657,661,663,665,667,670,671,673,674,676,677,683,685,686,688,693,700,702,703,717,719,720,721,725,727,729,731],"3":[1,3,7,17,18,20,32,48,50,51,58,68,69,70,78,79,80,81,82,83,90,104,109,110,127,132,133,139,145,146,150,151,153,157,158,159,165,170,173,178,179,183,184,185,189,190,196,199,201,203,208,215,216,217,221,224,230,237,241,243,244,249,255,259,260,265,268,275,278,283,284,301,305,306,307,311,317,333,334,335,336,341,342,345,347,350,356,359,363,370,372,373,374,375,381,387,389,390,397,402,411,414,417,419,422,424,438,439,443,444,451,458,459,461,462,476,479,483,490,494,495,496,499,500,503,515,520,524,527,528,531,534,545,546,547,549,553,556,562,564,567,570,572,573,575,579,580,584,586,590,592,596,597,598,600,601,606,609,616,617,619,629,637,640,646,651,653,660,669,679,680,682,684,687,690,694,695,696,697,699,701,704,705,708,709,712,713,716,722,724,726,728,730,732],"4":[4,12,52,98,105,108,114,118,149,168,169,182,223,232,234,245,261,292,313,331,360,395,399,415,441,477,489,550,551,552,581,625,628,636,643,664,678,689,691,698,706,710,711,723]},"id_with_achievement":["20","32","35","52","73","74","78","83","86","87","88","90","92","93","94","96","97","98","99","100","101","104","105","106","110","112","113","114","119","126","127","131","149","157","162","164","166","168","172","175","179","186","187","188","189","206","207","221","230","232","237","240","244","246","249","252","258","260","263","267","271","276","283","284","286","287","289","292","293","294","297","310","311","312","319","320","321","323","324","325","327","328","331","332","333","334","335","349","357","360","361","362","363","381","386","387","388","389","391","392","393","399","404","405","406","407","408","409","410","411","412","413","414","416","417","433","440","441","442","450","453","455","462","464","468","470","472","475","476","477","479","485","486","488","489","490","496","498","499","500","501","504","510","511","512","513","514","515","516","517","518","519","520","521","522","523","524","525","526","527","528","529","530","531","532","533","534","535","536","537","538","539","540","541","542","543","544","545","546","547","548","549","555","562","565","568","576","577","579","580","584","585","586","602","609","610","611","612","619","621","622","625","628","631","634","639","640","641","642","643","645","646","649","650","651","653","656","665","667","670","671","672","673","674","675","676","677","678","679","680","681","682","683","684","685","686","687","688","689","690","691","692","693","694","695","696","697","698","699","700","701","702","703","704","705","706","709","710","711","712","713","716","717","719","720","721","722","723","724","725","726","727","728","729"]}';
compressed = JSON.parse(compressed);
let item_pool_data_compressed = compressed.item_pool_data_compressed;
for (let i = 0; i < item_pool_data_compressed.length; i++) {
    let item_pool = [];
    let item_pool_compressed = item_pool_data_compressed[i];
    for (let weight in item_pool_compressed) {
        for (let j = 0; j < item_pool_compressed[weight].length; j++) {
            let id = item_pool_compressed[weight][j];
            item_pool.push({ id: id, weight: weight });
        }
    }

    item_pool_data[i] = item_pool;
}
let item_config_data_compressed = compressed.item_config_data_compressed;

for (let quality in item_config_data_compressed) {
    for (let i = 0; i < item_config_data_compressed[quality].length; i++) {
        let id = item_config_data_compressed[quality][i];
        item_config_data[id] = { quality: quality };
    }
}

for (let i = 0; i < compressed.id_with_achievement.length; i++) {
    let id = compressed.id_with_achievement[i];
    item_config_data[id].achievement_id = true;
}
/* 解压完毕 */

function GetItemPoolData(item_pool_id) {
    return item_pool_data[item_pool_id];
}
function GetItemConfig(item_id) {
    return item_config_data[item_id];
}
//预先确定的配方
let recipe_predefine_list = [
    { input: BigInt("0x0101010101010101"), output: 0x2d },
    { input: BigInt("0x0808080808080808"), output: 0xb1 },
    { input: BigInt("0x1D1D1D1D1D1D1D1D"), output: 0x24 },
    { input: BigInt("0x0202020202020202"), output: 0x2ae },
    { input: BigInt("0x1515151515151515"), output: 0x55 },
    { input: BigInt("0x1919191919191919"), output: 0x244 },
    { input: BigInt("0x0404040404040404"), output: 0xb6 },
    { input: BigInt("0x0F0F0F0F0F0F0F0F"), output: 0x25 },
    { input: BigInt("0x1616161616161616"), output: 0x4b },
    { input: BigInt("0x1818181818181818"), output: 0x1e9 },
    { input: BigInt("0x0303030303030303"), output: 0x76 },
    { input: BigInt("0x0606060606060606"), output: 0x274 },
    { input: BigInt("0x0C0C0C0C0C0C0C0C"), output: 0x157 },
    { input: BigInt("0x0101010101010101"), output: 0x1e3 },
    { input: BigInt("0x1616161616161603"), output: 0x28e },
    { input: BigInt("0x0504040404040201"), output: 0x14b },
    { input: BigInt("0x0707010101010101"), output: 0x27f },
    { input: BigInt("0x0D0D0C0C0C0C0C0C"), output: 0xaf },
    { input: BigInt("0x10100F0F0F0F0F0F"), output: 0x1e3 },
];

//input_array是长度为8的数组，表示配方，gameStartSeed是一个32位随机数字，需要用str2seed计算
function get_result(input_array, gameStartSeed, craftable_arr) {
    let sorted_items = bucket_sort_list_toint64(input_array);

    //先过滤预先确定好的配方
    for (let i = 0; i < recipe_predefine_list.length; i++) {
        if (recipe_predefine_list[i].input == sorted_items)
            return recipe_predefine_list[i].output;
    }

    //然后是游戏中的算法,后面这段没必要看懂，因为是从游戏里抄出来的，总之它返回道具id
    let item_count = [];
    for (let i = 0; i < 0x1f; i++) {
        item_count[i] = 0;
    }
    item_count[input_array[0]]++;
    item_count[input_array[1]]++;
    item_count[input_array[2]]++;
    item_count[input_array[3]]++;
    item_count[input_array[4]]++;
    item_count[input_array[5]]++;
    item_count[input_array[6]]++;
    item_count[input_array[7]]++;

    let score_matrix = [
        0x00000000, 0x00000001, 0x00000004, 0x00000005, 0x00000005, 0x00000005,
        0x00000005, 0x00000001, 0x00000001, 0x00000003, 0x00000005, 0x00000008,
        0x00000002, 0x00000007, 0x00000005, 0x00000002, 0x00000007, 0x0000000a,
        0x00000002, 0x00000004, 0x00000008, 0x00000002, 0x00000002, 0x00000004,
        0x00000004, 0x00000002, 0x00000007, 0x00000007, 0x00000007, 0x00000000,
        0x00000001,
    ];

    let item_score_sum =
        score_matrix[input_array[0]] +
        score_matrix[input_array[1]] +
        score_matrix[input_array[2]] +
        score_matrix[input_array[3]] +
        score_matrix[input_array[4]] +
        score_matrix[input_array[5]] +
        score_matrix[input_array[6]] +
        score_matrix[input_array[7]];

    // console.log("item score sum = " + item_score_sum)
    let weight_list = [
        { id: 0, weight: 1.0 },
        { id: 1, weight: 2.0 },
        { id: 2, weight: 2.0 },
        { id: 4, weight: item_count[4] * 10.0 },
        { id: 3, weight: item_count[3] * 10.0 },
        { id: 5, weight: item_count[6] * 5.0 },
        { id: 8, weight: item_count[5] * 10.0 },
        { id: 12, weight: item_count[7] * 10.0 },
        { id: 9, weight: item_count[25] * 10.0 },
        { id: 7, weight: item_count[29] * 10.0 },
    ];
    if (item_count[15] + item_count[12] + item_count[8] + item_count[1] == 0) {
        weight_list.push({ id: 26, weight: item_count[23] * 10.0 });
    }
    if (gameStartSeed == 0) {
        throw "Error";
    }

    let currentSeed = gameStartSeed;

    for (let item_i = 0; item_i < 0x1f; item_i++) {
        for (let j = 0; j < item_count[item_i]; j++) {
            currentSeed = RNG_Next(currentSeed, item_i);
        }
    }
    // console.log(currentSeed)
    let collectible_count = 733; // it equals to some_variable_a - some_variable_b

    let collectible_list = [];
    for (let i = 0; i < collectible_count; i++) {
        collectible_list[i] = 0.0;
    }

    let all_weight = 0.0;
    // console.log(weight_list)
    if (weight_list.length > 0) {
        for (
            let weight_select_i = 0;
            weight_select_i < weight_list.length;
            weight_select_i++
        ) {
            if (weight_list[weight_select_i].weight <= 0.0) {
                continue;
            }
            let score = item_score_sum;
            if (
                weight_list[weight_select_i].id == 4 ||
                weight_list[weight_select_i].id == 3 ||
                weight_list[weight_select_i].id == 5
            ) {
                score -= 5;
            }

            let quality_min = 0;
            let quality_max = 1;
            if (score > 34) {
                quality_max = 4;
                quality_min = 4;
            } else if (score > 30) {
                quality_max = 4;
                quality_min = 3;
            } else if (score > 26) {
                quality_max = 4;
                quality_min = 3;
            } else if (score > 22) {
                quality_max = 4;
                quality_min = 2;
            } else if (score > 18) {
                quality_max = 3;
                quality_min = 2;
            } else if (score > 14) {
                quality_min = 1;
                quality_max = 2;
            } else if (score > 8) {
                quality_min = 0;
                quality_max = 2;
            }

            let item_pools = GetItemPoolData(weight_list[weight_select_i].id);
            for (
                let item_pool_i = 0;
                item_pool_i < item_pools.length;
                item_pool_i++
            ) {
                let item_config = undefined;
                let item_id = item_pools[item_pool_i].id
                if (item_id >= 0) {
                    if (item_id >= collectible_count) {
                        item_config = undefined;
                    } else {
                        item_config = GetItemConfig(item_id);
                    }
                }
                let item_quality =
                    0 +
                    item_config.quality; /* there is not a zero, but a var from item_config, which is always zero when i'm testing */
                if (item_quality >= quality_min && item_quality <= quality_max) {
                    //be careful:the game use float instead of double, so js in not accurate!!!
                    let item_weight =
                        item_pools[item_pool_i].weight *
                        weight_list[weight_select_i].weight;
                    all_weight += item_weight;
                    // console.log(all_weight)
                    collectible_list[item_id] += item_weight;
                    if (craftable_arr && item_weight > 0) {
                        craftable_arr[item_id] = true
                    }
                }
            }
        }
    }
    // let retry_count = 0

    let selected;
    // let output = []
    for (; ;) {
        currentSeed = RNG_Next(currentSeed, 6);
        //use float instead!!!
        let remains = Number(currentSeed) * 2.3283062e-10 * all_weight;
        // console.log(remains)
        selected = 25;
        for (
            let current_select = 0;
            current_select < collectible_count;
            current_select++
        ) {
            // console.log(collectible_list[current_select])
            if (collectible_list[current_select] > remains) {
                selected = current_select;
                break;
            }
            remains -= collectible_list[current_select];
        }

        //默认全解锁
        return selected;
    }
}

function search_dfs(
    ids,
    max_use_count,
    current,
    callback,
    ids_i = 0,
    current_i = 0
) {
    if (current.length == current_i) {
        callback(current);
        //no more space
        return;
    }
    if (ids.length == ids_i) {
        //no more recipe
        return;
    }
    let max_consume = max_use_count[ids_i];
    if (current.length - current_i < max_consume)
        max_consume = current.length - current_i;

    for (let i = 0; i < max_consume; i++) {
        current[current_i + i] = ids[ids_i];
    }
    for (let i = max_consume; i >= 0; i--) {
        search_dfs(ids, max_use_count, current, callback, ids_i + 1, current_i + i);
    }
}

onmessage = function(event){
    let data = event.data
    if(data.cmd == 'start'){

        let items = [];

        let craftable_arr = []
        for(let i=0;i<800;i++){
          craftable_arr[i] = false
        }
  
        let watcher_counter = 0

        search_dfs(
            data.candidates,
            data.candidates_limit,
            [0, 0, 0, 0, 0, 0, 0, 0],
            (arr) => {
              if (arr.length != 8) {
                console.log("ERROR!");
              }
              let result = get_result(arr, data.seed, craftable_arr);
              if (items[result] == undefined) {
                items[result] = [];
                for (let i = 0; i < 8; i++) {
                  items[result][i] = arr[i];
                }
              }
              if((++watcher_counter) % 1000 == 0){
                this.postMessage({
                    cmd:"report",
                    items:items,
                    craftable_arr:craftable_arr,
                    count:watcher_counter
                })
              }

            }
          );
        this.postMessage({
            cmd:"result",
            items:items,
            craftable_arr:craftable_arr,
            count:watcher_counter
        })
    }
}