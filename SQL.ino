void dosql(){   /*****************   add to mysql   **************************/ 
  if ( IMPORT_ACTIVE_ENERGY>0 ) {  
  dtostrf((IMP_ENE), 1,3, chsolar);               dtostrf((PPR), 1,3, chPPR);  dtostrf((IMPORT_ACTIVE_ENERGY), 1,3, chelmer); 
  dtostrf((EXPORT_ACTIVE_ENERGY), 1,3, chpretok); dtostrf((CML), 1,4, chCML);  dtostrf((CML_den), 1,3, chCML_den);
                 
WiFiClient client = server.available();    HTTPClient http;  
       url = add_url+"?HDO="+sazba+"&odber="+POWERTOTAL+"&P_L1="+POWER1+"&P_L2="+POWER2+"&P_L3="+POWER3+"&vyroba="+vyroba+"&odber_CML="+CML_odber+"&odber_bojler="+bojler_odber+"&odber_pracka="+P_PR+"&odber_mycka="+P_myc+"&VT="+VT+"&NT="+NT+"&VT_den="+VT_den+"&NT_den="+NT_den+"&za_den="+za_den
                    +"&sol_den="+vyr_den+"&sol_doba="+doba+"&CML_den="+chCML_den+"&bojler_den="+bojler_den+"&bojler_den="+bojler_den+"&pracka_den="+PR_den+"&mycka_den="+myc_den+"&elmer="+chelmer+"&pretok="+chpretok+"&solar="+chsolar
                    +"&U_L1="+VOLTAGE1+"&U_L2="+VOLTAGE2+"&U_L3="+VOLTAGE3+"&freq="+FREQUENCY+"&I_L1="+CURRENT1+"&I_L2="+CURRENT2+"&I_L3="+CURRENT3+"&CML="+chCML+"&bojler="+bojler+"&bojler_doba="+doba_e+"&pracka="+chPPR+"&mycka="+mycka
                    +"&U_sol1="+U_sol1+"&I_sol1="+I_sol1+"&P_sol1="+P_sol1+"&U_bat1="+U_bat_real1+"&I_char1="+IP+"&SOC1="+SOCP+"&Ah="+AhP+"&ene1_in="+ene_d_in1+"&tr1_out="+tr1_out
                    +"&U_sol2="+U_sol2+"&I_sol2="+I_sol2+"&P_sol2="+P_sol2+"&U_bat2="+U_bat_real2+"&I_char2="+I_char_bat2+"&SOC2="+SOC2+"&ene2_in="+ene_d_in2+"&tr2_out="+tr2_out+"&procento="+procento+"&uspora="+uspora+"&vyr_NT="+vyr_NT+"&res="+ress
                    +"&t_panel="+t_panel+"&t_bat1="+t_bat1+"&t_bat2="+t_bat2+"&t_casse1="+c_temp1+"&t_casse2="+c_temp2+"&t_bat="+teplota+"&vlhkost="+vlhkost+"&SOC="+SOC1+"&I_char_tr="+I_char_bat1+"&t_pylon="+TP;
   http.begin(url);  httpCode = http.GET();  payload = http.getString();  /*Serial.println(url);    Serial.println(payload);*/    http.end();  ress=0;   //terminal.println("SQL"); terminal.flush();
  }
}/*===============================================================================================================================================================================================================================================*/
