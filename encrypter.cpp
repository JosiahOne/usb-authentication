#include <iostream>
#include <string>
#include <sstream>
using namespace std;

string _toEncryptOrDecrypt = "bar";
string _key = "foo";

string _ConvertToByteForm(string someString) {
  string returnString = " ";
  for (int i = 0; i < someString.size(); i++) {
    std::ostringstream oss;
    oss << returnString << static_cast<int>(static_cast<unsigned char>(someString[i])) << " ";
    returnString = oss.str();
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

	cout << _ConvertToByteForm(_DoXORCipher(_toEncryptOrDecrypt));
	return 0;
}
