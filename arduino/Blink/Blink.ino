/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman
  modified 11 Mar 2023
  by ARMW

  Basic assumption:
  Either HIGH or LOW are the only two states for the output pin, LED_BUILTIN
  This assumption may not prevail in a future release

  pinMode
  digitalRead
  digitalWrite
  delay

  LED_BUILTIN
  OUTPUT

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/


void setup() {                          // setup function runs once upon reset or power to the board
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}


void loop() {                           // loop function runs indefinitely
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); // flips the state of LED_BUILTIN
  delay(1000);                      // wait for 1000 milliseconds
}
