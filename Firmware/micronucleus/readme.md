This folder contains a pre-built version of the micronucleus bootloader configured to exit immediately unless P0 is held low.

While you don't strictly need this, this modified version offers two adavantages:

* Token can be used without delay when plugged in
* Prevents a potential attack in which an attacker would send to the bootloader an updater capable of exfiltrating the passwords without changing the counters. Modifying the token software now requires physical access to it as the bootloader doesn't run unless P0 is held low.

I did no changes to "micronucleus" V2.5 to build this `.hex` other than creating a config file with the pre-existing option turned on.

### Burn the pre-compiled version

I have pre-built for you micronucleus V2.5 with the option to enable the bootloader only if P0 is pulled low. If this version of the bootloader is suitable for you and you don't want to further customize it, the easiest way is to burn the pre-built version.

* Clone this repo
* Get the file `Firmware\micronucleus\micronucleus_2_5_t85_entry_p0_down.hex`
* Connect your programmer to the digistump
* Burn the bootloader: `avrdude -c usbasp -pt85 -U flash:w:micronucleus_2_5_t85_entry_p0_down.hex -F`

### Build your version of the bootloader

If you prefer you can build you own version of the bootloader. Checkout the original repo (https://github.com/micronucleus/micronucleus) and follow instructions there. You can then burn the resulting `.hex` file as explained above. You can use the config files in `t85_entry_p0_down` in this folder to get started by copying it to the cloned micronucleus folder under `firmware\configuration`.



