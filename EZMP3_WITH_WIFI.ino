#include <CytronEZMP3.h>
#include <CytronWiFiShield.h>
#include <CytronWiFiServer.h>
#include <SoftwareSerial.h>
#define WiFi wifi

ESP8266Server server(80); //Port Number in Wifly Apps

const char ssid[] = "CytronESPShield";     //  your network SSID (name)
const char pass[] = "12345678";           //Password
int keyIndex = 0;                 

CytronEZMP3 mp3;

void setup () {
  Serial.begin(9600);    
  Serial.begin(115200);     
  pinMode(13, OUTPUT);      
 
  if(!mp3.begin(Serial2)) //I was using port 8 and 9 in EZMP3 Shield
  {                       //If you are using port 10 and 11, write "Serial5"
                          //This is because I was using CT ARM instead of arduino.
    Serial.println("Init failed");
    while(1);
  }                                             //// check for the presence of the shield:
  if (!WiFi.begin(2, 3)) {                      //ports for ESP8266 Wifi Shield.
    Serial.println("WiFi shield not present");
    while (true);                                // don't continue
    }

  String fv = WiFi.firmwareVersion();
  Serial.println(fv);
                                                // attempt to connect to Wifi network:
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
  ESP8266Client client = server.available();   // listen for incoming clients

   if(!client) return;
  
  if (client.connected())                     //if client is present and connected
  {           
  char c = client.read();
  {
  if(c=='R')                                 //press right button on Wifly remote to start/skip o next song.
  {
    c==8;
    c==0;
  mp3.next();
  Serial.println("next");
  Serial.println("Now playing track " + (String)mp3.getTrackNo());
  delay (1000);
  }
  else if(c=='L')                           //press left button on Wifly remote to go back to the previous song
  {
    c==8;
    c==0;
    mp3.prev();
    Serial.println("previous");
    Serial.println("Now playing track " + (String)mp3.getTrackNo());
    delay (1000);
  }
   else if(c=='B')                          //press bottom button on wifly remote to stop the song.
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
