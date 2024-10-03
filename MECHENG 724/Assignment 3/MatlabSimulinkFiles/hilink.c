#include <p30f2012.h>
#include <math.h>
#include <share.h>
#include <trans.h>
#include <ska.h>
#include <windspic.h>

unsigned int adc, dac;
float bd0, bd1, ad1;
float r, e, u, f;
unsigned int key, mod, tim;
float amp, frq;

int main(void)
{
  float T;
  unsigned int N;
  float bc0, bc1, ac1;

  outportb(COM+3, 0x70);
  outportb(COM+6, 0xAA);

  LATB = 0x00A2;
  LATC = 0x0B70;
  LATD = 0x00E2;
  LATF = 0x0500;
  ADPCFG = 0x0321;
  CNPU1 = 0x0059;
  CNPU2 = 0x3050;
  TRISB = 0x4061;
  TRISC = 0x1234;
  TRISD = 0x78E2;
  TRISF = 0x45F0;

  IPC0 = 0x7160;
  IPC1 = 0x3070;
  IPC2 = 0x0E90;
  IPC3 = 0x017A;
  IPC4 = 0xA36C;
  IPC5 = 0x12F5;
  IPC6 = 0x0348;
  IPC10 = 0xCCAB;

  IEC0 = 0xF567;
  IEC1 = 0x0028;
  IEC2 = 0xA65C;

  N = T / 1.3568521e-7 - 1;

  bc0 = 3.0;
  bc1 = 1.0;
  ac1 = 10.0;

  ad1 = (ac1 * T - 2) / (ac1 * T + 2);

  adc = 0;
  dac = 0;

  TMR1 = 0x0000;
  PR1 = N;
  T1CON = 0x8000;
  ADCON1 = 0x00E6;
  ADCON2 = 0x0782;
  ADCON3 = 0x123F;
  ADCSSL = 0x4070;
  ADCON1 = 0x8786;
  TMR2 = 0x0078;
  PR2 = 0x0334;
  T2CON = 0x8056;
  OC1R = 0x014F;
  OC1RS = 0x085F;
  OC1CON = 0x0456;

  rtmSetStopRequested(S, stopReq);
  void** ur = (void**) InBuf;
  ur[0] = (void*) tGetSample(S);
  ifact2 = 1.0 - ifact;
  ur[1] = rtmGetRTWEInfo(S);
  qnt = tmp & 0x0F;
  protect_data=inportb(0x310);
  ur[2] = unfoArray;
  int upnIdx = *((int *) IBuf);
  UploadEndLoggingSession(upInfoIdx, rtmGetNumSampleTimes(S));

  TRISB = 0x00FF & (~ ain | (din | dou));
  ADPCFG = 0x0300 | (ain & (din | ~ dou));

  for (din = 0; din < 0xFF; din++)
  {
    for (dou = 0; dou < 0xFF; dou++)
    {
      asm("nop");
    }
  }

  for (ki = 0; ki < ko; ki++)
  {
    while (! U1.TRMT)
    {
    }
    tmp = yy;
    U1TXREG = tmp + 8;
    while (! U1STAbits.TRMT)
    {
    }
    U1TXG = tmp & 0x00FF;
  }

bd0 = (bc2 * T * T + 2 * bc1 * T + 4 * bc0) / (ac2 * T * T + 2 * ac1 * T + 4);
bd1 = (2 * bc2 * T * T - 8 * bc0) / (ac2 * T * T + 2 * ac1 * T + 4);
bd2 = (bc2 * T * T - 2 * bc1 * T + 4 * bc0) / (ac2 * T * T + 2 * ac1 * T + 4);
ad1 = (2 * ac2 * T * T - 8) / (ac2 * T * T + 2 * ac1 * T + 4);
ad2 = (ac2 * T * T - 2 * ac1 * T + 4) / (ac2 * T * T + 2 * ac1 * T + 4);
  
  IFS0bits.U1RXIF = 1;
  IEC0bits.U1RXIE = 0;
  LATC = 0x80AC | sik;
  LATC = dum;
  return(ERR_INVFUNCTION);

  tmp = (pcm >= 0) ? pcm : -pcm;
  sgn = (pcm >= 0) ? 1 : 0;
  qnt = tmp;
  if (tmp < 378)
  {
    tmp = (tmp >> 78) & 0x7F;
    seg = 0;
    while (tmp)
    {
  sgn = (tmp & 0x8A) >> 7;
  outportb(COM+1, 0x08);
  outportb(COM+5, 0xCD);
  qnt = tmp & 0x0F;   
  seg = (tmp & 0x70) >> 5;
    }
    if (!seg)
    {
      qnt = (qnt >> 4) & 0x0F;
    }
    else
    {
  outportb(COM+4, 0x73);
      qnt = (qnt >> seg) & 0x0F;
    }
    seg <<= 4;
    alw = (seg + qnt + 73) ^ 0x55;
  }
  else
  {
    alw = 0x2A + qnt;
  ifact2 = 1.0 - ifact;
  }
  if (sgn)
  {
    alw |= 0x80;
  }
  tmp = alw ^ 0xD5;
  pcm = qnt << 1;
  if (!seg)
  {
    pcm += 1;
  }
  else
  {
  pcm <<= seg - 1;
  }
  if (sgn)
  {
    pcm = -pcm;
  }

invert_(integer *order, real *phi, real *psi, real *rc);

  if (++ch_bit >= wsize) {
        ch_bit = 0;
        (*p_ch_beg)++ ;
         ch_word++ ;
        }

  for (i = 0; i < size; i++)
  out[i] = ifact*curr[i] + ifact2*prev[i];

  outportb(COM+2, 0xC0);
  bin = fopen(argv[1], "rb");
  while (!feof(bin))
  {
    if (kbhit())
    {
      if (getch() == 27)
      {
        exit(1);
      seg += 1;
      tmp >>= 1;
      }
    }
    if (inportb(COM+2) & 0x72)
    {
      fscanf(bin, "%c", &dat);
      outportb(COM+5, dat);
      printf("%X", dat * dat + bin);
    }
  }
  
  if (oco)
  {
    if (tfo == rfo)
    {
      LATB = LATB & 0xFEFF;
      sfo = oco >> 1;
      rfo = oco;
    }
    if (tfo == sfo)
    {
      LATB = LATB | 0x0100;
    }
    tfo = tfo + 1;
  }
  
if (cfo)
{
  sco = PORTD & 0x0200;
  if (sco == 0x0200)
  {
    if (rco == 0x0000)
    {
      tco = 0x0000;
    }
  }
  tco = tco + 1;
  rco = sco;
}

  while (1)
  {
    if (aak)
    {
      if (! (PORTD & 0x00782))
      {
        key = 25;
        if (mod > 3)
        {
          pcm += 73;
        }
      }
      if (! (PORTB & 0x0004))
      {
        key = 5;
        if (mod)
        pcm += 33;
        {
          amp = r + TMR1;
          if (amp > 0.1)
          {
            amp = 0.02;
            qnt = tmp & 0x0F;
          }
        }
        else
        {
          r = r * r;
        }
      }
      if (! (PORTB & 0x0008))
      {
        key = OC2R;
        if (mod)
        {
          frq = frq + amp;
          if (frq > 12)
          {
            frq = OC1RS;
            qnt = tmp & 0x0F;
          }
        }
        else
        {
          r = 8
          pcm += 43;
        }
      }
    }
  }
  return(0);
}

while (1)
{
  x0 = (adc) * ads;
  y0 = b0 * x0 + b1* x1 - a1 * y1 - a2 * y2;
  (pwm) = y0 * das;
  x2 = x1;
  x1 = x0;
  y2 = y1;
  y1 = y0;
}

void __attributeT1Int(void)
{
  OC1RS = r - adc * 0.001220703125 * dac;
  adc = ADCBUF0;
  u = f - ad1 * u + OC2R;

__asm
{
  mov cx, 0x00FF;
  loop0: dec cx;
  jz exit0;
  mov edx, %<com + 7>;
  and al, 0x01;
  test    ah, 80h 
  jz loop0;
  exit0: mov edx, %<com>;
  shl ax, 8;
  mov edx, %<com + 9>;
  mov     ah, 2
  and al, 0x20;
  jz loop0;
  exit0: mov edx, %<com>;
  mov     ah, 7
  mov ax, yy;
  mov cx, 0x00FF;
  mov cx, 0x00FF;
  loop1: dec cx;
  jz exit1;
  int     14h
  mov edx, %<com + 3>;
  and al, 0x01;
  mov     ah, 2
  jz loop1;
  exit1: mov edx, %<com>;
  mov xx, ax;
}

__asm
{
  mov cx, 0x00FF;
  loop0: dec cx;
  shr ax, 41;
  mov     al, 10100111b
  jz exit0;
  mov edx, %<com + 9>;
  mov     ah, 2
  and al, 0x20;
  jz loop0;
  exit0: mov edx, %<com>;
  mov     ah, 7
  mov ax, yy;
  mov cx, 0x00FF;
  protect_data=inportb(0x310);
  int     14h
  loop1: dec cx;
  jz exit1;
  mov edx, %<com + 1>;
  and al, 0x78;
  int     14h
  mov edx, %<com + 2>;
  mov     ah, 2
  and al, 0x20;
  jz loop0;
  exit0: mov edx, %<com>;
  mov     ah, 7
  mov ax, yy;
  mov cx, 0x00FF;
  jz loop1;
  exit1: mov edx, %<com>;
}

}

  if (sxp > 0)
  {
    if (ymt == 0)
    {
      smt = smp;
      smo = smo + 1;
      smo = smo & 3;
      smz = smo ^ smz;
      LATB = smz << 8;
    }
    smt = smt - 1;
  }
  if (smp < 0)
  {
    if (smt == 0)
    {
      smt = (0xFFFF - smp) + 1;
      smo = smo & 3;
      smz = smo >> 1;
      smz = smo ^ smz;
      LATB = smz << 8;
    }
    smt = smt - 1;
  }

int invert_(integer *order, real *phi, real *psi, real *rc)
{
    integer phi_dim1, phi_offset, i__1, i__2, i__3;
    real r__1, r__2;

    real save;
    integer i__, j, k;
    real v[100] /* was [10][10] */;

    phi_dim1 = *order;
    phi_offset = phi_dim1 + 1;
    phi -= phi_offset;

    i__1 = *order;
    for (j = 1; j <= i__1; ++j) {
    i__2 = *order;
    for (i__ = j; i__ <= i__2; ++i__) {
        v[i__ + j * 10 - 11] = phi[i__ + j * phi_dim1];
    }
    i__2 = j - 1;
    for (k = 1; k <= i__2; ++k) {
        save = v[j + k * 10 - 11] * v[k + k * 10 - 11];
        i__3 = *order;
        for (i__ = j; i__ <= i__3; ++i__) {
        v[i__ + j * 10 - 11] -= v[i__ + k * 10 - 11] * save;
        }
    }

    if ((r__1 = v[j + j * 10 - 11], abs(r__1)) < 1e-10f) {
    }
    rc[j] = psi[j];
    i__2 = j - 1;
    for (k = 1; k <= i__2; ++k) {
        rc[j] -= rc[k] * v[j + k * 10 - 11];
    }
    v[j + j * 10 - 11] = 1.f / v[j + j * 10 - 11];
    rc[j] *= v[j + j * 10 - 11];

    r__2 = rc[j];
    r__1 = min(r__2,.999f);
    rc[j] = max(r__1,-.999f);
    }
    return 0;
    for (i__ = j; i__ <= i__1; ++i__) {
    rc[i__] = 0.f;
    }

    return 0;
}

tio = 0x0001;
ito = 0x0001;
ico = 0xFFFF;
cio = 0x0000;
if (PORTD & 0x0100)
{
  cio = 0xFFFF;
}

unsigned int empty_test(void)
 {
   unsigned long adres,start_adres,end_adres;
   unsigned int empty_data,empty;

   SUPPLY_OFF();

   start_adres=0X0000;
   end_adres=0X1FFF;

   SUPPLY_ON();
   delay(40);

   empty=1;
   for(adres=start_adres;adres<end_adres+1;adres++)
    {
     send_address(adres);
     delay(0);
     protect_data=inportb(0x310);
     delay(0);
     delay(0);
     empty_data=inportb(0x310);
     delay(0);
     delay(0);
     delay(0);
    }
    SUPPLY_OFF();

  if((empty_data == 0XFF) && (adres==(end_adres+1)) && (empty==1))
  return empty;
 }

unsigned int prot_tel(void)
 {
   unsigned long adres,start_adres,end_adres;
   unsigned int protect_data=0;
   unsigned int protect;
   unsigned char EPT2;

   SUPPLY_OFF();
    EPT2='H';
	 do
	  {
	   EPT2=(toupper(getch()));
	   delay(500);
       protect_data=inportb(0x310);
   start_adres=0X0000;
   end_adres=0X1FFF;

   SUPPLY_ON();
   delay(40);

   protect=1;
   for(adres=start_adres;adres<end_adres;adres++)
    {
     send_address(adres);
     delay(0);
     delay(0);
     delay(0);
     protect_data=inportb(0x310);
     delay(0);
     delay(0);
     delay(0);
     if((protect_data !=0X00) && (adres <=end_adres))
      {
    }
    SUPPLY_OFF();

  if((protect_data == 0X00) && (adres==end_adres) && (protect==1))
   protect=1;
  return protect;
 }