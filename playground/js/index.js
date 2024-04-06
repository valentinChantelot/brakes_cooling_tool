import { createAlgorithm } from "./algorithm.js";

function onLoad() {
  /**
   * JS Selectors
   */
  const launchButton = document.querySelector(
    '[data-js-selector="launchButton"]'
  );
  const statResultTotal = document.querySelector(
    '[data-js-selector="statResult__total"]'
  );
  const statResultOpen = document.querySelector(
    '[data-js-selector="statResult__open"]'
  );
  const statResultClose = document.querySelector(
    '[data-js-selector="statResult__close"]'
  );
  const graphContainer = document.querySelector(
    '[data-js-selector="graphContainer"]'
  );
  const graph = document.querySelector('[data-js-selector="graph"]');

  /**
   * Constants and private functions
   */
  const algorithm = createAlgorithm();
  function _renderStats() {
    const { totalDuration, openedDuration, closedDuration } =
      algorithm.getStats();

    statResultTotal.innerHTML = "";
    statResultOpen.innerHTML = "";
    statResultClose.innerHTML = "";

    statResultTotal.innerText = totalDuration;
    statResultOpen.innerText = openedDuration;
    statResultClose.innerText = closedDuration;
    return;
  }

  function _renderGraph() {
    const results = algorithm.getResults();

    results.forEach((r) => {
      const li = document.createElement("li");
      li.classList.add(r.state === "HIGH" ? "high" : "low");
      graph.appendChild(li);
    });

    return;
  }

  /**
   * Event listeners
   */
  launchButton.addEventListener("click", function () {
    algorithm.refreshData();
    _renderStats();
    _renderGraph();

    if (graphContainer.style.display !== "block") {
      graphContainer.style.display = "block";
    }
  });
}

window.addEventListener("load", onLoad);
