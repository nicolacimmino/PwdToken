# PwdToken

A hardware implementation of a piece of paper with your password, use with judgment!

There are (are there?) good reasons sometimes to store a particularly long and complex password in clear form ready to be typed at will. Be careful what you do with this, 
I take no responsibility.

IF you can exclude the Evil Maid scenario this could be something useful which is only one (tiny) step more safe than a piece of paper under your keyboard. You could make an argument that, being this air-gapped, it's safer (Evil Maid scenario excluded) than using an online password manager while retaining the ease of a clear text file cut/paste (!). 

Mostly a novelty, I found it useful to store the guest WiFi password so, trusted, guests can just plug this in an log in.

# Store your password

* Copy  the contents of `config_example.h` into a new file `config.h` (this reduces the risk to push passwords to git as `config.h` is `.gitignore`d
* Edit the password needed
* Edit the label to something that means something to you (I would avoid the username!)
* Edit the seal to something you recognize, pretty much anything you can remember and is not sensitive will do
* Go to PwdToken.ino and **un**comment the line `#define BUILD_LABEL_AND_SEAL`
* Build and program you Digispaspark board

This writes the seal. You can now program the actual password:

* Go to PwdToken.ino and **comment** the line `#define BUILD_LABEL_AND_SEAL`
* Build and program you Digispaspark board
* Verify that the LED is lit, this confirms that software loaded is the one capable of typing the password




