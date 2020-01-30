#include <SPI.h>
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();

 int  preklop, odber;
 char tftvyroba[8], tftodber[9], tftSOCP[6];
 
void setupTFT() { /***********************  SETUP TFT *********************************/
 tft.init(); tft.setRotation(3); /*tft.setFreeFont(&FreeSerif9pt7b);*/ tft.setTextSize(2); tft.setTextDatum(MC_DATUM);  // Nastaveni velikosti a geometrie pisma
      tft.fillScreen(TFT_BLACK);  tft.setTextColor(TFT_RED,TFT_BLACK);
   tft.drawString(verze,  tft.width() / 2, tft.height() / 4 );    tft.drawString(dat,  tft.width() / 2, tft.height() / 2 );
   tft.drawString("connect to Wi-Fi",  tft.width() / 2, tft.height()/2 + 25 );

// tft.setTextSize(2);    tft.setTextColor(ILI9341_WHITE,ILI9341_BLACK);
//// tft.setFont(&TomThumb);  verze.toCharArray(ver,16);
//tft.setCursor(35, 100);  tft.print(verze);

// Ubat = "Ubat : " + String(U) + " V"; Ichar = "Ichar : " + String(I) + " A";  sSOC = "SOC : " + String(SOC,0) + " %";
}/*===================================================================================*/

void connectTFT() { /***********************  connectTFT *****************************************************/   
               tft.setTextSize(2);  
           if ( wifiOK == 1 ) {  tft.setCursor(0, 180); tft.setTextColor(TFT_GREEN,TFT_BLACK);   ips = "Wi-Fi O.K. IP :" + ipa; tft.print(ips);   
                              }
                         else {  tft.setCursor(20, 180);  switch (preklop) { case 0: tft.setTextColor(TFT_RED,TFT_BLACK);     tft.print("Connect to Wi-Fi");   preklop = 1;  break;     
                                                                             case 1: tft.setTextColor(TFT_ORANGE,TFT_BLACK);  tft.print("Connect to Wi-Fi");   preklop = 0;  break; }
                              }  
}/*==========================================================================================================*/

void doTFTco() {
tft.setTextSize(2); tft.setTextColor(TFT_YELLOW,TFT_BLACK); tft.setCursor(5, 70); tft.print(brzda);  
}

void doTFT() { /***********************  TFT  *********************************/

tft.setTextSize(2); tft.setTextColor(TFT_BLUE,TFT_BLACK);
tft.setCursor(0, 10); tft.print(dnes);tft.setTextColor(TFT_CYAN,TFT_BLACK); tft.print(datum); tft.print(" "); tft.println(cas);       

tft.setTextSize(3);
tft.setTextColor(TFT_LIGHTGREY,TFT_BLACK);    //snprintf(tftvyr_den, sizeof(tftvyr_den), " %d", vyr_den); 
    tft.setCursor(5, 110); tft.print(vyr_den);   tft.print(" kW ");

odber = POWERTOTAL;
tft.setTextSize(4);  //tft.setFont(&FreeSerif18pt7b);  
//dtostrf((POWERTOTAL), 1,1, tftodber);
tft.setTextColor(TFT_WHITE,TFT_BLACK);    snprintf(tftodber, sizeof(tftodber), " %d W", odber); 
    tft.setCursor(50, 60); tft.print(tftodber);

tft.setTextColor(TFT_GREEN,TFT_BLACK);    snprintf(tftSOCP, sizeof(tftSOCP), " %d", SOCP); 
    tft.setCursor(180, 110); tft.print(tftSOCP);   tft.print(" %");  
    
  tft.setTextSize(6);  //tft.setFont(&FreeSerif18pt7b); 
if (vyroba==     0) {tft.setTextColor(TFT_RED,TFT_BLACK);        snprintf(tftvyroba, sizeof(tftvyroba), "   %d W", vyroba); }
if (vyroba<      0) {tft.setTextColor(TFT_RED,TFT_BLACK);        snprintf(tftvyroba, sizeof(tftvyroba), "  %d W", vyroba); }
if (vyroba>      0) {tft.setTextColor(TFT_LIGHTGREY,TFT_BLACK);  snprintf(tftvyroba, sizeof(tftvyroba), "   %d W", vyroba); }
if (vyroba>   9.99) {tft.setTextColor(TFT_PINK,TFT_BLACK);       snprintf(tftvyroba, sizeof(tftvyroba), "  %d W", vyroba); }
if (vyroba>  99.99) {tft.setTextColor(TFT_ORANGE,TFT_BLACK);     snprintf(tftvyroba, sizeof(tftvyroba), " %d W", vyroba); }
if (vyroba> 999.99) {tft.setTextColor(TFT_YELLOW,TFT_BLACK);     snprintf(tftvyroba, sizeof(tftvyroba), "%d W", vyroba); } 
    tft.setCursor(70, 170); tft.print(tftvyroba);// tft.setCursor(30, 70); tft.print(tftvyroba);//

   
tft.setTextSize(2);    tft.setTextColor(TFT_RED,TFT_BLACK); tft.setCursor(80, 240);  tft.print(verze);   
}/*====================================================================================*/




//  // Original Adafruit_GFX "Free Fonts"
//  #include <Fonts/GFXFF/TomThumb.h>  // TT1
//
//  #include <Fonts/GFXFF/FreeMono9pt7b.h>  // FF1 or FM9
//  #include <Fonts/GFXFF/FreeMono12pt7b.h> // FF2 or FM12
//  #include <Fonts/GFXFF/FreeMono18pt7b.h> // FF3 or FM18
//  #include <Fonts/GFXFF/FreeMono24pt7b.h> // FF4 or FM24
//
//  #include <Fonts/GFXFF/FreeMonoOblique9pt7b.h>  // FF5 or FMO9
//  #include <Fonts/GFXFF/FreeMonoOblique12pt7b.h> // FF6 or FMO12
//  #include <Fonts/GFXFF/FreeMonoOblique18pt7b.h> // FF7 or FMO18
//  #include <Fonts/GFXFF/FreeMonoOblique24pt7b.h> // FF8 or FMO24
//  
//  #include <Fonts/GFXFF/FreeMonoBold9pt7b.h>  // FF9  or FMB9
//  #include <Fonts/GFXFF/FreeMonoBold12pt7b.h> // FF10 or FMB12
//  #include <Fonts/GFXFF/FreeMonoBold18pt7b.h> // FF11 or FMB18
//  #include <Fonts/GFXFF/FreeMonoBold24pt7b.h> // FF12 or FMB24
//  
//  #include <Fonts/GFXFF/FreeMonoBoldOblique9pt7b.h>  // FF13 or FMBO9
//  #include <Fonts/GFXFF/FreeMonoBoldOblique12pt7b.h> // FF14 or FMBO12
//  #include <Fonts/GFXFF/FreeMonoBoldOblique18pt7b.h> // FF15 or FMBO18
//  #include <Fonts/GFXFF/FreeMonoBoldOblique24pt7b.h> // FF16 or FMBO24
//  
//  // Sans serif fonts
//  #include <Fonts/GFXFF/FreeSans9pt7b.h>  // FF17 or FSS9
//  #include <Fonts/GFXFF/FreeSans12pt7b.h> // FF18 or FSS12
//  #include <Fonts/GFXFF/FreeSans18pt7b.h> // FF19 or FSS18
//  #include <Fonts/GFXFF/FreeSans24pt7b.h> // FF20 or FSS24
//  
//  #include <Fonts/GFXFF/FreeSansOblique9pt7b.h>  // FF21 or FSSO9
//  #include <Fonts/GFXFF/FreeSansOblique12pt7b.h> // FF22 or FSSO12
//  #include <Fonts/GFXFF/FreeSansOblique18pt7b.h> // FF23 or FSSO18
//  #include <Fonts/GFXFF/FreeSansOblique24pt7b.h> // FF24 or FSSO24
//  
//  #include <Fonts/GFXFF/FreeSansBold9pt7b.h>  // FF25 or FSSB9
//  #include <Fonts/GFXFF/FreeSansBold12pt7b.h> // FF26 or FSSB12
//  #include <Fonts/GFXFF/FreeSansBold18pt7b.h> // FF27 or FSSB18
//  #include <Fonts/GFXFF/FreeSansBold24pt7b.h> // FF28 or FSSB24
//  
//  #include <Fonts/GFXFF/FreeSansBoldOblique9pt7b.h>  // FF29 or FSSBO9
//  #include <Fonts/GFXFF/FreeSansBoldOblique12pt7b.h> // FF30 or FSSBO12
//  #include <Fonts/GFXFF/FreeSansBoldOblique18pt7b.h> // FF31 or FSSBO18
//  #include <Fonts/GFXFF/FreeSansBoldOblique24pt7b.h> // FF32 or FSSBO24
//  
//  // Serif fonts
//  #include <Fonts/GFXFF/FreeSerif9pt7b.h>  // FF33 or FS9
//  #include <Fonts/GFXFF/FreeSerif12pt7b.h> // FF34 or FS12
//  #include <Fonts/GFXFF/FreeSerif18pt7b.h> // FF35 or FS18
//  #include <Fonts/GFXFF/FreeSerif24pt7b.h> // FF36 or FS24
//  
//  #include <Fonts/GFXFF/FreeSerifItalic9pt7b.h>  // FF37 or FSI9
//  #include <Fonts/GFXFF/FreeSerifItalic12pt7b.h> // FF38 or FSI12
//  #include <Fonts/GFXFF/FreeSerifItalic18pt7b.h> // FF39 or FSI18
//  #include <Fonts/GFXFF/FreeSerifItalic24pt7b.h> // FF40 or FSI24
//  
//  #include <Fonts/GFXFF/FreeSerifBold9pt7b.h>  // FF41 or FSB9
//  #include <Fonts/GFXFF/FreeSerifBold12pt7b.h> // FF42 or FSB12
//  #include <Fonts/GFXFF/FreeSerifBold18pt7b.h> // FF43 or FSB18
//  #include <Fonts/GFXFF/FreeSerifBold24pt7b.h> // FF44 or FSB24
//  
//  #include <Fonts/GFXFF/FreeSerifBoldItalic9pt7b.h>  // FF45 or FSBI9
//  #include <Fonts/GFXFF/FreeSerifBoldItalic12pt7b.h> // FF46 or FSBI12
//  #include <Fonts/GFXFF/FreeSerifBoldItalic18pt7b.h> // FF47 or FSBI18
//  #include <Fonts/GFXFF/FreeSerifBoldItalic24pt7b.h> // FF48 or FSBI24
//  
//#endif // #ifdef LOAD_GFXFF
//
////These enumerate the text plotting alignment (reference datum point)
//#define TL_DATUM 0 // Top left (default)
//#define TC_DATUM 1 // Top centre
//#define TR_DATUM 2 // Top right
//#define ML_DATUM 3 // Middle left
//#define CL_DATUM 3 // Centre left, same as above
//#define MC_DATUM 4 // Middle centre
//#define CC_DATUM 4 // Centre centre, same as above
//#define MR_DATUM 5 // Middle right
//#define CR_DATUM 5 // Centre right, same as above
//#define BL_DATUM 6 // Bottom left
//#define BC_DATUM 7 // Bottom centre
//#define BR_DATUM 8 // Bottom right
//#define L_BASELINE  9 // Left character baseline (Line the 'A' character would sit on)
//#define C_BASELINE 10 // Centre character baseline
//#define R_BASELINE 11 // Right character baseline
//
//
//// New color definitions use for all my libraries
//#define TFT_BLACK       0x0000      /*   0,   0,   0 */
//#define TFT_NAVY        0x000F      /*   0,   0, 128 */
//#define TFT_DARKGREEN   0x03E0      /*   0, 128,   0 */
//#define TFT_DARKCYAN    0x03EF      /*   0, 128, 128 */
//#define TFT_MAROON      0x7800      /* 128,   0,   0 */
//#define TFT_PURPLE      0x780F      /* 128,   0, 128 */
//#define TFT_OLIVE       0x7BE0      /* 128, 128,   0 */
//#define TFT_LIGHTGREY   0xC618      /* 192, 192, 192 */
//#define TFT_DARKGREY    0x7BEF      /* 128, 128, 128 */
//#define TFT_BLUE        0x001F      /*   0,   0, 255 */
//#define TFT_GREEN       0x07E0      /*   0, 255,   0 */
//#define TFT_CYAN        0x07FF      /*   0, 255, 255 */
//#define TFT_RED         0xF800      /* 255,   0,   0 */
//#define TFT_MAGENTA     0xF81F      /* 255,   0, 255 */
//#define TFT_YELLOW      0xFFE0      /* 255, 255,   0 */
//#define TFT_WHITE       0xFFFF      /* 255, 255, 255 */
//#define TFT_ORANGE      0xFDA0      /* 255, 180,   0 */
//#define TFT_GREENYELLOW 0xB7E0      /* 180, 255,   0 */
//#define TFT_PINK        0xFC9F
