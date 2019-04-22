# WebAssembly Fractals

This repo contains C code that compiles to WebAssembly. It generates various graphics using pre-determined parameters for "The Chaos Game." There is a mode to distort that randomly "nudges" the parameters to produce new results.

The intent of the project is to demonstrate how to share memory between JavaScript and Wasm code. A buffer is allocated in JavaScript and passed to WebAssembly, and WebAssembly renders to a buffer that is passed back.

Two helper scripts, one for Windows and one for Bash environments, are included. They use a pre-configured Docker file to compile the WebAssembly. They are intended to be run from the `src` directory and will copy the generated assets into `web`.

The generated `trees.js` and `trees.wasm` are included in `dist` case you want to get up and running quickly; simply copy them into the `web` directory to get started.

🔗 Read the related article: [Play the Chaos Game to Understand WebAssembly Memory Management](https://blog.jeremylikness.com/play-the-chaos-game-to-understand-webassembly-memory-management-5feaa7553a5)
