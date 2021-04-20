This folder contains a pre-built version of the micronucleus bootloader configured to exit immediately unless P0 is held low and to erase the application as soon as the bootloader enters.

While you don't strictly need this, this modified version offers two adavantages:

* Token can be used without delay when plugged in
* An attacker cannot, through USB, replace part of the user program and do nasty things if the original part containing passwords is not erased.

See Add-secure-boot-option.patch for changes to the micronucleus.

**NOTE**: with the added security comes also a risk. If you accidentally plug in the token while holding button B you will enter the bootloader and erase your passwords! Make sure you have a copy which, by they way, you should have anyway!

### Burn the pre-compiled version

I have pre-built for you micronucleus V2.5 with the patch included in this folder. If this version of the bootloader is suitable for you and you don't want to further customize it, the easiest way is to burn the pre-built version. This also implies you trust me not to have added any sort of backdoor.

* Clone this repo
* Get the file `Firmware\micronucleus\micronucleus_2_5_t85_sec_boot.hex`
* Connect your programmer to the digistump
* Burn the bootloader: `avrdude -c usbasp -pt85 -U flash:w:micronucleus_2_5_t85_sec_boot.hex`

**NOTE**: you will need to make adjustments to the command above if your programmer is not a USBAsp.

### Build your version of the bootloader

If you prefer you can build you own version of the bootloader. Clone the original micronucleus repo (https://github.com/micronucleus/micronucleus), check out V2.5 and apply the patch in this folder. Follow the instructions there to build. You can then burn the resulting `.hex` file as explained above. 

### Using the modified bootloader

If you choose to use this version of the bootloader when programming the PwdToken firmware with your passwords you will need to press and hold down button B (connected to P0) before inserting the token into the USB slot for programming.



