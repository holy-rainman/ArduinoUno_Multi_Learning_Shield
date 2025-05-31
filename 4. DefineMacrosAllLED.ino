#define pinLed1 13
#define pinLed2 12
#define pinLed3 11
#define pinLed4 10

#define led1(x) digitalWrite(pinLed1, x? LOW:HIGH)
#define led2(x) digitalWrite(pinLed2, x? LOW:HIGH)
#define led3(x) digitalWrite(pinLed3, x? LOW:HIGH)
#define led4(x) digitalWrite(pinLed4, x? LOW:HIGH)

void setup() 
{ pinMode(pinLed1,OUTPUT);
  pinMode(pinLed2,OUTPUT);
  pinMode(pinLed3,OUTPUT);
  pinMode(pinLed4,OUTPUT);
}

void loop() 
{ led1(HIGH); led2(LOW);  led3(HIGH); led4(LOW);
  delay(500);
  led1(LOW);  led2(HIGH); led3(LOW);  led4(HIGH);
  delay(500);
}
