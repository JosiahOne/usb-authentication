// Examples
#include "usbAuth.h"

using namespace std;

int main() {
  USBAuth *auth = new USBAuth;
  auth->SetKey("lathrupencryption");
  auth->ReadPin(1234);
   auth->Authenticate().username;

  delete auth;
  return 0;
}
