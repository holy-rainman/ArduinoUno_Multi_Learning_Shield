#define pinLed1 13
#define pinLed2 12
#define pinLed3 11
#define pinLed4 10
#define pinBuzz  3
#define pinDS    8
#define pinSH    7
#define pinST    4

#define led1(x) digitalWrite(pinLed1, x? LOW:HIGH)
#define led2(x) digitalWrite(pinLed2, x? LOW:HIGH)
#define led3(x) digitalWrite(pinLed3, x? LOW:HIGH)
#define led4(x) digitalWrite(pinLed4, x? LOW:HIGH)
#define buzz(x) digitalWrite(pinBuzz, x? LOW:HIGH)

#define DS(x)   digitalWrite(pinDS, x? HIGH:LOW)
#define SH(x)   digitalWrite(pinSH, x? HIGH:LOW)
#define ST(x)   digitalWrite(pinST, x? HIGH:LOW)

#define pb1  digitalRead(A1)
#define pb2  digitalRead(A2)
#define pb3  digitalRead(A3)

uint8_t ledSeq[]={1,3,7,14,12,8,0,8,12,14,7,3,1,0};
// Array data & variables used for 7-segment Common Anode - numeric value only
//                  INDEX:  0    1    2    3    4    5    6    7    8    9   10
//                    NUM:  0    1    2    3    4    5    6    7    8    9 BLNK
const uint8_t num[30] = {0xC0,0XF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0xFF};
const uint8_t seg[4]  = {0xF1,0xF2,0xF4,0xF8};
uint16_t ptr2disp;
uint16_t buff[4];

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
void beep(uint8_t kali, uint16_t masa)
{ for(uint8_t i=0;i<kali;i++)
  { buzz(1);  delay(masa);
    buzz(0);  delay(masa);
  }
}
void multiplexSegment(uint16_t x)
{ for(uint8_t i=0;i<4;i++)
  { switch(i)
    { case 0: // DIGIT 1
        ptr2disp = x / 1000;
        break;
      case 1: // DIGIT 2
        ptr2disp = (x % 1000) / 100;
        break;
      case 2: // DIGIT 3
        ptr2disp = (x % 100) / 10;
        break;
      case 3: // DIGIT 4
        ptr2disp = x % 10;
        break;
    }
    buff[i] = (num[ptr2disp]<<8) | seg[i];
  }
}
void displaySegment(void)
{ static uint8_t seg=0;
  ST(LOW);
  for(int8_t i=15;i>-1;i--)
  { SH(LOW);
    if(buff[seg] & (1<<i))  DS(HIGH);
    else                    DS(LOW);
    SH(HIGH);
  }
  ST(HIGH);
  if(++seg>3) seg=0;
}

void setup() 
{ // TIMER 0 for interrupt frequency 1000 Hz:
  cli(); 
  TCCR0A = 0; 
  TCCR0B = 0; 
  TCNT0  = 0; 
  OCR0A  = 249; 
  TCCR0B |= (1 << WGM01);
  TCCR0B |= (0 << CS02) | (1 << CS01) | (1 << CS00);
  TIMSK0 |= (1 << OCIE0A);
  sei(); 
  
  pinMode(pinLed1,OUTPUT);
  pinMode(pinLed2,OUTPUT);
  pinMode(pinLed3,OUTPUT);
  pinMode(pinLed4,OUTPUT);
  pinMode(pinBuzz,OUTPUT);
  buzz(0);
  
  pinMode(pinDS,OUTPUT);
  pinMode(pinSH,OUTPUT);
  pinMode(pinST,OUTPUT);

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
uint16_t cnt=0;
void loop() 
{ if(getPB()==1)
  { beep(1,50);
    cnt+=10;
    while(getPB()==1);
    delay(50);
  }

  if(getPB()==2)
  { beep(1,50);  
    cnt++;
    while(getPB()==2);
    delay(50);
  }
 
  multiplexSegment(cnt);
}

ISR(TIMER0_COMPA_vect)
{ displaySegment();
}
