/*
    Scratch remote sensor protocol

    You need to get ssid , password and host

    http://tiisai.dip.jp/?p=3665
*/

/*
  Copyright 2016 Takeshi MUTOH

  Redistribution and use in source and binary forms, with or without modification,
  are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice,
     this list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright notice,
     this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*
   This program is demonstration that Scrath Remote Sensor Protocol with ESP8266.

   My presentation is below:
   http://qml.610t.org/squeak/CodarDojoNara201612.html

*/

/*
   Sensors & Actuators
   D2:  RGB LED
   D3:  Button switch
   D4:  DHT sensor (DHT11)
   D13: Built-in LED
*/

#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>

#define RGBLEDPIN            D2
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, RGBLEDPIN, NEO_GRB + NEO_KHZ800);

#include "DHT.h"

#define DHTPIN D4
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

const char* ssid     = "MUTOH_HOME";
const char* password = "2236rhino610t";

const char* host = "192.168.24.60";
const int Port = 42001;

int ledOn = false;

int r = 0, g = 0, b = 0;

void setup() {
  // Set up I/O mode
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(D3, INPUT);

  // Initialize Serial
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // This initializes the NeoPixel library.
  pixels.begin();

  // Initialize DHT sensor
  dht.begin();
}

int value = 0;

void loop() {
  uint8_t buffer[128] = {0};
  float t, t_old, h, h_old;

  delay(5000);
  ++value;

  Serial.print("connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;

  if (!client.connect(host, Port)) {
    Serial.println("connection failed");
    return;
  }

  Serial.print("create tcp ok\r\n");

  char *broadcastcmd = "sensor-update \"v\" 0 ";
  for (uint32_t n = 0; n < 100000; n++) {
    delay(10);
    char scmd[32] = {0};
    char dhtcmd[32] = {0};
    int sw, stat;

    // Read all from server and print them to Serial
    client.setTimeout(100);
    uint32_t len = client.readBytes(buffer, sizeof(buffer));
    String msg = "";
    if (len > 0) {
      Serial.print("Received:[");
      for (uint32_t i = 0; i < len; i++) {
        Serial.print((char)buffer[i]);
        if (i >= 4) { // Skip 4 byte message header
          msg += (char)buffer[i];
        }
      }
      Serial.print("]\r\n");

      // Skip until broadcast or sensor-update
      while ((!msg.startsWith("broadcast") && !msg.startsWith("sensor-update")) && msg.length() > 0 ) {
        msg.substring(1);
      }

      if (msg.startsWith("broadcast") == true) {
        // message
        msg.replace("broadcast ", "");
        msg.replace("\"", "");
        Serial.print("{broadcast:" + msg + "}");
      } else if (msg.startsWith("sensor-update")) {
        // value
        msg.replace("sensor-update ", "");
        msg.replace("\"", "");
        msg.trim();

        while (msg.length() > 0) {
          msg.trim();
          switch (msg.charAt(0)) {
            case 'r':
              msg.replace("r ", "");
              r = int(msg.toFloat());
              Serial.println("{R:" + String(r) + "}");
              break;
            case 'g':
              msg.replace("g ", "");
              g = int(msg.toFloat());
              Serial.println("{G:" + String(g) + "}");
              break;
            case 'b':
              msg.replace("b ", "");
              b = int(msg.toFloat());
              Serial.println("{B:" + String(b) + "}");
              break;
          }
          Serial.println("{{msg:" + msg + "}}");

          // Skip var_value
          while (msg.charAt(0) != ' ' && msg.length() > 0) {
            msg = msg.substring(1);
          }
          Serial.println("{{msg2:" + msg + "}}");
        }
        Serial.println("{RGB:(" + String(r) + ", " + String(g) + ", " + String(b) + ")}");
      } else {
        Serial.println("NOP");
      }
    }

    // RGB LED
    pixels.setPixelColor(0, pixels.Color(r, g, b));
    pixels.show();

    // BUILTIN LED blinking (not work)
    /*
      if (msg.equals("LED")) {
      if (ledOn) {
        Serial.println("LED off");
        digitalWrite(LED_BUILTIN, LOW);
        ledOn = false;
      } else {
        Serial.println("LED on");
        digitalWrite(LED_BUILTIN, HIGH);
        ledOn = true;
      }
      }
    */

    // send broadcast message
    if (digitalRead(D3) != sw) {
      sw = digitalRead(D3); stat = 1;
      strcpy(scmd + 4, "broadcast \"button\"");
    } else {
      if (stat == 1) {
        stat = 0;
        if (digitalRead(D3) == LOW) {
          strcpy(scmd + 4, "sensor-update \"btn\" 1 ");
        } else {
          strcpy(scmd + 4, "sensor-update \"btn\" 0 ");
        }
      }
    }
    scmd[3] = (uint8_t)strlen(scmd + 4);

    if (0 != strlen(scmd + 4)) {
      for (uint32_t i = 0; i < 4 + strlen(broadcastcmd); i++) {
        Serial.print(scmd[i]);
      }
      if (client.write((const uint8_t*)scmd, 4 + strlen(scmd + 4))) {
        Serial.println("send ok");
      } else {
        Serial.println("send err");
      }
    }

    // Get DHT data
    t = NAN;
    h = NAN;
    while ( isnan(t) || isnan(h) ) {
      t = dht.readTemperature();
      h = dht.readHumidity();
    }

    if ( t != t_old ) {
      char t_str[10];
      dtostrf(t, 4, 2, t_str);

      sprintf(dhtcmd + 4, "sensor-update \"t\" %s", t_str);

      for (uint32_t i = 0; i < 4 + strlen(broadcastcmd); i++) {
        Serial.print(dhtcmd[i]);
      }

      dhtcmd[3] = (uint8_t)strlen(dhtcmd + 4);
      if (client.write((const uint8_t*)dhtcmd, 4 + strlen(dhtcmd + 4))) {
        Serial.println("send ok");
      } else {
        Serial.println("send err");
      }
    }

    if ( h != h_old ) {
      char h_str[10];
      dtostrf(h, 4, 2, h_str);

      sprintf(dhtcmd + 4, "sensor-update \"h\" %s", h_str);

      for (uint32_t i = 0; i < 4 + strlen(broadcastcmd); i++) {
        Serial.print(dhtcmd[i]);
      }

      dhtcmd[3] = (uint8_t)strlen(dhtcmd + 4);
      if (client.write((const uint8_t*)dhtcmd, 4 + strlen(dhtcmd + 4))) {
        Serial.println("send ok");
      } else {
        Serial.println("send err");
      }
    }

    // Store current h & t
    h_old = h;
    t_old = t;
  }
}

