#include <iostream>
#include <ctype.h>
#include <ctime>
#include <random>
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;

std::vector<std::string> getArgList(std::string & args) {
    std::cout << "Args: " << args << std::endl;
    std::vector<std::string> argList;
    size_t pos = 0;
    for (size_t i = 0; i < args.size(); i++) {
        if (args[i] == ' ') {
            argList.push_back(args.substr(pos, i-pos));
            pos = i+1;
        }
    }
    argList.push_back(args.substr(pos, args.size()-pos));
    return argList;
};

int main (int argc, char * argv[]) {
  srand(time(NULL));

  const int total_keys = 1;
  int totalCharacters = rand() % 51 + 50;

  if (argc > 1) {

    for (size_t i = 1; i < static_cast<size_t>(argc - 1); i++) {
        std::string argString(argv[i]);
        if (argString == "-size") {
            if (argc == i+1) {
                std::cout << "Error, need to provide value for -size: \"-size <N>\"" << std::endl;
                exit(1);
            } else {
                totalCharacters = std::atoi(argv[i+1]);
                std::cout << "Setting string size to :" << totalCharacters << std::endl;
                i++;
            }
        }
    }
  }

  if (totalCharacters <= 0) {
    std::cout << "Error, empty string requested." << std::endl;
    exit(1);
  }

  char myString[total_keys][totalCharacters+1];

  for (int j = 0; j < total_keys; j++) {
    for (int i = 0; i < totalCharacters; i++) {
      int num_or_char = rand() % 62;
      int character;
      if (num_or_char < 10) {
        // Number
        character = rand() % 10 + 48;
      } else if (num_or_char >= 10 && num_or_char < 36) {
        // Letter
        character = rand() % 26 + 65;
      } else {
        character = rand() % 26 + 97;
      }
      myString[j][i] = (char) character;
    }
    myString[j][totalCharacters] = '\n';
    cout << myString[j] << endl;
  }

  ofstream outputFile;
  outputFile.open("key.txt");

  for (int i = 0; i < total_keys; i++) {
   outputFile << myString[i] << endl;
  }
  outputFile.close();
  return 0;
}
