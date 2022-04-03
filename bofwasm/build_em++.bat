D:\emsdk\emsdk_env.bat && em++ main.cpp --no-entry -DUSE_EMCC -O3 -s WASM=1 -o main.wasm && python gen_wasm_files.py
