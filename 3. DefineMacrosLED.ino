#define pinLed1 13

#define led1(x) digitalWrite(pinLed1, x? LOW:HIGH)

void setup() 
{ pinMode(pinLed1,OUTPUT);
}

void loop() 
{ led1(HIGH);
  delay(500);
  led1(LOW);
  delay(500);
}
