# WebAssembly Fractals

[![Build Status](https://jeremylikness.visualstudio.com/wasm-trees/_apis/build/status/JeremyLikness.wasm-trees?branchName=master)](https://jeremylikness.visualstudio.com/wasm-trees/_build/latest?definitionId=10&branchName=master)

![Release Status](https://jeremylikness.vsrm.visualstudio.com/_apis/public/Release/badge/08f50b65-86c7-4848-b3c4-02391687c800/1/1)

This repo contains C code that compiles to WebAssembly. It generates various graphics using pre-determined parameters for "The Chaos Game." There is a mode to distort that randomly "nudges" the parameters to produce new results.

> This repository is continuously built and deployed using free Azure Pipelines. If you're interested in how it was setup and configured to build automatically and deploy to low cost Azure Storage Static Websites, read [Deploy WebAssembly from GitHub to Azure Storage Static Websites with Azure Pipelines](https://jlik.me/fzi).

The intent of the project is to demonstrate how to share memory between JavaScript and Wasm code. A buffer is allocated in JavaScript and passed to WebAssembly, and WebAssembly renders to a buffer that is passed back.

Two helper scripts, one for Windows and one for Bash environments, are included. They use a pre-configured Docker file to compile the WebAssembly. They are intended to be run from the `src` directory and will copy the generated assets into `web`.

The generated `trees.js` and `trees.wasm` are included in `dist` case you want to get up and running quickly; simply copy them into the `web` directory to get started.

🔗 Read the related article: [Play the Chaos Game to Understand WebAssembly Memory Management](https://blog.jeremylikness.com/play-the-chaos-game-to-understand-webassembly-memory-management-5feaa7553a5)

👀 [Live Demo](https://jlikme.z13.web.core.windows.net/wasm/wasm-trees)
