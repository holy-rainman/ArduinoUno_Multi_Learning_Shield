#define pinLed1 13
#define pinLed2 12
#define pinLed3 11
#define pinLed4 10

#define led1(x) digitalWrite(pinLed1, x? LOW:HIGH)
#define led2(x) digitalWrite(pinLed2, x? LOW:HIGH)
#define led3(x) digitalWrite(pinLed3, x? LOW:HIGH)
#define led4(x) digitalWrite(pinLed4, x? LOW:HIGH)

void LEDs(uint8_t x)
{ led1(x & (1<<0));
  led2(x & (1<<1));
  led3(x & (1<<2));
  led4(x & (1<<3));
}

void setup() 
{ pinMode(pinLed1,OUTPUT);
  pinMode(pinLed2,OUTPUT);
  pinMode(pinLed3,OUTPUT);
  pinMode(pinLed4,OUTPUT);
}

void loop() 
{ LEDs(5);
}
