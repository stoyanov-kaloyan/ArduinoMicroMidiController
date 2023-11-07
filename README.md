# ArduinoMicroMidiController

This Arduino sketch is designed to create a MIDI controller using multiplexers to read potentiometer values and send MIDI control change messages to a computer. The controller has two 8-channel multiplexers, and it can control a total of 15 MIDI parameters.

It is designed to work with the Arduino Micro, for the Atmega32U4 microcontroller but it will also work on any other arduino with this chip. It is important to note that not any arduino will be capable of executing this code properly because the code uses the MIDI USB interface, so you'll need a microcontroller with a built-in USB controller.

## Features

- Supports up to 15 MIDI control parameters.
- Uses multiplexers to read potentiometer values efficiently.
- Sends MIDI control change messages to a computer via USB.

## Components

- Arduino Micro board (or any other Atmega32U4 Arduino)
- 74HC4051 or similar analog multiplexers (two multiplexers used)
- Potentiometers (8 for the first multiplexer, 7 for the second multiplexer)
- USB cable to connect the Arduino to a computer

## Installation and Setup

1. Install the Arduino IDE if you haven't already: [Arduino Software](https://www.arduino.cc/en/software)

2. Clone or download this repository to your local machine.

3. Open the Arduino IDE and load the `MIDI_Controller_with_Multiplexers.ino` sketch from the repository.

4. Make sure you have the required libraries, such as `MIDIUSB`, installed in your Arduino IDE.

5. Connect your Arduino board to your computer via USB.

6. Select the appropriate board and port in the Arduino IDE.

7. Upload the sketch to your Arduino board.

8. Once uploaded, the MIDI controller is ready to use.

## Build steps

TODO: Upload photos and schematics

1. Connect your potentiometers to the multiplexers.

2. Connect the multiplexers to the pins specified in the sketch (MUXpins and MUXpins2).

3. Turn on your MIDI software on your computer.

4. Move the potentiometers, and the Arduino will send MIDI control change messages to your computer.

5. Configure your MIDI software to respond to the received MIDI messages.

## Customization

You can customize the sketch by changing the following parameters:

- `sensitivity`: Adjust the deadzone for the potentiometers to avoid sending unnecessary MIDI messages.

- `MUXpins` and `MUXpins2`: Define the pins that control the multiplexers.

- `potsCount`: Set the number of potentiometers for each multiplexer.

- `potParameters` and `potParameters2`: Specify the MIDI control parameters that change for each potentiometer.

- You can modify the multiplexer setup if you are using a different multiplexer model.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

Feel free to contribute, report issues, or suggest improvements.

Happy MIDI controlling!
