// Super Minimalistic example of USBAuth. 
#include "usbAuth.h"

using namespace std;

int main() {
  USBAuth *auth = new USBAuth;
  auth->SetKey("lathrupencryption");
  auth->ReadPin(1234);
  cout << auth->Authenticate().username << endl;
  cout << auth->Authenticate().password << endl;

  delete auth;
  return 0;
}
