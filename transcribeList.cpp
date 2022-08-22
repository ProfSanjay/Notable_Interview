#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

// Method Declarations
string transcribe(string msg);

int main() {
    string notes;
    bool cont = true;
    char in;

    cout << "Welcome to the Notes Transcriber! Please enter your notes now:" << endl;

    while(cont) {
        getline(cin, notes);    // Gets the input of the doctors' notes
        cout << endl;           
        string editedNotes = transcribe(notes); // Transcribes the notes
        cout << editedNotes << endl;            // Prints it out to the console

        cout << "Would you like to transcribe more notes? Enter Y to continue: ";
        cin >> in;
        cin.ignore();
        toupper(in);

        if (in != 'Y')
            cont = false;
    }

    cout << "\nThank you for using the Notes Transcriber!" << endl;

    return 0;
}

string transcribe(string msg) {
    vector<string> words;           // Vector to hold each word of the input string to parse through
    map<string, int> convert = {    // Map to hold conversions from text to number
        {"one", 1},
        {"two", 2},
        {"three", 3},
        {"four", 4},
        {"five", 5},
        {"six", 6},
        {"seven", 7},
        {"eight", 8},
        {"nine", 9}};

    string delim = " ", end = ".", transcribed, listNum;
    int num;
    size_t pos = 0;

    // Moves the text from a massive string into a vector of words to parse through
    while(((pos = msg.find(delim)) != string::npos) || ((pos = msg.find(end)) != string::npos)) {
        words.push_back(msg.substr(0, pos));
        msg.erase(0, pos + delim.length());
    }

    // Parses through the vector of words
    for (int i = 0; i < words.size(); i++) {
        // First Case: Beginning the ordered list i.e. a start number is given
        if (words[i] == "Number" && words[i + 1] != "next") {
            listNum = words[i + 1]; // Takes the start number as a word

            // Iterate through map to see how to convert word to number
            for (auto it : convert) {
                if (listNum == it.first) {
                    words[i + 1] = "\n" + to_string(it.second) + ")";   // The actual transcribing
                    num = it.second;    // A placemarker for the "next" case
                }
            }

            i++;                                        // Skip the word "Number"
            words[i + 1][0] = toupper(words[i + 1][0]); // Capitalize the beginning of the next word
        }

        // Second Case: Continuing the list i.e. how to make the list count up properly
        if (words[i] == "Number" && words[i + 1] == "next") {
            i++;                                        // Skip the word "Number"
            words[i] = "\n" + to_string(++num) + ")";   // Add 1 to the placemarker, then convert "next"
        }                                               // to the correct number listing

        transcribed += words[i] + " ";  // Add the transcribed text to the end of the return string
    }
    
    return transcribed;
}