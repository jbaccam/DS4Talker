#DS4Talker
DS4Talker allows you to use a PlayStation DS4 controller to type words on a Windows system through Cygwin. 

#Requirements
*PlayStation DS4 Controller
*Windows operating system with Cygwin installed
*Bluetooth or USB connection for the DS4 controller

#Installation
*Install Cygwin on your Windows system if not already installed.
*Clone or download the DS4Talker repository to your local machine.
*Ensure your DS4 controller is connected to your PC via Bluetooth or a USB cable.
*Place all DS4Talker project files in the same directory to ensure proper functionality.
*Run with ./ds4rd-real.exe -d 054c:05c4 -D DS4_BT -t -b -j -bt | ./DS4Talker wordlist.txt
*Compile with gcc -o DS4Talker DS4Talker.c -lncurses

#Usage
Control the cursor with the right joystick to navigate through the word list displayed on the screen. Words can be selected and manipulated using the controller buttons as follows:

Triangle: Prints the selected word followed by a space.
Square: Prints the selected word without a space.
X: Deletes the last entered word.
Circle: Turns on capitalization. 

#Note:
Ensure all project files are located in the same directory, and the controller is connected before launching the program.
If you're using USB, make sure to change ./ds4rd-real.exe -d 054c:05c4 -D DS4_BT -t -b -j -bt | ./DS4Talker wordlist.txt
to ./ds4rd-real.exe -d 054c:05c4 -D DS4_USB -t -b -j -bt | ./DS4Talker wordlist.txt
Also depending on your controller you may have to change 054c:05c4 to 054c:09cc
