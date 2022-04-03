# decrafting

这是灰机wiki上[Decrafting](https://isaac.huijiwiki.com/wiki/Decrafting)的源代码。

使用`vue3`开发，`node v16.13.1`，`vue cli`。

## 安装依赖
```
npm install
```

## 编译、热重载调试
```
npm run serve
```

已经将灰机wiki中的部分css放到`index.html`，可以用于调试。

## 编译、用于生产环境
```
npm run build
```

添加了`transform.js`，会先将生成的app.js和chunk-vendors.js合并，然后做`Babel`转换，再做`es3ify-mw`，得到mediawiki支持的js，输出到`dist/js/output.js`，直接将此文件上传到wiki的`Gadget:Decrafting.app.js`即可。

## Lints and fixes files
```
npm run lint
```
# 道具品质信息来源

道具品质信息生成自[这个工程](https://github.com/frto027/IsaacBagOfCraftingHuijiGadget)，`src/App.vue`里面的compressed变量，就是那个写在字符串里面的WebWorker。

wasm的品质信息是单独生成的，编译在二进制代码里面。

# wasm的编译

修改以下路径：
- `boswasm/build_em++.bat`中的`D:\emsdk\emsdk_env.bat`，需要自行下载wmsdk
- `boswasm/gen_item_data.py`中的三个xml文件位置（提前解包好游戏）

```
cd boswasm
python gen_item_data.py
./build_em++.bat
```

编译后会生成data.txt文件，把这个文件内容拷贝到`src/App.vue`的`webWorkerText`变量里面对应位置上。

# 有些做法太粗暴了

嗯。

问题不大。

折腾出来的东西，暂时感觉没必要花时间做优雅，辛辛苦苦写好几天的编译脚本，就为了替自己复制粘贴一下，别人还看不懂，没必要。
## Customize configuration
See [Configuration Reference](https://cli.vuejs.org/config/).
