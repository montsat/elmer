//int ID_tracer2 = 3; // 3 = TRACER24V

//  TRACER 24V
int    s_out2;   //3202
int    s_bat2, s_char2;
double U_sol2, I_sol2, P_sol2, I_char_bat2, U_out2, b_temp2, c_temp2, SOC2, ene_d_in2, U_bat_real2, S_max2, bat_max2, bat_min2;
String bat2, nabijeni2;
int    mod2, vt_nt2, tr2_out, vybito2;

int    man_tracer2, out_tracer2; 


void GET_TRACER2() {/*************** read TRACER2 - 24V register *******************************/      
 // ElmerSerial.begin(9600, SERIAL_8N1, RX1_PIN, TX1_PIN);  node.begin(3, ElmerSerial); 
  ElmerSerial.begin(9600, SERIAL_8N1, RX1_PIN, TX1_PIN);  node.begin(3, ElmerSerial);   
// ElmerSerial.begin(9600, SERIAL_8N1, RX1_PIN, TX1_PIN);  
 //ElmerSerial.begin(115200); node.begin(3, ElmerSerial);  
//U_sol2 = 0; I_sol2 = 0; I_char_bat2 = 0; P_sol2 = 0; U_out2 = 0; b_temp1 = 0; c_temp2 = 0; SOC2 = 0; s_bat2 = 5; s_char2 = 4; ene_d_in2 = 0; U_bat_real2 = 0;
/*=========== REGISTER 3202 =====================*/
     result = node.readInputRegisters(0x3202,1);
if (result == node.ku8MBSuccess) {
  s_out2    = (node.getResponseBuffer(0x00));}
  // else { return; } 
/*=========== REGISTER 3100 =====================*/     
       result = node.readInputRegisters(0x3100, 19);  
  if (result == node.ku8MBSuccess) {
 U_sol2      = (node.getResponseBuffer(0x00)/100.0f);
 I_sol2      = (node.getResponseBuffer(0x01)/100.0f);
 //P_sol2      = (node.getResponseBuffer(0x03)/100.0f);
 I_char_bat2 = (node.getResponseBuffer(0x05)/100.0f);
 U_out2      = (node.getResponseBuffer(0x0C)/100.0f);
 b_temp2     = (node.getResponseBuffer(0x10)/100.0f); 
 c_temp2     = (node.getResponseBuffer(0x11)/100.0f); } 
/*=========== REGISTER 311A =====================*/  
      result = node.readInputRegisters(0x311A,1);
 if (result == node.ku8MBSuccess) {
       SOC2 = (node.getResponseBuffer(0x00)/1.0f); }
/*=========== REGISTER 3200 =====================*/ 
      result = node.readInputRegisters(0x3200, 1);
 if (result == node.ku8MBSuccess) {
     s_bat2 = (node.getResponseBuffer(0x00) >>0);
  switch (s_bat2) { case 0: bat2 = "Normal";     break; 
                    case 1: bat2 = "Overvolt";   break;   
                    case 2: bat2 = "Undervolt";  break;
                    case 3: bat2 = "Disconnect"; break;
                    case 4: bat2 = "error";      break; } }        
/*=========== REGISTER 3201 =====================*/ 
      result = node.readInputRegisters(0x3201, 1);
 if (result == node.ku8MBSuccess) {
    s_char2 = lowByte(node.getResponseBuffer(0x00)>>2 ); 
  switch (s_char2) { case 0: nabijeni2 = "NoChar";  break; 
                     case 1: nabijeni2 = "Float";   break;   
                     case 2: nabijeni2 = "Boost";   break;
                     case 3: nabijeni2 = "Equaliz"; break; } }  
/*=========== REGISTER 3300 =====================*/ 
      result = node.readInputRegisters(0x3300,29);
 if (result == node.ku8MBSuccess) { 
   S_max2   = (node.getResponseBuffer(0x00)/100.0f);
  bat_max2  = (node.getResponseBuffer(0x02)/100.0f);  
  bat_min2  = (node.getResponseBuffer(0x03)/100.0f);     
 ene_d_in2  = (node.getResponseBuffer(0x0C)/100.0f);
U_bat_real2 = (node.getResponseBuffer(0x1A)/100.0f); }

    if ( U_out2 > 0 ) { tr2_out = 1; } else { tr2_out = 0; }
/****************** změna TRACER2 *******************/ 
 if ( kolecko == 1 ) {
    if (( U_out2 == 0) && ( out_tracer2 == 1 )) { result = node.writeSingleCoil(0x0002, out_tracer2); terminal.print(cas); terminal.println(F(" -  TRACER2 out ON"));  terminal.flush(); }   
    if (( U_out2 >  0) && ( out_tracer2 == 0 )) { result = node.writeSingleCoil(0x0002, out_tracer2); terminal.print(cas); terminal.println(F(" -  TRACER2 out OFF")); terminal.flush(); } 
                     }
 /*=========== WRITE REGISTER 903D =====================*/ 
if (( mod2 == 1 ) && ( kolecko == 1 )) {  terminal.print(cas); terminal.println(F(" - Tracer2 zmena stavu mode")); terminal.flush(); 
   result = node.writeSingleRegister(0x903D, sys_tracer); /*mod2 = 0;*/ }      

if ( sendBlynk == 1 ) { Blynk.virtualWrite( V_I_char_bat2, I_char_bat2 ); Blynk.virtualWrite( V_SOC2,           SOC2 );  Blynk.virtualWrite( V_P_sol2,       P_sol2 );                        
                        Blynk.virtualWrite( V_U_sol2,           U_sol2 ); Blynk.virtualWrite( V_I_sol2,       I_sol2 );  Blynk.virtualWrite( V_s_bat_t2,       bat2 );
                        Blynk.virtualWrite( V_U_bat_real2, U_bat_real2 ); Blynk.virtualWrite( V_s_char_t2, nabijeni2 );  Blynk.virtualWrite( V_ene_d_in2, ene_d_in2 );               
                       }
}/*====================================== END TRACER ==================================*/
/*======================================================================================*/
