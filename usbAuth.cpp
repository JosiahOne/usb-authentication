#include "usbAuth.h"

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
    identity.username = _DecryptString(_GetUsername());
    identity.password = _DecryptString(_GetPassword());
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
   locations = {"F:\\\\", "F://", "/cygdrive/f/", "/media/IDENTCARD/"};
   tinydir_dir dir;

   for (int i = 0; i < locations.size(); i++) {
     tinydir_open(&dir, locations[i].c_str());
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
  return strtol(_DecryptString(_GetFile("pin.aid")).c_str(), NULL, 10);
}

string USBAuth::_GetFile(string name) {
  string returnData = "";
  tinydir_dir dir;
  tinydir_open(&dir, _LocateUSB().c_str());
  while (dir.has_next) {
    tinydir_file file;
    tinydir_readfile(&dir, &file);
    if (string(file.name) == name) {
      std::ifstream ifs(file.path);
      std::string stringContent = "";
      getline(ifs, stringContent);

      returnData = stringContent;
    }

    tinydir_next(&dir);
  }
  return returnData;
}

string USBAuth::_DecryptString(string someString) {
  return _DoXORCipher(someString);
}

string USBAuth::_EncryptString(string someString) {
  return _DoXORCipher(someString);
}

string USBAuth::_DoXORCipher(string someString) {
  string longKey = _key;
  while (longKey.length() < someString.length()) {
    longKey += _key;
  }

  for (int i = 0; i < someString.size(); i++) {
    someString[i] ^= longKey[i];
  }

  cout << someString;
  std::ofstream out("pin.aid");
      out << someString;
      out.close();
  return someString;

}
