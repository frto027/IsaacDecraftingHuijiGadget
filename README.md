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

## Customize configuration
See [Configuration Reference](https://cli.vuejs.org/config/).
