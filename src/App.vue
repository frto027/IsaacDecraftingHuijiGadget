<template>
  <h1>合成宝袋挖掘器</h1>
  <hr />

  <div>
    <div>
      <div style="margin:1px;text-align:center;">
        <div style="width: 100%;background: var(--brand-primary);padding:10px;font-size:16px;color:#fff;border-radius:4px 4px 0 0">种子</div>
        <input class="form-control" v-model="seed" style="border-radius:0 0 4px 4px" />
      </div>

      <!-- 配方列表 -->
      <div style="background: var(--detail-infobox-bg); margin: 10px 1px">
          <transition-group name="flip-list">
            <template v-for="(item, index) in items" v-bind:key="item.id">
              <div
                v-bind:id="'list_item_' + item.id"

                v-bind:draggable="true"
                @dragstart="begin_drag($event, index), (item.draging = true)"
                @dragover="over_drag($event, index)"
                @dragend="item.draging = false"
                @drop="drop_drag($event, index)"
                @dragleave="
                  () => {
                    if (drag_over_index == index) drag_over_index = -1;
                  }
                "
                :style="(drag_over_index == index && index != draging_index) ?(index < draging_index ? 'border-left:dashed var(--brand-warning);padding-right:1px':'border-right:dashed var(--brand-warning);padding-left:1px') : 'padding:0 1px'"
                style="width: fit-content; display: inline-block;border-width:1px;cursor:move"
              >
                <div style="width:fit-content;text-align:center;margin:2px;padding:8px 4px;;background:var(--sub-a);border-radius:4px;">
                    <div
                      :class="
                        'decrafting_recipe decrafting_recipe_' + item.id
                      "
                      @click="item.count=(item.count>0?0:8),resort()"
                      style="cursor:pointer"
                    ></div>
                    <div>
                    <select
                      class="form-control input-sm"                        
                      v-model="item.count"
                      @change="resort()"
                    >
                      <template v-for="i in 9" :key="i-1">
                        <option>{{ i - 1 }}</option>
                      </template>
                    </select>

                    </div>
                </div>
              </div>
            </template>
          </transition-group>
      </div>
      <div class="row" style="margin-bottom:4px;">
        <div class="col-xs-8">
          <button class="col-xs-8 btn btn-success" @click="calculate" v-if="worker_status=='idle'">
            开始合成
          </button>
          <button class="col-xs-8 btn btn-success" v-if="worker_status=='busy'" disabled>
            正在合成(已探索{{calculated_count}})
          </button>
          <button class="col-xs-4 btn btn-link" @click="clear_items">
            清空配方
          </button>
        </div>
        <div class="col-xs-4">
          <select class="form-control input-sm" v-model="display_mode">
            <option value="craftable">显示可合成道具({{craftable_count}})</option>
            <option value="crafted">显示已合成道具({{crafted_count}})</option>
          </select>

        </div>

      </div>
      <!-- 结果列表 -->
      <div
        style="
          background: var(--detail-infobox-bg); 
          margin:0 1px;
          padding: 1px;
        "
      >
        <template v-for="result in results" v-bind:key="result.id">
          <div v-if="result.valid && ((display_mode == 'craftable' && result.craftable) || (display_mode == 'crafted' && result.crafted))" style="
          display:inline-block;width:fit-content;margin:2px;text-align:center;
          background:var(--detail-bg);border:solid;border-radius:4px;border-width:1px;
          "
          :style="'border-color:' + (result.crafted ? 'var(--brand-primary)': result.craftable ? 'gray':'black')"
          >
            <a
              class="icons collectibles"
              :id="
                'collectibles_' +
                '000'.substr(('' + result.id).length) +
                result.id
              "
              :href="'/wiki/C' + result.id"
              style="transform:scale(1.5);image-rendering:pixelated;margin:8px 0"
            ></a>
            <div>
              <template v-for="(item, index) in result.items" v-bind:key="index">
                <div
                  class="decrafting_recipe decrafting_recipe_result"
                  :class="'decrafting_recipe_' + item"
                ></div>
                <br v-if="index == 3"/>
              </template>
            </div>
            <div style="margin:0;border-radius:0 0 4px 4px" :style="result.crafted ? 'background:var(--brand-primary)': result.craftable ? 'background:gray':'background:black'">
              <span class="" style="color:white">{{result.id}}</span>
            </div>


          </div>
        </template>
      </div>
      <div class="row post-reading dash-line">
        <p>配方候选列表按照从左到右、从上到下的优先级进行探索，可拖拽排序以调整优先级。</p>
        <p>此算法对解空间进行完全穷举，过多的配方会增加计算时间，可能会导致网页未响应，请按需选择。</p>
        <ul>
          <li>可合成道具：基于配方类型、数量计算而来，理论上可合成的道具。与游戏种子无关，理论最大值为690个道具。</li>
          <li>已合成道具：基于游戏种子、配方类型、数量进行完全穷举而来。本局游戏中，在当前给定的配方限制下，实际可合成的道具。</li>
        </ul>
      </div>
    </div>
  </div>
</template>
<script>
//============================
/* global DecraftingPredefinedWebWorker */
let webWorker
if(DecraftingPredefinedWebWorker){
  /* debug */
  webWorker = DecraftingPredefinedWebWorker
}else if(window.Worker){
  /* release */
  webWorker = new Worker('idk, something from huijiwiki.com')
}else{
  alert("浏览器不支持worker特性，该更新辣")
  webWorker = undefined
}

function str2seed(seed) {
    if (seed.length != 9) return 0;
    //"xxxx xxxx"
    if (seed[4] != " ") {
        return 0;
    }

    let dict = [];
    for (let i = 0; i < 255; i++) {
        dict[i] = 0xff;
    }
    for (let i = 0; i < 32; i++) {
        dict["ABCDEFGHJKLMNPQRSTWXYZ01234V6789".charCodeAt(i)] = i;
    }

    let num_seed = [];
    for (let i = 0; i < 9; i++) {
        if (i == 4) continue;
        let j = i;
        if (i > 4) {
            j = i - 1;
        }
        num_seed[j] = dict[seed.charCodeAt(i)];
        if (num_seed[j] == 0xff) return 0;
    }

    let v8 = 0;
    let v10;

    //num_seed[x] j is unsigned int8
    for (
        let j =
            ((num_seed[6] >>> 3) |
                (4 *
                    (num_seed[5] |
                        (32 *
                            (num_seed[4] |
                                (32 *
                                    (num_seed[3] |
                                        (32 *
                                            (num_seed[2] |
                                                (32 * (num_seed[1] | (32 * num_seed[0])))))))))))) ^
            0xfef7ffd;
        j != 0;
        v8 = ((v10 >>> 7) + 2 * v10) & 0xff
    ) {
        v10 = ((j & 0xff) + v8) & 0xff;
        j >>>= 5;
    }
    if (v8 == (num_seed[7] | (0xff & (32 * num_seed[6])))) {
        return (
            ((num_seed[6] >> 3) |
                (4 *
                    (num_seed[5] |
                        (32 *
                            (num_seed[4] |
                                (32 *
                                    (num_seed[3] |
                                        (32 *
                                            (num_seed[2] |
                                                (32 * (num_seed[1] | (32 * num_seed[0])))))))))))) ^
            0xfef7ffd
        );
    }
    return 0;
}

export default {
  name: "App",
  data() {
    let items = [];
    let predefined = {
      1:{count:8,order:1},
      2:{count:8,order:2},
      // 3:{count:8,order:3},
      // 4:{count:1,order:40},
      // 5:{count:1,order:41},
      // 6:{count:1,order:42},
      // 7:{count:1,order:43},
      // 8:{count:8,order:8},
      // 23:{count:2,order:9},
      // 25:{count:1,order:39},
      // 29:{count:8,order:11},
    }
    for (let i = 1; i < 30; i++) {
      let count = 0
      if(predefined[i])
        count = predefined[i].count

      items.push({ id: i, count: count });
    }
    let results = [
      // {
      //   id: 5,
      //   valid:true,
      //   craftable: undefined,
      //   crafted: false,
      //   items: [0, 0, 0, 0, 0, 0, 0, 0],
      // },
    ];

    for (let i = 0; i < 733; i++) {
      results[i] = {
        id: i,
        valid: false,
        craftable: undefined,
        crafted: false,
        items: [0, 0, 0, 0, 0, 0, 0, 0],
      };
    }

    /* resort */
    {
      let changed = false;
      do {
        changed = false;
        for (let i = 0; i < items.length - 1; i++) {
          if (((items[i].count == 0 && items[i + 1].count > 0) 
            || (items[i].count!=0 && items[i+1].count != 0 &&
                  predefined[items[i].id].order >= predefined[items[i+1].id].order))) {
            let temp = items[i];
            items[i] = items[i + 1];
            items[i + 1] = temp;
            changed = true;
          }
        }
      } while (changed);
    }

    return {
      items: items,
      draging_index:-1,
      drag_over_index: -1,
      results: results,
      seed: "JKD9 Z0C9",
      display_mode:'crafted', /* valid, craftable, crafted */
      craftable_count:0,
      crafted_count:0,
      calculated_count:0,
      worker_status:'idle', /* idle, busy */
    };
  },
  methods: {
    move_down(index) {
      let temp = this.items[index];
      console.log(document.getElementById("list_item_" + temp.id));
      this.items[index] = this.items[index + 1];
      this.items[index + 1] = temp;
    },
    move_up(index) {
      let temp = this.items[index];
      this.items[index] = this.items[index - 1];
      this.items[index - 1] = temp;
    },
    begin_drag(event, index) {
      event.dataTransfer.setData("text/list-index", index);
      event.dataTransfer.dropEffect = "move";
      this.draging_index = index;
    },
    over_drag(ev, index) {
      ev.preventDefault();
      ev.dataTransfer.dropEffect = "move";
      this.drag_over_index = index;
    },
    drop_drag(ev, index) {
      this.drag_over_index = -1;
      let from = ev.dataTransfer.getData("text/list-index");
      if (from == undefined) return;
      let to = index;

      // if (from > to) to++;

      if (from < to) {
        let temp = this.items[from];
        while (from < to) {
          this.items[from] = this.items[++from];
        }
        this.items[to] = temp;
      } else if (from > to) {
        let temp = this.items[from];
        while (from > to) {
          this.items[from] = this.items[--from];
        }
        this.items[to] = temp;
      }

      // let temp = this.items[from]
      // this.items[from] = this.items[to]
      // this.items[to]=temp
    },
    clear_items(){
      for(let i=0;i<this.items.length;i++){
        this.items[i].count = 0
      }
    },
    resort() {
      let changed = false;
      do {
        changed = false;
        for (let i = 0; i < this.items.length - 1; i++) {
          if (this.items[i].count == 0 && this.items[i + 1].count > 0) {
            let temp = this.items[i];
            this.items[i] = this.items[i + 1];
            this.items[i + 1] = temp;
            changed = true;
          }
        }
      } while (changed);
    },
    calculate() {
      let check_seed_reg = new RegExp("^[A-Z0-9]{4} [A-Z0-9]{4}$", "g");

      let invalid_seed = false;
      if (this.seed.length != 9 || !this.seed.match(check_seed_reg))
        invalid_seed = true;
      let seed
      seed = str2seed(this.seed);
      if (seed == 0) invalid_seed = true;
      if (invalid_seed) {
        alert("种子错了的说！");
        return;
      }

      let candidates = [];
      let candidates_limit = [];
      for (let i = 0; i < this.items.length; i++) {
        if (this.items[i].count > 0) {
          candidates.push(+this.items[i].id);
          candidates_limit.push(+this.items[i].count);
        }
      }

      if (candidates.length <= 0) return;
      this.worker_status='busy'
      webWorker.postMessage({
        cmd:'start',
        candidates:candidates,
        candidates_limit:candidates_limit,
        seed:seed
      })
    },
  },
};

webWorker.onmessage = function(event){
    let data = event.data
    if(data.cmd == "result" || data.cmd == "report"){
      let vue_data = window.decraftingVueRoot
      if(data.cmd == "result"){
        vue_data.worker_status = 'idle'
      }
      let craftable_count = 0
      let crafted_count = 0
      for (let i = 1; i < vue_data.results.length; i++) {
        if (data.items[i]) {
          vue_data.results[i].valid = true;
          vue_data.results[i].crafted = true;
          vue_data.results[i].craftable = true;
          vue_data.results[i].items = data.items[i];
          craftable_count++
          crafted_count++
        }else{
          vue_data.results[i].crafted = false;
          vue_data.results[i].valid = data.craftable_arr[i];
          vue_data.results[i].craftable = data.craftable_arr[i];
          vue_data.results[i].items = [0,0,0,0,0,0,0,0]
          if(data.craftable_arr[i])
            craftable_count++
        }
      }
      vue_data.craftable_count = craftable_count
      vue_data.crafted_count = crafted_count
      vue_data.calculated_count = data.count
    }
}

</script>
<style scoped>
.flip-list-move {
  transition: transform 0.2s ease;
}
.decrafting_recipe {
  image-rendering: pixelated;
  transform: scale(2);
  width: 16px;
  height: 16px;
  display: inline-block;
  margin:4px;
  background-image: url("https://huiji-public.huijistatic.com/isaac/uploads/8/89/Crafting_ui_sprite.png");
}
.decrafting_recipe_result {
  transform: scale(1.5) !important;
  width: 16px;
  height: 16px;
  display: inline-block;
  margin:1.5px;
}
.decrafting_recipe_0 {
  background-position: -0px -0px;
}
.decrafting_recipe_1 {
  background-position: -16px -0px;
}
.decrafting_recipe_2 {
  background-position: -32px -0px;
}
.decrafting_recipe_3 {
  background-position: -48px -0px;
}
.decrafting_recipe_4 {
  background-position: -64px -0px;
}
.decrafting_recipe_5 {
  background-position: -80px -0px;
}
.decrafting_recipe_6 {
  background-position: -96px -0px;
}
.decrafting_recipe_7 {
  background-position: -112px -0px;
}
.decrafting_recipe_8 {
  background-position: -0px -16px;
}
.decrafting_recipe_9 {
  background-position: -16px -16px;
}
.decrafting_recipe_10 {
  background-position: -32px -16px;
}
.decrafting_recipe_11 {
  background-position: -48px -16px;
}
.decrafting_recipe_12 {
  background-position: -64px -16px;
}
.decrafting_recipe_13 {
  background-position: -80px -16px;
}
.decrafting_recipe_14 {
  background-position: -96px -16px;
}
.decrafting_recipe_15 {
  background-position: -112px -16px;
}
.decrafting_recipe_16 {
  background-position: -0px -32px;
}
.decrafting_recipe_17 {
  background-position: -16px -32px;
}
.decrafting_recipe_18 {
  background-position: -32px -32px;
}
.decrafting_recipe_19 {
  background-position: -48px -32px;
}
.decrafting_recipe_20 {
  background-position: -64px -32px;
}
.decrafting_recipe_21 {
  background-position: -80px -32px;
}
.decrafting_recipe_22 {
  background-position: -96px -32px;
}
.decrafting_recipe_23 {
  background-position: -112px -32px;
}
.decrafting_recipe_24 {
  background-position: -0px -48px;
}
.decrafting_recipe_25 {
  background-position: -16px -48px;
}
.decrafting_recipe_26 {
  background-position: -32px -48px;
}
.decrafting_recipe_27 {
  background-position: -48px -48px;
}
.decrafting_recipe_28 {
  background-position: -64px -48px;
}
.decrafting_recipe_29 {
  background-position: -80px -48px;
}
.decrafting_recipe_30 {
  background-position: -96px -48px;
}
</style>