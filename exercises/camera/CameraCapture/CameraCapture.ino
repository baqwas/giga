/*
  CameraCapture.ino
  OV767X - Camera Test Pattern

  This sketch waits for the letter 'c' on the Serial Monitor,
  it then reads a frame from the OmniVision OV7670 camera and 
  prints the data to the Serial Monitor as a hex string.

  The website https://rawpixels.net - can be used the visualize the data:
    width: 176
    height: 144
    RGB565
    Little Endian

  Circuit:
    - Arduino Nano 33 BLE board
    - OV7670 camera module:
      - 3.3 connected to 3.3
      - GND connected GND
      - SIOC connected to A5
      - SIOD connected to A4
      - VSYNC connected to 8
      - HREF connected to A1
      - PCLK connected to A0
      - XCLK connected to 9
      - D7 connected to 4
      - D6 connected to 6
      - D5 connected to 5
      - D4 connected to 3
      - D3 connected to 2
      - D2 connected to 0 / RX
      - D1 connected to 1 / TX
      - D0 connected to 10

  This example code is in the public domain.
*/
#include "camera.h"
#include "ov767x.h"

#define IMAGE_MODE CAMERA_RGB565

OV7675 ov767x;
Camera cam(ov767x);

unsigned short pixels[176 * 144]; // QCIF: 176x144 X 2 bytes per pixel (RGB565)

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("OV767X Camera Capture");
  Serial.println();

  if (!cam.begin(CAMERA_R320x240, IMAGE_MODE, 30)) {
    Serial.println("Failed to initialize camera!");
    while (1);
  }

  Serial.println("Camera settings:");
  Serial.print("\twidth = ");
  Serial.println(cam.width());
  Serial.print("\theight = ");
  Serial.println(cam.height());
  Serial.print("\tbits per pixel = ");
  Serial.println(cam.bitsPerPixel());
  Serial.println();

  Serial.println("Send the 'c' character to read a frame ...");
  Serial.println();
}

void loop() {
  if (Serial.read() == 'c') {
    Serial.println("Reading frame");
    Serial.println();
    cam.readFrame(pixels);

    int numPixels = cam.width() * cam.height();

    for (int i = 0; i < numPixels; i++) {
      unsigned short p = pixels[i];

      if (p < 0x1000) {
        Serial.print('0');
      }

      if (p < 0x0100) {
        Serial.print('0');
      }

      if (p < 0x0010) {
        Serial.print('0');
      }

      Serial.print(p, HEX);
    }
  }
}