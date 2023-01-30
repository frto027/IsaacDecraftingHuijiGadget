<template>
  <h1>合成宝袋挖掘器</h1>
  <hr />
  <div>
    <div>
      <div style="margin: 1px; text-align: center">
        <div
          style="
            width: 100%;
            background: var(--brand-primary);
            padding: 10px;
            font-size: 16px;
            color: #fff;
            border-radius: 4px 4px 0 0;
          "
        >
          种子
        </div>
        <input
          class="form-control"
          v-model="seed"
          style="border-radius: 0 0 4px 4px"
        />
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
              :style="
                drag_over_index == index && index != draging_index
                  ? index < draging_index
                    ? 'border-left:dashed var(--brand-warning);padding-right:1px'
                    : 'border-right:dashed var(--brand-warning);padding-left:1px'
                  : 'padding:0 1px'
              "
              style="
                width: fit-content;
                display: inline-block;
                border-width: 1px;
                cursor: move;
              "
            >
              <div
                style="
                  width: fit-content;
                  text-align: center;
                  margin: 2px;
                  padding: 8px 4px;
                  background: var(--sub-a);
                  border-radius: 4px;
                "
              >
                <div
                  :class="'decrafting_recipe decrafting_recipe_' + item.id"
                  @click="(item.count = item.count > 0 ? 0 : 8), resort()"
                  style="cursor: pointer"
                  :title="recipe_name[item.id]"
                ></div>
                <div>
                  <select
                    class="form-control input-sm"
                    v-model="item.count"
                    @change="resort()"
                  >
                    <template v-for="i in 9" :key="i - 1">
                      <option>{{ i - 1 }}</option>
                    </template>
                  </select>
                </div>
              </div>
            </div>
          </template>
        </transition-group>
      </div>
      <div class="row" style="margin-bottom: 4px">
        <div class="col-xs-4 col-md-3 col-lg-2">
          <select class="form-control input-sm" v-model="display_mode">
            <option value="craftable">
              显示可合成道具({{ craftable_count }})
            </option>
            <option value="crafted">显示已合成道具({{ crafted_count }})</option>
          </select>
        </div>
        <div class="col-xs-4 col-md-3 col-lg-2">
          <select class="form-control input-sm" v-model="craft_count" v-bind:disabled="worker_status == 'busy'">
            <option value="1">仅记录一个配方</option>
            <option value="10">记录10个配方</option>
            <option value="20">记录20个配方</option>
            <option value="50">记录50个配方</option>
            <option value="100">记录100个配方</option>
          </select>
        </div>
        <div class="col-xs-4 col-md-3 col-lg-2">
          <select class="form-control input-sm" v-model="real_time_flush" v-bind:disabled="worker_status == 'busy'">
            <option value="true">启用实时刷新</option>
            <option value="false">禁用实时刷新</option>
          </select>
        </div>
        <div class="col-xs-4 col-md-3 col-lg-2">
          <select class="form-control input-sm" v-model="enable_wasm" v-bind:disabled="worker_status == 'busy' || no_wasm">
            <option value="true">启用wasm加速</option>
            <option value="false">禁用wasm加速</option>
          </select>
        </div>

      </div>
      <div class="btn-group" style="margin:6px 0px">
        <div type="button" @click="safe_is_greed=!safe_is_greed" :class="safe_is_greed? 'btn-success' : 'btn-default'" id="crafting_item_greed" class="btn btn-xs">贪婪模式</div>
        <div type="button" @click="safe_is_daily_run=!safe_is_daily_run" :class="safe_is_daily_run? 'btn-success' : 'btn-default'" id="crafting_item_daily_run" class="btn btn-xs">每日挑战</div>
        <div type="button" @click="safe_current_stage=safe_current_stage>=7?1:7" :class="safe_current_stage >= 7? 'btn-success' : 'btn-default'" id="crafting_item_stage_more_7" class="btn btn-xs">7层及以上</div>
        <div type="button" @click="safe_has_tlost=!safe_has_tlost" :class="safe_has_tlost? 'btn-success' : 'btn-default'" id="crafting_item_tlost" class="btn btn-xs">堕化游魂</div>
        <div type="button" @click="safe_has_keeper=!safe_has_keeper" :class="safe_has_keeper? 'btn-success' : 'btn-default'" id="crafting_item_keeper" class="btn btn-xs">（堕化）店主</div>
        <div type="button" @click="safe_has_lost=!safe_has_lost" :class="safe_has_lost? 'btn-success' : 'btn-default'" id="crafting_item_lost" class="btn btn-xs">游魂</div>
        <div type="button" @click="safe_has_c691=!safe_has_c691" :class="safe_has_c691? 'btn-success' : 'btn-default'" id="crafting_item_c691" class="btn btn-xs">道具：十字圣球</div>
        <div type="button" @click="safe_has_t88=!safe_has_t88" :class="safe_has_t88? 'btn-success' : 'btn-default'" id="crafting_item_t88" class="btn btn-xs">饰品：不！</div>
      </div>

      <div class="row" style="margin-bottom: 4px">
        <div class="col-xs-8">
          <button
            class="col-xs-8 btn btn-success"
            @click="calculate"
            v-if="worker_status == 'idle'"
          >
            开始合成
          </button>
          <button
            class="col-xs-8 btn btn-success"
            v-if="worker_status == 'busy'"
            disabled
          >
            正在合成({{ calculated_count }}/{{all_calculate_count}})
            <div style="position:absolute;left:0;top:0;background-color:#CCC7;height:100%;"
              :style="'width:' + (worker_status == 'busy' ? ( calculated_count*100/all_calculate_count ) + '%' :'0')"
            ></div>

          </button>
          <button class="col-xs-4 btn btn-link" @click="clear_items">
            清空组件
          </button>
        </div>
      </div>
      <!-- 结果列表 -->
      <div
        style="
          background: var(--detail-infobox-bg);
          margin: 0 1px;
          padding: 1px;
        "
      >
        <transition-group name="flip-item-list">
          <template v-for="result in results" v-bind:key="result.id">
            <!-- 渲染第一个配方 -->
            <div
              v-bind:key="'recipes_'+result.id+'_'+0"
              v-if="
                result.valid &&
                ((display_mode == 'craftable' && result.craftable) ||
                  (display_mode == 'crafted' && result.crafted))
              "
              style="
                display: inline-block;
                width: fit-content;
                margin: 2px;
                text-align: center;
                background: var(--detail-bg);
                border: solid;
                border-radius: 4px;
                border-width: 1px;
              "
              :style="
                'border-color:' +
                (result.crafted
                  ? 'var(--brand-primary)'
                  : result.craftable
                  ? 'gray'
                  : 'black')
              "
            >
              <a
                class="icons collectibles"
                :id="
                  'collectibles_' +
                  '000'.substr(('' + result.id).length) +
                  result.id
                "
                :href="'/wiki/C' + result.id"
                style="
                  transform: scale(1.5);
                  image-rendering: pixelated;
                  margin: 8px 0;
                "
              ></a>
              <div>
                <template v-if="result.items.length > 0">
                  <template
                    v-for="(item, index) in result.items[0]"
                    v-bind:key="index"
                  >
                    <div
                      class="decrafting_recipe decrafting_recipe_result"
                      :class="'decrafting_recipe_' + item"
                      :title="recipe_name[item]"
                    ></div>
                    <br v-if="index == 3" />
                  </template>
                </template>
                <template v-else>
                  <template v-for="index in 8" v-bind:key="index">
                    <div
                      class="
                        decrafting_recipe
                        decrafting_recipe_result
                        decrafting_recipe_0
                      "
                    ></div>
                    <br v-if="index == 4" />
                  </template>
                </template>
              </div>
              <a
                style="color: var(--detail-wikitable-color)"
                class="btn btn-link btn-xs"
                @click="result.fold = false"
                >{{ result.items.length }}个配方</a
              >
              <div
                style="margin: 0; border-radius: 0 0 4px 4px"
                :style="
                  result.crafted
                    ? 'background:var(--brand-primary)'
                    : result.craftable
                    ? 'background:gray'
                    : 'background:black'
                "
              >
                <span style="color: white">{{ result.id }}</span>
              </div>
            </div>

            <template
              v-if="
                result.valid &&
                result.crafted &&
                result.items.length > 1 &&
                result.fold == false
              "
            >
              <!-- 展开渲染其它配方 -->
              <template
                v-for="(items, index) in result.items"
                v-bind:key="result.id + '_' + index"
              >
                <div
                  v-if="index > 0"
                  v-bind:key="'recipes_'+result.id+'_'+index"
                  style="
                    display: inline-block;
                    width: fit-content;
                    margin: 2px;
                    text-align: center;
                    background: var(--detail-bg);
                    border: solid;
                    border-radius: 4px;
                    border-width: 1px;
                    border-color: var(--brand-primary);
                  "
                >
                  <a
                    class="icons collectibles"
                    :id="
                      'collectibles_' +
                      '000'.substr(('' + result.id).length) +
                      result.id
                    "
                    :href="'/wiki/C' + result.id"
                    style="
                      transform: scale(1.5);
                      image-rendering: pixelated;
                      margin: 8px 0;
                    "
                  ></a>
                  <div>
                    <template v-if="index > 0">
                      <template
                        v-for="(item, index) in items"
                        v-bind:key="index"
                      >
                        <div
                          class="decrafting_recipe decrafting_recipe_result"
                          :class="'decrafting_recipe_' + item"
                          :title="recipe_name[item]"
                        ></div>
                        <br v-if="index == 3" />
                      </template>
                    </template>
                  </div>
                  <a
                    style="color: var(--detail-wikitable-color)"
                    class="btn btn-link btn-xs"
                    @click="result.fold = true"
                    >隐藏此配方</a
                  >
                  <div
                    style="margin: 0; border-radius: 0 0 4px 4px"
                    :style="
                      result.crafted
                        ? 'background:var(--brand-primary)'
                        : result.craftable
                        ? 'background:gray'
                        : 'background:black'
                    "
                  >
                    <span style="color: white">{{ result.id }}</span>
                  </div>
                </div>
              </template>
            </template>
          </template>
        </transition-group>
      </div>
      <div class="row post-reading dash-line">
      </div>
    </div>
  </div>
</template>
<script>
//============================
let webWorkerText = `
//启用webAssembly
if(fetch && WebAssembly){
        WebAssembly.instantiateStreaming(fetch("data:application/wasm;base64,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gD/EAAAAAACAP/8AAAAAAIA/VQEAAAAAgD9XAQAAAACAP1gBAAAAAIA/YgEAAAAAgD9jAQAAAACAP3IBAAAAAIA/rAEAAAAAAD+2AQAAAACAP7wBAADNzMw9xwEAAAAAgD/IAQAAAACAPxYCAAAAAAA/OwIAAM3MzD2EAgAAAACAP8QCAAAAAIA/2gIAAAAAgD/cAgAAAACAP1EAAAAAAIA/hQAAAAAAgD+GAAAAAACAP4wAAAAAAIA/kQAAAAAAgD/UAAAAAACAPykBAAAAAIA/PAEAAAAAgD9zAQAAAACAP9sBAADNzMw9NQIAAAAAAD9EAgAAzczMPYICAAAAAIA/jgIAAM3MTD6ZAgAAAACAPzMAAAAAAIA/TwAAAAAAgD9QAAAAAACAP1EAAAAAAIA/fgAAAAAAgD+FAAAAAACAP4YAAAAAAIA/kQAAAAAAgD/UAAAAAACAP9cAAAAAAIA/2AAAAAAAgD/hAAAAAACAP/EAAAAAAIA/BAEAAAAAgD9zAQAAAACAP5gBAAAAAIA/ugEAAAAAgD/DAQAAAACAP9QBAAAAAIA/2wEAAM3MTD7wAQAAAACAP/cBAAAAAIA/GAIAAAAAgD81AgAAAACAPzkCAAAAAIA/RAIAAAAAgD+CAgAAAACAP44CAAAAAAA/mQIAAAAAgD+0AgAAAACAP7YCAAAAAAA/uQIAAAAAAD++AgAAAACAP8cCAAAAAIA/TAIAAAAAgD9NAgAAAACAP04CAAAAAIA/TwIAAAAAgD9QAgAAAACAP1ECAAAAAIA/UgIAAAAAgD9TAgAAAACAP1QCAAAAAIA/VQIAAAAAgD9WAgAAAACAPwAAAACXAQAAlwEAAF8AAAD2AQAAOwAAADECAABeAAAAjwIAAEIAAADRAgAAPgAAAP//////////DwMAAAYAAAAVAwAAGQAAAC4DAAAPAAAA/////////////////////z0DAAAiAAAA//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////9fAwAACwBB4MMAC601////////////////AwAAAP////8CAAAA/////wMAAAD/////BAAAAP////8CAAAA/////wIAAAD/////AwAAAP////8BAAAA/////wAAAAD/////AgAAAP////8CAAAA/////wQAAAD/////AgAAAP////8CAAAA/////wIAAAD/////AgAAAP////8DAAAA/////wMAAAD/////AAAAAAgAAAADAAAA/////wIAAAD/////AQAAAP////8BAAAA/////wEAAAD/////AQAAAP////8BAAAA/////wEAAAD/////AQAAAP////8BAAAA/////wEAAAD/////AQAAAIsAAAADAAAA/////wEAAAD/////AgAAACQAAAABAAAA/////wAAAAD/////AQAAAP////8CAAAA/////wEAAAD/////AAAAAP////8AAAAA/////wEAAAD///////////////8AAAAA/////wEAAAD/////AgAAAP////8BAAAA/////wMAAAD/////AgAAAP////8DAAAA/////wMAAAALAAAABAAAAP////8BAAAA/////wIAAAD/////AQAAAP////8AAAAA/////wIAAAD/////AwAAAP////8AAAAA/////wEAAAD///////////////8BAAAA/////wIAAAD/////AwAAAP////8BAAAA/////wEAAAD/////AQAAAP////8DAAAA/////wMAAAD/////AwAAAP////8CAAAA/////wIAAAAGAAAAAgAAAAoAAAABAAAA/////wIAAAD/////AgAAAP////8BAAAABwAAAAMAAAD/////AwAAAP////8DAAAA/////wMAAAD/////AwAAAAkAAAACAAAA/////wIAAAD/////AgAAAA0AAAABAAAADwAAAAEAAAAOAAAAAgAAAP////8CAAAADAAAAAMAAAD/////AgAAABMAAAACAAAAGgAAAAEAAAAVAAAAAQAAAP////8BAAAAGQAAAAIAAAAWAAAAAgAAABQAAAADAAAAFwAAAAIAAAAYAAAAAgAAABsAAAACAAAA/////wEAAAD/////AQAAAB8AAAADAAAAHQAAAAQAAAAcAAAAAgAAAP////8CAAAA/////wQAAAD/////AwAAACMAAAADAAAA/////wAAAAAtAAAAAgAAAC8AAAACAAAAKwAAAAQAAAD/////AgAAAP////8CAAAA/////wAAAAD/////BAAAAJMAAAACAAAA/////wIAAAD/////AgAAAP////8CAAAA/////wEAAAD/////AQAAAP////8CAAAALAAAAAAAAAAwAAAAAwAAAP////8BAAAA/////wEAAAD/////AgAAAC4AAAACAAAA/////wMAAAD/////AwAAAP////8CAAAA/////wEAAAD/////AQAAAP////8BAAAA/////wIAAAD/////AgAAAP////8BAAAA/////wAAAAD/////AgAAAP////8CAAAA/////wEAAAD/////AgAAAP////8DAAAA/////wEAAAD/////AAAAAIwAAAAEAAAA/////wMAAAD/////AwAAAP////8CAAAA/////wMAAAD/////AgAAAP////8CAAAA/////wIAAAA2AAAAAgAAAP////8DAAAA/////wMAAAD/////AgAAAP////8BAAAAMgAAAAEAAAD/////AQAAADsAAAACAAAA/////wMAAAAxAAAAAgAAAP////8BAAAAPgAAAAQAAAD/////BAAAAP////8DAAAA/////wEAAAA1AAAAAgAAAP////8DAAAA/////wEAAAA6AAAAAgAAAP////8BAAAA/////wAAAAD/////AwAAAHEAAAADAAAA/////wAAAAD/////AgAAAP////8EAAAA/////wMAAAD/////AwAAAP////8DAAAAOAAAAAAAAABBAAAAAQAAADMAAAAAAAAAPwAAAAMAAAD/////AwAAAP////8CAAAA/////wEAAAD/////AgAAAP////8BAAAA/////wEAAAD/////AwAAAP////8CAAAA/////wEAAAD/////AwAAAP////8BAAAA/////wIAAAD/////AgAAAP////8DAAAA/////wEAAAD/////AgAAAGsAAAACAAAABgAAAAIAAAD/////AwAAAP////8CAAAA/////wEAAAD/////AAAAAP////8BAAAA/////wIAAAD/////AQAAAP////8DAAAA/////wMAAAD/////AgAAAP////8CAAAA/////wIAAAD/////AgAAAJYAAAADAAAA/////wIAAAD/////BAAAAP////8DAAAA/////wIAAAD/////AgAAAP////8BAAAA/////wIAAAD/////AgAAAIAAAAADAAAA/////wIAAACKAAAABAAAAP////8AAAAA/////wMAAAD///////////////8BAAAAZwAAAAMAAAD/////AAAAAP////8AAAAAjQAAAAEAAAD/////AwAAAP////8CAAAA/////wIAAABoAAAAAwAAAP////8EAAAAhgAAAAIAAAD/////AgAAAP////8CAAAAhwAAAAMAAAD/////AQAAAP////8CAAAAkgAAAAAAAAD/////AgAAAP////8CAAAA/////wMAAAD/////AQAAAP////8CAAAAaQAAAAAAAAD/////AwAAAIgAAAADAAAA/////wMAAAD/////AAAAAOkAAAACAAAA/////wIAAAD/////AwAAAP////8CAAAAZgAAAAEAAAD/////AwAAAP////8BAAAA/////wIAAAB8AAAAAgAAAP////8BAAAA/////wEAAAD/////AAAAAP////8CAAAAgQAAAAAAAAD/////AQAAAP////8DAAAA/////wIAAAD/////AQAAAP////8BAAAA/////wEAAACFAAAAAwAAAJQAAAACAAAA/////wEAAAB5AAAAAgAAAHoAAAABAAAA/////wEAAACJAAAAAgAAAP////8AAAAA/////wEAAAB+AAAABAAAAI8AAAACAAAAkQAAAAEAAAD/////AQAAAP////8CAAAAdwAAAAIAAAD/////AQAAAP////8BAAAA/////wIAAAD/////AwAAAP////8BAAAA/////wIAAAD/////AQAAAP////8DAAAA/////wMAAAD/////AwAAAP////8CAAAA/////wIAAABwAAAAAwAAAGwAAAADAAAAbQAAAAIAAAD/////BAAAAP////8BAAAA/////wAAAAD/////AAAAAP////8DAAAA/////wEAAABuAAAAAgAAAHIAAAABAAAAcwAAAAEAAAD/////AgAAAGoAAAABAAAAfQAAAAIAAAAeAAAAAQAAAP////8BAAAAOQAAAAIAAABOAAAAAgAAAP////8CAAAA/////wIAAACcAAAABAAAAHQAAAABAAAAggAAAAMAAACDAAAAAwAAAIQAAAADAAAA/////wMAAAD/////AQAAAP////8BAAAA/////wEAAAD/////AQAAAP////8DAAAA/////wMAAAD/////AgAAAP////8BAAAA/////wMAAAD/////AQAAAP////8DAAAA/////wIAAAD0AAAAAQAAAP////8DAAAA/////wEAAAD/////AQAAAP////8CAAAA/////wIAAAD/////AgAAAP////8DAAAAywAAAAEAAAD/////AQAAAP////8DAAAAvgAAAAQAAAC3AAAAAgAAAMAAAAACAAAAvQAAAAMAAAD/////AQAAAP////8CAAAA/////wEAAAD/////AgAAAP////8CAAAA/////wIAAAD/////AwAAAP////8AAAAA/////wMAAAD/////AwAAAP////8DAAAA/////wMAAAD/////AgAAAP////8BAAAA/////wIAAAD/////AgAAAP////8CAAAAvAAAAAMAAAD/////AQAAAP////8BAAAA/////wIAAAD/////AQAAALUAAAABAAAAwQAAAAMAAADIAAAAAAAAANoAAAADAAAA/////wMAAAC2AAAAAQAAAMoAAAABAAAA3AAAAAIAAAD/////AQAAAP////8EAAAA/////wEAAAD/////AwAAAP////8BAAAAugAAAAMAAAD/////AgAAAP////8DAAAA/////wMAAAD/////AQAAALMAAAABAAAAyQAAAAEAAADnAAAAAgAAALQAAAADAAAAuAAAAAMAAAC7AAAAAgAAAMIAAAACAAAAxgAAAAMAAADbAAAAAgAAAN4AAAABAAAAhwAAAAMAAAD/////BAAAAO4AAAACAAAA3QAAAAMAAAD/////AgAAAP////8DAAAA/////wEAAAD/////AQAAAP///////////////wIAAAD/////AwAAAP////8BAAAA/////wAAAAD/////AQAAAP////8CAAAA/////wIAAAD/////AQAAAP////8CAAAA/////wIAAADDAAAAAgAAAP////8CAAAA/////wEAAAD/////AQAAAP////8BAAAA/////wMAAAD/////AgAAAOgAAAACAAAAFAEAAAQAAAAiAQAAAQAAAP////8DAAAA/////wMAAAD/////AgAAAP////8BAAAA/////wAAAAD/////AQAAAP////8BAAAANAEAAAIAAAD/////AgAAAP////8BAAAAIwEAAAMAAAD/////AgAAADMBAAACAAAA/////wEAAAD/////AgAAAP////8CAAAA/////wMAAAD/////AQAAAP////8DAAAAKwEAAAMAAAD/////AgAAACkBAAACAAAA/////wIAAAD/////AgAAAP////8BAAAAHQEAAAAAAAD/////AQAAADsBAAAAAAAA/////wIAAAAeAQAAAQAAAP////8BAAAA/////wAAAAAxAQAAAAAAACgBAAACAAAAJwEAAAQAAAD/////AQAAAD4BAAACAAAA/////wEAAAD/////AAAAAP////8AAAAA/////wMAAAD/////AQAAACYBAAACAAAAIAEAAAEAAAD/////AgAAAC8BAAABAAAAGgEAAAQAAAAhAQAAAwAAAP////8CAAAA/////wIAAAD/////AgAAAP////8DAAAA/////wMAAAAkAQAAAwAAAP////8DAAAAMgEAAAEAAAAbAQAAAwAAACoBAAADAAAATwEAAAEAAAD/////AQAAAP////8DAAAAPAEAAAAAAAD/////AgAAAP////8DAAAA/////wIAAAD/////AgAAAP////8BAAAAUgEAAAEAAABgAQAAAQAAAF0BAAABAAAAYQEAAAIAAABiAQAAAwAAAF4BAAADAAAAXwEAAAIAAABkAQAAAQAAAGMBAAACAAAAZQEAAAIAAABvAQAAAwAAAGwBAAACAAAAbQEAAAEAAABuAQAAAQAAAHEBAAADAAAAcAEAAAEAAAB0AQAAAgAAAHMBAAADAAAAdQEAAAMAAAB2AQAAAQAAAHgBAAACAAAAeQEAAAQAAAB6AQAAAgAAAHwBAAADAAAAewEAAAMAAACBAQAAAgAAAH8BAAACAAAAgAEAAAEAAACCAQAAAgAAAIMBAAABAAAAfgEAAAIAAACIAQAAAQAAAIkBAAACAAAAjgEAAAEAAACKAQAAAgAAAJEBAAADAAAAkAEAAAMAAACNAQAAAwAAAIsBAAABAAAAjAEAAAMAAAD/////BAAAAP////8EAAAA/////wQAAAD/////AwAAAP////8BAAAARwIAAAEAAAD/////AwAAAP////8CAAAA/////wEAAAD/////AgAAAP////8BAAAA/////wEAAACxAQAAAwAAAP////8CAAAA/////wMAAADOAQAAAQAAAP////8CAAAA/////wMAAACnAQAAAgAAAP////8BAAAA/////wIAAAD/////AgAAAP////8DAAAA/////wMAAAD/////AgAAAP////8DAAAABQIAAAEAAACwAQAAAgAAAP////8BAAAACAIAAAMAAACfAQAAAwAAAP////8EAAAA/////wEAAAD/////AgAAAKEBAAADAAAApAEAAAIAAACtAQAAAwAAAP///////////////wIAAAD/////AgAAAP////8DAAAA/////wIAAAD/////AwAAAP////8CAAAA/////wIAAAD/////AgAAAP////8DAAAA/////wMAAAD/////AwAAAP////8CAAAA/////wMAAAD/////AwAAAEYCAAACAAAA/////wEAAAD/////AQAAAP////8BAAAA/////wMAAAD/////AQAAAP////8CAAAAwAEAAAMAAADCAQAAAQAAAPEBAAACAAAAzAEAAAIAAAD///////////////8CAAAA/////wMAAAD/////AwAAAP////8DAAAA/////wIAAACvAQAAAwAAAP//////////rgEAAAIAAAC0AQAAAwAAAP////8BAAAA/////wEAAAAjAgAABAAAAP////8AAAAA/////wAAAAB8AgAABAAAAP////8DAAAA//////////+4AQAAAQAAAP////8CAAAA/////wMAAAAHAgAAAgAAAP////8BAAAA/////wQAAAD/////AwAAAP////8CAAAAugEAAAEAAACiAQAAAwAAAL4BAAACAAAA2AEAAAIAAADWAQAABAAAAP////8BAAAAyAEAAAEAAAAiAgAAAgAAAP////8CAAAA//////////+ZAQAAAQAAAJoBAAABAAAAqQEAAAMAAAD/////AQAAAKgBAAACAAAA/////wIAAAD/////AQAAALABAAACAAAA/////wEAAAD/////AQAAAP////8BAAAA/////wMAAAD/////AgAAAP///////////////wIAAAD/////BAAAALwBAAACAAAA///////////3AQAAAgAAAP////8AAAAA/////wMAAAC5AQAAAgAAALsBAAABAAAAvQEAAAEAAAC/AQAAAgAAANUBAAACAAAAwwEAAAEAAADFAQAAAQAAAMkBAAACAAAAzwEAAAQAAADHAQAAAgAAAMEBAAACAAAA0gEAAAEAAADTAQAAAwAAANQBAAACAAAAzQEAAAIAAADXAQAAAgAAAKYBAAABAAAA2QEAAAMAAACyAQAAAgAAAOsBAAAEAAAA7AEAAAMAAAD1AQAABAAAAO4BAAABAAAA7wEAAAIAAADwAQAAAwAAAMQBAAACAAAA8wEAAAMAAACzAQAAAgAAAPYBAAAEAAAA8gEAAAIAAAD4AQAAAwAAAPkBAAADAAAA+gEAAAEAAAD7AQAAAgAAAE4CAAACAAAASwIAAAIAAABVAgAABAAAAP////8BAAAA/////wMAAAC1AQAAAgAAAEoCAAD/////UAIAAAQAAABXAgAAAwAAAE0CAAADAAAA/////wAAAAD/////AAAAANABAAADAAAAVAIAAAIAAAD//////////9EBAAACAAAAywEAAAMAAAD0AQAAAAAAAFgCAAADAAAASAIAAAQAAABJAgAAAgAAAEwCAAAAAAAATwIAAAEAAABSAgAAAgAAAFMCAAADAAAAVgIAAAIAAAD/////AwAAAP////8CAAAA/////wMAAAD//////////wEAAAAFAAAAEAAAAAEAAAAFAAAAEwAAAAEAAAAJAAAAHQAAAAEAAAALAAAABgAAAAEAAAALAAAAEAAAAAEAAAATAAAAAwAAAAEAAAAVAAAAFAAAAAEAAAAbAAAAGwAAAAIAAAAFAAAADwAAAAIAAAAFAAAAFQAAAAIAAAAHAAAABwAAAAIAAAAHAAAACQAAAAIAAAAHAAAAGQAAAAIAAAAJAAAADwAAAAIAAAAPAAAAEQAAAAIAAAAPAAAAGQAAAAIAAAAVAAAACQAAAAMAAAABAAAADgAAAAMAAAADAAAAGgAAAAMAAAADAAAAHAAAAAMAAAADAAAAHQAAAAMAAAAFAAAAFAAAAAMAAAAFAAAAFgAAAAMAAAAFAAAAGQAAAAMAAAAHAAAAHQAAAAMAAAANAAAABwAAAAMAAAAXAAAAGQAAAAMAAAAZAAAAGAAAAAMAAAAbAAAACwAAAAQAAAADAAAAEQAAAAQAAAADAAAAGwAAAAQAAAAFAAAADwAAAAUAAAADAAAAFQAAAAUAAAAHAAAAFgAAAAUAAAAJAAAABwAAAAUAAAAJAAAAHAAAAAUAAAAJAAAAHwAAAAUAAAANAAAABgAAAAUAAAAPAAAAEQAAAAUAAAARAAAADQAAAAUAAAAVAAAADAAAAAUAAAAbAAAACAAAAAUAAAAbAAAAFQAAAAUAAAAbAAAAGQAAAAUAAAAbAAAAHAAAAAYAAAABAAAACwAAAAYAAAADAAAAEQAAAAYAAAARAAAACQAAAAYAAAAVAAAABwAAAAYAAAAVAAAADQAAAAcAAAABAAAACQAAAAcAAAABAAAAEgAAAAcAAAABAAAAGQAAAAcAAAANAAAAGQAAAAcAAAARAAAAFQAAAAcAAAAZAAAADAAAAAcAAAAZAAAAFAAAAAgAAAAHAAAAFwAAAAgAAAAJAAAAFwAAAAkAAAAFAAAADgAAAAkAAAAFAAAAGQAAAAkAAAALAAAAEwAAAAkAAAAVAAAAEAAAAAoAAAAJAAAAFQAAAAoAAAAJAAAAGQAAAAsAAAAHAAAADAAAAAsAAAAHAAAAEAAAAAsAAAARAAAADQAAAAsAAAAVAAAADQAAAAwAAAAJAAAAFwAAAA0AAAADAAAAEQAAAA0AAAADAAAAGwAAAA0AAAAFAAAAEwAAAA0AAAARAAAADwAAAA4AAAABAAAADwAAAA4AAAANAAAADwAAAA8AAAABAAAAHQAAABEAAAAPAAAAFAAAABEAAAAPAAAAFwAAABEAAAAPAAAAGg=="))
        .then(obj=>{
            let exports = obj.instance.exports
            let buffer = new Uint8Array(exports.memory.buffer, exports.getRecipeBuffer())
            BagOfCraftingWasmHelper = {
                calc(seed,arr){
                    for(let i=0;i<8;i++){
                        buffer[i]=arr[i]
                    }
                    return exports.getResult(seed)
                }
            }
        })
}

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
    '{"item_pool_data_compressed":[{"1":[1,2,3,4,5,6,7,8,10,13,14,15,19,36,37,38,39,40,41,42,44,45,46,47,48,49,52,53,55,56,57,58,62,65,66,67,68,69,71,72,75,76,77,78,85,86,87,88,89,91,92,93,94,95,96,97,99,100,102,103,104,105,106,107,108,109,110,111,113,115,117,120,121,123,124,125,126,127,128,129,131,136,137,138,140,142,143,144,146,148,149,150,151,152,153,154,155,157,160,161,162,163,166,167,169,170,171,172,173,174,175,176,178,180,186,188,189,191,192,200,201,202,206,209,210,211,213,214,217,220,221,222,223,224,225,227,228,229,231,233,234,236,240,242,244,245,256,257,261,264,265,266,267,268,269,270,271,272,273,274,275,276,277,278,279,280,281,282,283,284,285,287,288,291,292,294,295,298,299,300,301,302,303,304,305,306,307,308,309,310,312,314,315,316,317,318,319,320,321,322,323,324,325,329,330,332,336,350,351,352,353,358,359,361,362,364,365,366,367,368,369,371,373,375,377,378,379,381,382,384,385,386,388,389,390,391,392,393,394,395,397,398,401,404,405,406,407,410,411,418,419,421,422,426,427,430,431,432,435,436,437,440,443,444,445,446,447,448,449,452,453,454,457,458,459,460,461,463,465,466,467,469,470,471,473,476,478,481,482,485,488,491,492,493,494,495,496,497,502,504,506,507,508,509,511,512,513,516,517,522,524,525,529,531,532,537,539,540,542,543,544,545,548,549,553,555,557,558,559,560,561,563,565,570,575,576,578,581,583,605,607,608,610,611,612,614,615,616,617,618,629,631,635,637,639,641,645,649,652,655,657,658,661,663,671,675,676,678,680,681,682,683,687,690,693,695,709,710,713,717,720,722,724,725,726,727,729],"0.5":[12,101,609,650,703,728],"0.1":[17,168,190,625,723],"0.2":[98,114,237,313,333,334,335,374,677]},{"1":[21,33,54,60,63,64,75,85,102,116,137,139,147,156,164,177,195,199,203,204,205,208,227,232,246,247,248,249,250,251,252,260,289,290,295,296,297,337,338,347,348,349,356,357,372,376,380,383,396,403,414,416,422,425,434,439,451,472,479,480,486,487,505,514,515,518,520,521,523,527,534,535,566,585,599,602,603,604,619,621,623,624,638,647,670,716],"0.5":[286,402,424,483,485,660,719],"0.2":[475],"0.1":[642]},{"1":[14,22,23,24,25,26,27,28,29,30,31,32,51,70,141,143,165,176,183,193,194,195,196,197,198,218,219,240,253,254,255,339,340,341,342,343,344,345,346,354,355,370,438,455,456,538,541,547,564,600,624,644,659,707,708,730,731],"0.5":[92,428]},{"1":[8,34,35,51,67,74,79,80,81,82,83,84,97,109,113,114,115,118,122,123,133,134,145,157,159,163,172,186,187,212,215,216,225,230,237,241,259,262,268,269,275,278,292,311,360,391,399,408,409,411,412,417,420,431,433,442,462,468,498,503,506,519,526,530,536,545,554,556,569,572,577,606,634,646,654,665,672,679,684,692,695,698,699,702,728],"0.2":[127,441,475],"0.5":[477,694,704,705,706,712]},{"1":[7,33,72,78,98,101,108,112,124,138,142,146,156,162,173,178,182,184,185,197,243,313,326,331,332,333,334,335,363,374,387,390,400,407,413,415,423,464,490,498,499,519,526,528,533,543,567,568,573,574,579,586,601,622,634,640,643,651,653,685,686,696],"0.5":[477,584,691],"0.4":[510]},{"1":[11,16,17,20,35,84,120,121,127,168,190,213,226,242,258,262,263,271,286,287,316,321,348,388,389,402,405,424,450,489,500,501,546,562,571,580,582,609,612,625,628,632,636,664,667,669,674,675,677,688,689,700,701,703,711,716,717,719,721,723],"0.5":[691,697]},null,{"1":[9,36,209,378,504,576]},{"1":[28,29,32,74,194,196,255,341,343,344,354,355,370,438,455,456,644,708,730,732],"0.5":[179,428,534],"0.1":[444,571]},{"1":[81,133,134,140,145,212,297,316,371,642,665],"0.1":[475,580],"0.5":[565],"0.2":[654]},null,null,{"1":[51,79,80,81,126,133,134,145,212,215,216,225,241,260,371,408,442,451,468,496,503,536,565,569,580,642,665,692,702,711],"0.2":[475],"0.5":[654,694,697]},null,null,null,null,null,null,null,null,null,null,null,null,null,{"1":[588,589,590,591,592,593,594,595,596,597,598]}],"item_config_data_compressed":{"0":[9,19,36,40,41,44,56,59,111,117,126,141,148,177,180,186,188,211,233,238,239,252,258,262,274,276,290,315,316,371,388,426,447,468,470,474,475,481,482,504,626,627,668,714,715,721,725],"1":[8,22,23,24,25,26,27,28,29,30,31,33,35,37,39,42,45,47,53,55,60,62,65,66,67,74,77,86,87,93,94,95,102,103,123,124,128,129,135,136,137,140,144,147,161,162,163,167,171,174,176,187,192,194,195,198,200,204,210,212,214,227,236,240,250,256,267,269,272,273,277,280,281,282,285,287,288,291,294,295,298,299,302,304,314,318,320,321,323,325,326,332,337,338,339,340,344,346,349,351,352,357,358,364,366,377,382,383,385,386,391,392,394,396,398,403,404,405,413,420,421,425,427,430,435,436,437,442,446,448,449,452,456,460,467,469,472,473,478,480,484,486,488,498,501,502,509,510,511,512,517,522,523,525,529,537,539,541,543,548,554,555,558,560,561,565,569,576,578,582,603,604,605,607,610,623,624,631,635,639,644,645,649,650,652,655,657,658,659,671,672,675,676,681,686,692,702,707,726],"2":[2,5,6,10,11,13,14,15,16,21,34,38,46,49,54,57,63,71,72,73,75,76,83,84,85,88,89,91,92,96,97,99,100,101,106,107,112,113,115,116,119,120,121,122,125,130,131,134,138,139,142,143,145,152,154,155,156,157,160,164,166,172,175,181,191,193,197,201,202,205,206,207,209,213,217,218,219,220,222,225,226,228,229,231,242,243,246,247,248,251,253,254,257,263,264,266,270,271,275,279,284,286,289,293,296,297,300,303,308,309,312,319,322,324,327,328,329,330,343,348,353,354,355,361,362,365,367,368,369,376,378,379,380,384,393,400,406,409,410,412,416,418,423,428,429,431,432,433,434,439,440,445,450,451,454,455,457,458,463,464,465,466,471,476,479,485,487,491,492,493,505,507,508,513,516,518,519,521,526,530,532,535,536,538,540,542,544,557,559,563,566,568,570,571,574,577,583,585,588,589,591,593,594,595,599,602,608,611,612,614,618,621,632,634,638,641,642,646,647,653,654,656,661,663,665,667,670,673,674,677,679,680,683,684,685,688,693,695,697,699,703,704,705,709,717,719,724,727,729,731],"3":[1,3,7,17,18,20,32,48,50,51,58,64,68,69,70,78,79,80,81,82,90,98,104,109,110,127,132,133,146,150,151,153,158,159,165,170,173,178,179,183,184,185,189,190,196,199,203,208,215,216,221,224,230,234,237,241,244,249,255,259,260,261,265,268,278,283,301,305,306,307,310,311,317,333,334,335,336,341,342,345,347,350,356,359,363,370,372,373,374,375,381,387,389,390,397,399,401,402,407,408,411,414,417,419,424,438,443,444,453,459,461,462,483,490,494,495,496,497,499,500,503,506,514,515,520,524,527,528,533,534,545,546,547,549,553,556,562,564,567,572,573,575,579,580,584,586,590,592,596,597,598,600,601,606,609,615,616,617,619,622,629,633,637,640,651,660,669,682,687,690,694,696,700,701,708,712,713,716,720,722,728,730,732],"4":[4,12,52,105,108,114,118,149,168,169,182,223,232,245,292,313,331,360,395,415,441,477,489,531,550,551,552,581,625,628,636,643,664,678,689,691,698,706,711,723],"-1":[422,710]},"id_with_achievement":[20,32,35,52,73,74,78,83,86,87,88,90,92,93,94,96,97,98,99,100,101,104,105,106,110,112,113,114,119,126,127,131,149,157,162,164,166,168,172,175,179,186,187,188,189,206,207,221,230,232,237,240,244,246,249,252,258,260,263,267,271,276,283,284,286,287,289,292,293,294,297,310,311,312,319,320,321,323,324,325,327,328,331,332,333,334,335,349,357,360,361,362,363,381,386,387,388,389,391,392,393,399,404,405,406,407,408,409,410,411,412,413,414,416,417,433,440,441,442,450,453,455,462,464,468,470,472,475,476,477,479,485,486,488,489,490,496,498,499,500,501,504,510,511,512,513,514,515,516,517,518,519,520,521,522,523,524,525,526,527,528,529,530,531,532,533,534,535,536,537,538,539,540,541,542,543,544,545,546,547,548,549,555,562,565,568,576,577,579,580,584,585,586,602,609,610,611,612,619,621,622,625,628,631,634,639,640,641,642,643,645,646,649,650,651,653,656,665,667,670,671,672,673,674,675,676,677,678,679,680,681,682,683,684,685,686,687,688,689,690,691,692,693,694,695,696,697,698,699,700,701,702,703,704,705,706,709,710,711,712,713,716,717,719,720,721,722,723,724,725,726,727,728,729],"id_with_tags":{"lazarusshared":[238,239,327,328,626,627,633,668,673,697],"nodaily":[482,636],"offensive":[1,2,3,4,5,6,7,8,12,14,17,18,19,21,27,28,29,30,31,32,33,34,35,37,38,39,41,42,44,46,47,48,49,50,51,52,54,55,56,57,58,63,64,65,66,67,68,69,70,71,74,75,76,77,79,80,84,85,86,87,88,89,90,91,93,94,95,97,99,100,101,102,103,104,105,106,107,109,110,111,113,114,116,118,120,121,122,123,124,125,127,128,130,131,132,134,136,137,139,140,141,143,144,145,147,149,150,151,152,153,154,155,158,160,163,164,165,166,167,168,169,170,171,174,175,177,178,181,182,183,187,188,189,190,191,192,194,195,196,197,198,199,200,201,203,206,208,209,213,215,216,217,220,221,222,224,228,229,230,231,233,234,237,238,239,240,241,244,245,246,247,248,249,250,251,252,254,255,256,257,258,259,260,261,263,266,267,268,269,270,271,272,273,275,277,280,283,284,285,286,287,288,289,291,293,294,295,297,300,304,305,306,307,308,309,310,315,316,317,318,319,320,322,323,324,325,327,328,329,330,331,333,336,338,339,340,341,342,343,344,345,347,348,349,350,351,352,353,355,356,357,358,359,360,361,362,364,365,366,367,368,369,370,372,373,374,376,377,378,379,380,381,382,383,384,385,386,388,389,390,391,392,393,394,395,396,397,398,399,400,401,402,403,405,406,407,408,410,411,414,415,416,417,418,419,420,421,422,424,426,427,429,430,431,432,433,434,435,437,438,439,440,441,443,444,445,446,447,450,451,453,454,455,458,459,460,461,462,463,464,465,466,467,468,469,470,471,472,473,475,476,477,478,479,480,481,483,484,485,488,489,490,491,492,494,495,496,497,498,499,500,502,503,504,505,506,507,510,511,512,515,516,517,518,519,520,521,522,523,524,526,527,528,529,530,531,532,533,534,536,537,540,544,545,547,548,550,551,552,553,555,556,557,558,559,561,562,563,564,565,566,567,570,572,573,574,575,576,577,578,579,580,582,583,584,585,586,588,589,590,591,592,593,594,595,596,597,598,599,600,601,602,603,604,605,606,607,608,609,611,616,617,618,619,621,622,623,624,625,628,631,632,634,635,636,637,638,640,641,642,643,644,646,647,649,650,651,653,654,656,657,659,660,661,663,665,667,669,670,673,678,679,680,681,682,683,684,685,686,687,689,691,696,697,698,699,700,701,703,704,705,706,708,709,710,711,712,716,717,719,720,721,722,723,725,726,727,728,729,730,731,732],"nolostbr":[13,15,16,20,22,23,24,25,26,40,45,60,62,72,78,82,92,96,98,108,115,117,119,126,129,133,135,142,146,148,156,157,159,161,162,176,179,180,184,185,186,193,202,204,205,211,214,218,219,225,226,227,236,253,262,274,276,290,292,296,301,311,312,314,326,332,334,346,354,371,412,413,428,436,442,448,452,456,482,487,493,501,513,525,539,541,543,549,560,569,571,610,614,639,658,664,671,675,676,677,692,695,702,707,713,724],"nokeeper":[672],"nogreed":[21,54,241,249,376,580,660,670,672,697],"nochallenge":[161,311,332,482,636]},"active_item_ids":[33,34,35,36,37,38,39,40,41,42,44,45,47,49,56,58,65,66,77,78,83,84,85,86,93,97,102,105,107,111,123,124,126,127,130,133,135,136,137,145,146,147,158,160,164,166,171,175,177,181,186,192,263,282,283,284,285,286,287,288,289,290,291,292,293,294,295,296,297,298,323,324,325,326,338,347,348,349,351,352,357,382,383,386,396,406,419,421,422,427,434,437,439,441,474,475,476,477,478,479,480,481,482,483,484,485,486,487,488,489,490,504,507,510,512,515,516,521,522,523,527,536,545,550,552,555,556,557,577,578,580,582,585,604,605,609,611,622,623,625,628,631,635,636,638,639,640,642,650,653,655,685,687,703,704,705,706,709,710,711,712,713,714,715,719,720,722,723,728,729]}';
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

for (let tag in compressed.id_with_tags) {
  for (let id of compressed.id_with_tags[tag]) {
    if (item_config_data[id]) {
      item_config_data[id][tag] = true;
    }
  }
}

for (let active_id of compressed.active_item_ids) {
  item_config_data[active_id].is_active_item = true;
}
/* 解压完毕 */

function GetItemPoolData(item_pool_id) {
    return item_pool_data[item_pool_id];
}
function GetItemConfig(item_id) {
    return item_config_data[item_id];
}

let safe_is_daily_run = false
let safe_is_greed = false
let safe_challenge_id = undefined
let safe_current_stage = 1
let safe_has_keeper = false //id:14 or 33
let safe_has_lost = false // id:10 only
let safe_has_tlost = false 
let safe_game_start_seed = 0
let safe_has_c691 = false
let safe_has_t88 = false

function IsSafeToGenerage(item_config, flag){
    //assert flag == 6 || flag == 1
    if((flag & 1) != 0){
        /* if(safe_challenge_id == 29) not support */
        if(safe_challenge_id != undefined && item_config["nochallenge"])
            return false;
        if(safe_is_daily_run && item_config["nodaily"])
            return false;
        if(safe_is_greed && item_config["nogreed"])
            return false;
        if(safe_has_lost && item_config["nolostbr"])
            return false;
    }
    if((flag & 4) != 0){
        if((!safe_is_greed) && safe_current_stage >= 7 && item_config.id == 697)
            return false;
        if(safe_has_keeper && item_config["nokeeper"])
            return false;
        if(safe_has_tlost){
            if(!item_config["offensive"])
                return false;
            if(item_config.quality < 2){
                //do something...
                if(RNG_Next(safe_game_start_seed + item_config.id, 18) % 5 == 0){
                    return false;
                }
            }
        }
        if(safe_has_c691){
            if(item_config.quality < 2)
                return false;
            if(RNG_Next(safe_game_start_seed + item_config.id, 19) % 3 == 0){
                return false;
            }
        }
        if(safe_has_t88 && item_config.is_active_item) /* 没有主动数据，所以不支持... */
            return false
    }
    if((flag & 2) != 0){
        // handle achievement, we dont do that
    }
    return true
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
    { input: BigInt("0x1111111111111111"), output: 0x1e3 },
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

    safe_game_start_seed = gameStartSeed
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
                if(IsSafeToGenerage(item_config, 1) && item_quality >= quality_min && item_quality <= quality_max){
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
        if(IsSafeToGenerage(GetItemConfig(selected),6))
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

        safe_is_daily_run = data.safe_is_daily_run
        safe_is_greed = data.safe_is_greed
        safe_challenge_id = data.safe_challenge_id
        safe_current_stage = data.safe_current_stage
        safe_has_keeper = data.safe_has_keeper
        safe_has_lost = data.safe_has_lost
        safe_has_tlost = data.safe_has_tlost
        safe_game_start_seed = data.safe_game_start_seed
        safe_has_c691 = data.safe_has_c691
        safe_has_t88 = data.safe_has_t88

        let items = [];

        let craftable_arr = []
        for(let i=0;i<800;i++){
          craftable_arr[i] = false
        }
  
        let watcher_counter = 0

        let craft_count = data.craft_count
        let real_time_flush = data.real_time_flush
        let wasm = data.enable_wasm && BagOfCraftingWasmHelper
        let base_div = wasm ? 100000 : 1000
        let all_count = 0
        search_dfs(
            data.candidates,
            data.candidates_limit,
            [0, 0, 0, 0, 0, 0, 0, 0],
            (arr)=>{all_count++}
          )

        search_dfs(
            data.candidates,
            data.candidates_limit,
            [0, 0, 0, 0, 0, 0, 0, 0],
            (arr) => {
              // if (arr.length != 8) {
              //   console.log("ERROR!");
              // }
              let result
              if(wasm){
                result = BagOfCraftingWasmHelper.calc(data.seed, arr);
              }else{
                result = get_result(arr, data.seed, craftable_arr);
              }
              if (items[result] == undefined) {
                let marr = []
                for (let i = 0; i < 8; i++) {
                  marr[i] = arr[i];
                }
                items[result] = [marr];
              }else if(items[result].length < craft_count){
                let marr = []
                for (let i = 0; i < 8; i++) {
                  marr[i] = arr[i];
                }
                items[result].push(marr)
              }
              if((++watcher_counter) % base_div == 0){
                if(real_time_flush){
                  this.postMessage({
                      cmd:"report",
                      real_time_flush:true,
                      items:items,
                      craftable_arr:craftable_arr,
                      count:watcher_counter,
                      all_count:all_count,
                  })
                }else{
                  this.postMessage({
                    cmd:"report",
                    real_time_flush:false,
                    /*craftable_arr:craftable_arr,*/
                    count:watcher_counter,
                    all_count:all_count,
                })

                }
              }

            }
          );
        this.postMessage({
            cmd:"result",
            items:items,
            craftable_arr:craftable_arr,
            count:watcher_counter,
            all_count:all_count,
        })
    }
}
`;

let webWorker;
if (window.Worker) {
  /* release */
  webWorker = new Worker(
    "data:text/javascript," + encodeURIComponent(webWorkerText)
  );
} else {
  //其实可以做一个wrapper来支持这些古老的浏览器，但目前没必要
  alert("浏览器不支持worker特性，该更新辣");
  webWorker = undefined;
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
      1: { count: 8, order: 1 },
      2: { count: 8, order: 2 },
      // 3:{count:8,order:3},
      // 4:{count:1,order:40},
      // 5:{count:1,order:41},
      // 6:{count:1,order:42},
      // 7:{count:1,order:43},
      // 8:{count:8,order:8},
      // 23:{count:2,order:9},
      // 25:{count:1,order:39},
      // 29:{count:8,order:11},
    };
    for (let i = 1; i < 30; i++) {
      let count = 0;
      if (predefined[i]) count = predefined[i].count;

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
        fold: true,
        items: [0, 0, 0, 0, 0, 0, 0, 0],
      };
    }

    /* resort */
    {
      let changed = false;
      do {
        changed = false;
        for (let i = 0; i < items.length - 1; i++) {
          if (
            (items[i].count == 0 && items[i + 1].count > 0) ||
            (items[i].count != 0 &&
              items[i + 1].count != 0 &&
              predefined[items[i].id].order >=
                predefined[items[i + 1].id].order)
          ) {
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
      draging_index: -1,
      drag_over_index: -1,
      results: results,
      seed: "JKD9 Z0C9",
      display_mode: "crafted" /* valid, craftable, crafted */,
      craftable_count: 0,
      crafted_count: 0,
      calculated_count: 0,
      all_calculate_count: 0,
      worker_status: "idle" /* idle, busy */,
      craft_count: 1,
      real_time_flush: "true",
      recipe_name:{
        0:"空槽位",
        1:"红心",
        2:"魂心（魂心/半魂心）",
        3:"黑心",
        4:"永恒之心",
        5:"金心",
        6:"骨心",
        7:"腐心",
        8:"硬币",
        9:"镍币/黏性镍币",
        10:"铸币",
        11:"幸运硬币",
        12:"钥匙",
        13:"金钥匙",
        14:"充能钥匙",
        15:"炸弹",
        16:"金炸弹",
        17:"巨型炸弹",
        18:"微型电池",
        19:"小电池",
        20:"超级电池",
        21:"卡牌/紧急联络",
        22:"药丸",
        23:"符文/灵魂石",
        24:"骰子碎片",
        25:"碎裂的钥匙",
        26:"金硬币",
        27:"金药丸",
        28:"金电池",
        29:"屎块",
        30:"其它",
      },
      no_wasm: !(fetch && WebAssembly != null),
      enable_wasm: fetch && WebAssembly != null ? "true" : "false",
      safe_is_daily_run: false,
      safe_is_greed: false,
      safe_challenge_id: false,
      safe_current_stage: 1,
      safe_has_keeper: false,
      safe_has_lost: false,
      safe_has_tlost: false,
      safe_game_start_seed: false,
      safe_has_c691: false,
      safe_has_t88: false,
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
    clear_items() {
      for (let i = 0; i < this.items.length; i++) {
        this.items[i].count = 0;
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
      let seed;
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
      this.worker_status = "busy";
      webWorker.postMessage({
        cmd: "start",
        candidates: candidates,
        candidates_limit: candidates_limit,
        seed: seed,
        craft_count: +this.craft_count,
        real_time_flush: this.real_time_flush == "true",
        enable_wasm: this.enable_wasm == "true",

        safe_is_daily_run: this.safe_is_daily_run,
        safe_is_greed: this.safe_is_greed,
        safe_challenge_id: this.safe_challenge_id,
        safe_current_stage: this.safe_current_stage,
        safe_has_keeper: this.safe_has_keeper,
        safe_has_lost: this.safe_has_lost,
        safe_has_tlost: this.safe_has_tlost,
        safe_game_start_seed: this.safe_game_start_seed,
        safe_has_c691: this.safe_has_c691,
        safe_has_t88: this.safe_has_t88,
      });

      for (let i = 0; i < this.results.length; i++) {
        this.results[i].valid = false;
        this.results[i].crafted = false;
        this.results[i].items = [];
        this.results[i].fold = true;
      }
      this.all_calculate_count = 0;
      this.calculated_count = 0;
    },
  },
};

webWorker.onmessage = function (event) {
  let data = event.data;
  if (data.cmd == "result" || data.cmd == "report") {
    let vue_data = window.decraftingVueRoot;
    if (data.cmd == "result") {
      vue_data.worker_status = "idle";
    }
    let craftable_count = 0;
    let crafted_count = 0;
    if (data.cmd == "result" || data.real_time_flush) {
      for (let i = 1; i < vue_data.results.length; i++) {
        if (data.items[i]) {
          vue_data.results[i].valid = true;
          vue_data.results[i].crafted = true;
          vue_data.results[i].craftable = true;
          vue_data.results[i].items = data.items[i];
          craftable_count++;
          crafted_count++;
        } else {
          vue_data.results[i].crafted = false;
          vue_data.results[i].valid = data.craftable_arr[i];
          vue_data.results[i].craftable = data.craftable_arr[i];
          vue_data.results[i].items = [];
          if (data.craftable_arr[i]) craftable_count++;
        }
      }
    } else {
      /*for (let i = 1; i < vue_data.results.length; i++) {
        vue_data.results[i].crafted = true;
        vue_data.results[i].valid = data.craftable_arr[i];
        vue_data.results[i].craftable = data.craftable_arr[i];
        if (data.craftable_arr[i]) craftable_count++;
      }*/
    }
    vue_data.craftable_count = craftable_count;
    vue_data.crafted_count = crafted_count;
    vue_data.calculated_count = data.count;
    vue_data.all_calculate_count = data.all_count
  }
};
</script>
<style scoped>
.flip-list-move {
  transition: transform 0.2s ease;
}

/* .flip-item-list-move {
  transition: transform 0.1s ease;
} */

.decrafting_recipe {
  image-rendering: pixelated;
  transform: scale(2);
  width: 16px;
  height: 16px;
  display: inline-block;
  margin: 4px;
  background-image: url("https://huiji-public.huijistatic.com/isaac/uploads/8/89/Crafting_ui_sprite.png");
}
.decrafting_recipe_result {
  transform: scale(1.5) !important;
  width: 16px;
  height: 16px;
  display: inline-block;
  margin: 1.5px;
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