docker run -it --rm -v %cd%:/src trzeci/emscripten emcc trees.c -O2 -s WASM=1 -s EXPORTED_FUNCTIONS="['_renderTree', '_getAddresses']" -s EXTRA_EXPORTED_RUNTIME_METHODS="['ccall','cwrap']" -o trees.js -s ALLOW_MEMORY_GROWTH=1
copy trees.js ..\web\
copy trees.wasm ..\web\