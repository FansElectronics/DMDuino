///////// animasi GAMBAR MASJID
void anim_masjid(int DrawAdd)
  {
    // check RunSelector
    if(!dwDo(DrawAdd)) return; 
    
    static uint8_t    y;
    static uint8_t    s; // 0=in, 1=out              
    static uint16_t   lsRn;
    uint16_t          Tmr = millis();

    if((Tmr-lsRn)>100) 
      { 
        if(s==0 and y<16){lsRn=Tmr;y++;}
        if(s==1 and y>0){lsRn=Tmr;y--;}
        
      }
    if((Tmr-lsRn)>10000 and y ==16) {s=1;}
    if (y==16)
    
      {
      
      }
    if (y == 0 and s==1) {dwDone(DrawAdd); s=0;}
    //fType(1);
   // masjida(y-8);
   // gambar();
    nama(16-y);
    masjida(16-y);
    masjidb(16-y);   
  
  }
//====================
void masjida(uint16_t y){
 static const uint8_t dall[] PROGMEM = {
       16,16,
B00100000,B00000001,
B00100000,B00000011,
B00100000,B00000111,
B00100000,B00001111,
B00100000,B00011111,
B01110000,B00011111,
B11111000,B00001111,
B01110000,B00000111,
B01110111,B11111111,
B01110000,B00000000,
B01110111,B11111111,
B01110111,B01111110,
B01110110,B00111100,
B01110110,B00111100,
B01110110,B00111100,
B01010110,B00111100};    
Disp.drawBitmap(1,y, dall); 
DoSwap = true;     
 }
void masjidb(uint16_t y){
 static const uint8_t eall[] PROGMEM = {
       16,16,
B00000000,B00001000,
B10000000,B00001000,
B11000000,B00001000,
B11100000,B00001000,
B11110000,B00001000,
B11110000,B00011100,
B11100000,B00111110,
B11000000,B00011100,
B11111111,B11011100,
B00000000,B00011100,
B11111111,B11011100,
B11111101,B11011100,
B01111000,B11011100,
B01111000,B11011100,
B01111000,B11011100,
B01111000,B11010100};    
Disp.drawBitmap(17,y, eall);
DoSwap = true;      
 }

void nama(uint16_t y){
  fType(1);
  dwCtr(34,y-1,"MASJID");
  fType(1);
  dwCtr(34,y+8,"Mujahid 212");
  DoSwap = true;
}

