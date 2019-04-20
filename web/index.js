const app = () => {
    
    const state = {
        counter: 1,
        model: 1,
        distort: 0
    };
    
    const canvas = document.getElementById("fractalCanvas");
    const ctx = canvas.getContext("2d");
    const width = canvas.width;
    const height = canvas.height;
    const distortButton = document.getElementById("distort");
    
    const renderTree = Module.cwrap("renderTree", "number", ["array", "number", "number", "number", "number"]);
    
    const render = (model, distort) => {
        ctx.clearRect(0, 0, width, height);
        console.time(`Render${state.counter}`);
        let typedArray = new Uint8Array(width * height);
        let buffer = Module._malloc(typedArray.length * typedArray.BYTES_PER_ELEMENT);
        console.log(`Buffer: ${buffer}`);
        Module.HEAPU8.set(typedArray, buffer);
        let offset = renderTree(typedArray, width, height, model, distort);
        console.timeEnd(`Render${state.counter}`);
        console.log(`Offset: ${offset}`);
        let imageBuffer = new Uint8ClampedArray(width * height * 4);
        for (let idx = 0; idx < typedArray.length; idx += 1) {
            let color = Module.HEAPU8[offset + idx];
            if (color != 0) {
                let pos = idx * 4;
                imageBuffer[pos] = imageBuffer[pos + 1] = imageBuffer[pos + 2] = color;
                imageBuffer[pos + 3] = 255;
            }
        }
        Module._free(buffer);
        let imageData = new ImageData(imageBuffer, width, height);
        ctx.putImageData(imageData, 0, 0);
        state.counter++;
    }
    
    const wireButton = (id, model) => {
        const btn = document.getElementById(id);
        btn.addEventListener("click", () => {
            state.model = model;
            render(model, 0);
        });
    }
    
    const loop = () => {
        if (state.distort === 1) {
            render(state.model, 1);
        }
        requestAnimationFrame(loop);
    };
    
    distortButton.addEventListener("click", () => {
        state.distort = state.distort === 0 ? 1 : 0;
        distortButton.innerText = state.distort ? "Freeze" : "Distort";
    });
    
    ["tree", "fern", "triangle", "maze", "koch"]
        .forEach((id, model) => wireButton(id, model + 1));
    
    setTimeout(loop, 100);
};

setTimeout(app, 100);