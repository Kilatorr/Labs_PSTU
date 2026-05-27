#include <iostream>
#include <string>

using namespace std;

int boyerMooreSearch(const string& text, const string& pattern) {
    int textLen = text.size();
    int patternLen = pattern.size();


    if (textLen == 0 || patternLen == 0 || patternLen > textLen) {
        return -1;
    }

    const int ALPHABET_SIZE = 256;
    const int MIN_SHIFT = 1;

    
    int badChar[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        badChar[i] = -1;
    }
    for (int i = 0; i < patternLen; ++i) {
        badChar[pattern[i]] = i;
    }


    int* suffix = new int[patternLen];
    int* goodShift = new int[patternLen];

    int g = patternLen - 1, f = patternLen - 1;
    suffix[patternLen - 1] = patternLen;

    for (int i = patternLen - 2; i >= 0; --i) {
        if (i > g && suffix[i + patternLen - 1 - f] < i - g) {
            suffix[i] = suffix[i + patternLen - 1 - f];
        } else {
            if (i < g) g = i;
            f = i;
            while (g >= 0 && pattern[g] == pattern[patternLen - 1 - (f - g)]) {
                --g;
            }
            suffix[i] = f - g;
        }
    }

    for (int i = 0; i < patternLen; i++) {
        goodShift[i] = patternLen;
    }

    int j = 0;
    for (int i = patternLen - 1; i >= 0; i--) {
        if (suffix[i] == i + 1) {
            for (; j < patternLen - 1 - i; j++) {
                if (goodShift[j] == patternLen) {
                    goodShift[j] = patternLen - 1 - i;
                }
            }
        }
    }
    for (int i = 0; i <= patternLen - 2; i++) {
        goodShift[patternLen - 1 - suffix[i]] = patternLen - 1 - i;
    }

    
    int pos = 0;
    int result = -1;

    while (pos <= textLen - patternLen) {
        j = patternLen - 1;
        while (j >= 0 && pattern[j] == text[pos + j]) {
            --j;
        }

        if (j < 0) {
            result = pos;
            break;
        }

        int badCharShift = j - badChar[text[pos + j]];
        if (badCharShift < MIN_SHIFT) {
            badCharShift = MIN_SHIFT;
        }

        int goodSuffixShift = goodShift[j];
        pos += (badCharShift > goodSuffixShift) ? badCharShift : goodSuffixShift;
    }

    
    delete[] suffix;
    delete[] goodShift;

    return result;
}

int main() {
    string text = "idechvetothamam turckayabanya";
    string pattern = "etothamam";
    int index = boyerMooreSearch(text, pattern);
    if (index != -1) {
        cout << "Found, index: " << index << endl;
    } else {
        cout << "Not found" << endl;
    }

    return 0;
}