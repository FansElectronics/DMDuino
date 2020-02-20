
void serialEvent()
  { 
    int prm_idx = 0;
    char bchar;

    bchar =Serial.peek();
    
    if ((bchar == 'C') or (bchar == 'N') or (bchar == 'S'))
      {
        while ((bchar != '\n')and(prm_idx < 150))
          {
          if(Serial.available())
            { 
              bchar = (char)Serial.read();
              CH_Prm[prm_idx]=bchar;
              prm_idx ++;
            //    digitalWrite (BUZZ, HIGH);
            //    delay(50);
            //    digitalWrite (BUZZ, LOW);
             Buzzer(1); 
            }
          }
        CH_Prm[prm_idx-1]='\0';
        LoadPrm();
      }
    else
      {  
        while(Serial.available()) {Serial.read();}
       // digitalWrite (BUZZ, LOW);
       Buzzer(0);
      }
  }
  
void LoadPrm()
  { 
    String BT_Param;
    uint16_t  eeAdd = 0;
    uint8_t   eePut = 0; 
    uint8_t   eeMax = 0;
    uint8_t   lenprm = strlen(CH_Prm)-3;

    // Put Char Data 
    if (CH_Prm[0]=='C')
      { if(CH_Prm[1]=='M' and CH_Prm[2]=='N')       {eeAdd = 55;  eeMax=74;}
        else if(CH_Prm[1]=='N' and CH_Prm[2]=='1')  {eeAdd = 130; eeMax=149;} 
        else if(CH_Prm[1]=='N' and CH_Prm[2]=='2')  {eeAdd = 280; eeMax=149;}  
        else if(CH_Prm[1]=='N' and CH_Prm[2]=='3')  {eeAdd = 430; eeMax=149;}
        else if(CH_Prm[1]=='S' and CH_Prm[2]=='M')  {eeAdd = 580; eeMax=149;}
        else if(CH_Prm[1]=='J' and CH_Prm[2]=='M')  {eeAdd = 730; eeMax=149;}

        int eeCount =0;        
        while((eeCount<= lenprm) and (eeCount < eeMax))
          {
            EEPROM.update(eeAdd+eeCount,CH_Prm[3+eeCount]);
            eeCount++;
          }
        EEPROM.update(eeAdd+eeCount,'\0');  
      }
      
    // Put Numeric Data
    else if (CH_Prm[0] =='N')
      {
        BT_Param = String(CH_Prm);
        
        
        if(BT_Param.substring(1,3).equals("LA"))       {eeAdd = 1 ; eePut=1;} 
        else if(BT_Param.substring(1,3).equals("LO"))  {eeAdd = 5 ; eePut=1;}  
        else if(BT_Param.substring(1,3).equals("AL"))  {eeAdd = 9 ; eePut=1;}  
        else if(BT_Param.substring(1,3).equals("TZ"))  {eeAdd = 13; eePut=1;}
        else if(BT_Param.substring(1,3).equals("MT"))  {eeAdd = 17; eePut=2;}
        else if(BT_Param.substring(1,3).equals("BL"))  {eeAdd = 18; eePut=2;}
        else if(BT_Param.substring(1,3).equals("IH"))  {eeAdd = 19; eePut=2;}
        else if(BT_Param.substring(1,3).equals("SO"))  {eeAdd = 20; eePut=2;}
        else if(BT_Param.substring(1,3).equals("JM"))  {eeAdd = 21; eePut=2;}
        else if(BT_Param.substring(1,3).equals("I1"))  {eeAdd = 22; eePut=2;}
        else if(BT_Param.substring(1,3).equals("I4"))  {eeAdd = 23; eePut=2;}
        else if(BT_Param.substring(1,3).equals("I5"))  {eeAdd = 24; eePut=2;}
        else if(BT_Param.substring(1,3).equals("I6"))  {eeAdd = 25; eePut=2;}
        else if(BT_Param.substring(1,3).equals("I7"))  {eeAdd = 26; eePut=2;}
        else if(BT_Param.substring(1,3).equals("BZ"))  {eeAdd = 27; eePut=2;}                
        else if(BT_Param.substring(1,3).equals("SI"))  {eeAdd = 28; eePut=2;}                
        else if(BT_Param.substring(1,3).equals("ST"))  {eeAdd = 29; eePut=2;}                
        else if(BT_Param.substring(1,3).equals("SU"))  {eeAdd = 30; eePut=2;}
        else if(BT_Param.substring(1,3).equals("CH"))  {eeAdd = 31; eePut=3;}                
        else if(BT_Param.substring(1,3).equals("IM"))  {eeAdd = 32; eePut=2;}
        else if(BT_Param.substring(1,3).equals("II"))  {eeAdd = 33; eePut=2;}
        else if(BT_Param.substring(1,3).equals("IS"))  {eeAdd = 34; eePut=2;}
        else if(BT_Param.substring(1,3).equals("IL"))  {eeAdd = 35; eePut=2;}
        else if(BT_Param.substring(1,3).equals("IA"))  {eeAdd = 36; eePut=2;}                
                       
        

        if(eePut == 1)
          {
          EEPROM.put(eeAdd,BT_Param.substring(3,BT_Param.length()).toFloat());
          }
        if(eePut == 2)
          {
          EEPROM.put(eeAdd,(uint8_t)BT_Param.substring(3,BT_Param.length()).toInt());
          }
        if(eePut == 3) // put uint8_t
          {
          EEPROM.put(eeAdd,(int8_t)BT_Param.substring(3,BT_Param.length()).toInt());
          }
  
      }
    else
    if (CH_Prm[0]=='S' and CH_Prm[1]=='D' and CH_Prm[2]=='T')  
      {
          BT_Param = String(CH_Prm);
          Clock.setClockMode(false);
          Clock.setDate(byte(BT_Param.substring(3,5).toInt()));
          Clock.setMonth(byte(BT_Param.substring(5,7).toInt()));
          Clock.setYear(byte(BT_Param.substring(7,9).toInt()));
          Clock.setHour(byte(BT_Param.substring(9,11).toInt()));
          Clock.setMinute(byte(BT_Param.substring(11,13).toInt()));
          Clock.setSecond(byte(BT_Param.substring(13,15).toInt()));       
          Clock.setDoW(byte(BT_Param.substring(15,16).toInt()));
      }
  // Get New/updeted parameter*/
  GetPrm();
  }
  
void GetPrm()
  {
//    Serial.println("Get parameter");
    // Get Parameter and check
    EEPROM.get(0, Prm);
    if(Prm.state != 212) //check value of Prm State .. set Default  
      {
        set_default_prm();
      }
    if (now.year() < 2018)//check date time .. less than 1 jan 2018 set Default
      {
        set_default_time();
      }
    Iqomah[1]=Prm.I1;
    Iqomah[4]=Prm.I4;
    Iqomah[5]=Prm.I5;
    Iqomah[6]=Prm.I6;
    Iqomah[7]=Prm.I7;
    // user New Parameter
    setBrightness(int(Prm.BL));
    update_All_data();
   // SendPrm();   
  }

void set_default_prm()
      {
        // Put Parameter start form addr 500
        Prm = (struct_param){212,-7.069757,109.325131,45,7,1,20,1,10,30,15,10,10,7,10,1,1,1,1};
        EEPROM.put(0,Prm);
        EEPROM.put(55, "Mujahid 212\0");
        EEPROM.put(130, "Info 1\0");
        EEPROM.put(280,"Info 2\0");
        EEPROM.put(430,"Info 3\0");
        EEPROM.put(580,"Ayo Sholat\0");
        EEPROM.put(730,"Ayo Jumatan\0");

      }

void set_default_time()
  {
    Clock.setClockMode(false);  // set to 24h
    Clock.setYear(byte(18));
    Clock.setMonth(byte(1));
    Clock.setDate(byte(1));
    Clock.setDoW(byte(2));
    Clock.setHour(byte(12));
    Clock.setMinute(byte(0));
    Clock.setSecond(byte(0));
    Clock.turnOffAlarm(1);
    Clock.turnOffAlarm(2);    
  }

// for debug
void SendPrm()
  {
   // char Info1[150];
    Serial.println(sizeof(Prm));
    Serial.print("state\t");  Serial.println(Prm.state);
    Serial.print("L_LA\t"); Serial.println(Prm.L_LA);
    Serial.print("L_LO\t"); Serial.println(Prm.L_LO);
    Serial.print("L_AL\t"); Serial.println(Prm.L_AL);
    Serial.print("L_TZ\t"); Serial.println(Prm.L_TZ);
    Serial.print("MT\t"); Serial.println(Prm.MT);
    Serial.print("BL\t"); Serial.println(Prm.BL);
    Serial.print("IH\t"); Serial.println(Prm.IH);
    Serial.print("SO\t"); Serial.println(Prm.SO);
    Serial.print("JM\t"); Serial.println(Prm.JM);
    Serial.print("I1\t"); Serial.println(Prm.I1);
    Serial.print("I4\t"); Serial.println(Prm.I4);
    Serial.print("I5\t"); Serial.println(Prm.I5);
    Serial.print("I6\t"); Serial.println(Prm.I6);
    Serial.print("I7\t"); Serial.println(Prm.I7);
    Serial.print("BZ\t"); Serial.println(Prm.BZ);
    Serial.print("SI\t"); Serial.println(Prm.SI);
    Serial.print("ST\t"); Serial.println(Prm.ST);
    Serial.print("SU\t"); Serial.println(Prm.SU);
    Serial.print(F("NIM  : ")); Serial.print(Prm.IM);Serial.print("\t");
    Serial.print(F("NII  : ")); Serial.print(Prm.II);Serial.print("\t");
    Serial.print(F("NIS  : ")); Serial.print(Prm.IS);Serial.print("\t");
    Serial.print(F("NIL  : ")); Serial.print(Prm.IL);Serial.print("\t");
    Serial.print(F("NIA  : ")); Serial.print(Prm.IA);Serial.print("\t");
    for(int i =0; i <=7;i++){
    Serial.print("iqomah"); Serial.print(i); Serial.print("\t"); Serial.println(Iqomah[i]);  
    }
  }
