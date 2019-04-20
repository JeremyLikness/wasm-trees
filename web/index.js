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
    const variablesDiv = document.getElementById("variables");

    const renderTree = Module.cwrap("renderTree", "number", ["array", "number", "number", "number", "number"]);
    const loadValues = Module.cwrap("getAddresses", "number", []);

    const getValues = () => {
        let variables = ['a', 'b', 'c', 'd', 'e', 'f'];
        const ptr = loadValues();
        let str = 'Variables:';
        variables.forEach((val, idx) => {
            const varOffset = Module.HEAPU32[ptr / Uint32Array.BYTES_PER_ELEMENT + idx];
            str += "\n";
            for (let i = 0; i < 4; i += 1) {
                const value = Module.HEAPF32[varOffset / Float32Array.BYTES_PER_ELEMENT + i];
                str += `${val}[${i}]=${value.toFixed(2)}  `;
            }
        });
        return str;
    };

    const render = (model, distort) => {
        ctx.clearRect(0, 0, width, height);
        console.time(`Render${state.counter}`);
        let typedArray = new Uint8Array(width * height);

        // draw grid lines
        const mid_x = width / 2;
        const mid_y = height / 2;
        for (let x = 0; x < width; x += 1) {
            for (let y = 0; y < height; y += 1) {
                typedArray[mid_y * width + x] =
                    typedArray[y * width + mid_x] = 1;
            }
        }

        let buffer = Module._malloc(typedArray.length * typedArray.BYTES_PER_ELEMENT);
        console.log(`Buffer: ${buffer}`);
        Module.HEAPU8.set(typedArray, buffer / typedArray.BYTES_PER_ELEMENT);
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
        variablesDiv.innerText = getValues();
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