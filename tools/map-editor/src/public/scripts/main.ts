// Since I can't figure out how to get tsc to compile this client-side code with
// support for the 'import' and 'require' statement, I'm forced to put all the code
// into one file. If someone finds a good way to do this, without re-doing the
// directory structure of the entire project, feel free to create a PR.
//
// Sorry in advance.

// ==================================
// = Utility types and functions ====
// ==================================
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
};

// Returns a given element in the DOM
const $ = (what: string): HTMLElement | null => {
    return document.querySelector(what);
};

// Returns a NodeList of all selected elements in DOM
const _ = (what: string): NodeListOf<Element> => {
    return document.querySelectorAll(what);
};

// ==========================
// = Main initialization ====
// ==========================
(function () {
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

        // Translate it before performing any drawing/manipulation
        // to avoid blurry lines and weird scaling
        context.translate(0.5, 0.5);

        const viewport_ref: CanvasRef = {
            canvas: {
                object: viewport,
                context: context,
                dimensions: [width, height],
            },
        };

        // Retranslate it
        context.translate(-0.5, -0.5);
    };

    // Make sure the DOM is loaded before we try to manipulate it
    window.addEventListener('DOMContentLoaded', init);
})();
