This re-configured micronucleus does exit the bootloader immediately unless P0 pulled down.

To upload the pre-build micronucleus bootloader:

* Connect the digistump with a USBASP programmer

* avrdude -c usbasp -pt85 -U flash:w:micronucleus_2_5_t85_entry_p0_down.hex -F


If you want to further tweak the bootloader:

* Clone micronucleus repo

* Copy `t85_entry_p0_down` to micronucleus\firmware\configuration\

* make CONFIG=t85_entry_p0_down

* Connect the digistump with a USBASP programmer

* avrdude -c usbasp -pt85 -U flash:w:main.hex -F

