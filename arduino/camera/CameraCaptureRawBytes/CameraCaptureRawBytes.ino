/*
 * CameraCaptureRawBytes.ino
 * 
 * Camera pixel format enumeration
 * The different formats use different number of bits per pixel:
 * Grayscale (8-bit), Bayer (8-bit), RGB565 (16-bit)
 *
 *  CAMERA_GRAYSCALE    = 0,
 *  CAMERA_BAYER        = 1,
 *  CAMERA_RGB565       = 2,
 *  CAMERA_PMAX                 //Sentinel value
 *
 *  Camera resolution enumeration
 *  CAMERA_R160x120     = 0,   // QQVGA Resolution
 *  CAMERA_R320x240     = 1,   // QVGA Resolution
 *  CAMERA_R320x320     = 2,   // 320x320 Resolution
 *  CAMERA_R640x480     = 3,   // VGA
 *  CAMERA_R800x600     = 5,   // SVGA
 *  CAMERA_R1600x1200   = 6,   // UXGA
 *  CAMERA_RMAX                // Sentinel value
 *
 * OV7675:
 *   Image sizes:
 *      VGA:    640 x 480
 *      QVGA:   320 x 240
 *      QQVGA:  160 x 120
 *   Output formats:
 *      YUV4.2.2
 *      RAW RGB
 *      ITU656
 *      RGB565
 * References:
 *   https://docs.arduino.cc/tutorials/giga-r1-wifi/giga-camera
 *   https://www.ovt.com/wp-content/uploads/2022/01/OV7675-PB-v1.2-WEB.pdf
 *   https://github.com/arduino/ArduinoCore-mbed/blob/main/libraries/Camera/docs/api.md
 *
 */

#include "camera.h"
#include "SDRAM.h"

#ifdef ARDUINO_NICLA_VISION
  #include "gc2145.h"
  GC2145 galaxyCore;
  Camera cam(galaxyCore);
  #define IMAGE_MODE CAMERA_RGB565
#elif defined(ARDUINO_PORTENTA_H7_M7)
  #include "hm0360.h"
  HM0360 himax;
  Camera cam(himax);
  #define IMAGE_MODE CAMERA_GRAYSCALE
#elif defined(ARDUINO_GIGA)
  //#include "ov7670.h"//Compilation error: ov7670.h: No such file or directory
  //OV7670 ov7670;
  //Camera cam(ov7670);
  #include "ov767x.h"
  OV7675 ov767x;
  Camera cam(ov767x);
  #define IMAGE_MODE CAMERA_RGB565
#else
#error "This board is unsupported."
#endif


/*
Other buffer instantiation options:
  FrameBuffer fb(0x30000000);
  FrameBuffer fb(320,240,2);
*/
//FrameBuffer fb;
/**
 * construct a new frame buffer object with a fixed size
 * @x width of the frame buffer
 * @y height of the frame buffer
 * @bpp bits per pixel
 */
//[FrameBuffer](#)
FrameBuffer fb(SDRAM_START_ADDRESS);

unsigned long lastUpdate = 0;

void blinkLED(uint32_t count = 0xFFFFFFFF)
{
  pinMode(LED_BUILTIN, OUTPUT);
  while (count--) {
    digitalWrite(LED_BUILTIN, LOW);  // turn the LED on (HIGH is the voltage level)
    delay(50);                       // wait for a second
    digitalWrite(LED_BUILTIN, HIGH); // turn the LED off by making the voltage LOW
    delay(50);                       // wait for a second
  }
}

void setup() {
  SDRAM.begin();                     // using a fixed address for resolutions greater than 320x240
  if (!cam.begin(CAMERA_R640x480, IMAGE_MODE, 30)) {  // Initthe cam QVGA, 30FPS
  //if (!cam.begin(CAMERA_R320x240, IMAGE_MODE, 30)) {  // Initthe cam QVGA, 30FPS
    blinkLED();
  }
  blinkLED(5);
}

void loop() {
  if(!Serial) {    
    Serial.begin(921600);
    while(!Serial);
  }

  bool timeoutDetected = millis() - lastUpdate > 2000;  // Time out after 2 seconds and send new data
  
  if(!timeoutDetected && Serial.read() != 1) return;    // Wait for sync byte

  lastUpdate = millis();
  
  if (cam.grabFrame(fb, 3000) == 0) {  // Grab frame and write to serial
    Serial.write(fb.getBuffer(), cam.frameSize());
  } else {
    blinkLED(20);
  }
}