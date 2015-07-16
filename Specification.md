# USBAuth specification #

## Abstract ##

Security sucks. Specifically, user name and password combos suck even more. The process is unnecessarily long and can be guessed (granted in O(n^2) time) by machines. Most people aren't willing to come up with multiple, long, complex passwords, so they are generally useless when security is an issue.

As an example, consider a business which requires its' employees to clock in and out using a computer. Now, before they can start work, they must open up the computer, type in their user name, type in their password, and then click log in. That's best-case-scenerio. What if they forget their password? Now your IT guy has to once more reset the password.

What's the alternative? Well, turns out that is quite difficult. Biometrics, while simplistic and seemingly thorough, have quite significant issues. Consider for example if you accidentally leak biometric data. There is no resetting it, it's out there forever. Also, in the case of fingerprint scanners, what if their fingers are dirty, they may quickly come to despise the process.

USBAuth attempts to solve these problems by providing a cheap, simplistic, and thorough security solution, similar to what Google is attempting. The gist of the solution is that each user will have a USB drive loaded with specific, encrypted user name and password data (which they don't need to know). When plugged in to a machine, the library will read the user name and password from the drive and prompt for a PIN. If they match, we log in with the user name and password provide. Optionally, you can randomly require a fingerprint scan to verify that the PIN and USB holder actually IS the person who is on the drive.

## USB File System Spec ##

### Error-Preventation Notice ###

The USB File system requires data to be EXACT, if anything is wrong, we wipe the stick. Wiping the stick will of course make that stick unusable for login.

### Files ###

#### username.aid ####
A file that contains ONLY an encrypted/disgused version of the user's user name.

#### password.aid ####
A file that contains ONLY an encrypted/disgused version of the user's password.

#### pin.aid ####
The pin that we compare with.

#### biodata.aid ####
A file containing the biometric data which will be compared with at random times. This data should be synced FROM some database that all your applications will use. More on that later.

### Location of drive ###
There should be NO other USB drives plugged into the client machine. On Windows, the F: drive should be used by the USB stick, nothing else.

## App-side process (AKA, what the Library does) ##

1. Read PIN from client App-side
2. Prompt for USB drive.
3. Compare PINs.
4. (If Match, continue, else, fail).
5. Send back username/password
6. If the BIO flag is set, then randomly pick a number from 0 - BIONUM. If number == BIONUM, prompt for a fingerprint scan.
7. If match, log in, else fail. Mark that we MUST have a fingerprint for next scan.

## Encryption Spec ##

All files on the USB drive are stored using the same (generally basic) encryption scheme. The encryption algorithm uses a key to encrypt all strings, this key is your "application encryption key" and is used to give each company a unique encryption algorithm. This way users at home can not decrypt their own files without it.

Remember, each USB drive can only have ONE key holder at a time. So you could not use the same key for both personal and private applications. This is on purpose.

## BIO Spec ##

The BIO process requires three things. A BIO-Database, which is where you will store the "main" bio data, and can only be added to, not deleted. When a new user sets up a USB key drive, their bio data is first added to the database.

You then Load their BIO to their flash drive, and load the BIO data to the client machine.

### Log in Process ###

                              User Logs in
                                   |
                                   V
    Compare the USB BIO Data with the BIO data stored on the client machine
                                   |
                                   V
     If Match, compare fingerprint scan to the data on the client machine.
                                   |
                                   V
          Occasionally sync machine BIO data with database BIO data.
