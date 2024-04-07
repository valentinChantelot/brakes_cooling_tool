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
    const {
      totalDuration,
      openedDuration,
      openedDurationPercentage,
      closedDuration,
      closedDurationPercentage,
    } = algorithm.getStats();

    statResultTotal.innerHTML = "";
    statResultOpen.innerHTML = "";
    statResultClose.innerHTML = "";

    statResultTotal.innerText = totalDuration;
    statResultOpen.innerText = `${openedDuration} - ${openedDurationPercentage}%`;
    statResultClose.innerText = `${closedDuration} - ${closedDurationPercentage}%`;
    return;
  }

  function _renderGraph() {
    // reset graph
    graph.innerHTML = "";
    // reset animation
    document.documentElement.style.setProperty(
      "--dynamic-js-animation-name",
      "none"
    );
    graph.offsetHeight;
    document.documentElement.style.setProperty(
      "--dynamic-js-animation-name",
      "shrinkWidth"
    );

    const results = algorithm.getResults();
    const { totalDuration } = algorithm.getStats();

    results.forEach((r) => {
      const li = document.createElement("li");
      li.classList.add(r.state === "HIGH" ? "high" : "low");
      li.style.width = `${(parseInt(r.duration) * 100) / totalDuration}%`;
      graph.appendChild(li);
    });

    document.documentElement.style.setProperty(
      "--dynamic-js-animation-duration",
      `${totalDuration}ms`
    );

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
