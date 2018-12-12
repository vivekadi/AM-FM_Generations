#include<reg51.h>

sbit AM=P2^0;

 char str;
 char Charin=0;

void delay(int time)
{
 unsigned int i,j;
 for(i=0;i<time;i++)
 for(j=0;j<1275;j++);
}

void Serialwrite(char byte)
{
  SBUF=byte;
  while(!TI);
  TI=0;
}

void Serialprintln(char *p)
{
  while(*p)
  {
    Serialwrite(*p);
    p++;
  }
  Serialwrite(0x0d);
}

void Serialbegin()
{
   TMOD=0x20;
   SCON=0x50;
   TH1=0xfd;
   TR1=1;
}

void main()
{
  P2=0x00;
  Serialbegin();
  Serialprintln("MODULATION SELECTOR");
  delay(50);
  while(1)
  {
    while(!RI);
    Charin=SBUF;
    str=Charin;
    RI=0;
      if(str=='1')
      {
        AM=1;
        Serialprintln(" AM");
        delay(50);
      }
		else if(str=='2')
      {	AM=0;
		Serialprintln("FM");
			}
        
      str=0;
  }
}