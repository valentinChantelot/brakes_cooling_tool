import { getAlgorithmData } from "./data.js";
import { NO_ACTION_DELAY } from "./constants.js";

export function createAlgorithm() {
  const data = getAlgorithmData();
  const sequence = [];
  let temperatureEntry = undefined;
  let temperatureParams = undefined;
  let actionData = undefined;

  let totalDuration = undefined;
  let openedDuration = undefined;
  let openedDurationPercentage = undefined;
  let closedDuration = undefined;
  let closedDurationPercentage = undefined;

  function _setTemperatureData() {
    temperatureEntry = data.getEntryTemperature();
    temperatureParams = data.getTemperatureParams();
    return;
  }

  function _setActionData() {
    // Reduce temperature
    if (parseInt(temperatureEntry) >= parseInt(temperatureParams.secondLevel)) {
      actionData = data.getReduceTemperatureParams();
      return;
    }

    // Maintain temperature
    if (parseInt(temperatureEntry) >= parseInt(temperatureParams.firstLevel)) {
      actionData = data.getMaintainTemperatureParams();
      return;
    }

    // Do nothing
    actionData = undefined;
    return;
  }

  function _isOdd(number) {
    if (number % 2 == 0) return false;
    return true;
  }

  function _calculateSequence() {
    sequence.length = 0; // emptying the sequence

    if (!actionData) {
      // if there is no action, we wait for the NO_ACTION_DELAY duration
      sequence.push({ state: "LOW", duration: NO_ACTION_DELAY });
      return;
    }

    const { iterations, closingTime, openingTime } = actionData;
    for (let i = 1; i < iterations; i++) {
      _isOdd(i)
        ? sequence.push({ state: "HIGH", duration: openingTime })
        : sequence.push({ state: "LOW", duration: closingTime });
    }
    return;
  }

  function _calculateStats() {
    if (!actionData) {
      // if there is no action, the stats are simple
      totalDuration = NO_ACTION_DELAY;
      openedDuration = 0;
      openedDurationPercentage = 0;
      closedDuration = NO_ACTION_DELAY;
      closedDurationPercentage = 100;
      return;
    }

    totalDuration = 0;
    openedDuration = 0;
    openedDurationPercentage = 0;
    closedDuration = 0;
    closedDurationPercentage = 0;

    sequence.forEach((r) => {
      const intDuration = parseInt(r.duration);
      totalDuration += intDuration;

      if (r.state === "HIGH") {
        openedDuration += intDuration;
      }

      if (r.state === "LOW") {
        closedDuration += intDuration;
      }
    });

    openedDurationPercentage = (openedDuration * 100) / totalDuration;
    closedDurationPercentage = (closedDuration * 100) / totalDuration;
    return;
  }

  function refreshData() {
    _setTemperatureData();
    _setActionData();
    _calculateSequence();
    _calculateStats();
    return;
  }

  function getResults() {
    return sequence;
  }

  function getStats() {
    return {
      totalDuration,
      openedDuration,
      openedDurationPercentage: openedDurationPercentage.toFixed(2),
      closedDuration,
      closedDurationPercentage: closedDurationPercentage.toFixed(2),
    };
  }

  return {
    refreshData,
    getResults,
    getStats,
  };
}
