LiquidCrystal_I2C lcd(0x27, 16, 2);
#include"time.h"
bool displayTimeColon = true;
unsigned long second = 0;


void lcdUpdate(){
  int _hour;
   if(( millis() - second ) >= 1000){
    displayTimeColon = !displayTimeColon;
    second = millis();
    LCDWeatherTimer ++;
    if(LCDWeatherTimer >= 5){
      LCDWeatherTimer = 0;
      displayWeather ++;
      if(displayWeather > 2){
        displayWeather = 0;
      }
    }
    
  }

  
  if(WiFi.status() != WL_CONNECTED){
   lcd.setCursor(0,0);
    lcd.print("    ");
   }else{
    lcd.setCursor(0,0);
   lcd.write((byte)3);
   lcd.print("   ");
   }
   
if(indoorLight == true){
  
  lcd.setCursor(15,0);
  lcd.write((byte)1);
}else{
  lcd.setCursor(15,0);
  lcd.print(" ");
  
  
}
if(securityLight == true){
  lcd.setCursor(14,0);
  lcd.write((byte)1);
}else{
  lcd.setCursor(14,0);
  lcd.print(" ");
}
    
    lcd.setCursor(3,0);
  if(hour < 10){
   lcd.print(" "); 
  }
  if(hour <= 12){
    if(hour < 10){
  lcd.print(" ");  
    }
  lcd.print(String(hour));
  }else if(hour > 12){
    _hour = hour - 12;
    if( _hour < 10){
      lcd.print(" ");
    }
    lcd.print(_hour);
  }

 
  if(displayTimeColon == true){
  lcd.print(":");
  }else{
   lcd.print(" "); 
  }
  if(minutes < 10){
   lcd.print("0"); 
  }
  lcd.print(String(minutes));
  lcd.print(" ");

if(hour < 12){
    lcd.print("AM");
  }else if(hour >= 12){
    lcd.print("PM");
  }
  lcd.print("  ");
  if(false){
   lcd.setCursor(0,1);
   
   switch(displayWeather){
    case 0:
      lcd.print("TEMPERATURE:");
      lcd.print(temperature);
      lcd.write((byte)4);
      lcd.print("C");
      lcd.print("   ");
     break;
     case 1:
        lcd.print("   ");
        lcd.print("HUMIDITY:");
        lcd.print(humidity);
        lcd.print("   ");
     break;
     case 2:
        lcd.print(currentWeather);
        lcd.print("            ");
      break;
   }}
   
   
   if(lcdTimer >= 1){
  backlit = false;
  lcd.noBacklight();
  
}else if (lcdTimer < 1){
  lcd.backlight();
  backlit = true;
}


  
  
  }