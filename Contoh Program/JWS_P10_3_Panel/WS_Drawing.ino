// =========================================
// Drawing Content Block====================    
// =========================================
static const uint8_t data[]PROGMEM =
{
  32,16,
0x00, 0x01, 0x00, 0x00, 0x20, 0x03, 0x80, 0x08, 0x20, 0x0f, 0xe0, 0x08, 0x20, 0x3e, 0xf0, 0x08, 0x70, 0x78, 0x3c, 0x1c, 0xf8, 0xf0, 0x1e, 0x3e, 0xd8, 0xf0, 0x1e, 0x36, 0xd8, 0xf8, 0x3e, 0x36, 0x70, 0x7f, 0xfc, 0x1c, 0x7f, 0xff, 0xff, 0xfc, 0x7f, 0xfe, 0xff, 0xfc, 0x7e, 0xfc, 0x7e, 0xfc, 0x74, 0x48, 0x24, 0x5c, 0x74, 0x48, 0x24, 0x5c, 0x74, 0x48, 0x24, 0x5c, 0x7c, 0x78, 0x3c, 0x7c
};
//}
static const uint8_t satu[] PROGMEM = {
                                            16,16,
                                            0x01, 0x00, 0x07, 0x12, 0x0c, 0x36, 0x19, 0x36, 0x03, 0x36, 0x03, 0x36, 0x13, 0x36, 0x33, 0x36, 0x73, 0x36, 0xd3, 0x36, 0x93, 0x76, 0xff, 0xe6, 0x3e, 0xc6, 0x18, 0x86, 0x10, 0x04, 0x00, 0x00
};
   static const uint8_t dua[] PROGMEM = {
                                            16,14,
                                            0x18,0x08,
                                            0x0C,0x14,
                                            0x06,0x1C,
                                            0x06,0x70,
                                            0x06,0xC0,
                                            0x06,0x80,
                                            0x06,0xFF,
                                            0x06,0x1E,
                                            0x1B,0xF8,
                                            0xB1,0x80,
                                            0xE0,0x6C,
                                            0x00,0x7E,
                                            0x00,0x12,
                                            0x00,0x0C,
                                            };

void drawAzzan(int DrawAdd)
  {
    // check RunSelector
    if(!dwDo(DrawAdd)) return;
    uint8_t           ct_limit =240;  //harus angka genap
    static uint8_t    ct;
    static uint16_t   lsRn;
    uint16_t          Tmr = millis();

    if((Tmr-lsRn) > 500 and ct <= ct_limit)
      {
        lsRn = Tmr;
        if((ct%2) == 0)
          { Disp.drawRect(33,0,95,15);       
            Disp.drawRect(34,1,94,14);
            drawSmallTS(0);
            
            fType(1);
            dwCtr(33,-1,"ADZAN");
            fType(0);
            if(jumat) {dwCtr(33,9,sholatN(8));}
            else      {dwCtr(33,9,sholatN(SholatNow));}       //Koordinat Box Adzan
            if (ct>20) Buzzer(0);
            else Buzzer(1);
          }
        else 
          { Buzzer(0);}
        DoSwap = true; 
        ct++;
      }
    if ((Tmr-lsRn)>2000 and (ct > ct_limit))
      {dwDone(DrawAdd);
       ct = 0;
       Buzzer(0);}
  }

void drawIqomah(int DrawAdd)  // Countdown Iqomah (9 menit)
  {  
    // check RunSelector
    if(!dwDo(DrawAdd)) return;

    static uint16_t   lsRn;
    uint16_t          Tmr = millis();
    static int        ct;
    int               mnt, scd,cn_l ;
    char              locBuff[6];           
    
    cn_l  = (Iqomah[SholatNow]*60);
            Disp.drawRect(32,0,95,15);       //koordinat box iqomah
            Disp.drawRect(33,1,94,14);
            
    
    if((Tmr-lsRn) > 1000 and ct <=cn_l)
      {
          lsRn = Tmr;        
          mnt = floor((cn_l-ct)/60); 
          scd = (cn_l-ct)%60;
          if(mnt>0) {sprintf(locBuff,"%d:%02d MENIT",mnt,scd);}
            else    {sprintf(locBuff,"%d DETIK",scd);}
          dwCtr(33,-1,"IQOMAH");
          fType(0);
          dwCtr(33,9,locBuff);
          if (ct> (cn_l-2)) Buzzer(1);   // Buzzer on 3 seccon before Iqomah
          ct++;
          DoSwap = true;
          drawSmallTS(0);                  //jam besar
             
      }
    if (ct > cn_l)
      {
       dwDone(DrawAdd);
       ct = 0;
       Buzzer(0);
      }    
  }

void drawSholat_S(int sNum,int c) // Box Sholah Time
  {
    char  BuffTime[10];
    char  BuffShol[7];
    float   stime   = sholatT[sNum];
    uint8_t shour   = floor(stime);
    uint8_t sminute = floor((stime-(float)shour)*60);
    uint8_t ssecond = floor((stime-(float)shour-(float)sminute/60)*3600);
    sprintf(BuffTime,"%02d:%02d",shour,sminute);
    Disp.drawRect(c+1,2,94,13);         //Koordinat Box Display Sholat
    //Disp.drawRect(c+2,1,61,14);
    
    fType(1); dwCtr(c+0,-1,sholatN(sNum));   
    fType(0); dwCtr(c+0,10,BuffTime);
    DoSwap = true;          
  }

void drawSholat(int DrawAdd)
  {
    // check RunSelector
//    int DrawAdd = 0b0000000000000100;
    if(!dwDo(DrawAdd)) return; 

    static uint8_t    x;
    static uint8_t    s; // 0=in, 1=out
    static uint8_t    sNum; 
    static uint16_t   lsRn;
    uint16_t          Tmr = millis();
    uint8_t           c=32;
    uint8_t    first_sNum = 0; 
    int               DrawWd=DWidth - c;    

    if((Tmr-lsRn)>10) 
      {
        if(s==0 and x<(DrawWd/2)){x++;lsRn=Tmr;}
        if(s==1 and x>0){x--;lsRn=Tmr;}
      }
      
    if((Tmr-lsRn)>2000 and x ==(DrawWd/2)) {s=1;}
    if (x == 0 and s==1) 
      { 
        if (sNum <7){sNum++;}
        else 
          { 
           dwDone(DrawAdd);
           sNum=0;
          } 
        s=0;
      }

    if(Prm.SI==0) {first_sNum =1;}
    else {first_sNum =0;}
    if(Prm.SI==0 and sNum == 0) {sNum=1;}
    if(Prm.ST==0 and sNum == 2) {sNum=3;}
    if(Prm.SU==0 and sNum == 3) {sNum=4;}

 
    if(  (((sNum == first_sNum) and s ==0) or 
          ((sNum == 7)and s == 1)) 
          and x <=20) {drawSmallTS(0);} 
    else {drawSmallTS(0);}
    drawSholat_S(sNum, c);

    Disp.drawFilledRect(c,0,c+DrawWd/2-x,15,0);
    Disp.drawFilledRect(DrawWd/2+x+c,0,95,15,0);
  }

void drawGreg_DS(uint16_t y)   //Draw Date
  { 
    char  Buff[20];
    sprintf(Buff,"%d %s %d",now.day(),MonthName(now.month()),now.year());
    dwCtr(33,y,Buff);
    DoSwap = true;
  }

void drawSmallTS(int x)//===================================================================================JAM BESAR
  {
    char BuffH[3];
    char BuffM[3];
    static uint16_t   lsRn;
    uint16_t          Tmr = millis();
    sprintf(BuffH,"%02d",now.hour());
    sprintf(BuffM,"%02d",now.minute());
    Disp.setFont(angka6x13);
    Disp.drawText((x-10)+11,0,BuffH);
    Disp.drawText((x-10)+28,0,BuffM);
    if(Tmr-lsRn<500)Disp.drawFilledRect(15,4,16,5);
    if(Tmr-lsRn<500)Disp.drawFilledRect(15,9,16,10);
    //Disp.drawLine((x-10)+32,0,(x-10)+32,17,1);
    if(Tmr-lsRn>1000) lsRn = Tmr;
    DoSwap = true;
  }  

void drawGreg_TS(uint16_t y)   // Draw Time
  {
    char  Buff[20];
    sprintf(Buff,"%02d:%02d:%02d",now.hour(),now.minute(),now.second());
    dwCtr(3,y,Buff);
    DoSwap = true; 
  }

void anim_DT(int DrawAdd)
  {
    // check RunSelector
    if(!dwDo(DrawAdd)) return;
    
    // Disp.drawBitmap(0,1, data);
    Disp.drawBitmap(1,1,dua);             //Koordinat Bitmap kiri
    Disp.drawBitmap(80,1,satu);              //koordinat Bitmap Kanan
        
    static uint32_t    y;
    static uint32_t    s; // 0=in, 1=out              
    static uint32_t   lsRn;
    uint32_t          Tmr = millis();

    if((Tmr-lsRn)>100) 
      { 
        if(s==0 and y<7){lsRn=Tmr;y++;}
        if(s==1 and y>0){lsRn=Tmr;y--;}
      }
    if((Tmr-lsRn)>10000 and y ==7) {s=1;}
    if (y==7)
    {
    //Disp.drawBitmap(1,1, satu);               //Koordinat Display Bitmap
    }
      
    if (y == 0 and s==1) {dwDone(DrawAdd); s=0;}
    fType(0);
    Disp.drawRect(19,4,78,14);
    drawGreg_TS(6);
    
    
    //Disp.drawBitmap(79,1,dua);
     
    }

void dwMrq(const char* msg, int Speed, int dDT, int DrawAdd)
  { 
    // check RunSelector
    static uint32_t   x; 
    if(!dwDo(DrawAdd)) return;
    if (reset_x !=0) { x=0;reset_x = 0;}      

       
    static uint32_t   lsRn;
    int fullScroll = Disp.textWidth(msg) + DWidth;
    uint32_t          Tmr = millis();
    if((Tmr-lsRn)> Speed)
      { lsRn=Tmr;
        if (x < fullScroll) {++x;}
        else {  dwDone(DrawAdd); 
                x = 0;return;}
     if(dDT==1)
        {
        fType(0);
        
        if (x<=6)                     { drawGreg_DS(16-x);}
        else if (x>=(fullScroll-6))   { drawGreg_DS(16-(fullScroll-x));}
        else                          { Disp.drawRect(33,8,94,17);
                                        drawGreg_DS(10);}
        fType(1);                                
        Disp.drawText(DWidth - x, -1, msg);
        Disp.drawFilledRect(0,0,31,15,0);                               
        drawSmallTS(0);                                    
        }
     else if(dDT==2)
        {
        fType(0);
        if (x<=6)                     { drawGreg_DS(x-6);}
        else if (x>=(fullScroll-6))   { drawGreg_DS((fullScroll-x)-6);}
        else                          { Disp.drawRect(33,0,94,7);
                                        drawGreg_DS(0);}
                                          
        fType(1);
        Disp.drawText(DWidth - x, 8, msg);       // 8 koordinat tampilan hurup kolom running text 2
        Disp.drawFilledRect(0,0,31,15,0);
        drawSmallTS(0);
        }
     else
        {
        fType(1);
        //Disp.setFont(BritanicBold11);             // change font
        Disp.drawLine(32,0,96,0);
        Disp.drawLine(32,15,96,15);
        Disp.drawLine(32,1,94,1);
        Disp.drawLine(32,14,94,14);


     
        Disp.drawText(DWidth - x, 3, msg);
        Disp.drawFilledRect(0,0,31,15,0);
        drawSmallTS(0);// 3 koordinat Tampilan Running Text
        }
        DoSwap = true; 
      }          
  }

void blinkBlock(int DrawAdd)
  {
    // check RunSelector
    if(!dwDo(DrawAdd)) return;

    static uint16_t   lsRn;
    static uint16_t   ct, ct_l;
    uint16_t          Tmr = millis();

    if(jumat)       {ct_l = Prm.JM * 60;}
    else            {ct_l = Prm.SO * 60;}
    //jumat =false;
    drawSmallTS(0); 
    if((Tmr-lsRn)> 1000)
      { lsRn=Tmr;
//        Disp.drawChar(1, 1 , ct);
        if((ct%2) == 0)
          { 

           //Disp.drawFilledRect(DWidth-9, DHeight-3, DWidth-3, DHeight-2);
           }
        DoSwap = true; 
        ct++;}
    if (ct> ct_l) 
      { dwDone(DrawAdd);
        azzan = false;
        jumat =false;
        ct = 0;
      }
    Disp.drawBitmap(48,0, data);
    //Disp.drawText(1,7,String(ct_l-ct));     //countdown waktu sholat
  }

// =========================================
// Drawing Tools============================
// =========================================
boolean dwDo(int DrawAdd)
  { if (RunSel== DrawAdd) {return true;}
    else return false;}
  
void dwDone(int DrawAdd)
  { RunFinish = DrawAdd;
    RunSel = 0;}
    
void dwCtr(int x, int y,const char* Msg)
  { int   tw = Disp.textWidth(Msg);
    int   th = Disp.textHeight();
    int   c = int((DWidth-x-tw)/2);
    Disp.drawFilledRect(x+c-1,y,x+tw+c,y+th,0);
    Disp.drawText(x+c,y,Msg);}

void Buzzer(uint8_t state)
 {
    if(state ==1 and Prm.BZ == 1)
      {tone(BUZZ, 3000, 500);}
    else 
      {noTone(BUZZ);}
  }
  
void fType(int x)
  {
    if(x==0) Disp.setFont(SmallCap4x6);
    //if(x==0) Disp.setFont(SystemFont5x7); //GANTI FONT
    else Disp.setFont(ArialBlack10);  
  }
