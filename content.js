import { analyzeSentiment } from "./vader.js";

chrome.runtime.onMessage.addListener(async (message) => {
  let text = "";

  if (message.action === "analyzePage") {
    text = document.body.innerText;
  } else if (message.action === "analyzeSelection") {
    text = window.getSelection().toString();
  }

  if (!text.trim()) {
    alert("No text found!");
    return;
  }

  const score = await analyzeSentiment(text);

  let sentiment = "Neutral";
  if (score > 0.5) sentiment = "Positive";
  else if (score < -0.5) sentiment = "Negative";

  alert(`Sentiment: ${sentiment}\nScore: ${score.toFixed(2)}`);
});
