import { createAlgorithm } from "./algorithm.js";

function onLoad() {
  const temperature = document.querySelector(
    '[data-js-selector="temperature"]'
  );
  const launchButton = document.querySelector(
    '[data-js-selector="launchButton"]'
  );

  const algorithm = createAlgorithm();

  launchButton.addEventListener("click", function () {
    algorithm.refreshData();
    console.log(algorithm.getResults());
    console.log(algorithm.getStats());
  });
}

window.addEventListener("load", onLoad);
