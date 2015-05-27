#include "usbAuth.h"

USBAuth::USBAuth() {

}

USBAuth::~USBAuth() {

}

void USBAuth::ReadPin(int pin) {
  _pin = pin;
}

identReturn USBAuth::Authenticate() {
  identReturn identity;

  if (_GetPin() == _pin) {
    // Decide if we need to verify with a fingerprint
    // TODO: Just assume we don't for now.
    identity.username = _GetUsername();
    identity.password = _GetPassword();
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
   vector<char*> locations = {"F:\\\\", "F://", "/cygdrive/f/", "/media/IDENTCARD/"};
   tinydir_dir dir;

   for (int i = 0; i < locations.length(); i++) {
     tinydir_open(&dir, locations[i]);
     if (dir.has_next) {
       return string(locations[i]);
     }
   }

   return "ERROR";
}
