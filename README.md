# Arduino Driver for Brother AX350 Typewriter

I've decided to create this because:
 1. I happen to have a Brother AX350 typewriter from 1991
 2. The keyboard is NFG
 3. I wanted something simplish that I've already "*solved*" in my head.


What I decided to go with to create all of this is a [ProMicro 5V from Sparkfun](https://www.sparkfun.com/products/12640), two [8 channel multiplexers (also Sparkfun)](https://www.sparkfun.com/products/13906), [female headers](https://www.sparkfun.com/products/115), and [a lot of](https://www.sparkfun.com/products/13870) [m/m jumper wires](https://www.sparkfun.com/products/12795).

I went with the female over the male headers as I did not want to use a breadboard, and plan to hot glue the components in place after the code is "done," and I think that everything looks cleaner that way too. 

# Some useful things to know

 * I made a keymap manually by touching the contacts together about two years ago, I've long since lost it so I'll be making it again, this time by just tracing the traces on the keyboard itself.
 * There are 16 "pins" for the keyboard connector, and the way it works is the keyboard itself simply connects one of the first 8 to one of the second 8, thus the reason for two 8 channel multiplexers.
 * Yes, using two of those multiplexers with the Z pins connected to each other does allow any of the eight pins on one to connnect to one of the 8 on the other. I was fairly certain this should work just from the datasheets, but this also doesn't seem to be close to something anyone else has done before.
 * The resistance adds together between the two multiplexers, it does end up being around 150 Ohms when run at 5V (datasheet says resistance drops in multiplexer the higher the difference between VCC and GND/VEE), which considering I'm still waiting on some more headers in the mail to actually test this does still concern me a bit. Because...
 * Voltage between any of the first 8 and any of the second 8 is .56V according to my Klein meter, but hopefully this should be fine. I've had a hell of a time trying to figure out resistance of keyboard and it's flex PCB.

# Plans
 * Release a working "proof of concept" soonish
 * Actually finish this project, it's not that hard, come on *rolls eyes*
 * Write a PC/Raspberry PI client that handles buffering, 2.5KB of RAM on ProMicro is *not* a whole lot for buffering text. This file right at this point is already more than 2.5KB!
 * Tweak the crap out of the timing to find out just how fast I can get the AX350 to "print"
 
# PCB
 Yes, I was a bit stupid and designed a PCB before I had everything done, but hey, why not! First one I made was from SEEED Studio, and before it even arrived I changed my mind on where some things should be (and well, I forgot to add additional headers to the board so it would end up being a bit wonky, should have caught that). So I changed design a bit and sent off revision to [OSH Park](https://oshpark.com/shared_projects/Lo3atBIq) partly because Purple seems more awesomer, and OSH Park manufactures in the US. I don't really have anything against quality Chinese manufacturing, I'd just prefer to support companies that still operate out of the US. I've also added the Fritzing project I used to design PCB and the Gerber files to this project, and I should hopefully not have to edit them again.