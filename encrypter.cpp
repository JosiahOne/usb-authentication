#include <iostream>
#include <string>
#include <sstream>
#include "jcpp-helper/jstring.h"
#include <cstdlib>

using namespace std;

string _toEncryptOrDecrypt = "bar";
string _key = "foo";

string _ConvertToByteForm(string someString) {
  string returnString = " ";
  for (int i = 0; i < someString.size(); i++) {
    ostringstream oss;
    oss << returnString << static_cast<int>(static_cast<unsigned char>(someString[i])) << " ";
    returnString = oss.str();
  }

  return returnString;
}

string _ConvertToStringForm(string byteFormString) {
  string returnString = "";

  vector<string> stringArray = JCPP::GetStringsBetweenStrings(byteFormString, " ", " ");
  vector<int> intArray;
  cout << stringArray.size();
  for (int i = 0; i < stringArray.size(); i++) {
    intArray.push_back(strtol(stringArray[i].c_str(), NULL, 10));
    cout << intArray[i] << endl;
    char aChar = intArray[i];
    returnString += aChar;
  }

  return returnString;
}

string _DoXORCipher(string someString) {
  string longKey = _key;
  while (longKey.length() < someString.length()) {
    longKey += _key;
  }

  for (int i = 0; i < someString.size(); i++) {
    someString[i] ^= longKey[i];
  }

  return someString;
}

string _DecryptString(string someString) {
  return _DoXORCipher(someString);
}

string _EncryptString(string someString) {
  string encryptedString = _DoXORCipher(someString);
  string byteForm = _ConvertToByteForm(encryptedString);
  cout << byteForm;
  return byteForm;
}

int main(int argc, char** argv) {
	// your code goes here

  _key = string(argv[1]);
  _toEncryptOrDecrypt = string(argv[2]);

	string thing =  _ConvertToByteForm(_DoXORCipher(_toEncryptOrDecrypt));
  cout << thing << endl;
  string otherThing = _ConvertToStringForm(thing);
  cout << _DecryptString(otherThing);

	return 0;
}
