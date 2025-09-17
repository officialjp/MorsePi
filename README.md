# Pico Morse Code Decoder 🎶

> A simple, C-based Morse Code decoder for the Raspberry Pi Pico that uses a button for input and provides feedback via a 7-segment display, an LED, and a piezo buzzer.

## 📝 Overview

This project turns a Raspberry Pi Pico into an interactive Morse code translator. Users can input Morse code sequences using a single push-button. The program interprets the timings of the button presses to distinguish between dots and dashes.

  - If a **valid** Morse code sequence for a letter is entered, a short success tune plays on a piezo buzzer, and the corresponding letter is shown on a 7-segment display.
  - If an **invalid** sequence is entered, a red LED lights up, and the 7-segment display shows an 'E' for error.

The entire application is written in **C** using the Raspberry Pi Pico SDK, making it a great exercise for learning about GPIO handling, timing, and basic data structures in an embedded environment.

-----

## ✨ Features

  - **Single-Button Input**: Translates short and long button presses into Morse code dots and dashes.
  - **Real-time Decoding**: Decodes the 26 letters of the English alphabet.
  - **Visual Feedback**: A 7-segment display shows the decoded character or an error message.
  - **Error Indication**: A bright red LED immediately signals an incorrect Morse code sequence. 🔴
  - **Auditory Confirmation**: A cheerful melody plays from a piezo buzzer upon successful decoding. 🎵
  - **Lightweight & Efficient**: Built entirely in C for performance on the Pico.

-----

## 🛠️ Hardware Required

  - Raspberry Pi Pico
  - 1 x Push-button
  - 1 x Common Cathode 7-Segment Display
  - 1 x Red LED
  - 1 x Piezo Buzzer
  - 8 x 220Ω Resistors (7 for the display, 1 for the LED)
  - Breadboard
  - Jumper Wires

-----

## ⚙️ Software & Setup

This project is built using the official Raspberry Pi Pico C/C++ SDK.

### Prerequisites

Ensure you have the Pico SDK toolchain set up on your machine. If not, follow the official guide [here](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf).

### Build Instructions

1.  **Clone the repository:**

    ```bash
    git clone https://github.com/your-username/pico-morse-decoder.git
    cd pico-morse-decoder
    ```

2.  **Create a build directory and run CMake:**

    ```bash
    mkdir build
    cd build
    cmake ..
    ```

3.  **Compile the code:**

    ```bash
    make
    ```

4.  **Flash to Pico:**
    Hold the `BOOTSEL` button on your Pico while plugging it into your computer. It will mount as a USB mass storage device. Drag and drop the `morse_decoder.uf2` file from the `build` directory onto the Pico. The device will automatically reboot and run the program.

-----

## 🕹️ How to Use

The system interprets your button presses based on their duration.

  - **Dot (`.`):** A **short press** on the button (e.g., \~200ms).
  - **Dash (`-`):** A **long press** on the button (e.g., \~600ms).
  - **End of a Letter**: After inputting the sequence for a letter (e.g., `.--` for 'A'), **wait** for about 1 second. If the code is correct, the song will play and the letter will appear.
  - **Reset/New Letter**: The system automatically resets after each valid or invalid attempt, ready for a new letter.

### Example: Inputting 'S'

1.  Press the button three times quickly (dot, dot, dot).
2.  Wait for a moment.
3.  The success tune will play, and **'S'** will be displayed.

### Example: Inputting an Error

1.  Press the button five times quickly (an invalid code).
2.  Wait for a moment.
3.  The red LED will turn on, and **'E'** will be displayed.

-----

## 📜 License

This project is licensed under the MIT License. See the `LICENSE` file for more details.
