
## The hardware

You will need a Digispark Digistump or another ATTiny85 board with USB. Additionally you will need two push buttons. Connect them between P0 and P2 and ground. See photo for one of my prototypes.

![board](../Docs/board.png)


## Special bootloader (optional)

You can replace the standard "micronucleus" bootloader that comes with the Digistump with a version that doesn't wait in the bootloader by default when started. This makes your PwdToken immediately available when plugging it. Once you uploaded the re-configured bootloader you will need to pull P0 low (press button A before inserting the board in the USB port). To carry out this step you will need an ISP, I tested this with a USBASP. Others shouldn't be that much different but you will need to tweak the actual programming command. 

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
* Press button A until the desired password is selected
* Focus on the application/field in which you need to type the password
* Press and hold A for more than 2 seconds and the password will by typed

## Getting the token banner

The token benner is a piece of formatted text that contains non-confidential information and can be used to validate the boot counts as well as to make sure your keyboard layout is correct. The banner is always accessible without unlocking the token. To print the banner follow these steps:

* Open a text editor and ensure it's in focus
* Insert the token while keeping button B pressed
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

