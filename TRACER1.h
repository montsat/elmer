//int ID_tracer1 = 4; // 4 = TRACER48V

//  TRACER 48V
int    s_out1;   //3202
int    s_bat1, s_char1;
double U_sol1, I_sol1, P_sol1, I_char_bat1, U_out1, b_temp1, c_temp1, SOC1, ene_d_in1, U_bat_real1, S_max1, bat_max1, bat_min1;
String bat1, nabijeni1;
int    mod1, vt_nt1, tr1_out, vybito1;

int    man_tracer1, out_tracer1; 


void GET_TRACER1() {/*************** read TRACER2 - 24V register *******************************/      
//  ElmerSerial.begin(115200, SERIAL_8N1, RX1_PIN, TX1_PIN);  node.begin(4, ElmerSerial);  
  ElmerSerial.begin(115200, SERIAL_8N1, RX1_PIN, TX1_PIN);  node.begin(4, ElmerSerial);
 //ElmerSerial.begin(9600, SERIAL_8N1, RX1_PIN, TX1_PIN); 
 //ElmerSerial.begin(115200); node.begin(4, ElmerSerial);  
//U_sol1 = 0; I_sol1 = 0; I_char_bat1 = 0; P_sol1 = 0; U_out1 = 0; b_temp1 = 0; c_temp1 = 0; SOC1 = 0; s_bat1 = 5; s_char1 = 4; ene_d_in1 = 0; U_bat_real1 = 0; 
/*=========== REGISTER 3202 =====================*/
     result = node.readInputRegisters(0x3202,1);
if (result == node.ku8MBSuccess) {
  s_out1   = (node.getResponseBuffer(0x00));}
  // else { return; }
/*=========== REGISTER 3100 =====================*/     
       result = node.readInputRegisters(0x3100, 19);  
  if (result == node.ku8MBSuccess) { 
 U_sol1      = (node.getResponseBuffer(0x00)/100.0f);
 I_sol1      = (node.getResponseBuffer(0x01)/100.0f);
 //P_sol1      = (node.getResponseBuffer(0x03)/100.0f);
 I_char_bat1 = (node.getResponseBuffer(0x05)/100.0f);
 U_out1      = (node.getResponseBuffer(0x0C)/100.0f);
 b_temp1     = (node.getResponseBuffer(0x10)/100.0f);
 c_temp1     = (node.getResponseBuffer(0x11)/100.0f); } 
/*=========== REGISTER 311A =====================*/  
      result = node.readInputRegisters(0x311A,1);
 if (result == node.ku8MBSuccess) {
       SOC1 = (node.getResponseBuffer(0x00)/1.0f); }
/*=========== REGISTER 3200 =====================*/ 
      result = node.readInputRegisters(0x3200, 1);
 if (result == node.ku8MBSuccess) {
     s_bat1 = (node.getResponseBuffer(0x00) >>0);
  switch (s_bat1) { case 0: bat1 = "Normal";     break; 
                    case 1: bat1 = "Overvolt";   break;   
                    case 2: bat1 = "Undervolt";  break;
                    case 3: bat1 = "Disconnect"; break;
                    case 4: bat1 = "error";      break; } }    
/*=========== REGISTER 3201 =====================*/ 
      result = node.readInputRegisters(0x3201, 1);
 if (result == node.ku8MBSuccess) {
    s_char1 = lowByte(node.getResponseBuffer(0x00)>>2 ); 
  switch (s_char1) { case 0: nabijeni1 = "NoChar";  break; 
                     case 1: nabijeni1 = "Float";   break;   
                     case 2: nabijeni1 = "Boost";   break;
                     case 3: nabijeni1 = "Equaliz"; break; } }  
/*=========== REGISTER 3300 =====================*/ 
      result = node.readInputRegisters(0x3300,29);
 if (result == node.ku8MBSuccess) {
    S_max1  = (node.getResponseBuffer(0x00)/100.0f);
  bat_max1  = (node.getResponseBuffer(0x02)/100.0f);  
  bat_min1  = (node.getResponseBuffer(0x03)/100.0f);     
 ene_d_in1  = (node.getResponseBuffer(0x0C)/100.0f);
U_bat_real1 = (node.getResponseBuffer(0x1A)/100.0f); }

    if ( U_out1 > 0 ) { tr1_out = 1; } else { tr1_out = 0; }
/****************** změna TRACER1 *******************/ 
 if ( kolecko == 1 ) {
    if (( U_out1 == 0) && ( out_tracer1 == 1 )) { result = node.writeSingleCoil(0x0002, out_tracer1); terminal.print(cas); terminal.println(F(" -  TRACER1 out ON"));  terminal.flush(); }   
    if (( U_out1 >  0) && ( out_tracer1 == 0 )) { result = node.writeSingleCoil(0x0002, out_tracer1); terminal.print(cas); terminal.println(F(" -  TRACER1 out OFF")); terminal.flush(); } 
                     }
 /*=========== WRITE REGISTER 903D =====================*/ 
if (( mod1 == 1 ) && ( kolecko == 1 )) {  terminal.print(cas); terminal.println(F(" - Tracer1 zmena stavu mode")); terminal.flush(); 
   result = node.writeSingleRegister(0x903D, sys_tracer); /*mod2 = 0;*/ }      

if ( sendBlynk == 1 ) { Blynk.virtualWrite( V_I_char_bat1, I_char_bat1 ); Blynk.virtualWrite( V_SOC1,           SOC1 );  Blynk.virtualWrite( V_P_sol1,       P_sol1 );                        
                        Blynk.virtualWrite( V_U_sol1,           U_sol1 ); Blynk.virtualWrite( V_I_sol1,       I_sol1 );  Blynk.virtualWrite( V_s_bat_t1,       bat1 );
                        Blynk.virtualWrite( V_U_bat_real1, U_bat_real1 ); Blynk.virtualWrite( V_s_char_t1, nabijeni1 );  Blynk.virtualWrite( V_ene_d_in1, ene_d_in1 );               
                       }
}/*====================================== END TRACER ==================================*/ 
/*======================================================================================*/
