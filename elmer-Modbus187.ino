String verze = "* elmer-Modbus v1.87c - "; String dat = "29.1.2020";
String popis =  verze + dat + " - 23:02";           char   ver[16]; 

#include "esp_system.h"  // co to je ? jede to i bez toho

//#define BLYNK_DEBUG 
#define BLYNK_PRINT Serial
#define BLYNK_MAX_READBYTES 1024

#define ENABLE_DALLAS
//#define ENABLE_CIDLA

#include "1_config.h"

#include <WiFi.h>
#include <ESPmDNS.h> 
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <BlynkSimpleEsp32_SSL.h>
#include <WiFiUdp.h>
#include <Update.h>
#include <Udp.h>
#include <AutoWifi.h>
          AutoWifi a; 

char blynk_token[34] = "xxxxxxxxxxxx";

#include <WiFiClient.h>
          WiFiClient client;
          WiFiServer server(80);

#include <ArduinoOTA.h>  
#include     "webOTA.h"
WebServer  server1(81);

int wifiOK;
int httpCode;
String url, payload, ipa, ips;
String add_url    = "http://xxx.xxx.xxx.xxx/add_elms.php";

WidgetTerminal terminal(V_terminal);
WidgetBridge bridge_bojler(V_bridge_bojler);
#include <WidgetRTC.h>
BlynkTimer timer_elm;
WidgetRTC rtc;
#define BLYNK_USE_128_VPINS

WidgetLED LED_M1    (V_LED_M1);     WidgetLED LED_M2  (V_LED_M2); 
WidgetLED LED_Sdo1(V_LED_Sdo1);     WidgetLED LED_Sdo2(V_LED_Sdo2);
WidgetLED LED_server(V_LED_server); WidgetLED LED_NT  (V_LED_NT);   
WidgetLED LED_out1  (V_LED_out1);   WidgetLED LED_out2(V_LED_out2);
WidgetLED LED_220(V_LED_220);

#include <HardwareSerial.h>
HardwareSerial ElmerSerial(1);
HardwareSerial PzemSerial2(2);     // Use hwserial UART2 at pins IO-16 (RX2) and IO-17 (TX2)

#include <ModbusMaster.h>
ModbusMaster node; /* CONNECT THE RS485 MODULE RX->RX, TX->TX. */

#include    "TRACER1.h"
#include    "TRACER2.h"
#include   "PCF_8574.h"
#include       "PZEM.h"
#include        "CML.h"
#include "reg_SDM120.h"
#include "reg_SDM630.h"

#include        "TFT.h"
    
#ifdef ENABLE_DALLAS
    #include "t_Dallas.h"
 #endif
#ifdef ENABLE_CIDLA
    #include "CIDLA.h"
 #endif



void setup(){/*************** setup *****************************************************/   
 Serial.begin(9600); while (!Serial);Serial.println();Serial.println(popis);
     setupTFT(); /**************** TFT **************************************************/
  /************* AutoWiFi ***************************************************************/
WiFi.mode(WIFI_STA);  a.startWifi();
poc=0;      do { if (WiFi.status() != WL_CONNECTED)   {   connectTFT(); delay(500);  Serial.print(F(".")); connectTFT(); } poc++; }
while (poc<20);  if (WiFi.status() != WL_CONNECTED)   {   Serial.println("Není Wifi");   /*a.resetProvisioning();*/ }
  if(!a.isProvisioned())  Serial.println(F("Setup wifi!"));   else  Serial.println(String("join ") + a.getSSID());
WiFi.setHostname("Elmer_ESP32"); ipa = WiFi.localIP().toString();    Serial.println(F("WiFi connected")); wifiOK = 1;
Serial.println(ipa);   Serial.println(WiFi.SSID()); Serial.println(WiFi.psk()); rssi = WiFi.RSSI();  Serial.print(F("rssi  = ")); Serial.println(rssi); delay(1000);
         connectTFT();  Blynk.begin(blynk_token,WiFi.SSID().c_str(),WiFi.psk().c_str());delay(1000);
/********** OTA ***********************************************************************/  
 ArduinoOTA.setHostname("ELMER_MODBUS"); ArduinoOTA.begin(); setupOTA();  server1.on("/reboot", [](){ ESP.restart(); });
           snprintf(ip_add, sizeof(ip_add), "%s",  WiFi.localIP().toString().c_str());
/*********** RS485 ************************************************************************/    
// ElmerSerial.begin(  9600, SERIAL_8N1, RX1_PIN, TX1_PIN); // node.begin(1, ElmerSerial); node.begin(2, ElmerSerial);  node.begin(5, ElmerSerial); 
// ElmerSerial.begin(  9600, SERIAL_8N1, RX1_PIN, TX1_PIN); // node.begin(3, ElmerSerial); node.begin(4, ElmerSerial);
 ElmerSerial.begin(   9600, SERIAL_8N1, RX1_PIN, TX1_PIN); node.begin(1, ElmerSerial); node.begin(2, ElmerSerial); node.begin(5, ElmerSerial); node.begin(3, ElmerSerial);
 ElmerSerial.begin( 115200, SERIAL_8N1, RX1_PIN, TX1_PIN);  node.begin(4, ElmerSerial);
 /********** PZEM004T **********************************************************************/
 PzemSerial2.begin(  9600, SERIAL_8N1, RX2_PIN, TX2_PIN);  node.begin(6, PzemSerial2); node.begin(7, Serial);
/******************************************************************************************/
setupPCF();     /*Wire.begin();*/  // pustit pak Wire.begin(); kvůli #include <BH1750FVI.h>
setSyncInterval(10 * 60); /*timer_elm.setInterval(  1000L,   co1s);*/ timer_elm.setInterval(   1793L,    coxs); timer_elm.setInterval( 15149L, co15s); 
                          /*timer_elm.setInterval( 60327L, co1min);*/ timer_elm.setInterval( 3065901L,  co5min); 

 #ifdef ENABLE_DALLAS
     setupDALLAS();
   #endif
 #ifdef ENABLE_CIDLA
     setupCIDLA();
   #endif   
ress = 1;  start_elm=1; mod1 = 1; mod2 = 1;                                       
 /*terminal.clear();*/ terminal.println(popis);  terminal.print(F("IP - ")); terminal.print(ip_add); terminal.print(F(" RSSI - ")); terminal.print(rssi); terminal.print(F(" dB - ")); terminal.println(WiFi.SSID()); terminal.flush();          
}/*==============================================================================================================================================================================*/

/*************** BLYNK ******************************************************************/
BLYNK_CONNECTED() {  if (first_connect) { rtc.begin(); chcesOTA=0; Blynk.virtualWrite( V_OTA, chcesOTA ); Blynk.syncAll(); //Blynk.notify(F("ELMER connected"));                 
   s_mode_tracer = mode_tracer;  first_connect=false; }
                     bridge_bojler.setAuthToken("xxxxxxxxx"); }
/*=====================================================================================================================================================================================================================================*/

  /**************** obslužné tlačítka ****************/
BLYNK_WRITE( V_mode )    { mode_tracer = param.asInt(); if ( s_mode_tracer != mode_tracer ) { mod1 = 1; mod2 = 1;  s_mode_tracer = mode_tracer; }
                                                                     switch ( mode_tracer ) { case 1: sys_tracer = 0; break;     // systém    0 + ovládání  systému 
                                                                                              case 2: sys_tracer = 3; break;     // tracer    3 pouze tracer
                                                                                              case 3: sys_tracer = 0; break; }}  // manual    0 + manual tlačítko
BLYNK_WRITE( V_manual1 ) { man_tracer1 = param.asInt(); /*zmenit1 = 1;*/ }
BLYNK_WRITE( V_manual2 ) { man_tracer2 = param.asInt(); /*zmenit2 = 1;*/ }
BLYNK_WRITE( V_VT_NT1  ) { vt_nt1      = param.asInt(); } 
BLYNK_WRITE( V_VT_NT2 )  { vt_nt2      = param.asInt(); }
BLYNK_WRITE( V_vybito1 ) { vybito1     = param.asInt(); }
BLYNK_WRITE( V_vybito2 ) { vybito2     = param.asInt(); }

//BLYNK_WRITE( V_server_time ) { Server_time = param.asInt(); } // Manual/Timer -  časové vypínání serverovny na určitý čas    longhodina=hodina; sekund=((longhodina*3600)+(minuta*60)+sekunda);
//BLYNK_WRITE( V_timer1)       { TimeInputParam t(param); if ( t.hasStartTime() ) { server_start = (((t.getStartHour())*3600)+((t.getStartMinute())*60)+(t.getStartSecond())); }                                        
//                                                        if ( t.hasStopTime() )  { server_stop  = (((t.getStopHour()) *3600)+((t.getStopMinute()) *60)+(t.getStopSecond())); }}
BLYNK_WRITE( V_serverovna )   { Serverovna    = param.asInt(); } //stykač server okruh
BLYNK_WRITE( V_menic1 )       { Menic1        = param.asInt(); }
BLYNK_WRITE( V_menic2 )       { Menic2        = param.asInt(); }
BLYNK_WRITE( V_Manual_menic ) { Manual_menic  = param.asInt(); }

BLYNK_WRITE( V_manual_string ){ manual_string = param.asInt(); }
BLYNK_WRITE( V_string1 )      { string1       = param.asInt(); }
BLYNK_WRITE( V_string2 )      { string2       = param.asInt(); }

BLYNK_WRITE( V_UP )           { UP            = param.asDouble(); }
BLYNK_WRITE( V_IP )           { IP            = param.asDouble(); }
BLYNK_WRITE( V_SOCP )         { SOCP          = param.asInt();    }
BLYNK_WRITE( V_AhP )          { AhP           = param.asDouble(); }
BLYNK_WRITE( V_TP )           { TP            = param.asInt();    }

BLYNK_WRITE( V_bojler )       { bojler        = param.asDouble(); }
BLYNK_WRITE( V_bojler_odber ) { bojler_odber  = param.asInt();    }
BLYNK_WRITE( V_bojler_den )   { bojler_den    = param.asDouble(); }
BLYNK_WRITE( V_bojler_VTden ) { bojler_VT_den = param.asDouble(); }
BLYNK_WRITE( V_doba_e )       { doba_e        = param.asDouble(); }

  /**************** Načtení stavů ****************/
BLYNK_WRITE( V_VT )       { VT       = param.asDouble(); /*if ( VT > 0 ) { Blynk.virtualWrite( V_VT, VT );}*/ }
BLYNK_WRITE( V_NT )       { NT       = param.asDouble(); /*if ( NT > 0 ) { Blynk.virtualWrite( V_NT, NT );}*/ } 
BLYNK_WRITE( V_VT_null )  { VT_null  = param.asDouble(); /*Blynk.virtualWrite( V_VT_null,  VT_null );*/ }
BLYNK_WRITE( V_NT_null )  { NT_null  = param.asDouble(); /*Blynk.virtualWrite( V_NT_null,  NT_null );*/ }
BLYNK_WRITE( V_den_null ) { den_null = param.asDouble(); /*Blynk.virtualWrite( V_den_null, den_null );*/ }
BLYNK_WRITE( V_vyr_null ) { vyr_null = param.asDouble(); /*Blynk.virtualWrite( V_vyr_null, vyr_null );*/ }
BLYNK_WRITE( V_vyr_NT )   { vyr_NT   = param.asDouble(); /*Blynk.virtualWrite( V_vyr_NT,   vyr_NT );*/ }
BLYNK_WRITE( V_PR_null )  { PR_null  = param.asDouble(); /*Blynk.virtualWrite( V_PR_null,  PR_null );*/ }
BLYNK_WRITE( V_myc_null ) { myc_null = param.asDouble(); /*Blynk.virtualWrite( V_myc_null, myc_null );*/ }
BLYNK_WRITE( V_CML_null ) { CML_null = param.asDouble(); /*Blynk.virtualWrite( V_CML_null, CML_null );*/ }
BLYNK_WRITE( V_doba )     { doba     = param.asDouble(); /*Blynk.virtualWrite( V_doba,     doba );*/ }
  /**************** nastavení  hodnot ****************/
BLYNK_WRITE( V_setVT )    { setVT    = param.asDouble(); /*Blynk.virtualWrite( V_setVT,    setVT );*/ }
BLYNK_WRITE( V_setNT )    { setNT    = param.asDouble(); /*Blynk.virtualWrite( V_setNT,    setNT );*/ }
  /**************** obslužné tlačítka ****************/
BLYNK_WRITE( V_OTA )     { chcesOTA  = param.asInt(); }
BLYNK_WRITE( V_sendBl )  { sendBlynk = param.asInt(); }
BLYNK_WRITE( V_edit )    { s_edit    = param.asInt(); }
BLYNK_WRITE( V_setNull ) { s_setNull = param.asInt(); }
BLYNK_WRITE( V_resWiFi ) { s_resWiFi = param.asInt(); }
BLYNK_WRITE( V_restart ) { s_res     = param.asInt(); }
BLYNK_WRITE( V_set )     { s_set     = param.asInt(); }
/*======================================================================================*/


void Blynk_den() { /********* Blynk den **********/ 
  if ( sendBlynk == 1 ) {
Blynk.virtualWrite( V_VT, VT ); Blynk.virtualWrite( V_NT, NT ); Blynk.virtualWrite( V_za_den, za_den );
Blynk.virtualWrite( V_vyr_den, vyr_den ); Blynk.virtualWrite( V_doba, doba ); Blynk.virtualWrite( V_vyr_NT, vyr_NT );
Blynk.virtualWrite( V_PR_den, PR_den ); Blynk.virtualWrite( V_myc_den, myc_den ); 
Blynk.virtualWrite( V_CML_den, CML_den ); }
}/*===========================================================================================================================================================================*/

void Blynk_null() { /********* Blynk null **********/ 
Blynk.virtualWrite( V_VT_null, VT_null );         Blynk.virtualWrite( V_NT_null, NT_null ); Blynk.virtualWrite( V_den_null, den_null ); Blynk.virtualWrite( V_vyr_null, vyr_null );
Blynk.virtualWrite( V_vyr_NT_null, vyr_NT_null ); Blynk.virtualWrite( V_PR_null, PR_null ); Blynk.virtualWrite( V_myc_null, myc_null ); Blynk.virtualWrite( V_CML_null, CML_null ); 
}/*===========================================================================================================================================================================*/

void Blynk_bridge() { /********* Bridge **********/  bridge_bojler.virtualWrite( V_bridge_sazba, sazba ); } // Nahradit ESPNow
/*============================================================================================================================================================================*/

void do_slunicko() { /********* výpočet sluníčka **********/  
 /* porovnávat výrobu - P_sol - I_sol - I_char - odber ->   když odběr < 100 a zároven P_sol > xx */ 
  bridge_bojler.virtualWrite( V_bridge_slunicko, slunicko );                                               // Nahradit ESPNow
}/*============================================================================================================================================================================*/


void blynkuj() { /********* blynkuj **********/ 
  if ( sendBlynk == 1 ) {
  Blynk.virtualWrite( V_t_panel, t_panel ); Blynk.virtualWrite( V_c_temp1, c_temp1 ); Blynk.virtualWrite( V_c_temp2, c_temp2 ); /*Blynk.virtualWrite( V_220, Kontrola220 );*/ }
}/*============================================================================================================================================================================*/

void GET_ELMER_easy() {/*************** read ELMER easy register ***********************************************************************************************************************/
  ElmerSerial.begin(9600, SERIAL_8N1, RX1_PIN, TX1_PIN); node.begin(2, ElmerSerial);  
//ElmerSerial.begin(9600); node.begin(2, ElmerSerial);           
 for ( char i = 0; i < Elmer_of_Reg_easy ; i++){  DATA_ELMER_easy [i] = Read_Meter_float(ID_elmer, Reg_elmer_easy[i]); } 
  VOLTAGE1  = (DATA_ELMER_easy[0]);              VOLTAGE2 = (DATA_ELMER_easy[1]);              VOLTAGE3 = (DATA_ELMER_easy[2]); 
  CURRENT1  = (DATA_ELMER_easy[3]);              CURRENT2 = (DATA_ELMER_easy[4]);              CURRENT3 = (DATA_ELMER_easy[5]);    CURRENTSUM = (DATA_ELMER_easy[6]);
    POWER1  = (DATA_ELMER_easy[7]);                POWER2 = (DATA_ELMER_easy[8]);                POWER3 = (DATA_ELMER_easy[9]);    POWERTOTAL = (DATA_ELMER_easy[10]);
  FREQUENCY = (DATA_ELMER_easy[11]); IMPORT_ACTIVE_ENERGY = (DATA_ELMER_easy[12]); EXPORT_ACTIVE_ENERGY = (DATA_ELMER_easy[13]);     

if ( IMPORT_ACTIVE_ENERGY > 0 ) { 
    if ( start_elm == 1 ) { elm_odesli = IMPORT_ACTIVE_ENERGY; start_elm = 0; }
        elm_rozdil = IMPORT_ACTIVE_ENERGY - elm_odesli;         
            if (elm_rozdil>=0.005) { if (sazba==0) { VT = VT + elm_rozdil;  Blynk.virtualWrite( V_VT, VT ); Blynk.virtualWrite( V_VT_den, VT_den ); }
                                              else { NT = NT + elm_rozdil;  Blynk.virtualWrite( V_NT, NT ); Blynk.virtualWrite( V_NT_den, NT_den ); }                             
                            elm_odesli = IMPORT_ACTIVE_ENERGY; elm_rozdil = 0; }}     
                            
if ( POWER2 < 0 ) { pretok = 1; }                       VT_den = VT - VT_null; NT_den = NT - NT_null; za_den = IMPORT_ACTIVE_ENERGY - den_null;   

celkovy  = vyroba + POWERTOTAL; procento = ( 100/celkovy ) * vyroba;   
    
  if ( sendBlynk == 1 ) {
Blynk.virtualWrite( V_POWERTOTAL, POWERTOTAL ); Blynk.virtualWrite( V_sazba,      sazba );   Blynk.virtualWrite( V_procento, procento );
Blynk.virtualWrite( V_POWER1,     POWER1 );     Blynk.virtualWrite( V_POWER2,     POWER2 );   Blynk.virtualWrite( V_POWER3,     POWER3 ); }
}/*===========================================================================================================================================================================*/

void GET_SOLAR() {/*************** read SOLAR register ****************************************************/ 
  ElmerSerial.begin(9600, SERIAL_8N1, RX1_PIN, TX1_PIN); node.begin(1, ElmerSerial); 
//ElmerSerial.begin(9600); node.begin(1, ElmerSerial);                     
    for (char i = 0; i < Solar_of_Reg ; i++){ DATA_SOLAR [i] = Read_Meter_float(ID_solar, Reg_solar[i]);  } 
vyroba    = (DATA_SOLAR[0]); REACTIVE  = (DATA_SOLAR[1]); 
IMP_ENE   = (DATA_SOLAR[2]); EXP_ENE   = (DATA_SOLAR[3]); 

if ( vyroba > 0 ){   if ( pomzap == 0 ) { zacatek=millis(); pomzap=1; }
                                   else { konec = millis(); mezicas = (( konec - zacatek ) / 3600000.000000 ); zacatek = millis(); } }
   else { zacatek = 0; konec = 0; pomzap = 0; mezicas = 0; }
                  doba=doba+mezicas;                                    vyr_den = IMP_ENE-vyr_null;

if ( IMP_ENE > 0 ) {  if ( sazba == 1 ) { if ( s_vyr_NT == 0 ) { vyr_NT_null = IMP_ENE; s_vyr_NT = 1; }

               vyr_NT_rozdil = IMP_ENE - vyr_NT_null;
           
     if ( vyr_NT_rozdil > 0.005 ) { vyr_NT = vyr_NT + vyr_NT_rozdil; vyr_NT_null = IMP_ENE; vyr_NT_rozdil = 0; }}
                                          else { s_vyr_NT = 0; }
                               }
    vyr_VT = vyr_den - vyr_NT;   uspora = (( vyr_VT * VT_kWh ) + ( vyr_NT * NT_kWh ));         
  if ( sendBlynk == 1 ) {
Blynk.virtualWrite( V_vyroba, vyroba ); Blynk.virtualWrite( V_doba, doba ); Blynk.virtualWrite( V_vyr_NT, vyr_NT ); Blynk.virtualWrite( V_vyr_den, vyr_den ); Blynk.virtualWrite( V_uspora, uspora ); }
}/*=======================================================================================================*/ 

void GET_CML() {/*************** read CML register ****************************************************/ 
  ElmerSerial.begin(9600, SERIAL_8N1, RX1_PIN, TX1_PIN); node.begin(5, ElmerSerial); 
//ElmerSerial.begin(9600); node.begin(5, ElmerSerial);                      
    for (char i = 0; i < CML_of_Reg ; i++){ DATA_CML [i] = Read_Meter_float(ID_CML, Reg_CML[i]);   } 
CML_odber = (DATA_CML[0]); CML  = (DATA_CML[1]);              CML_den = CML-CML_null;    
  if ( sendBlynk == 1 ) {                                            
Blynk.virtualWrite( V_CML_odber, CML_odber );   Blynk.virtualWrite( V_CML_den, CML_den );  
Blynk.virtualWrite( V_VOLTAGE1,   VOLTAGE1 );   Blynk.virtualWrite( V_VOLTAGE2,   VOLTAGE2 ); Blynk.virtualWrite( V_VOLTAGE3,   VOLTAGE3 ); 
Blynk.virtualWrite( V_CURRENT1,   CURRENT1 );   Blynk.virtualWrite( V_CURRENT2,   CURRENT2 ); Blynk.virtualWrite( V_CURRENT3,   CURRENT3 );
                Blynk.virtualWrite( V_za_den, za_den );  }  
}/*===========================================================================================================================================================================*/                                                                                                


float Read_Meter_float(char addr , uint16_t  REG) {/****** read MODBUS *******************/
  float i = 0; uint8_t j, result;  uint16_t data[2]; uint32_t value = 0; 
  node.begin(addr, ElmerSerial); result = node.readInputRegisters (REG, 2); 
  if (result == node.ku8MBSuccess) { 
    for (j = 0; j < 2; j++) { data[j] = node.getResponseBuffer(j); }
    value = data[0]; value = value << 16; value = value + data[1]; i = HexTofloat(value); return i; } 
 else { /*Serial.print("Connec modbus fail. REG >>> "); Serial.println(REG, HEX); */ return 0; }
}/*======================================================================================*/

void rizeni(){/********************************* rizeni ****************************************************/
  if ((sekund<10)&&(kpulnoci==1)) {  VT_null=VT; NT_null=NT; den_null=IMPORT_ACTIVE_ENERGY; vyr_null=IMP_ENE; vyr_NT_null = IMP_ENE; PR_null=PPR; myc_null=mycka; CML_null=CML; 
       VT_den=0.000; NT_den=0.000; za_den=0.000; vyr_den=0.000; vyr_VT=0.00; vyr_NT=0.00; uspora=0.00; doba=0.00; CML_den=0.0000; PR_den=0.000; myc_den=0.000; kpulnoci=0; ress=3; dosql();                      
                     Blynk_null(); Blynk_den();        terminal.print(cas); terminal.println(F(" -  day NULL")); terminal.flush(); /*  Blynk.notify(" day NULL");*/ }   
  /*********************************************** bezpečnostní ***************************************************************************/     
 if ( kolecko == 1 ) {
  if (( c_temp1 > 50 ) || ( c_temp2 > 50 ) || ( t_bat1 > 35 ) || ( t_bat2 > 35)) { /* varování + vypnutí panelů, měničů případně ve druhé vlně i baterií */ } // * LIMIT !!!
  if ( teplota > 50 ) { /* zapni chlazení */ }  // * LIMIT !!!
  if ( teplota < -5 ) {  /* zapni topení */  }  // * LIMIT !!!
  if ( vlhkost > 70 ) {  /* zapni větrání */ }  // * LIMIT !!!
                     //}
    /******************************* rizeni ****************************************************/ 
   sazba = !( PCF_01.read( kontrolaHDO ));       s_Menic1 =  !(PCF_01.read( kontrolaM1 )); s_Menic2 =  !(PCF_01.read( kontrolaM2 ));  Kontrola220 =  (PCF_01.read( kontrola220 ));
   if ( sazba != s_sazba ) {          
      if ( sazba == 0 ) { Blynk.notify(F("sazba VT")); terminal.print(cas); terminal.println(F(" - sazba VT")); terminal.flush();} 
                   else { Blynk.notify(F("sazba NT")); terminal.print(cas); terminal.println(F(" - sazba NT")); terminal.flush();}
         s_sazba = sazba; }
   if ( Kontrola220 == 0 ) { if ( notify220 == 0 ) { Blynk.notify(F("!!! výpadek 220V !!!")); notify220 = 1; }}  
                      else { notify220 = 0;}
if ( Kontrola220 == 1 ) { LED_220.on();  } else { LED_220 .off(); }                         
if ( sazba == 1 )       { LED_NT  .on(); } else { LED_NT  .off(); }  
if ( U_out1 > 0 )       { LED_out1.on(); } else { LED_out1.off(); }
if ( U_out2 > 0 )       { LED_out2.on(); } else { LED_out2.off(); }
              
  if ( pretok==1 ) {    terminal.print(cas); terminal.println(F(" -  PŘETOK !!!")); terminal.flush(); /*Blynk.notify(" !!! PŘETOK !!!");*/ pretok=0; }

/* ===================== Hlídání proti podbití bat 48V ======================================================================== */
if ( SOCP < 11 )           { if ( vybito1 == 0 ) { Blynk.notify(F("Pylontech LOW %")); terminal.print(cas); terminal.println(F(" -  Pylontech LOW % !!!")); terminal.flush(); } vybito1 = 1; Blynk.virtualWrite( V_vybito1, vybito1 ); }   // * LIMIT !!!  -> zápis do blynk  + doplnit do sync + notify 
/* ===================== Hlídání proti podbití bat 24V ======================================================================== */
if ( U_bat_real2 < 23.0 )  { if ( vybito2 == 0 ) { Blynk.notify(F("Batt 24V LOW %"));  terminal.print(cas); terminal.println(F(" -  Batt 24V LOW % !!!"));  terminal.flush(); } vybito2 = 1; Blynk.virtualWrite( V_vybito2, vybito2 ); }  // * LIMIT !!!  -> zápis do blynk  + doplnit do sync + notify + akce zapnutí záložního zdroje
/* ===================== opětovné zapnutí po začátku nabíjení ================================================================= */
if (( vybito1 == 1 ) && ( SOCP > 25 ) && ( IP > 1.0 )) { if ( vybito1 == 1 ) {  Blynk.notify(F("Pylontech retry O.K. %"));  terminal.print(cas); terminal.println(F(" -  Pylontech retry O.K. %")); terminal.flush(); } vybito1 = 0;  Blynk.virtualWrite( V_vybito1, vybito1 ); }
if (( vybito2 == 1 ) &&  ( U_bat_real2 > 23.25 ))      { if ( vybito2 == 1 ) {  Blynk.notify(F("Batt 24V retry O.K. %"));   terminal.print(cas); terminal.println(F(" -  Batt 24V retry O.K. %"));  terminal.flush(); } vybito2 = 0;  Blynk.virtualWrite( V_vybito2, vybito2 ); }
/* ===================== hlídání výpadku komunikace z PYLONTECH ================================================================= */
                                     if ( SOCP == -1 ) { if ( vybito1 == 0 ) {  Blynk.notify(F("Pylontech comm error !!!"));}  vybito1 = 1;  Blynk.virtualWrite( V_vybito1, vybito1 ); }
/* ===================== ovládání výstupu TRACER1 ===================================== */
if ( mode_tracer == 1 ) {  if ( vybito1 == 0 ) { if ( vt_nt1 == 1 ) { if (( sazba == 0 ) && ( man_tracer1 == 1 )) { out_tracer1 = 1; }
                                                                        else { out_tracer1 = 0; } 
                                                                      /* ============================== když je vše echt i NT tak zapni ========================================== */ 
                                                                      if (( sazba == 1 ) && ( SOCP > 80 ) && ( 70 < SOCP ) && ( I_char_bat1 > 0 )) { out_tracer1 = 1; } } // LIMIT !!!                                                                                                                                
                                                               /* ============= když je vt_nt1 == 0 ================ */
                                                               else { if ( man_tracer1 == 1 ) { out_tracer1 = 1; }
                                                                                         else { out_tracer1 = 0; } } }
                              else { out_tracer1 = 0; } }  
    else { /* nedělej nic */ } 
/* ===================== ovládání výstupu TRACER2 ===================================== */  //   1- automat / 2- tracer / 3 - manual
if ( mode_tracer == 1 ) {  if ( vybito2 == 0 ) { if ( vt_nt2 == 1 ) { if (( sazba == 0 ) && ( man_tracer2 == 1 )) { out_tracer2 = 1; }
                                                                        else { out_tracer2 = 0; } 
                                                                      /* ============================== když je vše echt i NT tak zapni ====================================================== */ 
                                                                      if (( sazba == 1 ) && ( SOC2 > 65 ) && ( 40 < SOC2 ) && ( U_bat_real2 > 24.6 ) && ( I_char_bat2 > 5 )) { out_tracer2 = 1; } } // LIMIT !!!  
                                                               /* ============= když je vt_nt2 == 0 ================ */                                                                                                                  
                                                               else { if ( man_tracer2 == 1 ) { out_tracer2 = 1; }
                                                                                         else { out_tracer2 = 0; } } }
                              else { out_tracer2 = 0; } }                     
    else { /* nedělej nic */ } 
/* ================================================ ovládání měničů ============================================================= */
/********************** ovládání chodu měničů manuálně   - vyp/zap 1,   vyp/zap 2 podle prep  **********************/
                            if ( Menic1 == 1 ) { sys_Menic1 = 1; /*zapni měnič 1kW*/ }
                                          else { sys_Menic1 = 0; /*vypni měnič 1kW*/ }   /* ***** Měnič 1kW jen manuální ovládání ***** */
if ( Manual_menic == 1 ) {  if ( Menic2 == 1 ) { sys_Menic2 = 1; /*zapni měnič 2kW*/ }
     /* 1 = manual */                     else { sys_Menic2 = 0; /*vypni měnič 2kW*/ } }    /* ***** konec manuálního ovládání ***** */
/********************** ovládání chodu měničů systémem  ****************************/
if ( Manual_menic == 0 ) {  if (out_tracer1 == 1) { sys_Menic2 = 1; /*zapni měnič 2kW*/ }               
                                             else { sys_Menic2 = 0; /*vypni měnič 2kW*/ } } /* ***** konec systémového ovládání ***** */ 
 if ( sys_Menic1 == 1 ) { LED_M1.on(); }  else { LED_M1.off(); }     if ( sys_Menic2 == 1 ) { LED_M2.on(); }  else { LED_M2.off(); }
        /* ***** kontrola stavu ***** ( 1 = vypnuto, 0 = zapnuto - negováno !(PCF_01.read(...)  *** */
        
  //if ( kolecko == 1 ) {
        /* ***** výstupy na pulsní relé ***** */  
   if ( s_Menic1 != sys_Menic1 ) { PCF_01.write( menic1, zapni); delay(100); PCF_01.write( menic1, vypni); }
   if ( s_Menic2 != sys_Menic2 ) { PCF_01.write( menic2, zapni); delay(100); PCF_01.write( menic2, vypni); Blynk.virtualWrite( V_menic2, sys_Menic2 ); }
                      }/* KONEC KOLEČKA */

 if ( kolecko == 0 ) {  Blynk.virtualWrite( V_menic2, sys_Menic2 ); }
                      
 /* Do řízení serverovny zamontovat timer1 a volku timeru   57600 - 58500 ( 16:00 - 16:15 */
 if ( Serverovna == 1 ) { PCF_01.write( serverovna, zapni); LED_server.on(); }  else { PCF_01.write( serverovna, vypni); LED_server.off(); } 

  /********************** vyhodnocení pro bojler ( slunicko )  ****************************/




  /*********************************************** řízeni ovládání ***************************************************************************/   
               /****************** edit setNull ********************/ 
 if ((s_setNull==1 ) && (s_set==1)) {  VT_null=VT; NT_null=NT; den_null=IMPORT_ACTIVE_ENERGY; vyr_null=IMP_ENE; vyr_NT_null=IMP_ENE; PR_null=PPR; myc_null=mycka; CML_null=CML; 
                                       doba=0.00; uspora=0.00;  vyr_VT=0.00; vyr_NT=0.00;   Blynk_null();  terminal.print(cas); terminal.println(F(" -  set NULL")); terminal.flush(); /*Blynk.notify("set Null O.K.");*/ } 
               /****************** edit VT/NT ********************/  
 if ((s_edit==1 ) && (s_set==1)) {  if (setVT>0)  { VT=setVT; Blynk.virtualWrite( V_VT, VT ); setVT=0;    Blynk.virtualWrite( V_setVT, setVT ); }
                                    if (setNT>0)  { NT=setNT; Blynk.virtualWrite( V_NT, NT ); setNT=0;    Blynk.virtualWrite( V_setNT, setNT ); }   
                              terminal.print(cas); terminal.println(F(" -  set VT/NT")); terminal.flush(); /* Blynk.notify("set VT/NT O.K.");*/ }
        /****************** reset WiFi ********************/ 
  if ((s_resWiFi==1 ) && (s_set==1)) { a.resetProvisioning(); interruptReboot(); }   // terminal.println("rizeni"); terminal.flush();
        /*******************  restart  ********************/     
      if ((s_res==1 ) && (s_set==1)) { interruptReboot(); }   // terminal.println("rizeni"); terminal.flush();
}/*==========================================================================================================================================*/



void critical_error() {   /* odpoj panely, odpoj měniče rozdělit to podle tracerů*/
     /* možná dát první načtení dat a pak teprve kontrola */
      /*  error1 - bat1 - napětí + teplota;  bat2 - napětí + teplota  */ 
      /*  error2 - teplota + vlhkost - dát do normálního voidu k řízení  */
//////while (( U_bat_real1 < 30 ) || ( U_bat_real2 < 15 )) { delay(3000); terminal.print("kritická chyba odpojeno !!!"); Blynk.notify("kritická chyba odpojeno !!!"); 
//while ( U_bat_real2 < 15 ) { delay(3000); terminal.print("kritická chyba odpojeno !!!"); Blynk.notify("kritická chyba odpojeno !!!"); 
///*ID_tracer = 4; GET_TRACER(); */ ID_tracer = 3; GET_TRACER();}
////        detachInterrupt(critical_err);
}/*==============================================================================================================================================================*/

void error_temp() {
 /* podle teploty buď něco zapni , nebo vše odpoj */
}/*==============================================================================================================================================================*/  

void sendWifi() { rssi = WiFi.RSSI();  Blynk.virtualWrite( V_RSSI, rssi); }

void testwifi() { 
  if (WiFi.status() != WL_CONNECTED) {testwf++; terminal.print(F(" WiFi - error ")); Blynk.notify(F(" WiFi - error ")); terminal.println(cas); terminal.flush(); } else {testwf=0;}  
     if ( testwf == 6 ) { interruptReboot(); }
}/*==========================================================================================================================================================================*/

void reconnectBlynk() { if (!Blynk.connected()) { if(Blynk.connect()) { terminal.print( cas ); terminal.println(F(" - BLYNK Reconnected ")); terminal.flush(); } //BLYNK_LOG("Reconnected");
                                                                 else { /*BLYNK_LOG("Not reconnected");*/ }
                                           }
}/*======================================================================================================================================================================================*/

void interruptReboot(){ /* restart systému */  ESP.restart(); /* esp_restart_noos();*/ }
/*==============================================================================================================================*/

void loop() {/***************** loop *******************************************************************************************/
  if (Blynk.connected()) { Blynk.run(); }   timer_elm.run(); 
}/*============================================================================================================================*/
