/**************************************************************************
 Author: Savir Bhangu
 Purpose: UWE Dissertation
 Date: 2020
 **************************************************************************/
// Include these libraries
// #include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <qrcode.h>

// Screen size defined
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

QRCode qrcode;

const char* MESSAGE_CONFIGURE_WIFI[4] = { "Scan QR", "to setup", "WiFi", "" };
const char* MESSAGE_OPEN_WEBAPP[4] = { "Scan QR", "to open", "Satvir", "webapp " };

void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3D)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.clearDisplay();
  display.display();

 //Display QRCODE with link to UWE as first test
  display.clearDisplay();
	drawQrCode("https://www.uwe.ac.uk/about/website/login", MESSAGE_OPEN_WEBAPP);
  delay(5000);
}

void loop() {
}


void drawQrCode(const char* qrStr, const char* lines[]) {
	uint8_t qrcodeData[qrcode_getBufferSize(3)];
	qrcode_initText(&qrcode, qrcodeData, 3, ECC_LOW, qrStr);
 
  // Text starting point
  int cursor_start_y = 10;
  int cursor_start_x = 4;
  int font_height = 12;

	// QR Code Starting Point
  int offset_x = 62;
  int offset_y = 3;

  for (int y = 0; y < qrcode.size; y++) {
      for (int x = 0; x < qrcode.size; x++) {
          int newX = offset_x + (x * 2);
          int newY = offset_y + (y * 2);

          if (qrcode_getModule(&qrcode, x, y)) {
							display.fillRect( newX, newY, 2, 2, 0);
          }
          else {
							display.fillRect( newX, newY, 2, 2, 1);
          }
      }
  }
  display.setTextColor(1,0);
  for (int i = 0; i < 4; i++) {
    display.setCursor(cursor_start_x,cursor_start_y+font_height*i);
    display.println(lines[i]);
  }
  display.display();
}
