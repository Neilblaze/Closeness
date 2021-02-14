#include <ESP8266WiFi.h>

bool lights[5] = {false, false, false, false, false};
int light_pins[5] = {5, 4, 13, 12, 14};

void render() {
  for (int i = 0; i < 5; i++) {
    bool value = lights[i];
    int pin = light_pins[i];

    digitalWrite(pin, value ? HIGH : LOW);
  }
}

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < 5; i++) {
    int pin = light_pins[i];
    pinMode(pin, OUTPUT);
  }

  WiFi.mode(WIFI_STA);
}

void loop() {
  int n = WiFi.scanNetworks();
  bool found = false;
  
  for (int i = 0; i < n; i++)
  {
    if (WiFi.SSID(i) != "NearYouHotspot") continue;
    found = true;

    int p = -WiFi.RSSI(i);
    Serial.println(p);
    
    if (p < 50) {
      lights[0] = true;
      lights[1] = true;
      lights[2] = true;
      lights[3] = true;
      lights[4] = true;
    } else if (p < 60) {
      lights[0] = true;
      lights[1] = true;
      lights[2] = true;
      lights[3] = true;
      lights[4] = false;
    } else if (p < 73) {
      lights[0] = true;
      lights[1] = true;
      lights[2] = true;
      lights[3] = false;
      lights[4] = false;
    } else if (p < 86) {
      lights[0] = true;
      lights[1] = true;
      lights[2] = false;
      lights[3] = false;
      lights[4] = false;
    } else {
      lights[0] = true;
      lights[1] = false;
      lights[2] = false;
      lights[3] = false;
      lights[4] = false;
    }
  }

  if (!found) {
    lights[0] = false;
    lights[1] = false;
    lights[2] = false;
    lights[3] = false;
    lights[4] = false;
  }
  
  render();
}
