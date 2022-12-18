//
// Created by Taro K on 9/22/22.
//
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

void PrintMenu() {
    cout << "MENU" << endl;
    cout << "c - Number of non-whitespace characters" << endl;
    cout << "w - Number of words" << endl;
    cout << "f - Find text" << endl;
    cout << "r - Replace all !'s" << endl;
    cout << "s - Shorten spaces" << endl;
    cout << "q - Quit" << endl;
    cout << endl;
}

int GetNumOfWords(string text) {
    int wordCount = 0;
    for (std::size_t i = 0; i < text.length(); i++) {
        if (text[i] == ' ') {
            if (text[i + 1] == ' ') {
                continue;
            }
            else {
                wordCount++;
            }
        }
    }
    wordCount += 1;
    return wordCount;
}

int FindText(string findWord, string text) {
    int count = 0;
    size_t found = text.find(findWord, 0);
    while (found != string::npos) {
        count ++;
        found = text.find(findWord, found + 1);
    }
    return count;

}


int GetNumOfNonWSCharacters(string text_input) {
    int ofWhitespace = 0;
    int totalWhitespace;
    ofWhitespace = count(text_input.begin(), text_input.end(), ' ');
    totalWhitespace = text_input.length() - ofWhitespace;
     return totalWhitespace;
}

void ReplaceExclamation(string& text) {
    char replacement = '.';
    for (long unsigned int i = 0; i < text.length(); i++) {
        if (text[i] == '!') {
            text[i] = replacement;
        }
    }
}

void ShortenSpace (string& text) {
    for(int i = text.size() - 1; i >= 0; i--) {
        if(text[i] == ' ' && text[i] == text[i-1]) {
            text.erase(text.begin() + i);
        }
    }
    cout << text << endl;
}



void ExecuteMenu (char charCmd, string text_input) {
    if (charCmd == 'c') {
        auto result = GetNumOfNonWSCharacters(text_input);
        cout << "Number of non-whitespace characters: " << result << endl;
        cout << endl;
    }

    else if (charCmd == 'w') {
        auto result = GetNumOfWords(text_input);
        cout << "Number of words: " << result << endl;
        cout << endl;
    }

    else if (charCmd == 'f') {
        string findWord;
        cin.ignore();
        cout << "Enter a word or phrase to be found:" << endl;
        getline(cin, findWord);
        auto result = FindText(findWord, text_input);
        cout << "\"" << findWord << "\" instances: " << result << endl;
        cout << endl;
    }

    else if (charCmd == 'r') {
        ReplaceExclamation(text_input);
        cout << "Edited text: " << text_input << endl;
        cout << endl;
    }

    else if (charCmd == 's') {
        ShortenSpace(text_input);
        cout << "Edited text: " << text_input << endl;
        cout << endl;
    }
}

int main() {
    char ltr_cmd;
    string str;
    string usrString;
    cout << "Enter a sample text:" << endl;
    getline (cin, usrString);
    cout << endl;
    cout << "You entered: " << usrString << endl;
    cout << endl;
    while (ltr_cmd != 'q') {
        PrintMenu();
        cout << "Choose an option:" << endl;
        cin >> ltr_cmd;
        ExecuteMenu(ltr_cmd, usrString);

    }
    return 0;
}

