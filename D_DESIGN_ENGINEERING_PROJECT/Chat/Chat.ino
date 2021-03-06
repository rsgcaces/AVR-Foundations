// PROJECT  :Chat
// PURPOSE  :Utility to enable a peer-peer conversation between ACES' Arduino users
// DEVICE   :2 Arduinos
// AUTHOR   :Many hands
// DATE     :2020 11 17
// uC       :328p
// COURSE   :ICS3U
// STATUS   :Working
// REFERENCE:https://www.arduino.cc/en/Tutorial/SoftwareSerialExample
//          :http://darcy.rsgc.on.ca/ACES/Projects/SerialMastermind/index.html
// NOTES    :Hardware serial used to Rx/Tx from/to local Serial Monitor
//          :Software serial used to Tx/Rx to/from peer
//          :Be sure to wire a Common Ground line!
#include <SoftwareSerial.h>
#define RX  7
#define TX  8
SoftwareSerial chat(RX,TX); //Software Emulation of hardware UART
#define BAUD 9600           //Common BAUD rate for hardware UART and Software Serial

char ch;                    //single utility character for communication

void setup() {
  Serial.begin(BAUD);     //use the hardware UART for the Serial Monitor
  while (!Serial);        //wait for hardware serial port to connect
  Serial.println("Starting Chat Program...");
  chat.begin(BAUD);       //set the data rate for the SoftwareSerial port
  while(!chat);           //wait for software serial port to connect                       
  
  chat.println("Hello, world?");      //anyone home?
  Serial.println("Ready to chat..."); //local connection ready...
}

void loop() {
  if (chat.available()) {             //anything incoming?
    Serial.write(chat.read());        //if so, display the oldest character in the incoming (queued) buffer
  }
  if (Serial.available())  {          //anything outgoing?
    Serial.print("Self:\t");          //if so, let's get started...
    while (Serial.available()) {      //transmit each of the outgoing characters...
      ch = Serial.read();             //...to the software serial stream
      chat.write(ch);                 //...
      Serial.write(ch);               //also, echo each character on my local Serial Monitor
    }
    chat.println();                   //at end, transmit a newline (carriage return) character
    Serial.println();                 //at end, also write a newline character to the local Serial Monitor
  }
}
