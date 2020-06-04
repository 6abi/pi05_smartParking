
#include <FirebaseESP8266.h>
#include <FirebaseESP8266HTTPClient.h>
#include <FirebaseJson.h>

#include <ESP8266WiFi.h>
#include <Servo.h>


const char *ssid =  "unsafe";                        // Enter your WiFi Name
const char *pass =  "Lem@nn91";                     // Enter your WiFi Password

Servo myservoEntry;                               //servo as gate
Servo myservoExit;                               //servo as gate

int carEnter = D0;                              // entry sensor 
int carExited = A0;                           //exi sensor - LDR analogRead
int led = D6;                                //LED exit gate



const int CLOSE_ANGLE = 90;                 // The closing angle of the servo motor arm
const int OPEN_ANGLE = 0;                  // The opening angle of the servo motor arm    


//slots sensors - IR
int slot6 = D8;                            //special slot                
int slot4 = D1;                 
int slot2 = D5;
int slot1  = D7;

//time of use for calculate the value to pay
int  hh, mm, ss;                         //Set the time of use
int pos;
int posTwo;
int total = 6;


int slotAvailable = 0;

//for synchronized control with the front
int flag1 = 0;
int flag2 = 0;
int specialSlot = 1;
int slotToGo;

//String h, m,EntryTimeSlot1,ExitTimeSlot1, EntryTimeSlot2,ExitTimeSlot2, EntryTimeSlot3,ExitTimeSlot3, EntryTimeSlot4,ExitTimeSlot4;
boolean entrysensor;
int exitsensor = 0;       //LDR's value reed
boolean s1,s2,s3,s4,s5,s6;

int s1_occupied = 1;
int s2_occupied = 1;
int s3_occupied = 1;
int s4_occupied = 1;
int s5_occupied = 1;
int s6_occupied = 1;

//void slotOne();
//void slotTwo();
//void slotThree();
//void entryGate():
//void exitGate();
//void getRequest();
//void sendDatas();

void setup() {
  delay(1000);
  Serial.begin (115200); 

  myservoEntry.attach(D3);             // servo pin to D3
  myservoExit.attach(D4);            // servo pin to D5
  pinMode(carExited, INPUT);        // ir as input
  pinMode(carEnter, INPUT);         // ir as input
  pinMode(led,OUTPUT);

  pinMode(slot1, INPUT);
  pinMode(slot2, INPUT);
  pinMode(slot4, INPUT);
  pinMode(slot6, INPUT);
  wifiConnection();
}

void loop() {
  entryGate();
  slotDirection();
  exitGate();
  slotOne();
  slotTwo();
  slotThree();
  slotFour();
  slotFive();
  slotSix();
  countSlots();


  Serial.print("total de vagas: ");
  Serial.println(total);
  Serial.print("total de vagas diponíveis: ");
  Serial.println(slotAvailable);
  delay(3000);
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
    Serial.print(" MAC Address is : ");
    Serial.println(WiFi.macAddress());
 }
void entryGate(){
   entrysensor= !digitalRead(carEnter);
    if (entrysensor == 1) {                             // if high then count and send data
      if(slotAvailable > 0){
        Serial.print("Dirija-se até a vaga número: ");
        Serial.println(slotToGo);
         myservoEntry.write(CLOSE_ANGLE);
         delay(3000);
         myservoEntry.write(OPEN_ANGLE);      }
      else{
        Serial.println("Desculpe, nenuhuma vaga disponível");
        delay(1000);
      } 
    }
}

void exitGate(){
   exitsensor = analogRead(carExited);
   digitalWrite(led, LOW);
   if (exitsensor < 1020) {                                 //if high then count and send
     digitalWrite(led, HIGH);
     myservoExit.write(OPEN_ANGLE);
     Serial.println("Cancela Aberta");
     delay(3000);
     myservoExit.write(CLOSE_ANGLE);
  }
  else{
    digitalWrite(led, LOW);
    Serial.println("Cancela Fechada");
  }
  delay(10);
 }

 void slotOne(){
  s1 = !digitalRead(slot1);
  if (s1 == 1 && s1_occupied == 1) {                     
        Serial.println("vaga 1 está disponivel ");
        s1_occupied = 0;
        
  }
 if (s1 == 1 && s1_occupied == 0) {
     Serial.println(" Vaga 1 está ocupada ");
     s1_occupied = 0;
  }
  if(s1 == 0 && (s1_occupied == 1 || s1_occupied == 0 )){
      Serial.println("Vaga 1 está disponivel "); 
      s1_occupied = 1;
  }
}

void slotTwo(){
  s2 = !digitalRead(slot2);
  if (s2 == 1&& s2_occupied == 1) {                     
      Serial.println("Vaga 2 está disponivel "); 
      s2_occupied = 0;
  }
 if (s2 == 1 && s2_occupied == 0) {
     Serial.println(" Vaga 2 está ocupada ");
     s2_occupied = 0;
  }
  if(s2 == 0 && (s2_occupied == 1 ||s2_occupied == 0 )){
      Serial.println("Vaga 2 está disponivel "); 
      s2_occupied = 1;
  }
}

void slotThree(){
  s3 = 1;
  if (s3 == 1 && s3_occupied == 1) {                     
        Serial.println("vaga 3 está disponivel ");
        s3_occupied = 0;
        
  }
 if (s3 == 1 && s3_occupied == 0) {
     Serial.println(" Vaga 3 está ocupada ");
     s3_occupied = 0;
  }
  if(s3 == 0 && (s3_occupied == 1 || s3_occupied == 0 )){
      Serial.println("Vaga 3 está disponivel "); 
      s3_occupied = 1;
  }
}

 void slotFour(){
  s4 = !digitalRead(slot4);
  if (s4 == 1 && s4_occupied == 1) {                     
        Serial.println("vaga 4 está disponivel ");
        s4_occupied = 0;
        
  }
 if (s4 == 1 && s4_occupied == 0) {
     Serial.println(" Vaga 4 está ocupada ");
     s4_occupied = 0;
  }
  if(s4 == 0 && (s4_occupied == 1 || s4_occupied == 0 )){
      Serial.println("Vaga 4 está disponivel "); 
      s4_occupied = 1;
  }
}

//vague ghost only for demonstration
void slotFive(){
  s5 = 1;
  if (s5 == 1 && s5_occupied == 1) {                     
        Serial.println("vaga 5 está disponivel ");
        s5_occupied = 0;
        
  }
 if (s5 == 1 && s5_occupied == 0) {
     Serial.println(" Vaga 5 está ocupada ");
     s5_occupied = 0;
  }
  if(s5 == 0 && (s5_occupied == 1 || s5_occupied == 0 )){
      Serial.println("Vaga 5 está disponivel "); 
      s5_occupied = 1;
  }
}

void slotSix(){
  s6 = !digitalRead(slot6);
  if (s6 == 1&& s6_occupied == 1) {                     
      Serial.println("Vaga 6 está disponivel "); 
      s6_occupied = 0;
  }
 if (s6 == 1 && s6_occupied == 0) {
     Serial.println(" Vaga 6 está ocupada ");
     s6_occupied = 0;
  }
  if(s6 == 0 && (s6_occupied == 1 ||s6_occupied == 0 )){
      Serial.println("Vaga 6 está disponivel "); 
      s6_occupied = 1;
  }
}

void countSlots(){
  int count = 0;
  for ( int i = 0; i < 2; i++){
    count = (s1_occupied + s2_occupied + s3_occupied + s4_occupied + s5_occupied + s6_occupied);
  }
  slotAvailable = count;
}

void slotDirection(){
  int slotDirection;
  for (int i = 0; i < 2; i++){
      slotDirection = 0;
      if (s1_occupied == 1){
      slotDirection = 1;
      }
      else if (s2_occupied == 1 && s1_occupied == 0){
          slotDirection = 2;
      }
      else if (s3_occupied == 1 && s2_occupied == 0 && s1_occupied == 0){
          slotDirection =3;
      }
      else if (s4_occupied == 1 && s3_occupied == 0 && s2_occupied == 0 && s1_occupied == 0){
          slotDirection =4;
      }
      else if (s5_occupied == 1 && s4_occupied == 0 && s3_occupied == 0 && s2_occupied == 0 && s1_occupied == 0){
          slotDirection =5;
      }
      else if (s6_occupied == 1 && s5_occupied == 0 && s4_occupied == 0 && s3_occupied == 0 && s2_occupied == 0 && s1_occupied == 0){
          slotDirection =6;
      }
  }
  slotToGo = slotDirection;
}

 

 
