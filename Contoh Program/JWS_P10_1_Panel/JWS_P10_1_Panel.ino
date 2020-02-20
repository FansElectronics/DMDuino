#include "DMD.h"
#include "TimerOne.h"
#include "Wire.h"
#include "Sodaq_DS3231.h"
#include "PrayerTimes.h"
#include "SystemFont5x7.h"
#include "huruf_kecilku.h"
#include "angka6x13.h"
#include "SPI.h"
char weekDay[][9] = {"SENIN, " , "SELASA, ", "RABU, ", "KAMIS, ", "JUM'AT, ", "SABTU, ", "AHAD, ",   }; // array hari, dihitung mulai dari senin, hari senin angka nya =0,
int Buz = A0;
int langkah;
int lama_tampilnya;
boolean Menu_Setting = false;
///////////////////////////////// Mendifinisikan Pin Tombol ////////////////////////////////////////
#define Jam_bUP A1                  // Tombol setting sesuaikan dengan PIN di arduino anda mana  klo ini terhubung dengan PIN 3 Digital
#define tombol_bOK A2             // Tombol OK sesuaikan dengan PIN di arduino anda mana  klo ini terhubung dengan PIN 5 Digital
#define Jam_bDN A3           //tombol setting   sesuaikan dengan PIN di arduino anda mana  klo ini terhubung dengan PIN 4 Digital

///////////////////koding ini untuk setting rtc sesuai dengan laptop//// /////
//year, month, date, hour, min, sec and week-day(starts from 0 and goes to 6)
//writing any non-existent time-data may interfere with normal operation of the RTC.
//Take care of week-day also.
//DateTime dt(2017, 5, 4, 15, 11, 0, 4);

/*
 * PIN YANG DISAMBUNG
 * Arduino              P-10
 * -D6          ->      -A
 * -D7          ->      -B
 * -D8          ->      -SCLK
 * -D9          ->      -OE
 * -D11         ->      -DATA
 * -D13         ->      -CLK
 * -GND         ->      -GND
 */

DMD dmd(1, 1); //untuk mengatur jumlah panel yang kamu pakai

double times[sizeof(TimeName) / sizeof(char*)];

void ScanDMD()
{
  dmd.scanDisplayBySPI();
}


void setup()
{

  char val; //pencacah nilai
  Serial.begin(9600); //setting bautrate serial

  pinMode(Buz, OUTPUT);//----pin 2 untuk alarm adzan maghrib ---hubungkan dengan buzzer
  pinMode(3, OUTPUT);//----pin e ralay TF S-W

  langkah = 0;
  rtc.begin();
  //rtc.setDateTime(dt); //Adjust date-time as defined 'dt' above (ini untuk setting jam)
  Wire.begin();
  Timer1.initialize( 500 );
  Timer1.attachInterrupt( ScanDMD );
  dmd.clearScreen( true );

  pinMode(tombol_bOK, INPUT_PULLUP);                                 // Mode Pin Sebagai Input dengan Pull Up Internal
  pinMode(Jam_bUP, INPUT_PULLUP);                                    // Mode Pin Sebagai Input dengan Pull Up Internal
  pinMode(Jam_bDN, INPUT_PULLUP);                                    // Mode Pin Sebagai Input dengan Pull Up Internal

  attachInterrupt(0, Setting, FALLING);
}
////////////////////////////////// Fungsi Looping/Pengulangan ///////////////////////////////////////
void loop() {

  dmd.setKecerahan(115);
  if (Menu_Setting ) {

    MenuSetting(); // Jika Tombol OK/Interrupt ditekan maka masuk menu setting Manual
  }
  mulai();
}


/////////////////////////////////// Interrupt Button Setting ////////////////////////////////////////
void Setting() {
  Menu_Setting = true;                                                // Aktifkan Menu Setting
}

////////////////////////////////////// Fungsi Menu Setting //////////
void MenuSetting() {
  char val; //pencacah nilai
  val = Serial.read();
  Serial.print(val);



  DateTime now = rtc.now();
  String Teks;
  int tgl = now.date();         //Tanggal
  int bln = now.month();        //Bulan
  int thn = now.year();         //Tahun
  int hours, minutes;        //jam dan menit jawdwal sholat
  int jame = now.hour();     //jam
  int menit_e = now.minute(); //menit

  int harin_e = harin_e;  //hari
  detachInterrupt(0);// Matikan interrupt "0"
  delay(500);

  /////////////////////////////////////// Setting Jam & Menit ///////

  int kasus = 0;
setTimes:
  val = Serial.read();

  // Setting Times (Jam & Menit)
  if (digitalRead(Jam_bUP) == LOW || val == 'H') {                               // Tombol Setting Menit
    delay(10); menit_e++;                                        // Delay Tombol & Tambah Nilai Menit
    Serial.print(val);
    if (menit_e >= 60) {
      menit_e = 0; // Batas Nilai Menit Lebih dari 59 Kembali ke 0
    }
    while (digitalRead(Jam_bUP) == LOW) {}                         // Kunci Tombol Setting Menit Sampai Lepas Tombol
  }
  if (digitalRead(Jam_bDN) == LOW || val == 'G') {                               // Tombol Setting Menit
    delay(10); jame++;
    Serial.print(val);
    // Delay Tombol & Tambah Nilai Jam
    if (jame >= 24) {
      jame = 0; // Batas Nilai Jam Lebih dari 23 Kembali ke 0
    }
    while (digitalRead(Jam_bDN) == LOW) {}                         // Kunci Tombol Setting Jam Sampai Lepas Tombol
  } if (val == 'B') {
    val = 'B';
    kasus = 1;
  } if (val == 'C') {
    val = 'C';
    kasus = 2;
  }
  if (val == 'D') {
    val = 'D';
    kasus = 3;
  }
  if (val == 'E') {
    val = 'E';
    kasus = 4;
  } if (val == 'X') {
    val = 'X';
    kasus = 7;
  }






setTgl:
  val = 'W' ;
  val = Serial.read();

  // Setting tanggal
  if (digitalRead(Jam_bUP) == LOW || val == 'I') {                               // Tombol Setting tanggal
    delay(10); tgl++;
    Serial.print(val);
    if (tgl >= 32) {
      tgl = 1; // Batas Nilai tgl Lebih dari 31 Kembali ke 1
    }
    while (digitalRead(Jam_bUP) == LOW) {}                         // Kunci Tombol Setting tgl Sampai Lepas Tombol
  }
  if (digitalRead(Jam_bDN) == LOW || val == 'J') {                               // Tombol Setting bln
    delay(10); bln++;                                          // Delay Tombol & Tambah Nilai bln
    if (bln >= 13) {
      bln = 1; // Batas Nilai bln Lebih dari 12 Kembali ke 1
    }
    while (digitalRead(Jam_bDN) == LOW) {}                         // Kunci Tombol Setting blnSampai Lepas Tombol
  } if (val == 'B') {
    val = 'B';
    kasus = 1;
  } if (val == 'C') {
    val = 'C';
    kasus = 2;
  }
  if (val == 'D') {
    val = 'D';
    kasus = 3;
  }
  if (val == 'E') {
    val = 'E';
    kasus = 4;
  } if (val == 'X') {
    val = 'X';
    kasus = 7;
  }


  // ///////=======setting thn==

setThn:
  val = 'W' ;
  val = Serial.read();

  // Setting thn
  if (digitalRead(Jam_bUP) == LOW || val == 'K') {                               // Tombol Setting thn
    delay(10); thn++;                                        // Delay Tombol & Tambah Nilai thn
    Serial.print(val);
    if (thn >= 9999) {
      thn = 0; // Batas Nilai Menit Lebih dari 9999 Kembali ke 0
    }
    while (digitalRead(Jam_bUP) == LOW) {}                         // Kunci Tombol Setting thn Sampai Lepas Tombol
  }
  if (digitalRead(Jam_bDN) == LOW || val == 'L') {                               // Tombol Setting thn
    delay(10); thn--;                                          // Delay Tombol & Tambah Nilai thn
    if (thn <= 0) {
      thn = 0; // Batas Nilai kurang dari 0 Kembali ke 0
    }
    while (digitalRead(Jam_bDN) == LOW) {}                         // Kunci Tombol Setting thn Sampai Lepas Tombol
  } if (val == 'B') {
    val = 'B';
    kasus = 1;
  } if (val == 'C') {
    val = 'C';
    kasus = 2;
  }
  if (val == 'D') {
    val = 'D';
    kasus = 3;
  }
  if (val == 'E') {
    val = 'E';
    kasus = 4;
  }
  if (val == 'X') {
    val = 'X';
    kasus = 7;
  }



  // =======setting Hari======
  //hitungan hari mulai dari 0,1,2,3,4,5,6 = senin, selasa, rabu, kamis, jumat, sabtu, minggu

setHari:
  val = 'W' ;
  val = Serial.read();


  // Setting Times hari
  if (digitalRead(Jam_bUP) == LOW || val == 'M') {                               // Tombol Setting hari
    harin_e = harin_e;
    delay(10);
    harin_e++;                                        // Delay Tombol & Tambah Nilai hari,
    if (harin_e >= 7) {
      harin_e = 0; // Batas Nilai Menit Lebih dari 6 Kembali ke 0
    }
    while (digitalRead(Jam_bUP) == LOW) {}                         // Kunci Tombol Setting hariSampai Lepas Tombol
  }
  if (digitalRead(Jam_bDN) == LOW || val == 'N') {                               // Tombol Setting hari
    harin_e = harin_e;
    delay(10);
    harin_e--;                                          // Delay Tombol & Tambah Nilai hari
    if (harin_e <= 0) {
      harin_e = 0; // Batas Nilai kurang dari 0 Kembali ke 0
    }
    while (digitalRead(Jam_bDN) == LOW) {}                         // Kunci Tombol Setting hari Sampai Lepas Tombol
  } if (val == 'B') {
    val = 'B';
    kasus = 1;
  } if (val == 'C') {
    val = 'C';
    kasus = 2;
  }
  if (val == 'D') {
    val = 'D';
    kasus = 3;
  }
  if (val == 'E') {
    val = 'E';
    kasus = 4;
  } if (val == 'X') {
    val = 'X';
    kasus = 7;
  }

  ///============Tombol OKE =======================
  val = Serial.read();
  Serial.print(val);
  if ((digitalRead(tombol_bOK) == LOW ) || (val == 'A')) {                            // Tombol Selesai Setting

    val = Serial.read();

    Serial.print("--tombol oke ditekan-- ");


    kasus = kasus + 1;
    dmd.clearScreen(true);                                                                 // Hapus Tampilan P10
    DateTime dt(thn, bln, tgl, jame, menit_e, 0, harin_e);
    // DateTime dt(2017, 5, 4, 15, 11, 0, 4);
    rtc.setDateTime(dt); //Adjust date-time as defined 'dt' above
    while (digitalRead(tombol_bOK) == LOW ) {}
    delay(100);

    //  ============================================kasus-kasus===================

  } if (kasus == 1 || val == 'B') {  //kasus seting jam

    dmd.clearScreen(true);
    dmd.selectFont(SystemFont5x7);
    dmd.drawString(0, 0, "set-J", 5, 0);
    String xjam = Konversi(jame) + ":" + Konversi(menit_e) ;
    int pjg = xjam.length() + 1;
    char sjam[pjg];
    xjam.toCharArray(sjam, pjg);
    dmd.drawString(0, 9, sjam, pjg, 0);
    delay (100);
    goto setTimes; //lari ke fungsi seting jam

  }
  if (kasus == 2 || val == 'C') { //kasus seting tanggal

    dmd.clearScreen(true);
    dmd.selectFont(SystemFont5x7);
    dmd.drawString(0, 0, "Tgl", 3, 0);
    String xjam = Konversi(tgl) + "/" + Konversi(bln) ;
    int pjg = xjam.length() + 1;
    char sjam[pjg];
    xjam.toCharArray(sjam, pjg);
    dmd.drawString(0, 9, sjam, pjg, 0);
    delay (100);
    goto setTgl;//lari ke fungsi setting tanggal

  } if (kasus == 3 || val == 'D') { ///kasus seting tahun

    dmd.clearScreen(true);
    dmd.selectFont(SystemFont5x7);
    dmd.drawString(0, 0, "Thn", 3, 0);
    String xjam = Konversi(thn)  ;
    int pjg = xjam.length() + 1;
    char sjam[pjg];
    xjam.toCharArray(sjam, pjg);
    dmd.drawString(0, 9, sjam, pjg, 0);
    delay (100);
    goto setThn; //lari ke fungsi setting tahun

  }

  if (kasus == 4 || val == 'E') { //kasus seting hari

    dmd.clearScreen(true);
    dmd.selectFont(SystemFont5x7);
    dmd.drawString(0, 0, "Hari", 4, 0);
    String xjam = Konversi(harin_e)  ;
    if (harin_e == 0) {
      xjam = "SEN";
      int pjg = xjam.length() + 1;
      char sjam[pjg];
      xjam.toCharArray(sjam, pjg);
      dmd.drawString(0, 9, sjam, pjg, 0);
    }  if (harin_e == 1) {
      xjam = "SEL";

      int pjg = xjam.length() + 1;
      char sjam[pjg];
      xjam.toCharArray(sjam, pjg);
      dmd.drawString(0, 9, sjam, pjg, 0);
    }
    if (harin_e == 2) {
      xjam = "RAB";

      int pjg = xjam.length() + 1;
      char sjam[pjg];
      xjam.toCharArray(sjam, pjg);
      dmd.drawString(0, 9, sjam, pjg, 0);
    } if (harin_e == 3) {
      xjam = "KAM";

      int pjg = xjam.length() + 1;
      char sjam[pjg];
      xjam.toCharArray(sjam, pjg);
      dmd.drawString(0, 9, sjam, pjg, 0);
    } if (harin_e == 4) {
      xjam = "JUM";

      int pjg = xjam.length() + 1;
      char sjam[pjg];
      xjam.toCharArray(sjam, pjg);
      dmd.drawString(0, 9, sjam, pjg, 0);
    } if (harin_e == 5) {
      xjam = "SAB";

      int pjg = xjam.length() + 1;
      char sjam[pjg];
      xjam.toCharArray(sjam, pjg);
      dmd.drawString(0, 9, sjam, pjg, 0);
    } if (harin_e == 6) {
      xjam = "MIN";

      int pjg = xjam.length() + 1;
      char sjam[pjg];
      xjam.toCharArray(sjam, pjg);
      dmd.drawString(0, 9, sjam, pjg, 0);
    }
    delay (100);
    goto setHari; //lari ke seting hari

  }


  if (kasus == 5 ) {     //kasus wis Rampung
    dmd.clearScreen(true);
    goto endSetting;
    delay(500);

  }
  if (kasus == 7) {     //keluar blututh
    dmd.clearScreen(true);                                                                 // Hapus Tampilan P10
    DateTime dt(thn, bln, tgl, jame, menit_e, 0, harin_e);
    // DateTime dt(2017, 5, 4, 15, 11, 0, 4);
    rtc.setDateTime(dt); //Adjust date-time as defined 'dt' above
    delay(100);
    dmd.clearScreen(true);
    goto endSetting;
    delay(500);

  }

endSetting:                                                         // Label End Setting
  attachInterrupt(0, Setting, FALLING);                               // Interrupt Tombol OK
  Menu_Setting = false;

  kasus = 0;


}



//////////////////////==========================Program Jam==============

int menite = 1; ///waktu iqomah lamanya
void mulai()
{
  char val; //pencacah nilai
  val = Serial.read();
  val = Serial.read();
  Serial.print(val);


  dmd.clearScreen( true );
  long mulai = millis();

  ///
  rtc.begin();
  DateTime now = rtc.now();
  String Teks;
  int tgl = now.date();         //Tanggal
  int bln = now.month();        //Bulan
  int thn = now.year();         //Tahun
  int hours, minutes;        //jam dan menit jawdwal sholat
  int jame = now.hour();     //jam
  int menit_e = now.minute(); //menit
  int harin_e = harin_e;  //hari
  ///
  if (digitalRead(tombol_bOK) == LOW || val == 'A') {
    val = 'A';


    MenuSetting(); // Jika Tombol OK/Interrupt ditekan maka masuk menu setting Manual
    delay(1000);
  }
  if (now.second() > 1) {
    ///////////////interupsi tombol menu-----------

    digitalWrite(3, LOW);//nyalakan relay power TF-SW

    /////////////////////
    ///koding adzan sholat ashar
    get_float_time_parts(times[3], hours, minutes);
    if (now.hour() == hours && now.minute() == minutes && now.second() > 1 ) {
      digitalWrite(2, HIGH);//alarm sholat
      delay(1000);
      digitalWrite(2, LOW);//alarm sholat
      delay(500);
      digitalWrite(2, HIGH);//alarm sholat
      delay(1000);
      digitalWrite(2, LOW);//alarm sholat
      delay(500);

      int lamanya;
      for (lamanya = 0; lamanya < 150; lamanya++) {
        lamanya = lamanya + 1;
        delay(1000);

        ///ASHAR
        dmd.selectFont(SystemFont5x7);
        dmd.clearScreen( true );
        Teks = "ADZAN ";                    //baris atas
        char pj = Teks.length() + 1;
        char    tampil[pj];
        Teks.toCharArray(tampil, pj);
        dmd.drawString(0, 0, tampil, pj, 0); //koordinat tampilan
        String iqomahx = "ASHAR" ;
        int panjang_iqomahx = iqomahx.length() + 1;
        char waktu_iqomahx[panjang_iqomahx];
        iqomahx.toCharArray(waktu_iqomahx, panjang_iqomahx);
        dmd.drawString(0, 9, waktu_iqomahx, panjang_iqomahx, 0);

        delay(1000);
        dmd.clearScreen( true );
      }
      //iqomah----------------------------------
      int langkah;
      int waktu_iqomah;
      int panjang_iqomah;
      int iqomah;
      dmd.clearScreen( true );
      dmd.clearScreen( true );
      dmd.drawString(0, 0, "IQOMH", 5, 0); //koordinat tampilan
      int tampil;
      int detik = 60, menit = 10;
      for (detik = 60; detik >= 0; detik--) {
        delay(1000);
        String iqomah = Konversi(menit) + ":" + Konversi(detik);
        int panjang_iqomah = iqomah.length() + 1;
        char waktu_iqomah[panjang_iqomah];
        iqomah.toCharArray(waktu_iqomah, panjang_iqomah);
        dmd.drawString(0, 9, waktu_iqomah, panjang_iqomah, 0);
        if (detik <= 0) {
          detik = 60;
          menit = menit - 1;
        }
        /////buzer sholat////
        if (menit <= 0 && detik == 7) {
          digitalWrite(2, HIGH);//alarm sholat
        } if (menit <= 0 && detik == 6) {
          digitalWrite(2, LOW);//alarm sholat
        } if (menit <= 0 && detik == 5) {
          digitalWrite(2, HIGH);//alarm sholat
        } if (menit <= 0 && detik == 4) {
          digitalWrite(2, LOW);//alarm sholat
        } if (menit <= 0 && detik == 3) {
          digitalWrite(2, HIGH);//alarm sholat
        } if (menit <= 0 && detik == 2) {
          digitalWrite(2, LOW);//alarm sholat

        }
        ///////////////

        if (menit <= 0 && detik <= 1) {
          dmd.clearScreen( true );
          for (tampil = 0; tampil < 500 ; tampil++) {
            menit = 0;
            detik = 0;
            dmd.drawString(0, 0, "SOLAT", 5, 0); //koordinat tampilan
            digitalWrite(3, HIGH);//matikan relay power TF-SW
            ///////////////////////
            now = rtc.now();
            String xjam = Konversi(now.hour()) + ":" + Konversi(now.minute()) ; //tampilan jam
            int pjg = xjam.length() + 1;
            char sjam[pjg];
            xjam.toCharArray(sjam, pjg);

            dmd.drawString(0, 9, sjam, pjg, 0);

            /////////////////////
            ///////////////////////
            delay (1000);
          }
        }
      }
      ///////////////

    }
    ///koding adzan sholat Maghrib
    get_float_time_parts(times[4], hours, minutes);
    if (now.hour() == hours && now.minute() == minutes && now.second() > 1 ) {
      digitalWrite(2, HIGH);//alarm sholat
      delay(1000);
      digitalWrite(2, LOW);//alarm sholat
      delay(500);
      digitalWrite(2, HIGH);//alarm sholat
      delay(1000);
      digitalWrite(2, LOW);//alarm sholat
      delay(500);
      int lamanya;
      for (lamanya = 0; lamanya < 150; lamanya++) {
        lamanya = lamanya + 1;
        delay(1000);

        ///MAGHRIB
        dmd.selectFont(SystemFont5x7);
        dmd.clearScreen( true );
        Teks = "ADZAN ";                    //baris atas
        char pj = Teks.length() + 1;
        char    tampil[pj];
        Teks.toCharArray(tampil, pj);
        dmd.drawString(0, 0, tampil, pj, 0); //koordinat tampilan
        String iqomahx = "MGHRB" ;
        int panjang_iqomahx = iqomahx.length() + 1;
        char waktu_iqomahx[panjang_iqomahx];
        iqomahx.toCharArray(waktu_iqomahx, panjang_iqomahx);
        dmd.drawString(0, 9, waktu_iqomahx, panjang_iqomahx, 0);

        delay(1000);
        dmd.clearScreen( true );
      }
      //iqomah----------------------------------
      int langkah;
      int waktu_iqomah;
      int panjang_iqomah;
      int iqomah;
      dmd.clearScreen( true );
      dmd.clearScreen( true );
      dmd.drawString(0, 0, "IQOMH", 5, 0); //koordinat tampilan
      int tampil;
      int detik = 60, menit = 10;
      for (detik = 60; detik >= 0; detik--) {
        delay(1000);
        String iqomah = Konversi(menit) + ":" + Konversi(detik);
        int panjang_iqomah = iqomah.length() + 1;
        char waktu_iqomah[panjang_iqomah];
        iqomah.toCharArray(waktu_iqomah, panjang_iqomah);
        dmd.drawString(0, 9, waktu_iqomah, panjang_iqomah, 0);
        if (detik <= 0) {
          detik = 60;
          menit = menit - 1;
        }
        /////buzer sholat////
        if (menit <= 0 && detik == 7) {
          digitalWrite(2, HIGH);//alarm sholat
        } if (menit <= 0 && detik == 6) {
          digitalWrite(2, LOW);//alarm sholat
        } if (menit <= 0 && detik == 5) {
          digitalWrite(2, HIGH);//alarm sholat
        } if (menit <= 0 && detik == 4) {
          digitalWrite(2, LOW);//alarm sholat
        } if (menit <= 0 && detik == 3) {
          digitalWrite(2, HIGH);//alarm sholat
        } if (menit <= 0 && detik == 2) {
          digitalWrite(2, LOW);//alarm sholat

        }
        ///////////////

        if (menit <= 0 && detik <= 1) {
          dmd.clearScreen( true );
          for (tampil = 0; tampil < 500 ; tampil++) {
            menit = 0;
            detik = 0;
            dmd.drawString(0, 0, "SOLAT", 5, 0); //koordinat tampilan
            digitalWrite(3, HIGH);//matikan relay power TF-SW
            ///////////////////////
            now = rtc.now();
            String xjam = Konversi(now.hour()) + ":" + Konversi(now.minute()) ; //tampilan jam
            int pjg = xjam.length() + 1;
            char sjam[pjg];
            xjam.toCharArray(sjam, pjg);

            dmd.drawString(0, 9, sjam, pjg, 0);

            /////////////////////
            ///////////////////////
            delay (1000);
          }
        }
      }
      ///////////////

    }
    ///koding adzan sholat isya
    get_float_time_parts(times[6], hours, minutes);
    if (now.hour() == hours && now.minute() == minutes && now.second() > 1) {
      digitalWrite(2, HIGH);//alarm sholat
      delay(1000);
      digitalWrite(2, LOW);//alarm sholat
      delay(500);
      digitalWrite(2, HIGH);//alarm sholat
      delay(1000);
      digitalWrite(2, LOW);//alarm sholat
      delay(500);
      int lamanya;
      for (lamanya = 0; lamanya < 150; lamanya++) {
        lamanya = lamanya + 1;
        delay(1000);

        ///ISYA
        dmd.selectFont(SystemFont5x7);
        dmd.clearScreen( true );
        Teks = "ADZAN ";                    //baris atas
        char pj = Teks.length() + 1;
        char    tampil[pj];
        Teks.toCharArray(tampil, pj);
        dmd.drawString(0, 0, tampil, pj, 0); //koordinat tampilan
        String iqomahx = "ISYA'" ;
        int panjang_iqomahx = iqomahx.length() + 1;
        char waktu_iqomahx[panjang_iqomahx];
        iqomahx.toCharArray(waktu_iqomahx, panjang_iqomahx);
        dmd.drawString(0, 9, waktu_iqomahx, panjang_iqomahx, 0);

        delay(1000);
        dmd.clearScreen( true );
      }
      //iqomah----------------------------------
      int langkah;
      int waktu_iqomah;
      int panjang_iqomah;
      int iqomah;
      dmd.clearScreen( true );
      dmd.clearScreen( true );
      dmd.drawString(0, 0, "IQOMH", 5, 0); //koordinat tampilan
      int tampil;
      int detik = 60, menit = 10;
      for (detik = 60; detik >= 0; detik--) {
        delay(1000);
        String iqomah = Konversi(menit) + ":" + Konversi(detik);
        int panjang_iqomah = iqomah.length() + 1;
        char waktu_iqomah[panjang_iqomah];
        iqomah.toCharArray(waktu_iqomah, panjang_iqomah);
        dmd.drawString(0, 9, waktu_iqomah, panjang_iqomah, 0);
        if (detik <= 0) {
          detik = 60;
          menit = menit - 1;
        }
        /////buzer sholat////
        if (menit <= 0 && detik == 7) {
          digitalWrite(2, HIGH);//alarm sholat
        } if (menit <= 0 && detik == 6) {
          digitalWrite(2, LOW);//alarm sholat
        } if (menit <= 0 && detik == 5) {
          digitalWrite(2, HIGH);//alarm sholat
        } if (menit <= 0 && detik == 4) {
          digitalWrite(2, LOW);//alarm sholat
        } if (menit <= 0 && detik == 3) {
          digitalWrite(2, HIGH);//alarm sholat
        } if (menit <= 0 && detik == 2) {
          digitalWrite(2, LOW);//alarm sholat

        }
        ///////////////

        if (menit <= 0 && detik <= 1) {
          dmd.clearScreen( true );
          for (tampil = 0; tampil < 500 ; tampil++) {
            menit = 0;
            detik = 0;
            dmd.drawString(0, 0, "SOLAT", 5, 0); //koordinat tampilan
            digitalWrite(3, HIGH);//matikan relay power TF-SW
            ///////////////////////
            now = rtc.now();
            String xjam = Konversi(now.hour()) + ":" + Konversi(now.minute()) ; //tampilan jam
            int pjg = xjam.length() + 1;
            char sjam[pjg];
            xjam.toCharArray(sjam, pjg);

            dmd.drawString(0, 9, sjam, pjg, 0);

            /////////////////////
            ///////////////////////
            delay (1000);
          }
        }
      }
      ///////////////

    }
    ///koding adzan sholat jumattttt/////
    int harin_e = now.dayOfWeek();
    get_float_time_parts(times[2], hours, minutes);
    if ((now.hour() == hours && now.minute() == minutes && harin_e == 4 && now.second() > 1 ))

    {
      digitalWrite(2, HIGH);//alarm sholat
      delay(1000);
      digitalWrite(2, LOW);//alarm sholat
      delay(500);
      digitalWrite(2, HIGH);//alarm sholat
      delay(1000);
      digitalWrite(2, LOW);//alarm sholat
      delay(500);

      int lamanya;
      for (lamanya = 0; lamanya < 2700; lamanya++) {
        lamanya = lamanya + 1;
        delay(1000);
        dmd.drawString(0, 0, "Jumat", 5, 0); //koordinat tampilan
        digitalWrite(3, HIGH);//matikan relay power TF-SW
        ///////////////////////
        now = rtc.now();
        String xjam = Konversi(now.hour()) + ":" + Konversi(now.minute()) ; //tampilan jam
        int pjg = xjam.length() + 1;
        char sjam[pjg];
        xjam.toCharArray(sjam, pjg);
        dmd.drawString(0, 9, sjam, pjg, 0);


      }
    }



    ///koding adzan sholat DZUHUR

    get_float_time_parts(times[2], hours, minutes);
    if ((now.hour() == hours && now.minute() == minutes && harin_e != 4 && now.second() > 1 ))

    {
      digitalWrite(2, HIGH);//alarm sholat
      delay(1000);
      digitalWrite(2, LOW);//alarm sholat
      delay(500);
      digitalWrite(2, HIGH);//alarm sholat
      delay(1000);
      digitalWrite(2, LOW);//alarm sholat
      delay(500);
      int lamanya;
      for (lamanya = 0; lamanya < 150; lamanya++) {
        lamanya = lamanya + 1;
        delay(1000);

        ///DZUHUR
        dmd.selectFont(SystemFont5x7);
        dmd.clearScreen( true );
        Teks = "ADZAN ";                    //baris atas
        char pj = Teks.length() + 1;
        char    tampil[pj];
        Teks.toCharArray(tampil, pj);
        dmd.drawString(0, 0, tampil, pj, 0); //koordinat tampilan
        String iqomahx = "DZUHR" ;
        int panjang_iqomahx = iqomahx.length() + 1;
        char waktu_iqomahx[panjang_iqomahx];
        iqomahx.toCharArray(waktu_iqomahx, panjang_iqomahx);
        dmd.drawString(0, 9, waktu_iqomahx, panjang_iqomahx, 0);

        delay(1000);
        dmd.clearScreen( true );
      }
      //iqomah----------------------------------
      int langkah;
      int waktu_iqomah;
      int panjang_iqomah;
      int iqomah;
      dmd.clearScreen( true );
      dmd.clearScreen( true );
      dmd.drawString(0, 0, "IQOMH", 5, 0); //koordinat tampilan
      int tampil;
      int detik = 60, menit = 10;
      for (detik = 60; detik >= 0; detik--) {
        delay(1000);
        String iqomah = Konversi(menit) + ":" + Konversi(detik);
        int panjang_iqomah = iqomah.length() + 1;
        char waktu_iqomah[panjang_iqomah];
        iqomah.toCharArray(waktu_iqomah, panjang_iqomah);
        dmd.drawString(0, 9, waktu_iqomah, panjang_iqomah, 0);
        if (detik <= 0) {
          detik = 60;
          menit = menit - 1;
        }
        /////buzer sholat////
        if (menit <= 0 && detik == 7) {
          digitalWrite(2, HIGH);//alarm sholat
        } if (menit <= 0 && detik == 6) {
          digitalWrite(2, LOW);//alarm sholat
        } if (menit <= 0 && detik == 5) {
          digitalWrite(2, HIGH);//alarm sholat
        } if (menit <= 0 && detik == 4) {
          digitalWrite(2, LOW);//alarm sholat
        } if (menit <= 0 && detik == 3) {
          digitalWrite(2, HIGH);//alarm sholat
        } if (menit <= 0 && detik == 2) {
          digitalWrite(2, LOW);//alarm sholat

        }
        ///////////////

        if (menit <= 0 && detik <= 1) {
          dmd.clearScreen( true );
          for (tampil = 0; tampil < 500 ; tampil++) {
            menit = 0;
            detik = 0;
            dmd.drawString(0, 0, "SOLAT", 5, 0); //koordinat tampilan
            digitalWrite(3, HIGH);//matikan relay power TF-SW
            ///////////////////////
            now = rtc.now();
            String xjam = Konversi(now.hour()) + ":" + Konversi(now.minute()) ; //tampilan jam
            int pjg = xjam.length() + 1;
            char sjam[pjg];
            xjam.toCharArray(sjam, pjg);

            dmd.drawString(0, 9, sjam, pjg, 0);

            /////////////////////
            ///////////////////////
            delay (1000);
          }
        }
      }
      ///////////////


    }



    ///koding adzan sholat SUBUH
    get_float_time_parts(times[0], hours, minutes);
    if (now.hour() == hours && now.minute() == minutes && now.second() > 1 ) {
      digitalWrite(2, HIGH);//alarm sholat
      delay(1000);
      digitalWrite(2, LOW);//alarm sholat
      delay(500);
      digitalWrite(2, HIGH);//alarm sholat
      delay(1000);
      digitalWrite(2, LOW);//alarm sholat
      delay(500);
      int lamanya;
      for (lamanya = 0; lamanya < 150; lamanya++) {
        lamanya = lamanya + 1;
        delay(1000);

        ///subuh
        dmd.selectFont(SystemFont5x7);
        dmd.clearScreen( true );
        Teks = "ADZAN ";                    //baris atas
        char pj = Teks.length() + 1;
        char    tampil[pj];
        Teks.toCharArray(tampil, pj);
        dmd.drawString(0, 0, tampil, pj, 0); //koordinat tampilan
        String iqomahx = "SUBUH" ;
        int panjang_iqomahx = iqomahx.length() + 1;
        char waktu_iqomahx[panjang_iqomahx];
        iqomahx.toCharArray(waktu_iqomahx, panjang_iqomahx);
        dmd.drawString(0, 9, waktu_iqomahx, panjang_iqomahx, 0);

        delay(1000);
        dmd.clearScreen( true );
      }
      //iqomah----------------------------------
      int langkah;
      int waktu_iqomah;
      int panjang_iqomah;
      int iqomah;
      dmd.clearScreen( true );
      dmd.clearScreen( true );
      dmd.drawString(0, 0, "IQOMH", 5, 0); //koordinat tampilan
      int tampil;
      int detik = 60, menit = 10;
      for (detik = 60; detik >= 0; detik--) {
        delay(1000);
        String iqomah = Konversi(menit) + ":" + Konversi(detik);
        int panjang_iqomah = iqomah.length() + 1;
        char waktu_iqomah[panjang_iqomah];
        iqomah.toCharArray(waktu_iqomah, panjang_iqomah);
        dmd.drawString(0, 9, waktu_iqomah, panjang_iqomah, 0);
        if (detik <= 0) {
          detik = 60;
          menit = menit - 1;
        }
        /////buzer sholat////
        if (menit <= 0 && detik == 7) {
          digitalWrite(Buz, HIGH);//alarm sholat
        } if (menit <= 0 && detik == 6) {
          digitalWrite(Buz, LOW);//alarm sholat
        } if (menit <= 0 && detik == 5) {
          digitalWrite(Buz, HIGH);//alarm sholat
        } if (menit <= 0 && detik == 4) {
          digitalWrite(Buz, LOW);//alarm sholat
        } if (menit <= 0 && detik == 3) {
          digitalWrite(Buz, HIGH);//alarm sholat
        } if (menit <= 0 && detik == 2) {
          digitalWrite(Buz, LOW);//alarm sholat

        }
        ///////////////

        if (menit <= 0 && detik <= 1) {
          dmd.clearScreen( true );
          for (tampil = 0; tampil < 500 ; tampil++) {
            menit = 0;
            detik = 0;
            dmd.drawString(0, 0, "SOLAT", 5, 0); //koordinat tampilan
            digitalWrite(3, HIGH);//matikan relay power TF-SW
            ///////////////////////
            now = rtc.now();
            String xjam = Konversi(now.hour()) + ":" + Konversi(now.minute()) ; //tampilan jam
            int pjg = xjam.length() + 1;
            char sjam[pjg];
            xjam.toCharArray(sjam, pjg);

            dmd.drawString(0, 9, sjam, pjg, 0);

            /////////////////////
            ///////////////////////
            delay (1000);
          }
        }
      }
    }
    ///////////////



    DateTime now = rtc.now();
    if (now.second() > 10) {

      String Teks;

      ///================pengaturan koordinat-gunakan gps android untuk menentukan posisi anda=================
      double lintang = -7.7808;  //Latitude
      double bujur = 110.397;   //Longitude
      int Z = 7 ;                   //Zona Waktu GMT WIB biasanya 7


      int tgl = now.date();         //Tanggal
      int bln = now.month();        //Bulan
      int thn = now.year();         //Tahun
      int hours1, minutes1, hours2, minutes2, hours3, minutes3, hours4, minutes4, hours5, minutes5, hours6, minutes6, hours7, minutes7; //jam sholat dan  menit sholat

      long mulai = millis();

      set_calc_method(ISNA);        //Methode perhitungan mengikuti ISNA
      set_asr_method(Shafii);       //Pendapat Imam Syafi'i
      set_high_lats_adjust_method(AngleBased);
      set_fajr_angle(20);           //Sudut Waktu Subuh
      set_isha_angle(18);           ////Sudut Waktu Isya
      get_prayer_times(thn, bln, tgl, lintang, bujur, Z, times);

      ///////////////interupsi tombol menu-----------

      char val; //pencacah nilai
      if (digitalRead(tombol_bOK) == LOW || val == 'A') {
        val = 'A';

        MenuSetting(); // Jika Tombol OK/Interrupt ditekan maka masuk menu setting Manual

      }
      /////////////////////

      ///jam--besar///
      dmd.clearScreen( true );
      dmd.selectFont(angka6x13);
      int menit_e = now.minute();
      int jame = now.hour();
      int detik_e = now.second();
      String xjam = Konversi(jame) ; //tampilan jam
      int pjg = xjam.length() + 1;
      char sjam[pjg];
      xjam.toCharArray(sjam, pjg);
      dmd.drawString(1, 0, sjam, pjg, 0);

      /////menit///
      String xxjam = Konversi(menit_e) ; //tampilan menit
      int xpjg = xxjam.length() + 1;
      char xsjam[xpjg];
      xxjam.toCharArray(xsjam, xpjg);
      dmd.drawString(18, 0, xsjam, xpjg, 0);

      ///titik dua :

      ///


      String hariku1 = weekDay[now.dayOfWeek()] ;
      int dowo1 = hariku1.length() + 1;
      char detikanku1[dowo1];
      hariku1.toCharArray(detikanku1, dowo1);
      dmd.drawString(35, 0, detikanku1, dowo1, 0);

      ////

      dmd.selectFont(SystemFont5x7);
      dmd.drawChar( 14,  4, ':', GRAPHICS_NOR   );   // clock colon overlay on
      delay( 1000 );

      dmd.drawChar( 14, 4, ':', GRAPHICS_OR   );   // clock colon overlay off
      delay( 1000 );
      dmd.drawChar( 14,  4, ':', GRAPHICS_NOR   );   // clock colon overlay on
      delay( 1000 );

      dmd.drawChar( 14, 4, ':', GRAPHICS_OR   );   // clock colon overlay off
      delay( 1000 );
      dmd.drawChar( 14,  4, ':', GRAPHICS_NOR   );   // clock colon overlay on
      delay( 1000 );

      dmd.drawChar( 14, 4, ':', GRAPHICS_OR   );   // clock colon overlay off
      delay( 1000 );

      dmd.drawChar( 14,  4, ':', GRAPHICS_NOR   );   // clock colon overlay on
      delay( 1000 );

      dmd.drawChar( 14, 4, ':', GRAPHICS_OR   );   // clock colon overlay off
      delay( 1000 );
      dmd.drawChar( 14,  4, ':', GRAPHICS_NOR   );   // clock colon overlay on
      delay( 1000 );

      dmd.drawChar( 14, 4, ':', GRAPHICS_OR   );   // clock colon overlay off
      delay( 1000 );
      dmd.drawChar( 14,  4, ':', GRAPHICS_NOR   );   // clock colon overlay on
      delay( 1000 );

      dmd.drawChar( 14, 4, ':', GRAPHICS_OR   );   // clock colon overlay off
      delay( 1000 );





      ///////////////interupsi tombol menu-----------


      if (digitalRead(tombol_bOK) == LOW || val == 'A') {
        val = 'A';

        MenuSetting(); // Jika Tombol OK/Interrupt ditekan maka masuk menu setting Manual

      }




      ///////////////interupsi tombol menu-----------


      if (digitalRead(tombol_bOK) == LOW || val == 'A') {
        val = 'A';

        MenuSetting(); // Jika Tombol OK/Interrupt ditekan maka masuk menu setting Manual

      }
      /////////////////////
    }


    ////runing teks jam diatas----//
    dmd.clearScreen( true );
    String Teks;
    int tgl = now.date();         //Tanggal
    int bln = now.month();        //Bulan
    int thn = now.year();         //Tahun
    int hours0, minutes0, hours1, minutes1, hours2, minutes2, hours3, minutes3, hours4, minutes4, hours5, minutes5, hours6, minutes6, hours7, minutes7; //jam sholat dan  menit sholat

    int jame = now.hour();     //jam
    int menit_e = now.minute(); //menit
    int detik_e = now.second(); //detik

    delay(100);
    detachInterrupt(0);// Matikan interrupt "0"

    ////   // Tampilkan hari runnning teks
  } if (now.second() > 30) {

    ///
    ///jam--besar///
    dmd.clearScreen( true );

    int menit_e = now.minute();
    int jame = now.hour();
    int detik_e = now.second();
    String xjam = Konversi(jame) ; //tampilan jam
    int pjg = xjam.length() + 1;
    char sjam[pjg];
    xjam.toCharArray(sjam, pjg);
    dmd.drawString(0, 0, sjam, pjg, 0);

    /////menit///
    String xxjam = Konversi(menit_e) ; //tampilan menit
    int xpjg = xxjam.length() + 1;
    char xsjam[xpjg];
    xxjam.toCharArray(xsjam, xpjg);
    dmd.drawString(20, 0, xsjam, xpjg, 0);
    ///titik dua

    String xxxjam = ":" ; //tampilan titik dua
    int xxpjg = xxxjam.length() + 1;
    char xxsjam[xxpjg];
    xxxjam.toCharArray(xxsjam, xxpjg);
    dmd.drawString(14, 0, xxsjam, xxpjg, 0);





    ///////////////interupsi tombol menu-----------

    char val; //pencacah nilai
    if (digitalRead(tombol_bOK) == LOW || val == 'A') {
      val = 'A';

      MenuSetting(); // Jika Tombol OK/Interrupt ditekan maka masuk menu setting Manual

    }

    int hours0, minutes0, hours1, minutes1, hours2, minutes2, hours3, minutes3, hours4, minutes4, hours5, minutes5, hours6, minutes6, hours7, minutes7; //jam sholat dan  menit sholat
    get_float_time_parts(times[0], hours0, minutes0);

    if ((minutes0 >= 1) && (minutes0 < 10)) {
      minutes0 = 50 + minutes0;
      hours0--;
    }
    if (minutes0 == 00) {
      minutes0 = 50;
      hours0--;

    }

    else {
      minutes0 = minutes0 - 10 ;
    }
    get_float_time_parts(times[0], hours1, minutes1);//subuh
    get_float_time_parts(times[2], hours2, minutes2);//dzuhur
    get_float_time_parts(times[3], hours3, minutes3);//ashar
    get_float_time_parts(times[4], hours4, minutes4);//maghrib
    get_float_time_parts(times[5], hours5, minutes5);//mbuh iki opo
    get_float_time_parts(times[6], hours6, minutes6);//isya
    Teks = weekDay[now.dayOfWeek()] + Konversi(now.date()) + "-" + Konversi(now.month()) + "-" + Konversi(now.year()) + " JADWAL SHOLAT : "+"  IMSAK:" + Konversi(hours0) + ":" + Konversi(minutes0) + "  SUBUH:" + Konversi(hours1) + ":" + Konversi(minutes1)
           + "  DZUHUR:" + Konversi(hours2) + ":" + Konversi(minutes2) + "  ASHAR:" + Konversi(hours3) + ":" + Konversi(minutes3)
           + "  MAGHRIB:" + Konversi(hours4) + ":" + Konversi(minutes4) + "  ISYA':" + Konversi(hours6) + ":" + Konversi(minutes6) ;

    int kecepatan;
    kecepatan = 70;     //kecepatan runing teks
    int pj = Teks.length() + 1;
    char tampil[pj];
    Teks.toCharArray(tampil, pj);
    dmd.selectFont(SystemFont5x7);
    dmd.drawMarquee(tampil, pj, 32, 9);
    ///////////////interupsi tombol menu-----------

    val; //pencacah nilai
    if (digitalRead(tombol_bOK) == LOW || val == 'A') {
      val = 'A';

      MenuSetting(); // Jika Tombol OK/Interrupt ditekan maka masuk menu setting Manual

    }
    /////////////////////


    long timer = millis();
    boolean ret = false;
    while (!ret) {
      if ((timer + kecepatan) < millis()) {
        ret = dmd.stepSplitMarquee(8, 15, 0); ///dianimasikan baris 8 sampai 15, sampai kolom 0
        timer = millis();




        ///TOMBOL SET JAM//
        if (digitalRead(tombol_bOK) == LOW) {
          MenuSetting(); // Jika Tombol OK/Interrupt ditekan maka masuk menu setting Manual



        }
      }
    }
  }
}

//----------------------------------------------------------------------
///konversi angka agar ada nol didepannya jika diawah 10

String Konversi(int sInput) {
  if (sInput < 10)
  {
    return"0" + String(sInput);
  }
  else
  {
    return String(sInput);
  }
}

