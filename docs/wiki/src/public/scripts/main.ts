// Since I can't figure out how to get tsc to compile this client-side code with
// support for the 'import' and 'require' statement, I'm forced to put all the code
// into one file. If someone finds a good way to do this, without re-doing the
// directory structure of the entire project, feel free to create a PR.
//
// Sorry in advance.

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
        // TODO: do something perhaps...
    };

    // Make sure the DOM is loaded before we try to manipulate it
    window.addEventListener('DOMContentLoaded', init);
})();
