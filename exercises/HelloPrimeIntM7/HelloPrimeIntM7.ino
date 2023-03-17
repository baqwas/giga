/**
 * @file HelloPrimeInt.ino
 * @brief To monitor serial output from Arduino GIGA R1 WiFi board co-processor (viz. M4)
 * @author armw
 *
 * millis - returns elapsed time, in milliseconds as unsigned long, since the start of the current program
 */

#include <RPC.h>

/**
 * this section runs once at startup
 */
void setup() {                          // basic initialization
  Serial.begin(115200);                 // faster speeds may be supported
  Serial.println("GIGA R1 WiFi");       // for documentation purposes
  RPC.begin();                          // 
}

/**
 * this section runs indefinitely
 */
void loop() {                           // repeat the calculations
  String buffer = "";                   // receive buffer for M4 data

  while (RPC.available()) 
  {
    buffer += (char) RPC.read();
  }
  if (buffer.length() > 0)
  {
    Serial.print(buffer);
  }
}
