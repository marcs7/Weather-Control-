//librerie per esp8266

//interfaccia
#include "modWeather.h"

void getWeather()
{
  LiquidCrystal_I2C lcd(0x27, 20, 4);

  HTTPClient http; //Declare an object of class HTTPClient
  http.begin(
    "http://api.openweathermap.org/data/2.5/weather?id=6542141&lang=it&units=metric&appid=e7d7ff129b8e1db7e407aeb900243822"); //Specify request destination
  int httpCode = http.GET();                                                                                                                             //Send the request

  if (httpCode > 0)
  { //Check the returning code
    lcd.clear();

    const size_t bufferSize = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 2 * JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(12) + 390;
    DynamicJsonBuffer jsonBuffer(bufferSize);

    JsonObject &root = jsonBuffer.parseObject(http.getString());

    float coord_lon = root["coord"]["lon"]; // 10.88
    float coord_lat = root["coord"]["lat"]; // 46.38

    JsonObject &weather0 = root["weather"][0];
    int weather0_id = weather0["id"];                           // 801
    const char *weather0_main = weather0["main"];               // "Clouds"
    const char *weather0_description = weather0["description"]; // "low clouds"
    const char *weather0_icon = weather0["icon"];               // "02d"

    const char *base = root["base"]; // "stations"

    JsonObject &main = root["main"];
    float main_temp = main["temp"];         // -1
    float main_pressure = main["pressure"]; // 1019
    float main_humidity = main["humidity"]; // 100
    float main_temp_min = main["temp_min"]; // -1
    float main_temp_max = main["temp_max"]; // -1

    int visibility = root["visibility"]; // 10000

    float wind_speed = root["wind"]["speed"]; // 4.1
    int wind_deg = root["wind"]["deg"];       // 350

    int clouds_all = root["clouds"]["all"]; // 20

    long dt = root["dt"]; // 1544097300

    JsonObject &sys = root["sys"];
    int sys_type = sys["type"];               // 1
    int sys_id = sys["id"];                   // 6830
    float sys_message = sys["message"];       // 0.0027
    const char *sys_country = sys["country"]; // "IT"
    long sys_sunrise = sys["sunrise"];        // 1544078711
    long sys_sunset = sys["sunset"];          // 1544110201

    long id = root["id"];            // 3178548
    const char *name = root["name"]; // "Cagliari"
    int cod = root["cod"];           // 200

    // RETURN VARIABILI

    return(weather0_description);
    return(main_temp);
    return(main_temp_max);
    return(main_temp_min);

    //PRINT SU LCD

    lcd.setCursor(0, 0);
    lcd.print("Stato: ");
    lcd.print(weather0_description);

    lcd.setCursor(0, 1);
    lcd.print("Temp: ");
    lcd.print(main_temp);
    lcd.print(" C");

    lcd.setCursor(0, 2);
    lcd.print("Temp Max: ");
    lcd.print(main_temp_max);
    lcd.print(" C");

    lcd.setCursor(0, 3);
    lcd.print("Temp Min: ");
    lcd.print(main_temp_min);
    lcd.print(" C");

  }

  http.end(); //Close connection
}


