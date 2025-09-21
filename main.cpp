#include <LiquidCrystal.h>

// Initialize the LCD object
#include <Servo.h> // include servo library to use its related functions
#define Servo_PWM 6 // A descriptive name for D6 pin of Arduino to provide PWM signal
Servo MG995_Servo;  
const int led = 11; // Led positive terminal to the digital pin 9.              
const  int sensor = 5; // signal pin of sensor to digital pin 5.               
int state = HIGH;            
int val = 0;                
const float depth=(15.80)/100;
const int trigPin = 9;
const int echoPin = 10;

float duration, distance;
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5); // (RS, E, D4, D5, D6, D7)

void setup() {
  // Initialize the LCD with 16 columns and 2 rows
   pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
    pinMode(led, OUTPUT); // Led is determined as an output here.    
  pinMode(sensor, INPUT); // PIR motion sensor is determined is an input here.  
  
  Serial.begin(9600);
  lcd.begin(16, 2);  
   MG995_Servo.attach(Servo_PWM);  
    
}

void loop() {
  
 
digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  //Serial.print("Distance: ");
  //Serial.println(distance);

  lcd.setCursor(0, 0);//(col, row)
  //lcd.print(distance);
  lcd.print((distance/depth));
  lcd.print(" % EMPTY");
  lcd.setCursor(0, 1);//(col, row)
  lcd.print("SMART DUSTBIN");  
  delay(500);



 val = digitalRead(sensor);   
  if  (val == HIGH) {           
    digitalWrite(led, HIGH);   
    delay(500);  // Delay of led is 500             
    
    if (state == LOW) {
      Serial.println("  Motion detected "); 
      MG995_Servo.write(180);
      
      state = HIGH;       
    }
  } 
  else {
      digitalWrite(led, LOW);
      delay(500);             
      
      if  (state == HIGH){
        delay(2000);
        Serial.println("The action/ motion has stopped");
         MG995_Servo.write(90);
         
        state = LOW;       
    }
  }


}
