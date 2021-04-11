# PwdToken

This started as a hardware implementation of a piece of paper with your password on it and, in some respect, it sill is. So use it with judgment! I toyed at first with the idea mostly of having something to type the WiFi password on a new devices or for guests.

Once the novelty of the first quick implementation wore out, I started to wonder how I could make this at least reasonably secure. In its current incarnation the PwdToken offers the following features:

* Stores up to 4 passwords
* Emulates a USB keyboard and types the password
* Easy 2 buttons operation

Security features:
* Unlock password by morse keypad (optional)
* Unlock PIN by binary keypad (optional)
* Mechanism to validate count of boots and passwords recoveries (tamper/usage detection)

## Is it safe?

TLDR: **NO**

Long story. It can be reasonably safe depending on your use case. If you often need to log in on computers that are not yours and on which you can't run a password manager, this could be a viable option, especially if the alternative is to use a weak password that you can remember. At least you have shifted the extent of the potential attackers from anyone on the the Internet to anyone who can gain access to your token. 

## What makes this reasonably safe?

The passwords are stored in the actual application, and not in the data EEPROM. This means that if anyone attempts to replace the application with one that just exfiltrates the passwords then actually passwords will be wiped.

There's a meachanism (optional) to keep track of the boots count and amount of times passwords have been retrieved. A command line application can be used to validate these against a manifest containing, among other information, a shared secret. While this doesn't prevent password theft it makes tampering evident.

## Known vulnerabilities

**do I need to say it? this is bound to be an incomplete list**

* An attacker could craft an .hex file that doesn't override the portion of code with the passwords and exfiltrates them. For this attack to be successfull it would be enough to compromise a host machine and have a microncleus uploader waiting for a device all the time. This is an issue only if the stock micronucleus bootloader is used. This project provides a re-configured version of the bootloader that doesn't start unless P0 is held low. This defeats this attack unless the attacker has physical access to the device.
* An attacker could connect an AVR programmer and dump the application or replace the bootloader with one that exfiltrates the passwords. This is possible only if the attacker has physical access to the token. This could be further mitigated if the bootloader was wiped after programming and the device encased in epoxy. While the attacker could still possibly re-program it this would require access to the device for a longer time and the tampering would be evident.
* Because of the way the password lock works (just waits until the right PIN/Password is entered), and because the onboard LED signals the fact the token is locked an attacker could build a device that brute forces the PIN/Password quite easily. One possible mitigating action would be to add a max errors after which the device wipes itself. Also in this case physical access to the device is needed to carry out this attack.

## What can I do to make it safer?

* Make use of the provided modified bootloader so the device cannot be re-programmed without physical access to it
* Don't store the full password, use a Horcrux (in a nutshell, make your password something like `fsnfbsdmn23m!fnsfnSomethingIOnlyKnow` and only store the `fsnfbsdmn23m!fnsfn` part to then type the reminder)
* Don't leave the token unattended and keep track of your tokens so you can immeditely reset the passwords if one is missing
* Wipe the bootloader and encase the device in epoxy. Keep in mind you will have no way to re-program it, so every password change will mean a new build.

