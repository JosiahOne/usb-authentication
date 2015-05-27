#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "tinydir.h"
#include <vector>

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
  identReturn Authenticate();
private:
  int _pin;
  string _usbLocation;
  bool _ComparePINs();
  string _GetUsername();
  string _GetPassword();
  int _GetPin();
  string _DecryptUsername();
  string _DecryptPassword();
  string _LocateUSB();
}
