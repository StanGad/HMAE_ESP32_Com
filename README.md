# HMAE Nov2023 Project: 'LOVE BOX'

## Project Description

The LOVE BOX project is an application that uses an OLED screen and a keyboard to send and receive emojis (smileys) wirelessly using the ESP-NOW library on ESP32 modules.

## Project Files

### 1. `main.ino`

The main file of the Arduino program. It initializes components such as the OLED screen, the keyboard, and ESP-NOW communication. It also manages the main program cycle, including the reception and sending of emojis.

### 2. `Bitmaps.h`

This header file contains declarations of arrays of images representing different smileys. These declarations are used in the main program to display emojis on the screen.

### 3. `Bitmaps.cpp`

The associated source file for `Bitmaps.h`. It defines arrays of smiley images. These definitions are included in the main program to use the images.

### 4. `Keypad.h`

A header file that defines a class for managing the matrix keyboard. This class is used in the main program (`main.ino`) to detect pressed keys.

## Usage

1. Upload the program to an ESP32 module using the Arduino IDE.
2. Change the MAC address to that of your partner's board.
3. Use the keyboard to select an emoji and press the 'A' key to send it.
4. Press the 'B' key to display a received emoji when the screen is on.
5. You can turn off the screen with the 'T' button (Select).
6. Even with the screen off, when you receive a message, the screen turns on.
7. The 'S' button (Start) returns to the menu.

## Dependencies

- Adafruit_GFX Library
- Adafruit_SSD1306 Library
- Keypad Library
- esp_now Library

## Authors

Stanislas GADECEAU
Emma MOLERA
