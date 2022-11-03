#include <BearSSLHelpers.h>
#include <CertStoreBearSSL.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiGratuitous.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiClientSecureAxTLS.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiServer.h>
#include <WiFiServerSecure.h>
#include <WiFiServerSecureAxTLS.h>
#include <WiFiServerSecureBearSSL.h>
#include <WiFiUdp.h>
#include <Blynk.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define LED_PIN    D6
#define LED_COUNT 150
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);




char auth[] = "AUTH";
char ssid[] = "WIFI";
char pass[] = "WIFI-Password";
int i = 3;
int f = 255;//saturation
int d = 255;//brightness
long h = 0L;




BlynkTimer timer;
int StartDoTimer;
long l = 0L;
int RandTimer;
int g = 0;
int Delltimer;
int wait = 20;
int m = 0;
int Fuellen2timer;
int Dell2timer;
int Explosionstimer;
int RandTimer2;
/**
  Timerversuch Errorbutton
  BlynkTimer timer;
  #define VPIN_BUTTON_7 V7
  int relay7State = LOW;

  in setup():timer.setInterval(500L, state);
  void state() {
  if(relay7State = HIGH){
  //relay7State = !relay7State;
  //Blynk.virtualWrite(VPIN_BUTTON_7,relay7State);
  Serial.print(relay7State);
  exit(0);
  }

  //exitbutton
  BLYNK_WRITE(VPIN_BUTTON_7) {
  relay7State = param.asInt();
  //digitalWrite(RELAY_PIN_7,relay7State);
  }

  }

  in loop():timer.run();
**/








void setup() {
  strip.begin();
  strip.show();
  strip.setBrightness(125);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  StartDoTimer = timer.setInterval(1L, StartDo);
  timer.disable(StartDoTimer);
  RandTimer = timer.setInterval(1L, randomziehen );
  timer.disable(RandTimer);
  Delltimer = timer.setInterval(1L, waves);
  timer.disable(Delltimer);
  Fuellen2timer = timer.setInterval(1L, fuellen2);
  timer.disable(Fuellen2timer);
  Dell2timer = timer.setInterval(1L, waves2);
  timer.disable(Dell2timer);
  Explosionstimer = timer.setInterval(1L, explosion);
  timer.disable(Explosionstimer);
  RandTimer2 = timer.setInterval(1L, randomziehen2 );
  timer.disable(RandTimer2);
 
}

void loop()
{
  Blynk.run();
  timer.run();
}

void farbe(uint32_t v) {
  for (int j = 0; j < strip.numPixels(); j++) {
    strip.setPixelColor(i, v);
    strip.show();
    delay(wait);
  }
}

//buttons zum füllen
BLYNK_WRITE(1) {
  int p = param.asInt();
  h = long((p * 65.536));
  fuellen(strip.gamma32(strip.ColorHSV((p * 65.536),   f,   d)));
}
BLYNK_WRITE(4) {
  f = param.asInt();
}
BLYNK_WRITE(5) {
  d = param.asInt();
}
void fuellen(uint32_t v) {
  strip.fill(v);
  strip.show();
}

//explosionsbutton und funktion
BLYNK_WRITE(3) {
  int pinValue = param.asInt();
  if (param.asInt() == 1) {
    explosion();
    Blynk.virtualWrite(V3, LOW);
  } else {

  }
}
void explosion() {
  for (int j = 0; j <= (strip.numPixels()) / 2; j++) {
    strip.setPixelColor(j, strip.gamma32(strip.ColorHSV(873 * j, f, d)));
    strip.setPixelColor((strip.numPixels() - j), strip.gamma32(strip.ColorHSV(873 * j, f, d)));
    strip.show();
    delay(50);
  }
  for (int j = 0; j <= (strip.numPixels()) / 2; j++) {
    strip.setPixelColor((strip.numPixels()) / 2 + j, strip.ColorHSV(0, 0, d));
    strip.setPixelColor(((strip.numPixels() / 2) - j), strip.ColorHSV(0, 0, d));
    strip.show();
    delay(5);
  }

}
//wait variable
BLYNK_WRITE(6) {
  wait = param.asInt();

}
//fuellen2
void fuellen2() {
  uint32_t v = strip.gamma32(strip.ColorHSV((65.536),   f,   d));


  if ( m < 65536) {
    v = strip.gamma32(strip.ColorHSV(m,   f,   d));
    strip.fill(v);
    strip.show();
    delay(2);
    m = m + wait;
  } else {
    m = 0;
  }
}

//rainbow
void StartDo() {
  if (l < 5 * 65536) {
    for (int g = 0; g < strip.numPixels(); g++) {

      int pixelHue = l + (g * 65536L / strip.numPixels());
      strip.setPixelColor(g, strip.gamma32(strip.ColorHSV(pixelHue, f, d)));
    }
    strip.show();
    delay(wait);
    l = long(l + 256);
  } else {
    l = 0L;
  }
}

//randomziehen
void randomziehen() {
  int an[150];
  if (h >= (65536) / 2) {
    h = h - ((65536) / 2);
  } else {
    h = h + ((65536) / 2);
  }
  if (g < strip.numPixels()) {
    int w = random(0, 150);
    an[w] = an[w] + w;
    strip.setPixelColor(w, strip.gamma32(strip.ColorHSV(h, f, d)));
    /**if(an[w]==w & w!=0){
      strip.setPixelColor(w, strip.gamma32(strip.ColorHSV(h,f,d)));
      g=g+1;
      strip.show();
      }if(an[0]==w){
      an[0]=an[0]-1;
      strip.setPixelColor(w, strip.gamma32(strip.ColorHSV(h,f,d)));
      g=g+1;
      strip.show();
      }
      else{
      }**/
    strip.show();
    g = g + 1;
  } else {
    g = 0;
  }
}



//randomziehen soll randombeleuchten mit festgegebener farbe
void randomziehen2() {
  uint32_t white = strip.Color(0, 0, 0, 255);
  strip.fill(white);
  strip.show();

  int an [strip.numPixels()];
  for (int lik=0;lik<strip.numPixels();lik=lik+1){
    an[lik]=lik;
  }
  
  int ban [strip.numPixels()];
  for (int lik=0;lik<strip.numPixels();lik=lik+1){
    ban[lik]=lik;
  }
  for (int er=0;er < strip.numPixels();) {
    int w = random(0, strip.numPixels());
    int u =0;
    if(h<50000 & h>15536){//65536
    u = random(h-15536,h+15536);
    }
    if(h <= 6536 ){
      u = random(h,h+15536);
    }
    else{
      u = random(h-15536,h);
    }
    
    if(an[w]==w){
      an[w]=an[w]-1;
      strip.setPixelColor(w, strip.gamma32(strip.ColorHSV(u, f, d))); 
      strip.show();
      delay(wait);
      er=er+1;    
      if(er==strip.numPixels()){
        delay(wait+80*wait);
         for (int ber=0;ber < strip.numPixels();) {
    int w2 = random(0, strip.numPixels());
    
    if(ban[w2]==w2){
      ban[w2]=ban[w2]-1;
      strip.setPixelColor(w2, white); 
      strip.show();
      delay(wait);
      ber=ber+1;    
      if(ber==strip.numPixels()){
        delay(wait);
      }
    }
  } 
      }
    }
  } 
  
}


int q = 0;
//waves
void waves() {

  if (q < strip.numPixels()) {
    for (int n = 0; n <= 100; n = n + 50) {
      strip.setPixelColor(q + (n - 1), strip.gamma32(strip.ColorHSV(((q * 65536) / strip.numPixels()) - 65536 / 2, f, d)));
      strip.setPixelColor(q + n, strip.gamma32(strip.ColorHSV((q * 65536) / strip.numPixels(), f, d)));
      strip.setPixelColor(q + (n + 1), strip.gamma32(strip.ColorHSV((q * 65536) / strip.numPixels(), f, d)));
      strip.setPixelColor(q + (2 + n), strip.gamma32(strip.ColorHSV((q * 65536) / strip.numPixels(), f, d)));
      strip.setPixelColor(q + (3 + n), strip.gamma32(strip.ColorHSV((q * 65536) / strip.numPixels(), f, d)));
    }
    for (int n = 50; n <= 150; n = n + 50) {
      strip.setPixelColor(q + (-n - 1), strip.gamma32(strip.ColorHSV(((q * 65536) / strip.numPixels()) - 65536 / 2, f, d)));
      strip.setPixelColor(q - n, strip.gamma32(strip.ColorHSV((q * 65536) / strip.numPixels(), f, d)));
      strip.setPixelColor(q + (-n + 1), strip.gamma32(strip.ColorHSV((q * 65536) / strip.numPixels(), f, d)));
      strip.setPixelColor(q + (2 - n), strip.gamma32(strip.ColorHSV((q * 65536) / strip.numPixels(), f, d)));
      strip.setPixelColor(q + (3 - n), strip.gamma32(strip.ColorHSV((q * 65536) / strip.numPixels(), f, d)));
    }
    strip.show();
    delay(wait);
    q = q + 1;

  } else {
    q = 0;
  }
}


//waves2
int z = 0;

void waves2() {

  if (z < strip.numPixels()) {
    for (int n = 0; n <= 100; n = n + 25) {
      strip.setPixelColor(z + (n - 1), strip.gamma32(strip.ColorHSV(((z * 65536) / strip.numPixels()) - 65536 / 2, f, 0)));
      strip.setPixelColor(z + n, strip.gamma32(strip.ColorHSV((z * 65536) / strip.numPixels(), f, d)));
      strip.setPixelColor(z + (n + 1), strip.gamma32(strip.ColorHSV((z * 65536) / strip.numPixels()- 65536 / 2, f, d)));
      strip.setPixelColor(z + (2 + n), strip.gamma32(strip.ColorHSV((z * 65536) / strip.numPixels(), f, d)));
      strip.setPixelColor(z + (3 + n), strip.gamma32(strip.ColorHSV((z * 65536) / strip.numPixels()- 65536 / 2, f, d)));
    }
    for (int n = 25; n <= 150; n = n + 25) {
      strip.setPixelColor(z + (-n - 1), strip.gamma32(strip.ColorHSV(((z * 65536) / strip.numPixels()) - 65536 / 2, f, 0)));
      strip.setPixelColor(z - n, strip.gamma32(strip.ColorHSV((z * 65536) / strip.numPixels(), f, d)));
      strip.setPixelColor(z + (-n + 1), strip.gamma32(strip.ColorHSV((z * 65536) / strip.numPixels()- 65536 / 2, f, d)));
      strip.setPixelColor(z + (2 - n), strip.gamma32(strip.ColorHSV((z * 65536) / strip.numPixels(), f, d)));
      strip.setPixelColor(z + (3 - n), strip.gamma32(strip.ColorHSV((z * 65536) / strip.numPixels()- 65536 / 2, f, d)));
    }

    strip.show();
    delay(wait);
    z = z + 1;

  } else {
    z = 0;
  }
}





//Auswahlleiste mit mehreren Funktionen

BLYNK_WRITE(V11) {
  int pinValue = param.asInt();
    //clear
    if(pinValue ==0){
      timer.disable(RandTimer2);
      timer.disable(RandTimer);
      timer.disable(Fuellen2timer);
      timer.disable(Dell2timer);
      timer.disable(Delltimer);
      timer.disable(Explosionstimer);
      timer.disable(StartDoTimer);
      strip.fill();
      strip.show();
    }
    //explosion
    if (pinValue ==1){
      timer.disable(RandTimer2);
      timer.disable(RandTimer);
      timer.disable(StartDoTimer);
      timer.disable(Fuellen2timer);
      timer.disable(Dell2timer);
      timer.disable(Delltimer);
     timer.enable(Explosionstimer);
    }
     //waves 1
     if(pinValue==2){
      timer.disable(RandTimer2);
      timer.disable(StartDoTimer);
      timer.disable(Explosionstimer);
      timer.disable(RandTimer);
      timer.disable(Fuellen2timer);
      timer.disable(Delltimer);
      timer.enable(Dell2timer);
     }
     //waves 2
     if(pinValue==3){
      timer.disable(RandTimer2);
      timer.disable(StartDoTimer);
      timer.disable(RandTimer);
      timer.disable(Fuellen2timer);
      timer.disable(Dell2timer);
      timer.disable(Explosionstimer);
      timer.enable(Delltimer);
     }
     
     //random
     if(pinValue==4){
      timer.disable(RandTimer2);
      timer.disable(StartDoTimer);
      timer.disable(Fuellen2timer);
      timer.disable(Dell2timer);
      timer.disable(Delltimer);
    timer.disable(Explosionstimer);
      timer.enable(RandTimer);
     }
     //randomziehen2
     if(pinValue==5){
            timer.disable(Dell2timer);
      timer.disable(StartDoTimer);
      timer.disable(Delltimer);
     timer.disable(Explosionstimer);
      timer.disable(Fuellen2timer);
      timer.enable(RandTimer2);

     }
     //farbenwechsel
     if(pinValue==6){
      timer.disable(RandTimer2);
      timer.disable(RandTimer);
      timer.disable(Dell2timer);
      timer.disable(StartDoTimer);
      timer.disable(Delltimer);
     timer.disable(Explosionstimer);
      timer.enable(Fuellen2timer);
     }
        //rainbow
     if(pinValue==7){
      timer.disable(RandTimer2);
      timer.disable(RandTimer);
      timer.disable(Dell2timer);
      timer.disable(Explosionstimer);
      timer.disable(Delltimer);
     timer.disable(Fuellen2timer);
     timer.enable(StartDoTimer);
     }
  }
