# PwdToken

## Introduction

This started as a hardware implementation of a piece of paper with your password on it and, in some respect, it sill is. So use it with judgment! I toyed at first with the idea mostly of having something to type the WiFi password on new devices or for guests.

Once the novelty of the first quick implementation wore out, I started to wonder how I could make this at least reasonably secure. In its current incarnation the PwdToken offers the following features:

* Runs on a Digispark Digistump (or similart ATTiny85 device)
* Requires only 2 buttons to be soldered to the board
* Stores up to 4 passwords
* Emulates a USB keyboard and types the password
* Easy 2 buttons operation

Security features:
* Unlock password by morse keypad (optional)
* Unlock PIN by binary keypad (optional)
* Mechanism to validate count of boots and passwords recoveries (tamper/usage detection)

![board](Docs/board.png)

## Safety

Is it safe?

TLDR: **NO**

Long story. It can be reasonably safe depending on your use case. If you often need to log in on computers that are not yours and on which you can't run a password manager, this could be a viable option, especially if the alternative is to use a weak password that you can remember. At least you have shifted the extent of the potential attackers from anyone on the the Internet to anyone who can gain access to your token. 

### What makes this reasonably safe?

The passwords are stored in the actual application, and not in the data EEPROM. This means that if anyone attempts to replace the application with one that just exfiltrates the passwords then the passwords will actually be wiped.

There's a meachanism (optional) to keep track of the boots count and amount of times passwords have been retrieved. A command line application can be used to validate these against a manifest containing, among other information, a shared secret. While this doesn't prevent password theft it makes tampering evident.

### Known vulnerabilities

**do I need to say it? this is bound to be an incomplete list**

* An attacker could craft an .hex file that doesn't override the portion of code with the passwords and exfiltrates them. For this attack to be successfull it would be enough to compromise a host machine and have a microncleus uploader waiting for a device all the time. This is an issue only if the stock micronucleus bootloader is used. This project provides a re-configured version of the bootloader that doesn't start unless P0 is held low. This defeats this attack unless the attacker has physical access to the device.
* An attacker could connect an AVR programmer and dump the application or replace the bootloader with one that exfiltrates the passwords. This is possible only if the attacker has physical access to the token. This could be further mitigated if the bootloader was wiped after programming and the device encased in epoxy. While the attacker could still possibly re-program it this would require access to the device for a longer time and the tampering would be evident.
* Because of the way the password lock works (just waits until the right PIN/Password is entered), and because the onboard LED signals the fact the token is locked, an attacker could build a device that brute forces the PIN/Password quite easily. One possible mitigating action would be to add a max errors after which the device wipes itself. Also in this case physical access to the device is needed to carry out this attack.

### What can I do to make it safer?

* Make use of the provided modified bootloader so the device cannot be re-programmed without physical access to it
* Don't store the full password, use a Horcrux (in a nutshell, make your password something like `fsnf23m!abcSomethingIOnlyKnow` and only store the `fsnf23m!abc` part to then type the reminder)
* Don't leave the token unattended and keep track of your tokens so you can immeditely reset the passwords if one is missing
* Wipe the bootloader and encase the device in epoxy. Keep in mind you will have no way to re-program it, so every password change will mean a new build.

## Build one


### The hardware

You will need a Digispark Digistump or another ATTiny85 board with USB. Additionally you will need two push buttons. Connect them between P0 and P2 and ground. See photo for one of my prototypes.

![board](../Docs/board.png)


### Special bootloader (optional)

You can replace the standard "micronucleus" bootloader that comes with the Digistump with a version that doesn't wait in the bootloader by default when started. This makes your PwdToken immediately available when plugging it. Once you uploaded the re-configured bootloader you will need to pull P0 low (press button B before inserting the board in the USB port). To carry out this step you will need an ISP, I tested this with a USBASP. Others shouldn't be that much different but you will need to tweak the actual programming command. 

If you choose to skip this step the only downside will be that once you plug your board in the USB port you will need to wait a few seconds for the bootloader to give up and your program to start.

### Burn the pre-compiled version

I have pre-built for you micronucleus V2.5 with the option to enable the bootloader only if P0 is pulled low. If this version of the bootloader is suitable for you and you don't want to further customize it, the easiest way is to burn the pre-built version.

* Clone this repo
* Get the file `Firmware\micronucleus\micronucleus_2_5_t85_entry_p0_down.hex`
* Connect your programmer to the digistump
* Burn the bootloader: `avrdude -c usbasp -pt85 -U flash:w:micronucleus_2_5_t85_entry_p0_down.hex -F`

### Build your version of the bootloader

If you prefer you can build you own version of the bootloader. Checkout the original repo (https://github.com/micronucleus/micronucleus) and follow instructions there. You can then burn the resulting `.hex` file as explained above.

## Store Passwords (without manifest)

If you wish to just set up passwords and don't want to generate a manifest to verify the integrity of the token (and to have proof the token has not been used) follow these simple steps:

* Copy `secrets_example.h` to `secrets.h` (this last is .gitignore:d so you don't risk to push your passwords!)
* Edit `secrets.h` and set your passwords and unlock password/pin if desired
* Edit `options.h` and set options as needed 
* Build and upload

## Store Passwords (with manifest)

If you choose to generate a manifest for the token you will be able at a later time to verify that the token has not been tampered with and you will be able to determine if and how many times it has been booted and passwords retrieved.

To generate a manifest use the command line utility under `CommandLineTool\bin`:

* Run `pwdtoken gen`
* Choose a label for the token
* Choose a secret
* The utility will generate a manifest and store in clipboard
* Store the manifest somewhere safe (eg a password manager)
* The utility will also generate a `secrets.h` file
* Edit `secrets.h` and set your passwords and unlock password/pin if desired (don't change the OTP secret or the label though or you will invalidate the manifest!)
* Edit `options.h` and set options as needed 
* Build and upload


## Retrieve a Password

**note** the token emulates a standard US layout keyboard. You will need to make sure your keyboard layout matches, especially if your password contains symbols that might be mapped to different keys.

* Insert the token in a USB port and wait until the onboard red LED is solid red (or flashing slowly if you choose not to have an unlock PIN/Password)
* Type your PIN/Password if enabled
* Once unlocked the onboard red LED will start to flash. The flashes count indicate the selected password
* Press repeatedly button B until the desired password is selected
* Focus on the application/field in which you need to type the password
* Press and hold A for more than 2 seconds and the password will by typed

## Getting the token banner

The token benner is a piece of formatted text that contains non-confidential information and can be used to validate the boot counts as well as to make sure your keyboard layout is correct. The banner is always accessible without unlocking the token. To print the banner follow these steps:

* Open a text editor and ensure it's in focus
* Insert the token while keeping button A pressed
* Release the button as soon as the banner is starting to appear

A banner looks like this:

````
----------- begin -----------
 
; PwdToken 0.01-B
; Built Apr 11 2021 17:04:08
; Keyboard Layout US
; Hash Backslash: # \
LBL: TST002
OTP1: 3063762718
OTP2: 1882074943
 
------------ end ------------
````

You can use the `; Hash Backslash: # \` line to validate that the current keyboard layout is correct. Most of the rest of the information in the banner is data needed by the command line utility to validate the boot and password retrieval counters.



