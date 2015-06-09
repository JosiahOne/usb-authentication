#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "tinydir.h"
#include <vector>
#include <sstream>

struct identReturn {
  std::string username;
  std::string password;
  bool failed;
};

class USBAuth {
public:
  USBAuth();
  ~USBAuth();
  void ReadPin(int pin);
  void SetKey(std::string key);
  identReturn Authenticate();

private:
  int _pin;
  std::string _key;
  std::string _usbLocation;
  std::string _LocateUSB();
  bool _ComparePINs();
  std::string _GetPassword();
  std::string _GetUsername();
  int _GetPin();
  std::string _DecryptString(std::string someString);
  std::string _EncryptString(std::string someString);
  std::string _DoXORCipher(std::string someString);
  std::string _GetFile(std::string name);
  std::string _ConvertToByteForm(std::string someString);
  std::string _ConvertToStringForm(std::string byteFormString);
  #ifdef _UNICODE
  const wchar_t* _StringToProperChar(std::string someString);
  std::string _ProperCharToString(wchar_t* someCString);
  #else
  const char* _StringToProperChar(std::string someString);
  std::string _ProperCharToString(char* someCString);
  #endif
};
