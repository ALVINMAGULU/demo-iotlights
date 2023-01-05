#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

#define RXD1 16
#define TXD1 17

#define INDOORLIGHT 16
#define SECURITYLIGHT 18

#include <LiquidCrystal_I2C.h>
#include "internetM.h"
#include"lcd_chars.h"
#include "LCD.h"

#include "wifi_functions.h"

#include <WiFi.h>
#include <WiFiClient.h>
#include <NTPClient.h>

const char* wifissid     = "ssid";
const char* wifipassword = "password";
const long utcOffsetInSeconds = 10800;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);


int weatherTimer = 0;

int connection = 1;
bool pvs0;
bool pvs1;
bool bl;
bool newCon = true;
int network;

bool previndoorLightT;

bool prevsecurityLightT;

bool prevbacklightT;

hw_timer_t * timer = NULL;
volatile byte state = LOW;
 void IRAM_ATTR onTimer(){
 timeUpdate();
 lcdTimer++;
 connection++;
 weatherTimer++;
 LCDWeatherTimer ++;
}



  



void networkMonitor( void *pvParameters );
void clientHandler( void *pvParameters );



void setup() {

  pinMode(INDOORLIGHT,OUTPUT);
  pinMode(SECURITYLIGHT,OUTPUT);
  
  
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 60000000, true);
  timerAlarmEnable(timer);
  

  
 lcd.init();
 lcd.backlight();
 lcd.createChar(1, light);
//lcd.createChar(2,updateChar);
 lcd.createChar(3,WIFI);
 lcd.createChar(4,degree);
 
 Serial.begin(115200);
 lcd.setCursor(3,0);
 lcd.print("Configuring");
 
 wifiScanner(wifissid,wifipassword,lcdTimer);
//upgrade();
 if(WiFi.status() == WL_CONNECTED){
 timeClient.begin();
 timeClient.update();
 hour = timeClient.getHours();
 minutes = timeClient.getMinutes();
// ArduinoOTA.begin();
  weather();
 }
lcd.clear();
 Serial2.begin(9600, SERIAL_8N1, RXD1, TXD1);
 Serial2.print("OK");
  String ardcheck;

 // setting up wifi task
  xTaskCreatePinnedToCore(
    networkMonitor
    ,  "network monitor"   
    ,  1500 
    ,  NULL
    ,  1 
    ,  NULL 
    ,  ARDUINO_RUNNING_CORE);

     xTaskCreatePinnedToCore(
    clientHandler
    ,  "client handler"
    ,  2000  // Stack size
    ,  NULL
    ,  2  // Priority
    ,  NULL 
    ,  ARDUINO_RUNNING_CORE);
//  timeClient.begin();
}


 
void loop(){
  if(WiFi.status() != WL_CONNECTED){
 wifiScanner(wifissid,wifipassword,lcdTimer);
  _wifi = false;
    
  }else{
    if(_update == false){
   requester();
  
    } else {
      updater();
    }
   timeClient.update();
   hour = timeClient.getHours();
   minutes = timeClient.getMinutes();
    if(weatherTimer >= 5){
    weather();
    weatherTimer = 0;
  }
_wifi = true;
  }
  
  
  delay(5000);
  
  }
    



void networkMonitor(void *pvParameters)  // This is a task.
{
  (void) pvParameters;


  for (;;) // A Task shall never return or exit.
  {
    
    if(touchRead(T3) <= 20){
      if(previndoorLightT == false){
        indoorLight != indoorLight;
      }
      previndoorLightT = true;
      }else{
        previndoorLightT = false;
        }
      if(touchRead(T8) <= 20){
      if(prevsecurityLightT == false){
        indoorLight != indoorLight;
      }
      prevsecurityLightT = true;
      }else{
        prevsecurityLightT = false;
        }
       if(touchRead(T9) <= 20){
      if(prevbacklightT == false){
        indoorLight != indoorLight;
      }
      prevbacklightT = true;
      }else{
        prevbacklightT = false;
        }
  }
   

  
}
void clientHandler(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  


  for(;;)
  {
  //  lcd.clear();
 
lcdUpdate();


if(lcdTimer >= 1 && backlit != true){
  
  lcd.noBacklight();
  
}else if (lcdTimer < 1 || backlit == true){
  lcd.backlight();
}



if(pvs0 != indoorLight || pvs1 != securityLight || bl != backlit){
  lcdTimer = 0;
  pvs0 = indoorLight;
  pvs1 = securityLight;
  bl = backlit;
 
  
  
  //payloadP();
}
 
   if(_wifi == false){
   lcd.setCursor(0,0);
    lcd.print(" ");
   }else{
    lcd.setCursor(0,0);
   lcd.write((byte)3);
   }
 
 
  
   digitalWrite(INDOORLIGHT,!indoorLight);
   digitalWrite(SECURITYLIGHT,!securityLight);

   if(hour == 19 && minutes == 0){
    
      securityLight = true;
      _update = true;
   }else if(hour == 7 && minutes == 0){
    _update = true;
     securityLight = false;
   }
   vTaskDelay(500);
  
  }

}






 
