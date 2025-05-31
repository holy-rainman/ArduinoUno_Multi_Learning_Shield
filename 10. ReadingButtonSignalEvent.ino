#define pinLed1 13
#define pinLed2 12
#define pinLed3 11
#define pinLed4 10

#define led1(x) digitalWrite(pinLed1, x? LOW:HIGH)
#define led2(x) digitalWrite(pinLed2, x? LOW:HIGH)
#define led3(x) digitalWrite(pinLed3, x? LOW:HIGH)
#define led4(x) digitalWrite(pinLed4, x? LOW:HIGH)

#define pb1  digitalRead(A1)
#define pb2  digitalRead(A2)
#define pb3  digitalRead(A3)

uint8_t ledSeq[]={1,3,7,14,12,8,0,8,12,14,7,3,1,0};

void LEDs(uint8_t x)
{ led1(x & (1<<0));
  led2(x & (1<<1));
  led3(x & (1<<2));
  led4(x & (1<<3));
}
uint8_t getPB()
{ uint8_t x=0;
  if(pb1==0) x|=1<<0;
  if(pb2==0) x|=1<<1;
  if(pb3==0) x|=1<<2;
  return x;
}

void setup() 
{ pinMode(pinLed1,OUTPUT);
  pinMode(pinLed2,OUTPUT);
  pinMode(pinLed3,OUTPUT);
  pinMode(pinLed4,OUTPUT);

  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  Serial.begin(9600);

  for(uint8_t i=0;i<sizeof(ledSeq);i++)
  { LEDs(ledSeq[i]);
    delay(200);
  }
}

char tx2buf[100];
void loop() 
{ if(getPB()==1)
  { LEDs(1);
    delay(100);
    while(getPB()==1)
    { LEDs(2);
    }
    LEDs(4);
    delay(50);
  }
  LEDs(0);
}
