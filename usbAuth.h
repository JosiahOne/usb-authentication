#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "tinydir.h"
#include <vector>

using namespace std;

struct identReturn {
  string username;
  string password;
  bool failed;
};

class USBAuth {
public:
  USBAuth();
  ~USBAuth();
  void ReadPin(int pin);
  void SetKey(string key);
  identReturn Authenticate();
  string _GetUsername();

private:
  int _pin;
  string _key;
  string _usbLocation;
  string _LocateUSB();
  bool _ComparePINs();
  string _GetPassword();
  int _GetPin();
  string _DecryptUsername();
  string _DecryptPassword();
};
