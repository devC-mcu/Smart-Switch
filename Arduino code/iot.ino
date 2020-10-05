#include <EEPROM.h>

#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "plug-4ce8c.firebaseio.com"
#define FIREBASE_AUTH "3K0nyo5c3xxrGN9FiRC2E58OyPjYsg5jTSBoVThc"

String data, wifi, pass, fire, fireset, test, test1, test2,test3,test4,
test5,test6,test7,test8, saved;

  uint addr = 0;

  // fake data


void setup() {

  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  
  Serial.begin(9600); 
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);


  EEPROM.begin(4096);

  
  struct { 
    uint val = 0;
    char str[30] = "";
  } data;
      
    

  EEPROM.get(addr,data);
  Serial.println("New values are: "+String(data.val)+","+String(data.str));
  fireset = String(data.str);
  initialize();
}



void loop() {
  
  if(Serial.available()){
    char q = Serial.read();
    Serial.println(q);
        switch(q){
          case 'a': 
            digitalWrite(D0, HIGH);
            break;
          case 'A':  
            digitalWrite(D0, LOW);
            break;
          case 'b':  
            digitalWrite(D1, HIGH);
            break;
          case 'B':
            digitalWrite(D1, LOW);
            break;
          case 'c':
            digitalWrite(D2, HIGH);
            break;
          case 'C':
            digitalWrite(D2, LOW);
            break;
          case 'd':
            digitalWrite(D3, HIGH);
            break; 
          case 'D':
            digitalWrite(D3, LOW);;
            break; 
          case 'e': 
            digitalWrite(D4, HIGH);
            break;
          case 'E':  
            digitalWrite(D4, LOW);
            break;
          case 'f':  
            digitalWrite(D5, HIGH);
            break;
          case 'F':
            digitalWrite(D5, LOW);;
            break;
          case 'g':
            digitalWrite(D6, HIGH);
            break;
          case 'G':
            digitalWrite(D6, LOW);
            break;
          case 'h':
            digitalWrite(D7, HIGH);
            break; 
          case 'H':
            digitalWrite(D7, LOW);
            break; 
          case '1' :
            wifiSetup();
             break;
          case 's':
            fire="";
            fireset="";
            test="";
            test1="";
            test2="";
            test3="";
            test4="";
            test5="";
            test6="";
            test7="";
            test8="";
            firebaseSetup();
            break;
        }
  }
  if(WiFi.status() == WL_CONNECTED){
    Firebase.setInt(fire+"/wifi", 1);
    Serial.println(fireset);
    int internet = Firebase.getInt(test);
    Serial.println("yes");
    if(internet == 1){
      firebase();
    }
  }  
}

void firebaseSetup(){
  EEPROM.write(0, '8');
  while(!Serial.available()){
          Serial.print(".");
          delay(500);
        }
       
       while(Serial.available()){
          char c = Serial.read();
          if(c == ','){
            break;
          }
          fireset+=c;
        }

 char Cfire[30];
 fireset.toCharArray(Cfire, 30);
 Serial.print("Cfire value ");
 Serial.println(Cfire);

  struct { 
    uint val = 0;
    char str[30] = "";
  } data;
      
  strncpy(data.str, Cfire,30);
  EEPROM.put(addr,data);
  EEPROM.commit(); 
  Serial.println(fireset);
  initialize();
  
}



void initialize(){
  fire = "users/"+fireset;
  test = fire+"/internet";
  test1 = fire+"/My Room/light1";
  test2 = fire+"/My Room/light2";
  test3 = fire+"/My Room/light3";
  test4 = fire+"/My Room/light4";
  test5 = fire+"/My Room/light5";
  test6 = fire+"/My Room/light6";
  test7 = fire+"/My Room/light7";
  test8 = fire+"/My Room/light8";
}

void wifiSetup(){
  Serial.print("1");
      for(int i = 0; i < 2 ; i++){
        while(!Serial.available()){
          Serial.print(".");
          delay(500);
        }
        while(Serial.available()){
          char c = Serial.read();
          if(c == ','){
            break;
          }
          data+=c;
        }
        if(wifi.length()>0){
          pass = data;
        }else {
          wifi = data;
        }
        if(wifi.length()>0 && pass.length()>0){
          Serial.print("wifi = " +wifi + "\n");
          Serial.print("pass = " +pass + "\n");
          WiFi.begin(wifi, pass);
          Serial.print("connecting");
          delay(5000);
          if(WiFi.status() == WL_CONNECTED) {
            Firebase.setInt(fire+"/wifi", 1);
          }else{
            Firebase.setInt(fire+"/wifi", 0);
          }
          Serial.println();
          Serial.print("connected: ");
          Serial.println(WiFi.localIP());
        }data="";
      }pass="";
       wifi="";
}

void firebase(){
    digitalWrite(D0, Firebase.getInt(test1));
    Serial.println("light1");
    digitalWrite(D1, Firebase.getInt(test2));
    digitalWrite(D2, Firebase.getInt(test3));
    digitalWrite(D3, Firebase.getInt(test4));
    digitalWrite(D4, Firebase.getInt(test5));
    digitalWrite(D5, Firebase.getInt(test6));
    digitalWrite(D6, Firebase.getInt(test7));
    digitalWrite(D7, Firebase.getInt(test8));
}
