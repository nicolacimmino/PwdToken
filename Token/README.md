# PwdToken

A hardware implementation of a piece of paper with your password, use with judgment!

There are (are there?) good reasons sometimes to store a particularly long and complex password in clear form ready to be typed at will. Be careful what you do with this, 
I take no responsibility.

IF you can exclude the Evil Maid scenario this could be something useful which is only one (tiny) step more safe than a piece of paper under your keyboard. You could make an argument that, being this air-gapped, it's safer (Evil Maid scenario excluded) than using an online password manager while retaining the ease of a clear text file cut/paste (!). 

Mostly a novelty, I found it useful to store the guest WiFi password so, trusted, guests can just plug this in an log in.

## Store Passwords

Make a copy of `secrets_example.h` to a file named `secrets.h`, edit the passwords and the OTP secret. Build and upload. Wipe `secrets.h`

## Validate Token

See the TokenValidator folder for instructions on how to validate a token, check its OTP and determine if it has been used and how many times.

## Retrieve a Password

Insert the token in a USB port and wait until the onboard (red) LED starts to flash slowly (one flash and a few seconds pause). This indicates password 1 is armed. Press repeatedly the button as many times as needed to select the desired password (amount of flashes will change to indicate the selected password). Focus on the application where the password is to be typed and keep the button pressed for a couple of seconds.

