export function getAlgorithmData() {
  // Entry temperature
  const temperature = document.querySelector(
    '[data-js-selector="temperature"]'
  );

  // Temperature params
  const firstLevelInput = document.querySelector(
    '[data-js-selector="temperature_level1"]'
  );
  const secondLevelInput = document.querySelector(
    '[data-js-selector="temperature_level2"]'
  );

  // Maintain temperature
  const maintain_iterations = document.querySelector(
    '[data-js-selector="maintain_iterations"]'
  );
  const maintain_openingTime = document.querySelector(
    '[data-js-selector="maintain_openingTime"]'
  );
  const maintain_closingTime = document.querySelector(
    '[data-js-selector="maintain_closingTime"]'
  );

  // Reduce temperature
  const reduce_iterations = document.querySelector(
    '[data-js-selector="reduce_iterations"]'
  );
  const reduce_openingTime = document.querySelector(
    '[data-js-selector="reduce_openingTime"]'
  );
  const reduce_closingTime = document.querySelector(
    '[data-js-selector="reduce_closingTime"]'
  );

  function getEntryTemperature() {
    return temperature.value;
  }

  function getTemperatureParams() {
    return {
      firstLevel: firstLevelInput.value,
      secondLevel: secondLevelInput.value,
    };
  }

  function getReduceTemperatureParams() {
    return {
      iterations: maintain_iterations.value,
      openingTime: maintain_openingTime.value,
      closingTime: maintain_closingTime.value,
    };
  }

  function getMaintainTemperatureParams() {
    return {
      iterations: reduce_iterations.value,
      openingTime: reduce_openingTime.value,
      closingTime: reduce_closingTime.value,
    };
  }

  return {
    getEntryTemperature,
    getTemperatureParams,
    getReduceTemperatureParams,
    getMaintainTemperatureParams,
  };
}
