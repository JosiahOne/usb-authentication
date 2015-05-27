// Examples
#include "usbAuth.h"

using namespace std;

int main() {
  USBAuth *auth = new USBAuth;
  cout << auth->_GetUsername();
  delete auth;
  return 0;
}
