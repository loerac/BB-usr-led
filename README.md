# BB-usr-led
Choose between BeagleBone's usr0 - usr3 LED's to turn on, off, flash or look at the status. The input for the usr[n] LED's is in bitwise, where _n_ is 0 - 3. To turn on all of them on, enter _15 1_ where _15_ is the LED's and _1_ is turning the LED's ON. To flash usr0 and usr2, enter _5 3_, where _5_ the LED's and _3_ is flashing the LED's. For a better clarification on bitwise, click [here](https://en.wikipedia.org/wiki/Bitwise_operation).

This certainly works on the Beaglebone Green Wireless and Black.

# Bugs
There are bugs in the all the versions - it will crash out of nowhere and it has to do with clearing the input buffer. Currently looking into a effective ways to clear the input buffer out since I already am clearing it.
