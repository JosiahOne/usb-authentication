# USBAuth specification #

## Abstract ##

Security sucks. Specifically, user name and password combos suck even more. The process is unnecessarily long can be guessed (granted in O(n^2) time) by machines. Most people aren't willing to come up with multiple, long, complex passwords, so they are generally useless when security is an issue.

As an example, consider a business which requires its' employees to clock in and out using a computer. Now, before they can start work, they must open up the computer, type in their user name, type in their password, and then click log in. That's best-case-scenerio. What if they forget their password? Now your IT guy has to once more reset the password.

What's the alternative? Well, turns out that is quite difficult. Biometrics, while simplistic and seemingly thorough, have quite significant issues. Consider for example if you accidentally leak biometric data. There is no resetting it, it's out there forever. Also, in the case of fingerprint scanners, what if their fingers are dirty, they may quickly come to despise the process.

USBAuth attempts to solve these problems by providing a cheap, simplistic, and thorough security solution, similar to what Google is attempting. The gist of the solution is that each user will have a USB drive loaded with specific, encrypted user name and password data (which they don't need to know). When plugged in to a machine, the library will read the user name and password from the drive and prompt for a PIN. If they match, we log in with the user name and password provide. Optionally, you can randomly require a fingerprint scan to verify that the PIN and USB holder actually IS the person who is on the drive.

## USB File System Spec ##
