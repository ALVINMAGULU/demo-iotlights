
// Wifi connecting Method

/*IPAddress local_IP(192, 168, 15, 176);
IPAddress gateway(192, 168, 15, 149);
IPAddress subnet(255, 255, 255, 0);
*/
bool restart = false;
#include <WiFi.h>
#include <WiFiClient.h>
void wifiConnect(const char *ssid,const char *password,int lcdTimer){
  Serial.print("Connecting");

 // WiFi.config(local_IP, gateway, subnet);
//  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
   int t = 0;
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
   t ++;
    if(t >= 10){
    break;
    }
    delay(1000);
  }
     if(WiFi.status() == WL_CONNECTED){
      lcdTimer  = 0;
      Serial.println("Wifi connected");
      Serial.print("Wifi IP:");
      
      Serial.println(WiFi.localIP());
      Serial.print("Gateway IP: ");
Serial.println(WiFi.gatewayIP());
      Serial.print("Subnet Mask: ");
Serial.println(WiFi.subnetMask());
      
     }
  
}

//Wifi access point method.


//Method for scanning for Wifi
void wifiScanner(const char *ssid,const char *password,int lcdTimer){
  if (WiFi.status() != WL_CONNECTED){
  Serial.println("Scan for Wifi");
  int numSsid = WiFi.scanNetworks();
  
  if(numSsid != -1){
    for (int network = 0; network < numSsid; network++){
   
      if(WiFi.SSID(network) == ssid){
       wifiConnect(ssid,password,lcdTimer);
     
      }// if
    }//for
    
  }// if
  
}// if
}// method
