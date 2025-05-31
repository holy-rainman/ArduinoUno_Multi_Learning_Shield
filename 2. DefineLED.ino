#define pinLed1 13

void setup() 
{ pinMode(pinLed1,OUTPUT);
}
 void loop() 
{ digitalWrite(pinLed1,LOW);
  delay(500);
  digitalWrite(pinLed1,HIGH);
  delay(500);
}
