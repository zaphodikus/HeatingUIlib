
#inputs

##Push-to-make buttons
(use debounce logic and polling on a timer, not enough interrupts)

##Rotary encoders
[Illuminated RGB Quadrature](https://www.sparkfun.com/products/10982)


todo: Fork from Mercurial into git - for now use [QEI](https://os.mbed.com/cookbook/QEI)

mbed add http://os.mbed.com/users/aberk/code/QEI/


#Display
[Red on black 16x2 LCD](https://coolcomponents.co.uk/products/serial-enabled-16x2-lcd-red-on-black-5v?variant=45222877646) - part discontinued.

image:

![RED-on-Black](img/16x2-lcd-red-on-black.jpg)
[Serial LCD Commands](https://learn.sparkfun.com/tutorials/pic-based-serial-enabled-character-lcd-hookup-guide?_ga=2.160322362.623820446.1547752109-968112087.1538925376#firmware-overview)

# PyOCD install notes
If you are on Windblows and using Visual Studio code (free), then these notes may help.

[maclobdell/notebook/debugging-with-pyocd](https://os.mbed.com/users/maclobdell/notebook/debugging-with-pyocd/)

1. install pyocd 
1. install [libusb](https://libusb.info/) - the 32-bit dll into c:\python37 (the 64-bit dll is not going to get loaded by the python interpreter dwarves, even though you might be hopeing it will.)
1. run openocd 

https://libusb.info/

1. go to your .elf file folder (in a new shell)

cd ./BUILD/<targetname>/GCC_ARM

1. run gdb

arm-none-eabi-gdb
...

As usual it goes all wrong again at this point, so i am pasting notes from [Steve Mylroie'e Slideshare](https://www.slideshare.net/SMylroie/setting-up-a-vscode-development-environment-for-mbed-5-application-using-the-gcc-tool-chain-on-windows-114202826)

