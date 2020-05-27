#include <ESP8266WiFi.h>
#include <Servo.h>

const char *ssid =  "unsafe";           // Enter your WiFi Name
const char *pass =  "Lem@nn91";        // Enter your WiFi Password

Servo myservoEntry;                   //servo as gate
Servo myservoExit;                   //servo as gate

int carEnter = D0;                    // entry sensor 
int carExited = D2;                  //exi sensor
int slot4 = D8;                 
int slot3 = D7;                 
int slot2 = D6;
int slot1  = D5;
 
const int CLOSE_ANGLE = 90;              // The closing angle of the servo motor arm
const int OPEN_ANGLE = 0;               // The opening angle of the servo motor arm    
          
int  hh, mm, ss;
int count = 0;
int pos;
int posTwo;
int total = 2;
int space;

//for synchronized control with the front
int flag1 = 0;
int flag2 = 0;
int special_slot = 1;

//String h, m,EntryTimeSlot1,ExitTimeSlot1, EntryTimeSlot2,ExitTimeSlot2, EntryTimeSlot3,ExitTimeSlot3, EntryTimeSlot4,ExitTimeSlot4;
boolean entrysensor, exitsensor;
boolean s1,s2,s3,s4,s5,s6;

boolean s1_occupied = false;
boolean s2_occupied = false;
boolean s3_occupied = false;
boolean s4_occupied = false;
boolean s5_occupied = true;
boolean s6_occupied = true;




//void slotOne();
//void slotTwo();
//void slotThree();
//void entryGate():
//void exitGate();
//void getRequest();
//void sendDatas();

void setup() {
  delay(1000);
  Serial.begin (9600); 

  myservoEntry.attach(D3);             // servo pin to D3
  myservoExit.attach(D4);            // servo pin to D5
  pinMode(carExited, INPUT);        // ir as input
  pinMode(carEnter, INPUT);         // ir as input
  pinMode(slot1, INPUT);
  pinMode(slot2, INPUT);
  pinMode(slot3, INPUT);
  wifiConnection();
  
}

void loop() {
  entryGate();
  exitGate();
  slotOne();
  slotTwo();
  slotThree();
  Serial.print("total de vagas disponives: ");
  Serial.println(space);
  delay(3000);
  space = total;

}

void wifiConnection(){
    WiFi.begin(ssid, pass);                                     //try to connect with wifi
    Serial.print("Connecting to ");
    Serial.print(ssid);                                         // display ssid
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");                                      // if not connected print this
      delay(500);
    }
    Serial.println();
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP Address is : ");
    Serial.println(WiFi.localIP());                        //print local IP address
 }
void entryGate(){

   entrysensor= !digitalRead(carEnter);
    if (entrysensor == 1) {                             // if high then count and send data
      if(space > 0 ){
         count=  count+1;                             //increment count
         myservoEntry.write(OPEN_ANGLE);
         delay(3000);
         myservoEntry.write(CLOSE_ANGLE);
         space = space -1;
      }
      else{
        Serial.println("Desculpe, nenuhuma vaga disponível");
        delay(1000);
      } 
    }
}

void exitGate(){
   exitsensor = !digitalRead(carExited);
   if (exitsensor == 1) {                                 //if high then count and send
     count= count-1;                                    //decrement count
     myservoExit.write(OPEN_ANGLE);
     delay(3000);
     myservoExit.write(CLOSE_ANGLE);
     space = space +1;
  }
 }
 
void slotOne(){
  s1 = digitalRead(slot1);
  if (s1 == 1 && s1_occupied == false) {                     
        Serial.println("vaga 1 está disponivel ");
        s1_occupied = true;
   }
  if(s1 == 0 && s1_occupied == true) {
       Serial.println("Vaga 1 está ocupada ");
       s1_occupied = false;
  }
  
}

void slotTwo(){
  s2 = digitalRead(slot2);
  if (s2 == 1&& s2_occupied == false) {                     
      Serial.println("Vaga 2 está disponivel "); 
      s2_occupied = true;
    }
 if (s2 == 0 && s2_occupied == true) {
     Serial.println(" Vaga 2 está ocupada ");

     s2_occupied = false;
  }
  
}

//special slot
void slotThree(){
  s3 = digitalRead(slot3);
  if (s3 == 1&& s3_occupied == false) {                     
     Serial.println("Vaga 3 está disponivel ");
     s3_occupied = true;
     
  }
 if(s3 == 0 && s3_occupied == true) {
     Serial.println("Vaga 3 ocupada ");
     s3_occupied = false;
     special_slot--;
 } 
}

void slotFower(){
  s4 = digitalRead(slot4);
  if (s4 == 1&& s4_occupied == false) {                     
     Serial.println("Vaga 4 está disponivel ");
     s4_occupied = true;
  }
 if(s4 == 0 && s4_occupied == true) {
     Serial.println("Vaga 4 ocupada ");
     s4_occupied = false;
 } 
}

void slotFive(){
  s5 = 0;
  if (s3 == 1&& s3_occupied == false) {                     
     Serial.println("Vaga 5 está disponivel ");
     s3_occupied = true;
  }
 if(s3 == 0 && s3_occupied == true) {
     Serial.println("Vaga 5 ocupada ");
     s3_occupied = false;
 } 
}

void slotSix(){
  s6 = 0;
  if (s3 == 1&& s3_occupied == false) {                     
     Serial.println("Vaga 6 está disponivel ");
     s3_occupied = true;
  }
 if(s3 == 0 && s3_occupied == true) {
     Serial.println("Vaga 6 ocupada ");
     s3_occupied = false;
 } 
}
 
