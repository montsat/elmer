//#define ID_pzem     6
//#define ID_pzemyc   7
//uint8_t result;
//#include <stdint.h>

uint32_t  lowhigh;
double U_PR,   P_PR,   PPR,  PR_den,  PR_null,  PR_odesli,  PR_rozdil; char chPR_den[10],    chPPR[10];  // asi nee
double U_myc, P_myc, mycka, myc_den, myc_null, myc_odesli, myc_rozdil; char chmyc_den[10], chmycka[10];  // asi nee

//double mycka_odber, mycka_den; // získat z bridge


void GET_PZEM() {/***********************  PZEM004T pračka ********************************/
PzemSerial2.begin(9600, SERIAL_8N1, RX2_PIN, TX2_PIN);  node.begin(6, PzemSerial2); 
                                          result = node.readInputRegisters(0x0000, 9);
     if (result == node.ku8MBSuccess) { U_PR     = node.getResponseBuffer(0x00)/10.0f; // Blynk.virtualWrite( V_U_PR, U_PR ); 
                                        lowhigh  = 0x00000000; 
                                        lowhigh |= node.getResponseBuffer(0x03);
                                        lowhigh |= node.getResponseBuffer(0x04)<<8;
                                        P_PR     = lowhigh/10.000f;                                                              
                                        lowhigh  = node.getResponseBuffer(0x05);       Blynk.virtualWrite( V_prackove,  lowhigh );  //LowByte
                                        PPR      = lowhigh / 1000.000f;
                                        lowhigh  = node.getResponseBuffer(0x06) << 8;  Blynk.virtualWrite( V_prackove2, lowhigh );  //HighByte
                                        PPR      = PPR + lowhigh;  }                      
             // else { return; }                            
  PR_den=PPR-PR_null;       Blynk.virtualWrite( V_P_PR, P_PR );            Blynk.virtualWrite( V_PR_den, PR_den );  /* Blynk.virtualWrite( V_prackove, prackove ); *///  terminal.println("GET_PR"); terminal.flush();     
}/*==========================================================================================================*/

void GET_PZEMyc() {/***********************  PZEM004T mycka ********************************/
//Serial.begin(9600); //PzemSerial2.begin(9600, SERIAL_8N1, RX2_PIN, TX2_PIN); 
          node.begin(7, Serial);            result =  node.readInputRegisters(0x0000, 9);
     if (result == node.ku8MBSuccess) { U_myc      = (node.getResponseBuffer(0x00)/10.0f);
                                        lowhigh    = 0x00000000; 
                                        lowhigh   |= node.getResponseBuffer(0x03);
                                        lowhigh   |= node.getResponseBuffer(0x04)<<8;                                       
                                        P_myc      = lowhigh/10.000f;                                                        
                                        lowhigh    = node.getResponseBuffer(0x0005);                //LowByte
                                        mycka      = lowhigh / 1000.000f;
                                        lowhigh   |= node.getResponseBuffer(0x0006) << 8;           //HighByte
                                        PPR      = PPR + lowhigh; }       
           // else { return; }                        
myc_den=mycka-myc_null;  Blynk.virtualWrite( V_P_myc, P_myc );          Blynk.virtualWrite( V_myc_den, myc_den );  // terminal.println("GET_MYC"); terminal.flush(); //Serial.begin(115200);                                                                           
}/*===========================================================================================================*/


/*   *** PZEM modbus protocol ***
 * 0x0000 Volt                 0.1V
 * 0x0001 I low 16 bits        0.001A
 * 0x0002 I hihg 16 bits
 * 0x0003 Power low 16 bits    0.1W
 * 0x0004 Power high 16 bits
 * 0x0005 Energy low 16 bits   1W 
 * 0x0006 Energy high 16 bits
 * 0x0007 Freq                 0.1Hz 
 * 0x0008 Power Factor         0.01 
 * 0x0009 Alarm status         0xFFFF/0x0000 alarm/not alarm 
 *   Holding register + Write
 * 0x0001 Power alarm          1W (2300W)
 * 0x0002 Modbus RTU address   0x0001-0x00F7
 */
