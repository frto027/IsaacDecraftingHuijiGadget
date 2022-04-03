import base64

output = "data:application/wasm;base64,"

with open('main.wasm','rb') as f:
    output = output + base64.b64encode(f.read()).decode()

with open("data.txt",'w') as f:
    f.write(output)

