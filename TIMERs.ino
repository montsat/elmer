//void co1s(){/********************* Timer co 1s  ******************************************/  
//   docas();  doTFT();  if (chcesOTA==1) { serverOTA.handleClient(); ArduinoOTA.handle(); }
//if (start == 0) { terminal.print(cas); terminal.println(F(" * start systému")); terminal.flush(); tft.fillScreen(TFT_BLACK); start = 1; }
//}/*======================================================================================*/

void coxs(){/******************** Timer co xs  *******************************************/ 
  
   docas();  doTFT();  if (chcesOTA==1) { serverOTA.handleClient(); ArduinoOTA.handle(); }
if (start == 0) { terminal.print(cas); terminal.println(F(" * start systému")); terminal.flush(); tft.fillScreen(TFT_BLACK); start = 1; }

rozhoz(); rizeni();                          PCF_01.write( LED_Err, zapni ); pocLED = 0; do  { pocLED++; }
                     while ( pocLED < 10 );  PCF_01.write( LED_Err, vypni );

////  #ifdef ENABLE_DALLAS 
////              doDALLAS();
////        #endif
////  #ifdef ENABLE_CIDLA 
////              docidla();
////        #endif  
}/*======================================================================================*/

void co15s(){/********************* Timer co 15s  *******************************************/  
  dosql(); 
}/*=========================================================================================*/

//void co1min(){/********************* Timer co 1min *******************************************/  
//  /* zmenit1 = 1; zmenit2 = 1;*/  
//}/*=========================================================================================*/

void co5min(){/********************* Timer co 5min *******************************************/  
   testwifi(); sendWifi();  reconnectBlynk();
}/*=========================================================================================*/

void rozhoz() {/*********************** ROZHOZ *******************************************/
       switch (kam){ case 4: brzda = "T1";  doTFTco(); GET_TRACER1(); mod1 = 0;                    break; //4 = TRACER48V 
                     case 5: brzda = "T2";  doTFTco(); GET_TRACER2(); mod2 = 0;                    break; //3 = TRACER24V       
                     case 1: brzda = "S ";  doTFTco(); GET_SOLAR();                                break;   
                     case 2: brzda = "E ";  doTFTco(); GET_ELMER_easy(); /*do_slunicko();*/        break;
                     case 3: brzda = "C ";  doTFTco(); GET_CML();                                  break;
                     case 6: brzda = "S ";  doTFTco(); GET_SOLAR();   /*do_slunicko();*/           break;   
                     case 7: brzda = "EB";  doTFTco(); GET_ELMER_easy();                           break;
                     case 8: brzda = "P ";  doTFTco(); GET_PZEM();   Blynk_bridge();               break;
                     case 9: brzda = "M ";  doTFTco(); /*GET_PZEMyc();*/  blynkuj();  kolecko = 1; break; }                              
 kam++; if (kam>kolik) { kam=1;}  
}/*======================================================================================*/

void docas() {/************** docas *********************************************************/
  rok=year();hodina=hour();minuta=minute();sekunda=second();mesic=month();den=day();vtydnu=(weekday());
  longhodina=hodina; sekund=((longhodina*3600)+(minuta*60)+sekunda); if (sekund>86390) { kpulnoci=1; }
snprintf(datum, sizeof(datum), "%02d.%02d.%02d", den, mesic, rok); //(23*3600)+(59*60)+59   =  82800+3540+59 =  86399
snprintf(cas, sizeof(cas), "%02d:%02d:%02d",  hodina, minuta, sekunda);
    switch (vtydnu){ case 1: dnes="nedele ";break;  case 2: dnes="pondeli";break;  case 3: dnes="utery  ";break;   case 4: dnes="streda ";break;
                     case 5: dnes="ctvrtek";break;  case 6: dnes="patek  ";break;  case 7: dnes="sobota ";break; }
}/*=================================================================================================================================================*/

/*
 *                      Blynk_bridge()
 * GET_SOLAR();         Blynk_solar()
 * GET_ELMER_actual();  Blynk_actual()
 * GET_SOLAR();         Blynk_solar()
 * GET_ELMER_easy();    Blynk_actual()+Blynk_easy()
 * GET_TRACER1();       Blynk_TRACER1_act()
 * GET_TRACER2();       Blynk_TRACER2_act()
 * GET_PZEM();          Blynk_PR()
 * GET_PZEMyc();        Blynk_myc()
 *                      doBlynkInfo() (IP/RSSI)
 *                      Blynk_ADS()
 *                      Blynk_cidla()
 *                      Blynk_den()
 *                      Blynk_CML()
 *                      Blynk_statistic()   (VT, NT, VT/den, NT/den, ...)*/
