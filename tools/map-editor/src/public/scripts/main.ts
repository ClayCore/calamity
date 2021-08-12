// Since I can't figure out how to get tsc to compile this client-side code with
// support for the 'import' and 'require' statement, I'm forced to put all the code
// into one file. If someone finds a good way to do this, without re-doing the
// directory structure of the entire project, feel free to create a PR.
//
// Sorry in advance.

// Utility types and functions           //
// ------------------------------------- //

// Used for passing around references
// to the context and canvas, also used
// for passing around various configuration options
// and not having to type out the long types every time
type CanvasRef = {
    canvas: {
        object: HTMLCanvasElement;
        context: CanvasRenderingContext2D;
        dimensions: [number, number];
    };
    options: {
        grid: {
            cell_size: number;
            color: string;
        };
    };
};

// Returns a given element in the DOM
const $ = (what: string): HTMLElement | null => {
    return document.querySelector(what);
};

// Returns a NodeList of all selected elements in DOM
const _ = (what: string): NodeListOf<Element> => {
    return document.querySelectorAll(what);
};

// Canvas manipulation           //
// ----------------------------- //
function createGrid(ref: CanvasRef) {
    const [width, height] = ref.canvas.dimensions;
    const { context } = ref.canvas;
    const { cell_size, color } = ref.options.grid;

    context.lineWidth = 1;
    context.strokeStyle = color;

    for (let x = cell_size; x < width; x += cell_size) {
        context.moveTo(x, 0);
        context.lineTo(x, height);
    }

    for (let y = cell_size; y < height; y += cell_size) {
        context.moveTo(0, y);
        context.lineTo(width, y);
    }

    context.stroke();
    context.closePath();
}

// Main initialization           //
// ----------------------------- //
(function () {
    const draw = (ref: CanvasRef) => {
        const { context } = ref.canvas;

        // Translate canvas to avoid blurry lines
        context.translate(0.5, 0.5);

        // Draw stuff here.
        createGrid(ref);

        // Shift the canvas back after drawing
        context.translate(-0.5, -0.5);
    };

    const init = () => {
        // Get the main canvas viewport and its context
        const viewport = $('canvas#viewport') as HTMLCanvasElement;
        const context = viewport?.getContext('2d') as CanvasRenderingContext2D;

        // Get the dimensions of the page
        // and dynamically change the dimensions
        // of the canvas
        const { width, height } = viewport?.getBoundingClientRect();
        viewport.width = width;
        viewport.height = height;

        // Fill the canvas
        context!.fillStyle = '#000000';
        context!.fillRect(0, 0, width, height);

        const viewport_ref: CanvasRef = {
            canvas: {
                object: viewport,
                context: context,
                dimensions: [width, height],
            },
            options: {
                grid: {
                    cell_size: 64,
                    color: '#ffffff',
                },
            },
        };

        // Draw to the canvas
        draw(viewport_ref);
    };

    // Make sure the DOM is loaded before we try to manipulate it
    window.addEventListener('DOMContentLoaded', init);
})();
