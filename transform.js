const babel = require('@babel/core')

var transform = require('es3ify').transform;
var transformMW = require('es3ify-mw').transform;
var fs = require('fs');

console.log('transforming...')

var app_content = ''
var chunk_content = ''

for(filename of fs.readdirSync('dist/js/')){
    if(filename.endsWith('.js')){
        if(filename.startsWith('app.')){
            app_content += fs.readFileSync('dist/js/'+filename,'utf-8') + "\n"
        }
        if(filename.startsWith('chunk-vendors.')){
            chunk_content += fs.readFileSync('dist/js/'+filename,'utf-8') + "\n"
        }
    }
}

var merged = app_content + chunk_content

var originalFileContents = ''

for(line of merged.split('\n')){
    if(line.length > 0 && !line.startsWith('//'))
        originalFileContents += line + "\n"
}

originalFileContents = babel.transform(originalFileContents,{
    configFile:false, /* 不要用vue的config file，会出错 */
    comments:false,
    presets:[
        ['@babel/preset-env',{targets:['IE 8']}],
    ]
}).code

originalFileContents = transform(transformMW(originalFileContents));

fs.writeFileSync('dist/js/output.js', originalFileContents);

console.log('over. output at dist/js/output.js')