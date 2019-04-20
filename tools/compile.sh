docker run -it --rm -v $(pwd):/src trzeci/emscripten emcc trees.c -O2 -s WASM=1 -s EXPORTED_FUNCTIONS=['_renderTree']  -s EXTRA_EXPORTED_RUNTIME_METHODS=['ccall', 'cwrap'] -o trees.js --closure 1 -s ALLOW_MEMORY_GROWTH=1
cp trees.js ../web
cp trees.wasm ../web