#include "PCF8574.h"
PCF8574 PCF_01(0x20);   // (0xx|0xx|0xx)

 #define kontrola220 0
 #define kontrolaM1  1               //    0    1    2    3    4    5    6    7  
 #define kontrolaM2  2               //   220  kM1  kM2  HDO  err   M1   M2  serv            
 #define kontrolaHDO 3  
 #define LED_Err     4   
  
 #define menic1      5
 #define menic2      6   
 #define serverovna  7   // - stykač                  
        
int vychozi = HIGH, zapni = LOW, vypni = HIGH; 

int  KontrolaM1, KontrolaM2, KontrolaHDO, Kontrola220, S_LED_err; 


void setupPCF(){/********************************** SETUP PCF *****************************************/
     /*Wire.begin();*/  PCF_01.begin();  /* START PCF + výchozí stavy */
PCF_01.write(menic1, vychozi); PCF_01.write(menic2, vychozi); PCF_01.write(serverovna, vychozi); 
}/*=====================================================================================================*/
