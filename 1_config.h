#define HDO_PIN       34

#define alarmik       26

#define critical_err  36

#define kolik          9  // (6) pro novou verzi - rozhoz
 
#define RX1_PIN       27
#define TX1_PIN       14

#define RX2_PIN       16 // zvolit PIN  // už použito v 1_config.h
#define TX2_PIN       17

hw_timer_t *watchdogTimer = NULL;
long looptime = 0;

String brzda;

int poc, pocLED;

bool first_connect = true;

uint32_t FloatTohex(float x)    { return (*(uint32_t*)&x);}
   float HexTofloat(uint32_t x) { return (*(float*)&x);}

uint8_t result; uint16_t data[6];

int notify220;

double VT_kWh = 5.34; double NT_kWh = 2.49;
double celkovy, uspora, vyr_VT, vyr_NT, vyr_NT_null, vyr_NT_uloz, vyr_NT_rozdil;
int procento, s_vyr_NT;
int start, start_elm, kolecko;
int sys_tracer, s_sys_tracer, mode_tracer, s_mode_tracer, sendsql/*, zmenit1, zmenit2*/;
int testwf, kam, vypis;   char ip_add[25], myssid[25];
int s_set, s_setNull, s_resWiFi, s_edit, s_res, odesli, chcesOTA, stracer, stracer2, spzem, ssolar, selmer, sstart, ssendBl/*, smalo1, smalo2*/;
int ress, pretok;
int rok; unsigned int hodina, minuta, sekunda, den, mesic, tyden, vtydnu, kpulnoci; char   datum[11], cas[9];
unsigned long sekund, longhodina, start_time;// , stop_time,run_time; 
//unsigned long server_start, server_stop;
//int Server_time;

String dnes; 

int Serverovna, Manual_menic, Menic1, Menic2, manual_string, string1, string2; 
int sys_Menic1, sys_Menic2, s_Menic1, s_Menic2;//, s_string1, s_string2;

int    slunicko;
int    bojler_odber;
double bojler_den, bojler_VT_den, bojler, doba_e;

double UP, IP, AhP; 
int    SOCP, TP, cykl;

int   rssi; 
float procwf; 

int sendBlynk;
//#define sendBlynk       1

/* terminal */
#define V_terminal              V0
/* BRIDGE */
#define V_bridge_bojler         V1
/* BRIDGE */
#define V_bridge_sazba          V2
#define V_bridge_slunicko       V4
/* tlačítka/volby */
#define V_set                   V5
#define V_edit                  V6
#define V_restart               V7
#define V_OTA                   V8
#define V_setVT                 V9
#define V_setNT                 V10
#define V_setNull               V11
#define V_sendBl                V12
#define V_resWiFi               V13

//#define V_timer1                V19
//#define V_server_time           V20
#define V_serverovna            V21

#define V_mode                  V22
#define V_VT_NT1                V23
#define V_VT_NT2                V24

#define V_vybito1               V25
#define V_vybito2               V26
#define V_manual1               V27
#define V_manual2               V28
#define V_Manual_menic          V29
#define V_menic1                V30
#define V_menic2                V31
#define V_manual_string         V32
#define V_string1               V33
#define V_string2               V34
//#define V_220                   V35

/********* ELMER **********/
#define V_sazba                 V41
#define V_VT                    V42
#define V_NT                    V43

#define V_VT_den                V44  
#define V_NT_den                V45 
#define V_za_den                V46
#define V_vyr_den               V47
#define V_doba                  V48

#define V_VT_null               V49
#define V_NT_null               V50
#define V_den_null              V51
#define V_vyr_null              V52
#define V_PR_null               V53
#define V_myc_null              V57
#define V_CML_null              V58
#define V_vyr_NT_null           V59

/*********** ELMER **********/
#define V_VOLTAGE1              V61
#define V_VOLTAGE2              V62
#define V_VOLTAGE3              V63
#define V_CURRENT1              V64
#define V_CURRENT2              V65
#define V_CURRENT3              V66
#define V_CURRENTSUM            V67
#define V_POWER1                V68
#define V_POWER2                V69
#define V_POWER3                V70
#define V_POWERTOTAL            V71
#define V_FREQUENCY             V72
//#define V_IMPORT1               V73
//#define V_IMPORT2               V74
//#define V_IMPORT3               V75
#define V_IMPORT_ACTIVE_ENERGY  V78
#define V_EXPORT_ACTIVE_ENERGY  V79
#define V_procento              V80
/********* SOLAR **********/
#define V_vyroba                V81
#define V_REACTIVE              V82
#define V_IMP_ENE               V83
#define V_EXP_ENE               V84 
#define V_uspora                V85 
#define V_vyr_NT                V86
/********* TRACER1 48V ******/
#define V_I_sol1                V91
#define V_U_sol1                V92
#define V_P_sol1                V93
#define V_I_char_bat1           V94
#define V_ene_d_in1             V95
//#define V_U_out1                V96
//#define V_s_out1                V97 //*
#define V_c_temp1               V98
#define V_SOC1                  V99
//#define V_Ah                    V100
#define V_U_bat_real1           V101 
#define V_s_bat_t1              V102
#define V_s_char_t1             V103
/********* Pylontech ******/
#define V_SOCP                  V104
#define V_UP                    V105
#define V_IP                    V106
#define V_AhP                   V107
#define V_TP                    V108
#define V_cykl                  V109
/********* TRACER2 24V ******/
#define V_I_sol2                V110
#define V_U_sol2                V111
#define V_P_sol2                V112
#define V_I_char_bat2           V113
#define V_ene_d_in2             V114
//#define V_U_out2                V115
//#define V_s_out2                V116 //*
#define V_c_temp2               V117
#define V_SOC2                  V118
#define V_U_bat_real2           V119
#define V_s_bat_t2              V120 
#define V_s_char_t2             V121

/*********** BOJLER ********/
#define V_bojler                V122
#define V_bojler_odber          V123
#define V_bojler_den            V124
#define V_bojler_VTden          V125
#define V_doba_e                V126
/*********** PZEM ***********/
#define V_P_PR                  131
#define V_PPR                   132
#define V_PR_den                133
#define V_prackove              134
#define V_prackove2             135
//#define V_U_PR                  136
//#define V_prackove3             137
/*********** PZEMyc *********/
#define V_P_myc                 141
#define V_mycka                 142
#define V_myc_den               143
/*********** CML ************/
#define V_CML_odber             151
#define V_CML_den               152
#define V_CML                   153
///********* ADS1115 **********/
//#define V_ADS1                  161
//#define V_ADS2                  162
//#define V_ADS3                  163
//#define V_ADS4                  164
///********** čidla ***********/
#define V_t_panel               171
//#define V_teplota               172
//#define V_vlhkost               173
//#define V_svit                  174

#define V_RSSI                  181
//#define V_mod1                  182
//#define V_s_mode                183

#define V_LED_NT                201
#define V_LED_out1              202
#define V_LED_out2              203
#define V_LED_M1                204
#define V_LED_M2                205
#define V_LED_Sdo1              206
#define V_LED_Sdo2              207
#define V_LED_server            208
#define V_LED_220               209

/*           PINout ESP32WEMOS

  -   tx   rx   +    +   sdl  sda   -    -    +    tx   rx        -    D    +
  * -  *  - * - *    *  - *  - *  - *    *  - * -  * -  *         * -  * -  *   
       mycka              I2C                 pracka                    dallas        
                              
             
       *    *   *    *    *    *    *    *     *   *     *   *    *    *    *                    * 
 -    TX0  RX0  +   SCL  SDA   -    -   CS   MOSI CLK   DC   +   TX2  RX2  res  boot  -        dallas
GND   D1   D3  3V3  D22  D21  GND  GND  D19  D23  D18   D5  3V3  D17  D16   D4   D0  GND   D2  D15  
                     BH1750   
                     SI7021
                     PCF8574 
                    
          VP   VN
3V3   EN  D36  D39  D32  D33  D34  D35  D25  D26  D27  D14  D12  D13   5V  GND        
     res   *                                      RX1  TX1             5V   -
                                                   *    *               *   *
                     *    *    *    *    *    *              *    *
                     - - - - - - - - - - - - - - - - - - - - - - --     
 
       
**************************************************************************************************************************       
       Propojení I2C -> PCF8574          Propojení serial -> myčka
       ========================          =========================      

ESP32          SCL  SDA   -   +               +   -   TX  RX 
                BH   BO   H   O               O   H   BO  BH 

              VCC    O 
              GND    H
              SDA    BO
              SCL    BH 

**************************************************************************************************************************

        Propojení modbus + pračka   + - RX TX     0 B- A+     ( pračka H,Z,M,O )
        =========================      

                                                           H+M  BH  BM 
        A+  B-  0   +       TX  RX  -   -   RX  TX      +   0   B-  A+
        *   *   *   *   *   *   *   * - *   *   *   *   *   *   *   * 
        |   |   |   |       |   |___________|   |       |   |   |   |
        |   |   |   |       |___________________|       |   |   |   |
        |   |   |   |_______________________________ ___|   |   |   |
        |   |   |___________________________________________|   |   |
        |   |___________________________________________________|   |
        |___________________________________________________________|   


                                        |   |   |   |   |   |   |   | 
                                        |   |   |   |   |   |   |   | 
                                        |   |   |   |   |   |   |   | 
                                        

                                        *   *   *   *   *   *   *   *
                                        -   RX  TX      +   0   B-  A+
                                        Z   BZ  BO      O  H+M  BH  BM        

**************************************************************************************************************************
     
     */
