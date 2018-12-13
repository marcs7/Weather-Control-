//compila quindi penso funzioni
#include "modWeather.h"

const char* ssid = "SSID NETWORD";
const char* password = "PSW NETWORK";

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup () {

  lcd.begin();
  lcd.backlight();

  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {

    delay(1000);
    Serial.println("Connecting..");

  }

}
void loop() {

  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    
    Serial.println("connected");
    lcd.print("connected");
    getWeather();
    
    lcd.print(weather0_description);
  }

  delay(30000);    //Send a request every 30 seconds

}
