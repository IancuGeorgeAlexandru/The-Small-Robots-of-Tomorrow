
#include <LiquidCrystal_I2C.h> // display 
#include <dht.h>
LiquidCrystal_I2C lcd(0x3F , 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 


dht DHT;

#define DHT11_PIN A0

int a=0;

const int pwmA = 3 ;  //initializing pin 3 as pwm
const int in_2 = 2 ;
const int in_1 = 4 ;
const int pwmB = 9 ;
const int in_3 = 12 ;
const int in_4 =  8; 
int state = 0 ;

int trigPin = 11;
int echoPin = 13;
long duration;
int distance;
//For providing logic to L298 IC to choose the direction of the DC motor 

void setup()
{ pinMode(trigPin , OUTPUT);
  pinMode(echoPin , INPUT);
  lcd.begin(20, 4);
  Serial.begin(9600);
pinMode(pwmA,OUTPUT) ;   //we have to set PWM pin as output
pinMode(in_1,OUTPUT) ;  //Logic pins are also set as output
pinMode(in_2,OUTPUT) ;
pinMode(pwmB,OUTPUT) ;   //we have to set PWM pin as output
pinMode(in_3,OUTPUT) ;  //Logic pins are also set as output
pinMode(in_4,OUTPUT) ;

}

void loop()
 {
    if(Serial.available() > 0){
    state = Serial.read();
 }
 
 
  if( a== 0)
        {
       lcd.setCursor(2,0);
        lcd.print("Salut, sunt Alex");
        lcd.setCursor(0,1);
        lcd.print("Unde vrei sa mergem?");
        }

  if(state == 54) //SENZOR DE PROXIMITATE
      { 
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        duration=pulseIn(echoPin , HIGH);
        distance= duration*0.034/2;
        lcd.clear();
        lcd.setCursor(3,0);
        lcd.print("Distance: ");
        lcd.print(distance);
        lcd.print("cm");
        delay(800);
        a=1;
    }

    if(state == 55)         //SENZOR DE TEMP(C)+UMIDITATEA(%) 
       {
        lcd.clear();
          int chk = DHT.read11(DHT11_PIN);
          lcd.setCursor(3,0);
          lcd.print("Temp = ");
          lcd.print(DHT.temperature);
          lcd.print((char)223);
          lcd.print("C");
          lcd.setCursor(0,1);
          lcd.print("Humidity = ");
          lcd.print(DHT.humidity);
          lcd.print("%");
          delay(2000); 
            a=2; 
      }

    if(state == 53&& a==0)          //DEPLASARE IN SPATE
      {
        digitalWrite(in_1,HIGH) ;
       digitalWrite(in_2,LOW) ;
       analogWrite(pwmA,150) ;
       digitalWrite(in_3,LOW) ;
       digitalWrite(in_4,HIGH) ;
        analogWrite(pwmB,150) ;
      }

    if(state == 50 && a==0)         //DEPLASARE IN STANGA
      {
      digitalWrite(in_1,LOW) ;
      digitalWrite(in_2,HIGH) ;
      analogWrite(pwmA,250) ;
      digitalWrite(in_3,LOW) ;
      digitalWrite(in_4,HIGH) ;
      analogWrite(pwmB,250) ;
      }

    if(state == 49 && a==0)        //DEPLASARE IN FATA
      { 
      digitalWrite(in_1,LOW) ;
      digitalWrite(in_2, HIGH) ;
      analogWrite(pwmA,250) ;
      digitalWrite(in_3,HIGH) ;
      digitalWrite(in_4, LOW) ;
      analogWrite(pwmB ,250) ;
      }

    if(state == 52 && a==0)         //DEPLASARE IN DREAPTA     
      { 
        digitalWrite(in_1,HIGH) ;
        digitalWrite(in_2,LOW) ;
        analogWrite(pwmA,250) ;
        digitalWrite(in_3,HIGH) ;
        digitalWrite(in_4,LOW) ;
        analogWrite(pwmB ,250) ;
      }

    if(state == 97)  // stop
      { 
        digitalWrite(in_1,LOW) ;
        digitalWrite(in_2, LOW) ;
        analogWrite(pwmA,100) ;
        digitalWrite(in_3,LOW) ;
        digitalWrite(in_4, LOW) ;
        analogWrite(pwmB ,150) ;
        a=0;
     } 
}
