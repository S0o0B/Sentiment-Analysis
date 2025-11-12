chrome.runtime.onInstalled.addListener(() => {
  chrome.contextMenus.create({
    id: "analyzeSelection",
    title: "Analyze Sentiment of Selection",
    contexts: ["selection"]
  });
});

chrome.contextMenus.onClicked.addListener((info, tab) => {
  if (info.menuItemId === "analyzeSelection") {
    chrome.scripting.executeScript({
      target: { tabId: tab.id },
      files: ["vader.js", "content.js"]
    }, () => {
      chrome.tabs.sendMessage(tab.id, { action: "analyzeSelection" });
    });
  }
});
