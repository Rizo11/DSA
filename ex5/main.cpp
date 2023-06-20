// Mukhammadrizo Maribjonov DS-AI 4


#include <iostream>
#include <unordered_set>
#include <string>
#include <vector>
using namespace std;

unordered_set<string> dict;
vector<string> words;

// split the text and put in words
bool canSplit(const string& text, int start, vector<bool>& memo) {
    if (start == text.length()) {
        return true;
    }
    if (memo[start]) {
        return false;
    }
    memo[start] = true;
    for (int i = start + 1; i <= text.length(); i++) {
        string prefix = text.substr(start, i - start);
        if (dict.count(prefix) > 0 && canSplit(text, i, memo)) {
            words.push_back(prefix);
            return true;
        }
    }
    return false;
}

int main() {
    int n, k;
    cin >> n >> k;

    // Read in the dictionary words
    for (int i = 0; i < n; i++) {
        string word;
        cin >> word;
        dict.insert(word);
    }

    // Read in the corrupted text
    string text;
    cin >> text;

    // Use dynamic programming to split the text into words
    vector<bool> memo(k, false);
    canSplit(text, 0, memo);

    // Output the words
    for (int i = words.size() - 1; i >= 0; i--) {
        cout << words[i] << " ";
    }
    cout << endl;

    return 0;
}