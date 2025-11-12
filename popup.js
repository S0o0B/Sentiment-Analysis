document.getElementById("analyze-page").addEventListener("click", async () => {
  const [tab] = await chrome.tabs.query({ active: true, currentWindow: true });
  chrome.scripting.executeScript({
    target: { tabId: tab.id },
    files: ["vader.js", "content.js"]
  }, () => {
    chrome.tabs.sendMessage(tab.id, { action: "analyzePage" });
  });
});

document.getElementById("analyze-selection").addEventListener("click", async () => {
  const [tab] = await chrome.tabs.query({ active: true, currentWindow: true });
  chrome.scripting.executeScript({
    target: { tabId: tab.id },
    files: ["vader.js", "content.js"]
  }, () => {
    chrome.tabs.sendMessage(tab.id, { action: "analyzeSelection" });
  });
});
