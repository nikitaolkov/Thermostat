#include <Arduino.h>
#include "DHT.h"
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <EEPROM.h>
#include "webpages.h"

#define DEBUG_MODE                                      // -- КОНСТАНТА РЕЖИМА ОТЛАДКИ

#define INIT_ADDR 1023                                  // -- НОМЕР РЕЗЕРВНОЙ ЯЧЕЙКИ ДЛЯ ПЕРВОГО ЗАПУСКА
#define INIT_KEY 249                                    // -- КЛЮЧ ПЕРВОГО ЗАПУСКА

#define DHTPIN 4                                        // -- НОМЕР ПОРТА ПОДКЛЮЧЕНИЯ ДАТЧИКА ТЕМПЕРАТУРЫ
#define RELAY_PIN 16
#define DHTTYPE DHT22                                   // -- ТИП ДАТЧИКА ТЕМПЕРАТУРЫ

const char* PARAM_MIN_TEMP = "min_temp";                // -- ПАРАМЕТРЫ GET-ЗАПРОСА СО СТРАНИЦЫ НАСТРОЕК ВЕБ-ИНТЕРФЕЙСА
const char* PARAM_SSID = "ssid";
const char* PARAM_PASS = "pass";
const char* PARAM_STATIC_IP = "static_ip";

DHT dht(DHTPIN, DHTTYPE);                               // -- СОЗДАНИЕ ЭКЗЕМПЛЯРА КЛАССА ДАТЧИКА ТЕМПЕРАТУРЫ
AsyncWebServer server(80);                              // -- СОЗДАНИЕ ЭКЗЕМПЛЯРА КЛАССА ВЕБ-СЕРВЕРА

float temp_fridge = 0.0;                                // -- ТЕМПЕРАТУРА С ДАТЧИКА ХОЛОДИЛЬНИКА
float temp_freezer = 0.0;                               // -- ТЕМПЕРАТУРА С ДАТЧИКА МОРОЗИЛЬНОЙ КАМЕРЫ
float temp_compressor = 0.0;                            // -- ТЕМПЕРАТУРА С КОМПРЕССОРА                 
                                 

String relay_button_text = "Включить"; 
bool relay_activated = false;

struct Configuration {
  float min_temp = 20.0;                                 // -- МИНИМАЛЬНО ДОПУСТИМАЯ ТЕМПЕРАТУРА С ДАТЧИКА
  char ssid[10] = "termostat";                           // -- SSID ОСНОВНОЙ СЕТИ
  char password[15] = "141414121212";                    // -- ПАРОЛЬ ОСНОВНОЙ СЕТИ
};

String GetTemperature() 
{
  #ifdef DEBUG_MODE 
    Serial.println("Fridge temp: " + String(temp_fridge));  
  #endif
  
  return String(temp_fridge) + "/" + String(temp_freezer) + "/" + String(temp_compressor);
}

String processor(const String& var)
{

  #ifdef DEBUG_MODE
    Serial.println(var);
  #endif

  if (var == "TEMP_1") {
    if (!isnan(temp_fridge)) return String(temp_fridge);
  }
  else if (var == "TEMP_2") {
    if (!isnan(temp_freezer)) return String(temp_freezer);
  }
  else if (var == "TEMP_3") {
    if (!isnan(temp_compressor)) return String(temp_compressor);
  }
  return String();
}

Configuration configuration;

void setup() 
{
  pinMode(RELAY_PIN, OUTPUT);                            // -- ПИН РЕЛЕ 

#ifdef DEBUG_MODE 
  Serial.begin(115200); 
#endif

  EEPROM.begin(4096);
  delay(1000);

  if (EEPROM.read(INIT_ADDR) != INIT_KEY) { // -- ПЕРВЫЙ ЗАПУСК
    Serial.println("First EEPROM launch!");
    EEPROM.write(INIT_ADDR, INIT_KEY);    // -- ЗАПИСАЛИ КЛЮЧ
    EEPROM.put(0, configuration);
  }

  EEPROM.get(0, configuration);
  EEPROM.commit();
  EEPROM.end();

  dht.begin();
  delay(5000);

  WiFi.disconnect();
  WiFi.mode(WIFI_OFF);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(configuration.ssid, configuration.password);
  delay(1000);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
     request->send_P(200, "text/html", main_page, processor);
  });

  server.on("/main.html", HTTP_GET, [](AsyncWebServerRequest *request) {
     request->send_P(200, "text/html", main_page, processor);
  });
  
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/plain", GetTemperature().c_str());
  });

  server.on("/options.html", HTTP_GET, [](AsyncWebServerRequest *request) {
     request->send(200, "text/html", options_page);
  });

  server.on("/news.html", HTTP_GET, [](AsyncWebServerRequest *request) {
     request->send(200, "text/html", news_page);
  });

  server.on("/contacts.html", HTTP_GET, [](AsyncWebServerRequest *request) {
     request->send(200, "text/html", contacts_page);
  });

  server.on("/get_new_option_value", HTTP_GET, [](AsyncWebServerRequest *request) {
      String new_value;

      if (request->hasParam(PARAM_MIN_TEMP)) 
      {
        new_value = request->getParam(PARAM_MIN_TEMP)->value();
        if (new_value.toFloat() != configuration.min_temp) {
          configuration.min_temp = new_value.toFloat();

        #ifdef DEBUG_MODE
          Serial.println("Min Temp changed, new value: " + (String)configuration.min_temp);
        #endif
        }
      }

      if (request->hasParam(PARAM_SSID)) 
      {
        new_value = request->getParam(PARAM_SSID)->value();
        if (new_value != String(configuration.ssid)) {
          new_value.toCharArray(configuration.ssid, new_value.length() + 1);

          #ifdef DEBUG_MODE
            Serial.println("SSID changed, new value: " + String(configuration.ssid));
          #endif
        }
      }

      if (request->hasParam(PARAM_PASS)) 
      {
        new_value = request->getParam(PARAM_PASS)->value();
        if (new_value != String(configuration.password)) {
          new_value.toCharArray(configuration.password, new_value.length() + 1);

          #ifdef DEBUG_MODE
            Serial.println("Password changed, new value: " + String(configuration.password));
          #endif
        }
      }

      EEPROM.begin(4096);
      EEPROM.put(0, configuration);
      #ifdef DEBUG_MODE
        Serial.println("Configuration saved in EEPROM!");
      #endif
      EEPROM.commit();
      EEPROM.end();

      request->redirect("/options.html");
  });

  server.on("/get_options", HTTP_GET, [](AsyncWebServerRequest *request) {
    float temp_to_get = configuration.min_temp;
    request->send_P(200, "text/plain", (String(temp_to_get)
                                    + "/" + configuration.ssid 
                                    + "/" + configuration.password 
                                    ).c_str());
  });

  server.on("/relay_switch", HTTP_GET, [](AsyncWebServerRequest *request) {
    if(relay_button_text == "Включить")
      relay_button_text = "Выключить";
    else 
      relay_button_text = "Включить";

    relay_activated = !relay_activated;
    if (relay_activated)
      digitalWrite(RELAY_PIN, HIGH);
    else
      digitalWrite(RELAY_PIN, LOW);

    #ifdef DEBUG_MODE
      Serial.println(digitalRead(RELAY_PIN));
    #endif
    
    request->send_P(200, "text/plain", relay_button_text.c_str());
  });
  
  server.begin();

#ifdef DEBUG_MODE 
  Serial.println("Finished!!!");
#endif
  
}

void loop()
{
  temp_fridge = dht.readTemperature();
  temp_freezer = dht.readHumidity();
  
  delay(6000);
  #ifdef DEBUG_MODE
    Serial.println("Min_temp: " + String(configuration.min_temp));
  #endif
}

