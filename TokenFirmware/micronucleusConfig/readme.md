This re-configured micronucleus does:

* enable the bootloader LED

* exit bootloader immediately unless P0 pulled down

To build modified micronucleus for PWDToken:

* Clone micronucleus repo

* Copy `t85_pwtoken` to micronucleus\firmware\configuration\

* make CONFIG=t85_pwdtoken

* Connect the digistump with a USBASP programmer

* avrdude -c usbasp -pt85 -U flash:w:main.hex -F