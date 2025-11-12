let vaderLexicon = {};

async function loadVaderLexicon() {
  if (Object.keys(vaderLexicon).length > 0) return vaderLexicon; // already loaded

  const response = await fetch(chrome.runtime.getURL("vader_lexicon.txt"));
  const text = await response.text();

  const lines = text.split("\n");

  for (const line of lines) {
    if (line.trim() === "" || line.startsWith("#")) continue;

    // Each line is formatted like: "word  score  std_dev  [ratings...]"
    const parts = line.trim().split(/\s+/);
    const word = parts[0];
    const score = parseFloat(parts[1]);
    if (!isNaN(score)) {
      vaderLexicon[word.toLowerCase()] = score;
    }
  }

  console.log("✅ VADER lexicon loaded:", Object.keys(vaderLexicon).length, "entries");
  return vaderLexicon;
}

export async function analyzeSentiment(text) {
  await loadVaderLexicon();

  const words = text.toLowerCase().replace(/[^\w\s]/g, "").split(/\s+/);
  let total = 0;
  let count = 0;

  for (const word of words) {
    if (vaderLexicon[word] !== undefined) {
      total += vaderLexicon[word];
      count++;
    }
  }

  const score = count ? total / count : 0;
  return score;
}
