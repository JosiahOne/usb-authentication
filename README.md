# usb-authentication
[![Build Status](https://travis-ci.org/JosiahOne/usb-authentication.svg?branch=master)](https://travis-ci.org/JosiahOne/usb-
authentication)

# !!! WARNING !!!

This was written when I was back in high school and had no knowledge about security. This is NOT cryptographically secure in any way and shouldn't be used for critical systems.


Library and Spec for an alternative login process that uses USB drives instead of username/password.

### What's supplied?
#### Encrypter.cpp

This repo actually has a few different tools. If you build `encrypter.cpp`, you will obtain a tool for creating the data that goes on the USB drives.

**Syntax:** `./encrypterout encryptionkey thingtoencrypt`.

##### Example Usage

```
$ c++ encrypter.cpp
$ ./a.exe somekey somestring
 0 0 0 0 24 17 11 26 1 10
000024171126110
===
100
0
0
0
24
17
11
26
1
10
somestring
```

The first output line ` 0 0 0 0 24 17 11 26 1 10` is the data that you will put into one of the four files on the usb drive. There must be trailing whitespace at the end and beginning of the string! The rest of the output is there for debugging purposes and the very last line just verifies that it can undo the encryption. If the last line does not match your second argument, something went wrong.

#### usbAuth.cpp
usbAuth is the main class you integrate into your application to read and do authentication from the drives. You do not build this by itself, instead you include it in your application. It is extremely simple, the only public methods are:

```
  USBAuth();
  ~USBAuth();
  void ReadPin(int pin);
  void SetKey(std::string key);
  identReturn Authenticate();
```

#### main.cpp
main is simply an example that you can use to visualize how you use the tool. All it does it read the usb and output the username and password if the pin and ticket match. If you'd like you could build it and run the output (with no arguments).
