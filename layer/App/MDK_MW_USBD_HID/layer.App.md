MDK-Middleware: USB Device HID example
======================================

This application demonstrates **USB Device Human Interface Device class (HID)** developed with MDK-Middleware.

Detailed description is available in the [*MDK-Middleware USB Component documentation*](https://www.keil.com/pack/doc/MW/USB/html/dev_hid_tutorial.html).

Usage
-----
1. Build the application
2. Connect the debugger to the board
3. Configure the debugger in the uVision
4. Power-up the board
5. Download the code to the board
6. Reset the board
7. Connect the board's USB port to the USB Host (PC)

HID Client application is available for Microsoft Windows OS and can be used to view 
state of virtual buttons (vioBUTTONs) and control state of virtual LEDs (vioLEDs).  
The HID Client application **HIDClient.exe** can be found in the `<Keil-root>\ARM\Utilities\HID_Client\Release\` directory.
