#include "bools.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>
//#include "ota.h"

bool otaUpgrade = false;
String payload;
String httpweb = "http://140.238.86.79//update.php?";

String outdoor = "SL=";
String _backlight = "BL=";
String indoor = "IL=";
String _and = "&&";
String _ota = "OTA=";

String jsonbuffer;


String httpstate(bool state) {
  if (state == true) {
    return "L1";
  } else if (state == false) {
    return "L0";
  }
}

void updater() {
  HTTPClient http;
  String outstate = httpstate(securityLight);
  String instate = httpstate(indoorLight);
  String backstate = httpstate(backlit);
  String otaState = httpstate(otaUpgrade);

  String weblink = httpweb + indoor + instate + _and + outdoor + outstate + _and + _backlight + backstate + _ota + otaState;
  ;
  //Serial.println(weblink);
  http.begin(weblink);

  //payload = gsm.get(weblink,reader);

  http.end();
  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK) {
    _update = false;
    Serial.println(http.getString());
    // USE_SERIAL.println(payload);
  }
}

void requester() {
  HTTPClient http;
  String lightsJson;
  String Url = "http://140.238.86.79/request.php?device=Alvinesp1";
  if (http.begin(Url)) {
    int httpCode = http.GET();

    if (httpCode == HTTP_CODE_OK) {
      DynamicJsonBuffer JSON;
      lightsJson = http.getString();
      Serial.println(lightsJson);
      JsonObject& myObject = JSON.parseObject(lightsJson);
      if (myObject.success()) {
        indoorLight = myObject["Indoor"];
        securityLight = myObject["Outdoor"];
      }
    }
  }
}

void weather() {
  String weatherJson;
 String weatherUri = "http://api.openweathermap.org/data/2.5/weather?q=masaka,UG&APPID=df1488b9b87443f14d5212a7e529bb82";
    HTTPClient http;
    http.begin(weatherUri);
    int httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK) {
      weatherJson = http.getString();
      Serial.println(weatherJson);
      DynamicJsonBuffer JSON;
      JsonObject& myObject = JSON.parseObject(weatherJson);

      Serial.println(weatherJson);
      if (myObject.success()) {
        temperature = int(myObject["main"]["temp"]);
        Serial.println(temperature);
        temperature = temperature - 273.15;
        humidity = int(myObject["main"]["humidity"]);
        currentWeather = myObject["weather"][0]["description"].as<String>();
      }
    }
}
/*void error(String load){
  if(!gsm.isConnected()){
    while(gsm.signalQuality() <= 0 || gsm.signalQuality() == 99 ){
     
    }
     
     gsm.connect();
  }
  
}
*/