#include "usbAuth.h"
#include "jcpp-helper/jstring.h"

USBAuth::USBAuth() {

}

USBAuth::~USBAuth() {

}

void USBAuth::SetKey(string key) {
  _key = key;
}

void USBAuth::ReadPin(int pin) {
  _pin = pin;
}

identReturn USBAuth::Authenticate() {
  identReturn identity;

  if (_GetPin() == _pin) {
    // Decide if we need to verify with a fingerprint
    // TODO: Just assume we don't for now.
    cout << "PIN MATCH";
    identity.username = _DecryptString(_ConvertToStringForm(_GetUsername()));
    identity.password = _DecryptString(_ConvertToStringForm(_GetPassword()));
    identity.failed = false;
  } else {
    identity.failed = true;
  }

  return identity;
}

string USBAuth::_LocateUSB() {
  /* Expected drive locations by platforms:
   *   Windows: F:\\
   *   Windows (cywgin): /cygdrive/f/
   *   Linux: /media/IDENTCARD/
   *   OS X: /media/IDENTCARD/ ?
   */
   vector<string> locations(4);
   locations = {"F:\\\\", "F://", "/cygdrive/f/", "/media/IDENTCARD/",
                "G:\\\\", "G://", "/cygdrive/g/",
                "H:\\\\", "H://", "/cygdrive/h/",
                "I:\\\\", "I://", "/cygdrive/i/",
                "J:\\\\", "J://", "/cygdrive/j/"};
   tinydir_dir dir;

   for (int i = 0; i < locations.size(); i++) {
     tinydir_open(&dir, _StringToProperChar(locations[i]));
     if (dir.has_next) {
       return locations[i];
     }
   }
    
   return "ERROR";
}

string USBAuth::_GetUsername() {
  return _GetFile("username.aid");
}

string USBAuth::_GetPassword() {
  return _GetFile("password.aid");
}

int USBAuth::_GetPin() {
  return strtol(_DecryptString(_ConvertToStringForm(_GetFile("pin.aid"))).c_str(), NULL, 10);
}

string USBAuth::_GetFile(string name) {
  string returnData = "";
  tinydir_dir dir;
  tinydir_open(&dir, _StringToProperChar(_LocateUSB().c_str()));
  while (dir.has_next) {
    tinydir_file file;
    tinydir_readfile(&dir, &file);
    if (_ProperCharToString(file.name) == name) {
      std::ifstream ifs(file.path);
      std::string stringContent = "";
      getline(ifs, stringContent);

      returnData = stringContent;
    }

    tinydir_next(&dir);
  }
  return returnData;
}

string USBAuth::_ConvertToByteForm(string someString) {
  string returnString = " ";
  for (int i = 0; i < someString.size(); i++) {
    ostringstream oss;
    oss << returnString << static_cast<int>(static_cast<unsigned char>(someString[i])) << " ";
    returnString = oss.str();
  }

  return returnString;
}

string USBAuth::_ConvertToStringForm(string byteFormString) {
  string returnString = "";

  vector<string> stringArray = JCPP::GetStringsBetweenStrings(byteFormString, " ", " ");
  vector<int> intArray;
  for (int i = 0; i < stringArray.size(); i++) {
    intArray.push_back(strtol(stringArray[i].c_str(), NULL, 10));
    char aChar = intArray[i];
    returnString += aChar;
  }

  return returnString;
}

string USBAuth::_DoXORCipher(string someString) {
  string longKey = _key;
  while (longKey.length() < someString.length()) {
    longKey += _key;
  }

  for (int i = 0; i < someString.size(); i++) {
    someString[i] ^= longKey[i];
  }

  return someString;
}

string USBAuth::_DecryptString(string someString) {
  return _DoXORCipher(someString);
}

string USBAuth::_EncryptString(string someString) {
  string encryptedString = _DoXORCipher(someString);
  string byteForm = _ConvertToByteForm(encryptedString);
  cout << byteForm;
  return byteForm;
}

#ifdef _UNICODE
const wchar_t* USBAuth::_StringToProperChar(string someString) {
    wchar_t returnData[512];
    mbstowcs(returnData, someString.c_str(), 512);

    return returnData;
}
string USBAuth::_ProperCharToString(wchar_t* someCString) {
    wstring ws(someCString);
    string test( ws.begin(), ws.end() );

    return test;
}
#else
const char* USBAuth::_StringToProperChar(string someString) {
    return someString.c_str();
}
string USBAuth::_ProperCharToString(char* someCString) {
    return string(someCString);
}
#endif