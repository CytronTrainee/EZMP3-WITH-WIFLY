#include <CytronEZMP3.h>
#include <CytronWiFiShield.h>
#include <CytronWiFiServer.h>
#include <SoftwareSerial.h>
#define WiFi wifi

ESP8266Server server(80);

const char ssid[] = "CytronESPShield";      
const char pass[] = "12345678";  
int keyIndex = 0;                 

CytronEZMP3 mp3;

void setup () {
  Serial.begin(9600);
  Serial.begin(115200);     
  pinMode(13, OUTPUT);      
 
  if(!mp3.begin(Serial2))
  {
    Serial.println("Init failed");
    while(1);
  }
  if (!WiFi.begin(2, 3)) {
    Serial.println("WiFi shield not present");
    while (true);      
    }

  String fv = WiFi.firmwareVersion();
  Serial.println(fv);

  WiFi.setMode(WIFI_AP);
  if(!WiFi.softAP(ssid, pass))
 
  Serial.println("Setting softAP failed");
  Serial.println(WiFi.softAPIP());
  server.begin();       
  mp3.setVolume(22);
  Serial.print("Device: ");
  Serial.println(mp3.getCurrentDevice()==1?"U-Disk":"microSD");

  Serial.print("Total files: ");
  Serial.println(mp3.getTotalFiles());
  
}

void loop () {   
  ESP8266Client client = server.available();  

   if(!client) return;
  
  if (client.connected()) 
  {           
  char c = client.read();
  {
  if(c=='R')
  {
    c==8;
    c==0;
  mp3.next();
  Serial.println("next");
  Serial.println("Now playing track " + (String)mp3.getTrackNo());
  delay (1000);
  }
  else if(c=='L')
  {
    c==8;
    c==0;
    mp3.prev();
    Serial.println("previous");
    Serial.println("Now playing track " + (String)mp3.getTrackNo());
    delay (1000);
  }
   else if(c=='B')
  {
    c==8;
    c==0;
    
    mp3.stop();
    Serial.println("stop");
  }
  
  Serial.write(client.read()); 
  client.println();
  }
}
}
