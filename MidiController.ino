#include "MIDIUSB.h"

const int sensitivity = 2;                  // Deadzone for the potentiometer
const int MUXpins[] = {2, 3, 4};             // Pins that control multiplexer 1
const int MUXpins2[] = {5, 6, 7};            // Pins that control multiplexer 2
const int potsCount = 8;                     // Number of potentiometers for each multiplexer
int pots[8];                                 // Current values of the potentiometers
int pots2[7];                                // Current values of the potentiometers
int potsLastVal[] = {0, 0, 0, 0, 0, 0, 0, 0}; // Last values of the potentiometers
int potsLastVal2[] = {0, 0, 0, 0, 0, 0, 0, 0}; // Last values of the potentiometers
const int multiplexerInputPin = A0;         // Input pin of the analog-to-digital converter on the microcontroller
const int multiplexerInputPin2 = A1;        // Input pin of the analog-to-digital converter on the microcontroller
const int MUXtable[][3] = {
  {0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1},
  {1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}
}; // Values for multiplexer switching
const int potParameters[] = {4, 5, 6, 7, 8, 9, 10, 11};  // MIDI parameters that change
const int potParameters2[] = {12, 13, 14, 15, 16, 17, 18}; // MIDI parameters that change

// Function to send MIDI control change messages to the computer
void controlChange(byte channel, byte control, byte value)
{
    midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
    MidiUSB.sendMIDI(event);
}

void setup()
{
    // Set the corresponding pins of the multiplexers as output pins
    for (int i = 0; i < potsCount; i++)
    {
        pinMode(MUXpins[i], OUTPUT);
        pinMode(MUXpins2[i], OUTPUT);
    }

    // Set the pins of the multiplexer as input pins
    // Their value cannot be set but only read
    pinMode(multiplexerInputPin, INPUT);
    pinMode(multiplexerInputPin2, INPUT);
}

void loop()
{
    // On each iteration of the loop, the multiplexer input is switched
    // The value (voltage) of the potentiometer connected to that input is read
    // And is stored in an array, and if the value of the corresponding potentiometer
    // is different from the previous one, a message is sent to the computer

    for (int i = 0; i < 8; i++)
    {
        digitalWrite(MUXpins[0], MUXtable[i][0]);
        digitalWrite(MUXpins[1], MUXtable[i][1]);
        digitalWrite(MUXpins[2], MUXtable[i][2]);

        // Convert the value from 10-bit to 7-bit
        pots[i] = analogRead(multiplexerInputPin) >> 3;

        if (potsLastVal[i] > pots[i] + sensitivity || potsLastVal[i] < pots[i] - sensitivity)
        {
            controlChange(0x01, potParameters[i], pots[i]);
            potsLastVal[i] = pots[i];
        }

        // Ensure that all pending MIDI messages are sent
        MidiUSB.flush();
    }

    for (int i = 0; i < 7; i++)
    {
        digitalWrite(MUXpins2[0], MUXtable[i][0]);
        digitalWrite(MUXpins2[1], MUXtable[i][1]);
        digitalWrite(MUXpins2[2], MUXtable[i][2]);

        pots2[i] = analogRead(multiplexerInputPin2) >> 3;

        if (potsLastVal2[i] > pots2[i] + sensitivity || potsLastVal2[i] < pots2[i] - sensitivity)
        {
            controlChange(0x01, potParameters2[i], pots2[i]);
            potsLastVal2[i] = pots2[i];
        }

        MidiUSB.flush();
    }
}