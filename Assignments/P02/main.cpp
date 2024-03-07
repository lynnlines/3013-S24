#include "./headers/console.hpp"
#include "./headers/rang.hpp"
#include "./headers/json.hpp"
#include <string>
#include <fstream>
#include <vector>

using json = nlohmann::json;
using namespace std;
using namespace rang;

consoleSize console_size;

struct WordAndDef {
  string word;
  string def;
  WordAndDef(string a, string b): 
  word(a), def(b) {}
};

vector<string> partialMatch(vector<string> array, string substring);
void titleBar(string title, int length = console_size.width);
void horizontalBar(int length = console_size.width);
void printMenu(vector<string> options);
void printHighlightedSubstr(string word, string substr, int loc);
void printCurrent(char k, string word);
void errorMessage(string message);

class WordStuff{
  vector<string> found;
  json data;
public:
  WordStuff(string filename){
    ifstream f(filename);
    data = json::parse(f);
  }
  vector<string> findWords(string substr){
    vector<string> matching_words;


    // find axal is substr is empty
    for (auto& [key, value] : data.items()) {
      if(substr.empty())
      {
        std::size_t found = key.find("axal",0);
        if (found != string::npos)
        {
          matching_words.push_back(key);
        }
      }
else {
      std::size_t found = key.find(substr, 0,substr.length());
      if (found!=string::npos){
        matching_words.push_back(key);
      }}
    }

    return matching_words;
  }
};


int main() {
  console_size = getConsoleSize(); // get width and height of console
  vector<string> matching_words;
  
  char k;                          // holder for character being typed
  string key;                      // string version of char for printing
  string substr = "";              // var to concatenate letters to
  int loc;                // location of substring to change its color
  bool deleting = false;
  string str = "";
  vector<string> mainMenu;
  mainMenu.push_back("Type letters and watch the results change.");
  mainMenu.push_back(
      "Hit the DEL key to erase a letter from your search string.");
  mainMenu.push_back(
      "When a single word is found, hit enter. (this is for real assignment.");

  clearConsole();
  titleBar("Getch Example", console_size.width);
  printMenu(mainMenu);

  
  WordStuff ws("./input/dictionary.json");

  // While capital Z is not typed keep looping
  while ((k = getch()) != 'Z') {

    clearConsole();
    titleBar("Getch Example", console_size.width);
    printMenu(mainMenu);

    // Tests for a backspace and if pressed deletes
    // last letter from "substr".
    if ((int)k == 127) {
      if (substr.size() > 0) {
        substr = substr.substr(0, substr.size() - 1);
        deleting = true;
      }
    } else {
      deleting = false;
      // Make sure a letter was pressed and only letter
      if (!isalpha(k)) {
        errorMessage("Letters only!");
        continue;
      }

      // We know its a letter, lets make sure its lowercase.
      // Any letter with ascii value < 97 is capital so we
      // lower it.
      if ((int)k < 97) {
        k += 32;
      }
      substr += k; // append char to substr
    }
    horizontalBar();
    printCurrent(k, substr);
    matching_words = ws.findWords(substr);
    // Find any animals in the array that partially match
    // our substr word
    // matches = partialMatch(animals, substr);

    if ((int)k != 32) { // if k is not a space print it

      key = to_string(k);

      horizontalBar();

      cout << style::bold << style::underline << fg::black
           << "MATCHES: " << fg::green << matching_words.size() << style::reset
           << fg::reset << endl
           << endl;

      for (auto &c : substr)
        c = tolower(c);
      // This prints out all found matches
      int max = matching_words.size() > 10 ? 10 : matching_words.size();
      for (int i = 0; i < max; i++) {
        // find the substring in the substr
        loc = matching_words[i].find(substr, 0,substr.length());
        // if its found
        if (loc != string::npos) {
          printHighlightedSubstr(matching_words[i], substr, loc);
        }
        cout << " ";
      }
      cout << fg::reset << endl << endl << endl << endl;
      if (matching_words.size() == 1) {
        cout << "done?" << endl;
        // this isn't handled at all, just messin around
      }
    }
  }
  return 0;
}

/**
 * partialMatch
 *
 * Description:
 *      Finds partial matches in an array of strings and returns them. It
 *      doesn't matter where in the string the match is.
 * Params:
 *      vector<string>  array       - array to search
 *      string          substring   - substring to search for in each word
 *
 * Returns:
 *      vector<string> - holding all the matches to substring
 */
vector<string> partialMatch(vector<string> array, string substring) {
  vector<string> matches; // to hold any matches
  size_t found;           // size_t is an integer position of
                          // found item. -1 if its not found.

  if (substring.size() == 0) {
    return matches;
  }

  for (int i = 0; i < array.size(); i++) { // loop through array
    found = array[i].find(substring, 0, substring.length());      // check for substr match
    if (found != string::npos) {           // if found >= 0 (its found then)
      matches.push_back(array[i]);         // add to matches
    }
  }

  return matches;
}

/**
* Prints a long background row of gray, with text centered.
* Not a good function since colors are hard coded, but using
* rang, I don't want to invest the time to figuere out how to
* interact with rang's enumerated class types and ostream.
* I guess you could add a switch statement to change background
* color:
* switch(color){
  "black" : cout<<bgB::black;
            break;
  "red" : cout<<bgB::red;
          break;
  ...
  ...
  ...
}
But still not a good solution.
*/
void titleBar(string title,int length) {
  string padding = string((length / 2) - (title.size() / 2), ' ');
  title = padding + title + padding;
  cout << bgB::black << fg::gray << title << fg::reset << bg::reset << endl;
}

/**
 * horizontalBar
 *
 * Description:
 *      Prints a horizontal bar of a given length
 * Params:
 *      int length - length of the bar
 * Returns:
 *      void
 */
void horizontalBar(int length) {
  string line = string(20, '_');
  cout << fg::gray << line << fg::reset << bg::reset << endl;
}

/**
 * printMatches
 *
 * Description:
 *      Prints the matches to the screen.
 * Params:
 *      vector<string> matches - vector of matches
 * Returns:
 *      void
 */
void printMenu(vector<string> options) {
  int i = 1;
  for (auto s : options) {
    cout << fg::black << style::bold << i << ". " << style::reset << fg::cyan
         << s << fg::reset << bg::reset << endl;
    i++;
  }
  cout << fg::reset << bg::reset;
}

/**
 * printHighlightedSubstr
 *
 * Description:
 *      Given a word, print the substr underlined and red vs blue for the rest
 * of the word.
 * Params:
 *      string word - word to print
 *      string substr - substring to highlight in red
 *      int loc - location of substr in word
 * Returns:
 *      void
 */
void printHighlightedSubstr(string word, string substr, int loc) {
  for (int j = 0; j < word.size(); j++) {
    // if we are printing the substring turn it red
    if (j >= loc && j <= loc + substr.size() - 1) {
      cout << fg::red << style::underline << word[j] << fg::blue
           << style::reset;
    } else {
      cout << fg::blue << word[j] << fg::reset << style::reset;
    }
  }
}

/**
 * printCurrent
 *
 * Description:
 *      Prints the current key pressed and the current substr to the screen.
 * Params:
 *      char k - last character pressed.
 *      string word - current substring being printed.
 * Returns:
 *      void
 */
void printCurrent(char k, string word) {
  cout << fg::green << style::bold << "KeyPressed: \t\t" << style::reset
       << fgB::yellow;
  if (int(k) == 127) {
    cout << "del";
  } else {
    cout << k;
  }
  cout << " = " << (int)k << fg::reset << endl;
  cout << fg::green << style::bold << "Current Substr: \t" << fg::reset
       << fgB::blue << word << fg::reset << style::reset << endl;
  cout << endl;
}

/**
 * errorMessage
 *
 * Description:
 *      Prints an error message to the screen.
 * Params:
 *      string message - message to print
 * Returns:
 *      void
 */
void errorMessage(string message) {
  cout << bgB::red << fgB::gray << message << fg::reset << bg::reset << endl;
  sleep(1);
}

// g++ main.cpp -std=c++20 -o main 
