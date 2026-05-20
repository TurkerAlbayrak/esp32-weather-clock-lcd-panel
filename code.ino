#include <WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "time.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

const char* ssid = "WIFI_NAME";
const char* password = "WIFI_PASSWORD";

String apiKey = "OPENWEATHERAPI KEY";
String city = "CITY";
// String country = "TR";

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3 * 3600;
const int daylightOffset_sec = 0;

float temp = 0;
String weather = "";

unsigned long lastWeatherUpdate = 0;

void setup() {
  Serial.begin(115200);

  Wire.begin(21, 22);
  lcd.begin();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("WiFi baglaniyor");

  WiFi.begin(ssid, password);

  int counter = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");

    counter++;
    if (counter > 20) {
      lcd.clear();
      lcd.print("WiFi HATA");
      return;
    }
  }

  lcd.clear();
  lcd.print("WiFi OK");

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  delay(2000);
}

void getWeather() {
  if (WiFi.status() != WL_CONNECTED) return;

  HTTPClient http;

  String url = "http://api.openweathermap.org/data/2.5/weather?q=" +
               city + "," + country +
               "&appid=" + apiKey +
               "&units=metric";

  http.begin(url);
  int code = http.GET();

  if (code == 200) {
    String payload = http.getString();

    DynamicJsonDocument doc(2048);
    deserializeJson(doc, payload);

    temp = doc["main"]["temp"];
    weather = doc["weather"][0]["main"].as<String>();
  }

  http.end();
}

void loop() {

  if (millis() - lastWeatherUpdate > 60000 || lastWeatherUpdate == 0) {
    getWeather();
    lastWeatherUpdate = millis();
  }

  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    lcd.setCursor(0, 0);
    lcd.print("Saat yok");
    delay(1000);
    return;
  }

  char timeStr[6];
  strftime(timeStr, sizeof(timeStr), "%H:%M", &timeinfo);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Saat:");
  lcd.print(timeStr);

  lcd.setCursor(0, 1);
  lcd.print(city);
  lcd.print(" ");
  lcd.print(temp, 0);
  lcd.print(" ");
  lcd.print(weather);

  delay(1000);
}
