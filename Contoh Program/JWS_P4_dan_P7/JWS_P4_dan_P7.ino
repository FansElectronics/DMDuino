/*************************************************************************************
 *  Waktu Sholat P10   - Program jam petunjuk waktu Sholat otomatis yang dilekapi dengan
  Copyright (C) Des 2017 MFH Robotic. (info https://www.facebook.com/MFH.Robotic/)
  Fitur :
  
  1. Perhitungan waktu sholat otomatis berdasarkan data geografis lokasi
    (Latitude, Longitude, Altitude, Time Zone dan Prameter pengaman/
    Ihtiyati)
  2. Fasilitas remote menggunakan aplikasi yang berjalan pada HP Android.
  3. Fasilitas running text informasi yang berjumlah 3 x 150 karakter.
    Running text ini cukup besar untuk di isi dengan hadis atau informasi lainnya
    melalui fasilitas remote Aplikasi Android.
  4. Perhitungan Hari dan tanggal Hijriah secara otomatis dan perubahan tanggalnya
    sesuai sesuai standar Hijriah yaitu setelah azzan magrib
  5. Fasilitas nama Masjid dan jenis masjid nya:
        a. Masjid
        b. Musholla
        c. Surau
        d. Langgar
  6. Pengingat waktu sholat mulai dari Azzan, menunggu iqomah dan mulai Sholat
    termasuk pengingat sholat Jumat jika parameter jenis nya di set sebagai Masjid.
  7. Program ini sangat baik dipakai sebagai sarana belajar programing Arduino karena
    menggunakan banyak librari dan teknik pemrogramn yang asik seperti:
       - Library yang digunakan adalah:
              #include <SPI.h>            --> komunikasi ke modul P4.75
              #include <DMD3.h>           --> library untuk modul P4.75
              #include <Wire.h>           --> komunikasi ke modul RTC DS3231
              #include <DS3231.h>         --> library modul RTC DS 3231
              #include <Timer.h>          --> library Timer untuk mengatur timing tampilan
              #include <EEPROM.h>         --> library untuk penggunaan EEPROM sebagai sarana penyimpan parameter
              #include <avr/pgmspace.h>   --> library untuk penggunaan PROGMEM agar utilisasi SRAM bisa optimal
  8. Program dipecah menjadi 4 File sehingga maintenance bisa lebih mudah dan aman dan tidak mengganggu bagian
    lain.

  Created by Wardi Utari
  30 Des 2017

  ---

  Progarm ini TIDAK ROYALTY FREE, program ini FREE jika dipergunakan untuk
    1. Jika dipergunakan di sekolah/lembaga latihan/perorangan untuk pendidikan atau proses belajar
    2. Dipergunakan dalam proyek pembuatan Jam pengingat waktu sholat yang disumbangkan ke masjid, musholla dll.

  Jika program ini dipergunakan secara komersial baik keseluruhan atau sebagian, anda diwajibkan
  membayar ROYALTY FEE sebesar 2.5%. Royalty tersebut agar dibayarkan ke Masjid terdekat dengan lokasi
  anda, dalam bentuk Sedekah yang diniatkan untuk semua orang yang telah turut urun rembug dalam membuat dan
  menyempurnakan program ini.
**************************************************************************************/
#include "SPI.h"
#include "DMD3.h"
#include "font/Font4x6.h"
#include "font/DejaVuSansBold9.h"
#include "font/System_Min5x7.h"
#include "font/BigNumber.h"
#include "DS3231.h"
#include "EEPROM.h"
#include "avr/pgmspace.h"
#include "Wire.h"
#define BUZZ    A0
#define Font0 Font4x6
#define Font1 DejaVuSansBold9
#define Font2 BigNumber
#define Font3 DejaVuSansBold9

// Object Declarations
DMD3 Disp(2, 1);
char *pasar[] ={"Wage", "Kliwon", "Legi", "Pahing", "Pon"}; 
int maxday[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
RTClib          RTC;
DS3231          Clock;

//Structure of Variable
typedef struct  // loaded to EEPROM
{
  uint8_t state;   // 1 byte  add 0
  float   L_LA;    // 4 byte  add 1
  float   L_LO;    // 4 byte  add 5
  float   L_AL;    // 4 byte  add 9
  float   L_TZ;    // 4 byte  add 13
  uint8_t MT;      // 1 byte  add 17  // value 1-masjid  2-mushollah 3-surau 4-langgar
  uint8_t BL;      // 1 byte  add 18
  uint8_t IH;      // 1 byte  add 19
  uint8_t SO;      // 1 byte  add 20
  uint8_t JM;      // 1 byte  add 21
  uint8_t I1;      // 1 byte  add 22
  uint8_t I4;      // 1 byte  add 23
  uint8_t I5;      // 1 byte  add 24
  uint8_t I6;      // 1 byte  add 25
  uint8_t I7;      // 1 byte  add 26
  uint8_t BZ;      // 1 byte  add 27
  uint8_t SI;      // 1 byte  add 28
  uint8_t ST;      // 1 byte  add 29
  uint8_t SU;      // 1 byte  add 30
  int8_t  CH;      // 1 byte  add 31
  uint8_t IM;      // 1 byte  add 32
  uint8_t II;      // 1 byte  add 33
  uint8_t IS;      // 1 byte  add 34
  uint8_t IL;      // 1 byte  add 35
  uint8_t IA;      // 1 byte  add 36
} struct_param;

typedef struct
{
  uint8_t   hD;
  uint8_t   hM;
  uint16_t  hY;
} hijir_date;


// Variable by Structure
struct_param    Prm;
hijir_date      nowH;

// Time Variable
DateTime        now;
float           floatnow   = 0;
uint8_t         daynow     = 0;
uint8_t         ty_puasa   = 0;
uint8_t         hd_puasa   = 0;
int8_t          SholatNow  = -1;
boolean         jumat      = false;
boolean         azzan      = false;
uint8_t         reset_x    = 0;

//Other Variable
float sholatT[8]  = {0, 0, 0, 0, 0, 0, 0, 0};
uint8_t Iqomah[8] = {0, 0, 0, 0, 0, 0, 0, 0};

//Blue tooth Pram Receive
char        CH_Prm[155];
int         DWidth  = Disp.width();
int         DHeight = Disp.height();
boolean     DoSwap;
int         RunSel    = 1; //
int         RunFinish = 0 ;

//=======================================
//===SETUP===============================
//=======================================
void setup()
{ //init comunications
  Wire.begin();
  Serial.begin(9600);
  pinMode(BUZZ, OUTPUT);
  // Get Saved Parameter from EEPROM
  updateTime();
  GetPrm();
  //SendPrm();
  digitalWrite(A0, HIGH);
  delay(100);
  digitalWrite(A0, LOW);
  //init P10 Led Disp & Salam
  Disp_init();
}

//=======================================
//===MAIN LOOP Function =================
//=======================================
void loop()
{
  // Reset & Init Display State
  updateTime();   //every time
  check_azzan();  //check Sholah Time for Azzan
  DoSwap  = false ;
  fType(1);
  Disp.clear();
  // Timer Function every 10 Minutes
  // Up All function with Timer in this fuction
  Timer_Minute(1);


  // =========================================
  // List of Display Component Block =========
  // =========================================

  anim_DT(1);                                                 // addr: 1 show date time
  dwMrq(drawMasjidName(), 90, 2, 2);                          // addr: 2 show Masjid Name
  dwMrq(drawDayDate()   , 90, 1, 3);                          // addr: 3 show Hijriah date
  dwMrq(msgPuasa(hd_puasa, ty_puasa), 90, 0, 4);              // addr: 5 show Remander Puasa
  drawSholat(5);                                              // addr: 5 show sholat time
  dwMrq(drawInfo(130)    , 90, 1, 6);                          // addr: 6 show Info 1
  anim_DT(7);                                                 // addr: 7 show date time
  dwMrq(drawInfo(280)   , 90, 2, 8);                          // addr: 8 show Info 2
  drawSholat(9);                                              // addr: 9 show sholat time
  dwMrq(drawInfo(430)   , 90, 1, 10);                         // addr: 10 show Info 3

  drawAzzan(100);                                             // addr: 100 show Azzan
  drawIqomah(101);                                            // addr: 101 show Iqomah
  dwMrq(drawInfo(580), 90, 0, 102); //Message Sholat biasa       // addr: 202 show Message Sholah
  dwMrq(drawInfo(730), 90, 0, 103); //Message Sholat jumat       // addr: 203 show Message Jum'at
  blinkBlock(104);                                            // addr: 104 show Blink  Sholat

  // =========================================
  // Display Control Block ===================
  // =========================================
 // =========================================
    // Display Control Block ===================
    // =========================================
    if(RunFinish==1) {RunSel = 2; RunFinish =0;}                      //after anim 1 set anim 2
    if(RunFinish==2) {RunSel = 3; RunFinish =0;}                      //after anim 2 set anim 3
//  if(RunFinish==3) {RunSel = 3; RunFinish =0;}
    if(RunFinish==3)                                                  //after anim 3 set anim 5 or anim 4 if puasa
         {
          if (ty_puasa!=0)  {RunSel = 4; RunFinish =0;}
          else {RunSel = 5; RunFinish =0;}
         }
    if(RunFinish==4)  {RunSel = 5;  RunFinish =0;}                      //after anim 4 set anim 5
    if(RunFinish==5)  {RunSel = 6;  RunFinish =0;}                      //after anim 5 set anim 6
    if(RunFinish==6)  {RunSel = 7;  RunFinish =0;}                      //after anim 6 set anim 7
    if(RunFinish==7)  {RunSel = 8;  RunFinish =0;}                      //after anim 7 set anim 8
    if(RunFinish==8)  {RunSel = 9;  RunFinish =0;}                      //after anim 8 set anim 9
    if(RunFinish==9)  {RunSel = 10; RunFinish =0;}                      //after anim 9 set anim 10
    if(RunFinish==10) {RunSel = 1;  RunFinish =0;} 
    
    
    if(RunFinish==100 and jumat )     {RunSel = 103; RunFinish = 0; reset_x = 1;}  //after Azzan Jumat (anim 100)
    else if(RunFinish==100)           {RunSel = 101; RunFinish =0;}               //after Azzan Sholah (Iqomah)
        
    if(RunFinish==101) {RunSel = 102; RunFinish =0; reset_x=1;}       //after Iqomah(anim 101) set Message Sholah (anim 102)   
    if(RunFinish==102) {RunSel = 104; RunFinish =0;}                  //after Message Sholah (anim 102) set Blink Sholah(anim 104) 
    if(RunFinish==103) {RunSel = 104; RunFinish =0;}                  //after Messagw Jum'at (anim 103) set Blink Sholah(anim 104)
    if(RunFinish==104) {RunSel = 1; RunFinish =0;}                    //after Blink Sholah back to anim 1 


  // =========================================
  // Swap Display if Change===================
  // =========================================
  if (DoSwap) {
    Disp.swapBuffers(); // Swap Buffer if Change
  }
}


// =========================================
// DMD3 P10 utility Function================
// =========================================
void Disp_init()
{ Disp.setDoubleBuffer(true);
  Timer1.initialize(1350);
  Timer1.attachInterrupt(scan);
  setBrightness(int(Prm.BL));
  fType(1);
  Disp.clear();
  Disp.swapBuffers();
}

void setBrightness(int bright)
{
  Timer1.pwm(9, bright);
}

void scan()
{
  Disp.refresh();
}

// =========================================
// Time Calculation Block===================
// =========================================
void updateTime()
{ now = RTC.now();
  floatnow = (float)now.hour() + (float)now.minute() / 60 + (float)now.second() / 3600;
  daynow   = Clock.getDoW();    // load day Number
}

void Timer_Minute(int repeat_time) //load every  1 minute
{
  static uint16_t   lsRn;
  uint16_t          Tmr = millis();
  if ((Tmr - lsRn) > (repeat_time * 60000))
  {
    lsRn = Tmr;
    update_All_data();
  }
}

void update_All_data()
{
  uint8_t   date_cor = 0;
  updateTime();
  sholatCal();                                                // load Sholah Time
  check_puasa();                                              // check jadwal Puasa Besok
  if (floatnow > sholatT[6]) {
    date_cor = 1; // load Hijr Date + corection next day after Mhagrib
  }
  nowH = toHijri(now.year(), now.month(), now.day(), date_cor); // load Hijir Date

  if ((floatnow > (float)18) or (floatnow < (float)18.5) )    
  {setBrightness(Prm.BL);}
  else                                                   
  {setBrightness(Prm.BL);
  }
}


void check_azzan()
{ //Check Waktu Sholat
  SholatNow  = -1;
  for (int i = 0; i <= 7; i++)
  {
    if (i != 0 and i != 2 and i != 3) // bukan terbit dan bukan dhuha
    {
      if (floatnow >= sholatT[i])
      {
        SholatNow = i;
        if (!azzan and (floatnow > sholatT[i]) and (floatnow < (sholatT[i] + 0.03)))
        {
          if (daynow == 6 and SholatNow == 4 and Prm.MT == 1) {
            jumat = true;
          }
          azzan = true;
          RunSel = 100;
        }
      }
    }
  }
}


