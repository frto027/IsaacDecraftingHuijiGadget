#include <stdio.h>

#ifdef USE_EMCC
#include <emscripten/emscripten.h>
#endif

#include "item_data.h"
unsigned int rng_offsets[] = {
    0x00000001, 0x00000005, 0x00000010, 0x00000001, 0x00000005, 0x00000013, 0x00000001, 0x00000009,
    0x0000001D, 0x00000001, 0x0000000B, 0x00000006, 0x00000001, 0x0000000B, 0x00000010, 0x00000001,
    0x00000013, 0x00000003, 0x00000001, 0x00000015, 0x00000014, 0x00000001, 0x0000001B, 0x0000001B,
    0x00000002, 0x00000005, 0x0000000F, 0x00000002, 0x00000005, 0x00000015, 0x00000002, 0x00000007,
    0x00000007, 0x00000002, 0x00000007, 0x00000009, 0x00000002, 0x00000007, 0x00000019, 0x00000002,
    0x00000009, 0x0000000F, 0x00000002, 0x0000000F, 0x00000011, 0x00000002, 0x0000000F, 0x00000019,
    0x00000002, 0x00000015, 0x00000009, 0x00000003, 0x00000001, 0x0000000E, 0x00000003, 0x00000003,
    0x0000001A, 0x00000003, 0x00000003, 0x0000001C, 0x00000003, 0x00000003, 0x0000001D, 0x00000003,
    0x00000005, 0x00000014, 0x00000003, 0x00000005, 0x00000016, 0x00000003, 0x00000005, 0x00000019,
    0x00000003, 0x00000007, 0x0000001D, 0x00000003, 0x0000000D, 0x00000007, 0x00000003, 0x00000017,
    0x00000019, 0x00000003, 0x00000019, 0x00000018, 0x00000003, 0x0000001B, 0x0000000B, 0x00000004,
    0x00000003, 0x00000011, 0x00000004, 0x00000003, 0x0000001B, 0x00000004, 0x00000005, 0x0000000F,
    0x00000005, 0x00000003, 0x00000015, 0x00000005, 0x00000007, 0x00000016, 0x00000005, 0x00000009,
    0x00000007, 0x00000005, 0x00000009, 0x0000001C, 0x00000005, 0x00000009, 0x0000001F, 0x00000005,
    0x0000000D, 0x00000006, 0x00000005, 0x0000000F, 0x00000011, 0x00000005, 0x00000011, 0x0000000D,
    0x00000005, 0x00000015, 0x0000000C, 0x00000005, 0x0000001B, 0x00000008, 0x00000005, 0x0000001B,
    0x00000015, 0x00000005, 0x0000001B, 0x00000019, 0x00000005, 0x0000001B, 0x0000001C, 0x00000006,
    0x00000001, 0x0000000B, 0x00000006, 0x00000003, 0x00000011, 0x00000006, 0x00000011, 0x00000009,
    0x00000006, 0x00000015, 0x00000007, 0x00000006, 0x00000015, 0x0000000D, 0x00000007, 0x00000001,
    0x00000009, 0x00000007, 0x00000001, 0x00000012, 0x00000007, 0x00000001, 0x00000019, 0x00000007,
    0x0000000D, 0x00000019, 0x00000007, 0x00000011, 0x00000015, 0x00000007, 0x00000019, 0x0000000C,
    0x00000007, 0x00000019, 0x00000014, 0x00000008, 0x00000007, 0x00000017, 0x00000008, 0x00000009,
    0x00000017, 0x00000009, 0x00000005, 0x0000000E, 0x00000009, 0x00000005, 0x00000019, 0x00000009,
    0x0000000B, 0x00000013, 0x00000009, 0x00000015, 0x00000010, 0x0000000A, 0x00000009, 0x00000015,
    0x0000000A, 0x00000009, 0x00000019, 0x0000000B, 0x00000007, 0x0000000C, 0x0000000B, 0x00000007,
    0x00000010, 0x0000000B, 0x00000011, 0x0000000D, 0x0000000B, 0x00000015, 0x0000000D, 0x0000000C,
    0x00000009, 0x00000017, 0x0000000D, 0x00000003, 0x00000011, 0x0000000D, 0x00000003, 0x0000001B,
    0x0000000D, 0x00000005, 0x00000013, 0x0000000D, 0x00000011, 0x0000000F, 0x0000000E, 0x00000001,
    0x0000000F, 0x0000000E, 0x0000000D, 0x0000000F, 0x0000000F, 0x00000001, 0x0000001D, 0x00000011,
    0x0000000F, 0x00000014, 0x00000011, 0x0000000F, 0x00000017, 0x00000011, 0x0000000F, 0x0000001A};


class RNG {
private:
    unsigned int seed;
    int offset;
public:
    inline void setOffset(int offset){
        this->offset = offset;
    }
    inline void setSeed(unsigned int seed) {
        this->seed = seed;
    }

    inline unsigned int nextInt() {
        unsigned int a = rng_offsets[offset*3],b = rng_offsets[offset*3+1],c = rng_offsets[offset*3+2];
        seed = seed ^ (seed >> a) ^ ((seed ^ (seed >> a)) << b) ^ ((seed ^ (seed >> a) ^ ((seed ^ (seed >> a)) << b)) >> c);
        return seed;
    }

    inline float nextFloat() {
        return 2.3283062e-10f * nextInt();
    }
};


int safe_is_daily_run = 0;
int safe_is_greed = 0;
int safe_challenge_id = 0;
int safe_current_stage = 1;
int safe_has_keeper = 0;
int safe_has_lost = 0;
int safe_has_tlost = 0;
int safe_game_start_seed = 0;
int safe_has_c691 = 0;
int safe_has_t88 = 0;


int IsSafeToGenerageA(ItemConfigData*config, int item_id){
    int tags = config->tags;
    if(safe_challenge_id && (tags & TAG_NOCHALLENGE))
        return 0;
    if(safe_is_daily_run && (tags & TAG_NODAILY))
        return 0;
    if(safe_is_greed && (tags & TAG_NOGREED))
        return 0;
    return 1;
}
int IsSafeToGenerageB(ItemConfigData*config, int item_id){
    int tags = config->tags;
    if((!safe_is_greed) && safe_current_stage >= 7 && item_id == 697)
        return 0;
    if(safe_has_keeper && (tags & TAG_NOKEEPER))
        return 0;
    if(safe_has_lost && (tags & TAG_NOLOSTBR))
        return 0;
    if(safe_has_tlost){
        if(!(tags & TAG_OFFENSIVE))
            return 0;
        if(config->quality < 2){
            //do something...
            RNG rng;
            rng.setSeed(safe_game_start_seed + item_id);
            rng.setOffset(17);
            if(rng.nextInt() % 5 == 0){
                return 0;
            }
        }
    }
    if(safe_has_c691){
        if(config->quality < 2)
            return 0;
        if(config->quality == 2){
            RNG rng;
            rng.setSeed(safe_game_start_seed + item_id);
            rng.setOffset(18);

            if(rng.nextInt() % 3 == 0){
                return 0;
            }
        }
    }
    if(safe_has_t88 && config->quality == 0)
        return 0;
    return 1;
}

#define uint64 unsigned long long
#define ASSERT(x) do{}while(0)
struct{
    uint64 input;
    unsigned int output;
}predefined_recipes[] = {
    {0x0101010101010101, 0x2D},
    {0x0808080808080808, 0xB1},
    {0x1D1D1D1D1D1D1D1D, 0x24},
    {0x0202020202020202, 0x2AE},
    {0x1515151515151515, 0x55},
    {0x1919191919191919, 0x244},
    {0x0404040404040404, 0xB6},
    {0x0F0F0F0F0F0F0F0F, 0x6A},
    {0x1616161616161616, 0x4B},
    {0x1818181818181818, 0x1E9},
    {0x0303030303030303, 0x76},
    {0x0606060606060606, 0x274},
    {0x0C0C0C0C0C0C0C0C, 0x157},
    {0x1111111111111111, 0x1E3},
    {0x1616161616161603, 0x28E},
    {0x0504040404040201, 0x14B},
    {0x0707010101010101, 0x27F},
    {0x0D0D0C0C0C0C0C0C, 0xAF},
    {0x10100F0F0F0F0F0F, 0x1E3},
};

uint64 bucket_sort_list_toint64(unsigned char recipes[8]){
    int item_count[0x1F] = {0};
    for(int i=0;i<8;i++){
        ASSERT(recipes[i]<0x1F);
        item_count[recipes[i]]++;
    }
    uint64 result = 0;
    int offset = 0;
    for(int i=0;i<0x1F;i++){
        for(int j=0;j<item_count[i];j++){
            result |= ((uint64)i)<<offset;
            offset += 8;
        }
    }
    return result;
}

int AchievementUnlocked(int aid){
    if(aid <= 0){
        return 1;
    }
    return 1;
}

int calc(unsigned int seed, unsigned char recipes[8]){
    safe_game_start_seed = seed;

    uint64 sorted_items = bucket_sort_list_toint64(recipes);
    for(int i=0;i<sizeof(predefined_recipes)/sizeof(*predefined_recipes);i++){
        if(sorted_items == predefined_recipes[i].input)
            return predefined_recipes[i].output;
    }

    int item_count[0x1F] = {0};
    for(int i=0;i<8;i++){
        ASSERT(recipes[i]<0x1F);
        item_count[recipes[i]]++;
    }

    int score_matrix[] = {
            0x00000000, 0x00000001, 0x00000004, 0x00000005, 0x00000005, 0x00000005, 0x00000005,
            0x00000001, 0x00000001, 0x00000003, 0x00000005, 0x00000008, 0x00000002, 0x00000007, 
            0x00000005, 0x00000002, 0x00000007, 0x0000000A, 0x00000002, 0x00000004, 0x00000008, 
            0x00000002, 0x00000002, 0x00000004, 0x00000004, 0x00000002, 0x00000007, 0x00000007, 
            0x00000007, 0x00000000, 0x00000001
    };

    int item_score_sum = 
        score_matrix[recipes[0]] + 
        score_matrix[recipes[1]] + 
        score_matrix[recipes[2]] + 
        score_matrix[recipes[3]] + 
        score_matrix[recipes[4]] + 
        score_matrix[recipes[5]] + 
        score_matrix[recipes[6]] + 
        score_matrix[recipes[7]];

    struct{
        int id;float weight;
    }weight_list[] = {
        {0,1.0},
        {1,2.0},
        {2,2.0},
        {4,item_count[4] * 10.0f},
        {3,item_count[3] * 10.0f},
        {5,item_count[6] * 5.0f},
        {8,item_count[5] * 10.0f},
        {12,item_count[7] * 10.0f},
        {9,item_count[25] * 10.0f},
        {7,item_count[29] * 10.0f},
        {26,item_count[23]*10.0f}, // placeholder
    };

    int weight_list_length;

    if(item_count[15] + item_count[12] + item_count[8] + item_count[1] == 0){
        weight_list_length = 11;
    }else{
        weight_list_length = 10;
    }

    ASSERT(seed != 0);

    RNG rng;
    rng.setSeed(seed);
    for(int item_i=0;item_i<0x1F;item_i++){
        for(int j=0;j<item_count[item_i];j++){
            rng.setOffset(item_i);
            rng.nextInt();
        }
    }

    int collectible_count = 733;
    
    float collectible_list[1000];
    for(int i=0;i<collectible_count;i++)
        collectible_list[i]=0;

    float all_weight = 0;

    for(int weight_select_i=0;weight_select_i<weight_list_length;weight_select_i++){
        auto & witem = weight_list[weight_select_i];
        if(witem.weight <=0)
            continue;
        int score = item_score_sum;
        if(witem.id == 4 || witem.id == 3 || witem.id == 5)
            score -= 5;
        
        int qmin = 0, qmax = 1;
        if ( score > 34 )
        {
            qmax = 4;
            qmin = 4;
        }
        else if ( score > 30 )
        {
            qmax = 4;
            qmin = 3;
        }
        else if ( score > 26 )
        {
            qmax = 4;
            qmin = 3;
        }
        else if ( score > 22 )
        {
            qmax = 4;
            qmin = 2;
        }
        else if ( score > 18 )
        {
            qmax = 3;
            qmin = 2;
        }
        else if ( score > 14 )
        {
            qmin = 1;
            qmax = 2;
        }else if ( score > 8 )
        {
            qmin = 0;
            qmax = 2;
        }

        auto item_pools = GetItemPoolData(witem.id);
        for(int item_pool_i = 0;item_pool_i < item_pools.length;item_pool_i++){
            auto item_config = GetItemConfig(item_pools.datas[item_pool_i].id);
            if(IsSafeToGenerageA(item_config, item_pools.datas[item_pool_i].id) && item_config->quality >= qmin && item_config->quality <= qmax){
                float item_weight = item_pools.datas[item_pool_i].weight * witem.weight;
                all_weight += item_weight;
                collectible_list[item_pools.datas[item_pool_i].id] += item_weight;
            }
        }
    }
    //printf("Item pool weights: %f\n",all_weight);
    int retry_count = 0;
    while(true){
        rng.setOffset(6);
        float remains = rng.nextFloat() * all_weight;
        int selected = 25;
        for(int cur_select = 0;cur_select < collectible_count;cur_select++){
            if(collectible_list[cur_select] > remains){
                selected = cur_select;
                break;
            }else{
                remains -= collectible_list[cur_select];
            }
        }
        ItemConfigData * item_config = GetItemConfig(selected);
        if((IsSafeToGenerageB(item_config, selected) && AchievementUnlocked(item_config->aid)) || ++retry_count >= 20){
            return selected;
        } 
    }
}

extern "C"{
#ifdef USE_EMCC
    unsigned char buff[8];
    EMSCRIPTEN_KEEPALIVE
    unsigned char * getRecipeBuffer(){
        return buff;
    }
    EMSCRIPTEN_KEEPALIVE
    int getResult(unsigned int seed){
        return calc(seed,buff);
    }

    EMSCRIPTEN_KEEPALIVE
    void setSafeArg(
        int a_safe_is_daily_run,
        int a_safe_is_greed,
        int a_safe_challenge_id,
        int a_safe_current_stage,
        int a_safe_has_keeper,
        int a_safe_has_lost,
        int a_safe_has_tlost,
        int a_safe_has_c691,
        int a_safe_has_t88
    ){
        safe_is_daily_run = a_safe_is_daily_run;
        safe_is_greed = a_safe_is_greed;
        safe_challenge_id = a_safe_challenge_id;
        safe_current_stage = a_safe_current_stage;
        safe_has_keeper = a_safe_has_keeper;
        safe_has_lost = a_safe_has_lost;
        safe_has_tlost = a_safe_has_tlost;
        safe_has_c691 = a_safe_has_c691;
        safe_has_t88 = a_safe_has_t88;
    }

}
#endif

// int main(){
//     unsigned char rec[] = {1,1,1,1,6,6,6,6};
//     printf("beg\n");
//     // printf("bucket sort test: %I64X\n",bucket_sort_list_toint64(rec));
//     printf("end\n");
//     for(int i=0;i<30260340;i++){
//         calc(1302889765,rec);
//         // if(i % 1000 == 0){
//         //     printf("%d\n",i);
//         // }
//     }

//     printf("result: %d\n",calc(1302889765,rec));
// }