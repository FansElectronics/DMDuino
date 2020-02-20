// =========================================
// Drawing Content Block====================    
// =========================================

void drawAzzan(int DrawAdd)
  {
    // check RunSelector
    if(!dwDo(DrawAdd)) return;
    uint8_t           ct_limit =18;  //harus angka genap
    static uint8_t    ct;
    static uint16_t   lsRn;
    uint16_t          Tmr = millis();

    if((Tmr-lsRn) > 500 and ct <= ct_limit)
      {
        lsRn = Tmr;
        if((ct%2) == 0)
          { Disp.drawRect(1,2,62,13);
            fType(0);
            dwCtr(0,0,"ADZAN");
            fType(1);
            if(jumat) {dwCtr(0,8,sholatN(8));}
            else      {dwCtr(0,8,sholatN(SholatNow));}
            //Buzzer(1);
            digitalWrite (BUZZ, HIGH);
          }
        else 
          { 
            //Buzzer(0);}
            digitalWrite (BUZZ, LOW);
          }
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
    Disp.drawRect(1,2,62,13);
    if((Tmr-lsRn) > 1000 and ct <=cn_l)
      {
          lsRn = Tmr;        
          mnt = floor((cn_l-ct)/60); 
          scd = (cn_l-ct)%60;
          if(mnt>0) {sprintf(locBuff,"%d:%02d MENIT",mnt,scd);}
            else    {sprintf(locBuff,"%d DETIK",scd);}
          dwCtr(0,-1,"IQOMAH");
          fType(0);
          dwCtr(0,10,locBuff);
          if (ct> (cn_l-2)) digitalWrite (BUZZ, HIGH);//Buzzer(1);   // Buzzer on 2 seccon before Iqomah
          ct++;
          DoSwap = true;
             
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
    sprintf(BuffTime,"%02d:%02d:%02d",shour,sminute,ssecond);
    
   // Disp.drawRect(c+1,2,62,13);
    
    fType(1); dwCtr(c,-1,sholatN(sNum));
    fType(0); dwCtr(c,10,BuffTime);
    DoSwap = true;          
  }

void drawSholat(int DrawAdd)
  {
    // check RunSelector
//    int DrawAdd = 0b0000000000000100;
    if(!dwDo(DrawAdd)) return; 
    
    static uint8_t    y; //+
    static uint8_t    x;
    static uint8_t    s; // 0=in, 1=out
    static uint8_t    sNum; 
    static uint16_t   lsRn;
    uint16_t          Tmr = millis()/3;
    uint8_t           c=11;
    uint8_t           first_sNum = 0; 
    //int               DrawWd=DWidth - c;    
    int               DrawWh=DHeight+c; 
    int               DrawWd=DWidth;  
    

    if((Tmr-lsRn)>10) 
      {
        if(s==0 and y<(DrawWh/2) and x<(DWidth/2)){y++;x++;lsRn=Tmr;}
        if(s==1 and y>0 and x>0){y--;x--;lsRn=Tmr;}
      }
      
    if((Tmr-lsRn)>500 and y ==(DrawWh/2)and (DrawWd/2)) {s=1;}
    if (y == 0 and x == 0 and s==1) 
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
          and y <=8 and x<=34) {drawSmallTS(int(x/2));} 
          
    else {drawSmallTS(10);}
    drawSholat_S(sNum, c);
    Disp.drawLine(27-x,8,47+x,8,1);
    Disp.drawFilledRect(12,0-y,63,9-y,0);
    Disp.drawFilledRect(12,7+y,63,15+y,0);
     //Disp.drawFilledRect(c,0,10+DrawWd/2-x,15,0);
    //Disp.drawFilledRect(DrawWd/2+x+c,0,78,15,0);
    // Disp.drawCircle(9,7,x-13,1);
      //Disp.drawLine(12+DrawWd/2-x,0,12+DrawWd/2-x,15,1);
      //Disp.drawLine(DrawWd/2+x+11,0,DrawWd/2+x+11,15,1); 
     
   
     
   
  }

void drawGreg_DS(uint16_t y)   //Draw Date
  { 
    char  Buff[20];
    sprintf(Buff,"%d %s %d",now.day(),MonthName(now.month()),now.year());
    dwCtr(0,y,Buff);
    DoSwap = true;
  }

void drawSmallTS(int x)
  {
    char BuffH[3];
    char BuffM[3];
    static uint16_t   lsRn;
    uint16_t          Tmr = millis();
    sprintf(BuffH,"%02d",now.hour());
    sprintf(BuffM,"%02d",now.minute());
    fType(0);
    Disp.drawText((x-11)+1,0,BuffH);
    Disp.drawText((x-11)+1,9,BuffM);
    //if(Tmr-lsRn<500)Disp.drawLine((x-10)+4,6,(x-10)+6,6,1);//Disp.drawText((x-10)+1,9,BuffM);
    //if(Tmr-lsRn>1000) lsRn = Tmr;
    if(Tmr-lsRn<500)Disp.drawLine((x-10)+1,7,(x-10)+8,7,1);
    if(Tmr-lsRn>1000) lsRn = Tmr;
    DoSwap = true;
  }  

void drawGreg_TS(uint16_t y)   // Draw Time
  {
    char  Buff[20];
    sprintf(Buff,"%02d:%02d:%02d",now.hour(),now.minute(),now.second());
    dwCtr(0,y,Buff);
    DoSwap = true; 
  }

void anim_DT(int DrawAdd)
  {
    // check RunSelector
    if(!dwDo(DrawAdd)) return; 
    
    static uint8_t    y;
    static uint8_t    s; // 0=in, 1=out              
    static uint16_t   lsRn;
    uint16_t          Tmr = millis();

    if((Tmr-lsRn)>100) 
      { 
        if(s==0 and y<7){lsRn=Tmr;y++;}
        if(s==1 and y>0){lsRn=Tmr;y--;}
      }
    if((Tmr-lsRn)>10000 and y ==7) {s=1;}
    if (y==7)
      {
        Disp.drawRect(1,2,62,13);
      }
    if (y == 0 and s==1) {dwDone(DrawAdd); s=0;}
    fType(1);
    drawGreg_TS(y-8);
    fType(0);
    drawGreg_DS(17-y);      
    }

void dwMrq(const char* msg, int Speed, int dDT, int DrawAdd)
  { 
    // check RunSelector
    static uint16_t   x; 
    if(!dwDo(DrawAdd)) return;
    if (reset_x !=0) { x=0;reset_x = 0;}      

       
    static uint16_t   lsRn;
    int fullScroll = Disp.textWidth(msg) + DWidth;    
    uint16_t          Tmr = millis();
    if((Tmr-lsRn)> Speed)
      { lsRn=Tmr;
        if (x < fullScroll) {++x;}
        else {  dwDone(DrawAdd); 
                x = 0;return;}
     if(dDT==1)
        {
        fType(1);      
        Disp.drawText(DWidth - x, -1, msg);
        fType(0);
        if (x<=6)                     { drawGreg_TS(16-x);}
        else if (x>=(fullScroll-6))   { drawGreg_TS(16-(fullScroll-x));}
        else                          { Disp.drawRect(1,10,62,15);
                                        drawGreg_TS(10);}
        }
     else if(dDT==2)
        {    
        fType(0);
        if (x<=6)                     { drawGreg_TS(x-6);}
        else if (x>=(fullScroll-6))   { drawGreg_TS((fullScroll-x)-6);}
        else                          { Disp.drawRect(1,1,62,5);
                                        drawGreg_TS(0);}
        fType(1);
        Disp.drawText(DWidth - x, 6 , msg);
        }
     else
        {
        fType(1);
        Disp.drawLine(1,1,70,1);
        Disp.drawLine(1,15,70,15);
        Disp.drawText(DWidth - x, 3, msg);
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
    jumat =false;
     
    if((Tmr-lsRn)> 1000)
     { lsRn=Tmr;
//        Disp.drawChar(1, 1 , ct);
        if((ct%2) == 0)
          { 

            Disp.drawFilledRect(DWidth-3, DHeight-3, DWidth-2, DHeight-2);
          }
        DoSwap = true; 
        ct++;}
    if (ct> ct_l) 
      { dwDone(DrawAdd);
      jumat =false;
        azzan = false;
        ct = 0;
      }
    //Disp.drawText(1,7,String(ct_l-ct)); // menghilangkan counter angka 
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
      {tone(BUZZ, 500, 400);}
    else 
      {noTone(BUZZ);}
  }
  
void fType(int x)
  {
    if(x==0) Disp.setFont(SmallCap4x6);
    else Disp.setFont(DejaVuSansBold9);  
  }
