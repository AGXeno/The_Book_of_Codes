#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <sstream>
#include <map>

using namespace std;

int GetWordFrequency(vector<string> wordList, string currWord) {
    map <string, int> myMap;

    for (long unsigned int i = 0; i < wordList.size(); i++) {
        string temp = wordList.at(i);
        transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        transform(currWord.begin(), currWord.end(), currWord.begin(), ::tolower);
        if (temp == currWord) {
            //cout << "WORD LIST: " << wordList.at(i) << endl;
            myMap[currWord] ++;
        }
    }

    return myMap[currWord];

}


int main() {
    int count;
    int word_count;
    string currWord;

    cin >> word_count;
    getline(cin, currWord);
    vector <string> wordList(0);
    istringstream iss(currWord);
    while(iss >> currWord) {
        wordList.push_back(currWord); // adds string input into vector
    }
    for (int i = 0; i < wordList.size(); i++) {
        string word = wordList.at(i);
        count = GetWordFrequency(wordList, word);
        cout << word << " " << count << endl;
    }


    return 0;
}
