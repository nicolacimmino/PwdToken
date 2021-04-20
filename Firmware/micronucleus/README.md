This folder contains a pre-built version of the micronucleus bootloader configured to exit immediately unless P0 is held low and to erase the application as soon as the bootloader enters.

While you don't strictly need this, this modified version offers two adavantages:

* Token can be used without delay when plugged in
* Prevents an attacker to replace part of the user program only and do nasty things if the original part containing passwords is not erased.

See Add-secure-boot-option.patch for changes to the micronucleus.

### Burn the pre-compiled version

I have pre-built for you micronucleus V2.5 with the option to enable the bootloader only if P0 is pulled low. If this version of the bootloader is suitable for you and you don't want to further customize it, the easiest way is to burn the pre-built version.

* Clone this repo
* Get the file `Firmware\micronucleus\micronucleus_2_5_t85_entry_p0_down.hex`
* Connect your programmer to the digistump
* Burn the bootloader: `avrdude -c usbasp -pt85 -U flash:w:micronucleus_2_5_t85_sec_boot.hex`

### Build your version of the bootloader

If you prefer you can build you own version of the bootloader. Checkout the original repo (https://github.com/micronucleus/micronucleus), checkout V2.5 and apply the patch in this folder. Follow instructions there. You can then burn the resulting `.hex` file as explained above. 



