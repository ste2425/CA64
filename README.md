# CA64 (Commodore Arduino 64)

Converting a Commodore 64C into a USB keyboard. This project is built using a Commodore 64C however 
it is my understanding that other variants of the Commodore 64 family use the same internal keyboard.
Either way they are all simple matrixes so will be an easy task to modify the code accordingly.

# Components required

### Commodore 64C
### Arduino Leonardo
The Leonardo has built HID emulation. Other models which don't have that ability [have](http://biosrhythm.com/?p=910) been used in the past but those are more difficult to implement and need extra hardware also.
### Approx. 16 jumper wires
### Arduino IDE
This is not the only IDE. VSCode can be used with the Arduino extension among other editors and IDE's.
  
# Hardware setup. 

The commodore keyboard is an 8x8 matrix. This means 16 wires need connecting to the Arduino, 8 for the keyboard rows and another 8 for the columns. [Here's](http://pcbheaven.com/wikipages/How_Key_Matrices_Works/) a useful resource for how a keyboard matrix works. 

It’s quite simple just connect it up as per the following image.

![pinout](https://user-images.githubusercontent.com/8177767/42420437-e75da662-82bd-11e8-918d-a8c90e846902.png)

# Firmware

To make life easier an Arduino library called [Keypad](https://playground.arduino.cc/Code/Keypad) ([Github source](https://github.com/Chris--A/Keypad)) was used to deal with interfacing with a keyboard matrix.

The internal [Keyboard](https://www.arduino.cc/reference/en/language/functions/usb/keyboard/) library was used to emulate a HID Keyboard.

The flow is essentially get the pressed key. If it’s the shift key find the alternate for the second key pressed. If it’s not shift check if it’s an aliased key such as the DEL key or arrow keys.

The alternate key and aliased key maps are char arrays. It will iterate the array issuing a key press command for each key found in the array. Once all are pressed it will then issue a release all keys command.

# Acknowledgements
The following resources I found useful when researching this:
* https://www.waitingforfriday.com/?p=470
* http://biosrhythm.com/?p=910 
