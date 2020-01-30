#define ID_elmer             0x02
#define Elmer_of_Reg_easy    14

double VOLTAGE1, VOLTAGE2, VOLTAGE3, CURRENT1, CURRENT2, CURRENT3, CURRENTSUM, POWER1, POWER2, POWER3, POWERTOTAL, 
       FREQUENCY, IMPORT_ACTIVE_ENERGY, EXPORT_ACTIVE_ENERGY, 
       VT, NT, VT_den, NT_den, za_den, den_null, VT_null, NT_null, VT_in, NT_in;      
       
int    sazba, s_sazba;
double setVT, setNT, elm_odesli, elm_rozdil;
char   chVT_den[10], chNT_den[10], chza_den[10], chVT[10], chNT[10], chelmer[10], chpretok[10];

#define reg_VOLTAGE1                     0x0000   //0.  /V  /A
#define reg_VOLTAGE2                     0x0002   //1.  /V  /A
#define reg_VOLTAGE3                     0x0004   //2.  /V  /A 
#define reg_CURRENT1                     0x0006   //3.  /A   /E 
#define reg_CURRENT2                     0x0008   //4.  /A   /E
#define reg_CURRENT3                     0x000A   //5.  /A   /E
#define reg_CURRENTSUM                   0x0030   //6.  /A   /E
#define reg_POWER1                       0x000C   //7.  /W  /A
#define reg_POWER2                       0x000E   //8.  /W  /A
#define reg_POWER3                       0x0010   //9.  /W  /A
#define reg_POWERTOTAL                   0x0034   //10. /W  /A
#define reg_FREQUENCY                    0x0046   //11. /HZ       / E
#define reg_IMPORT_ACTIVE_ENERGY         0x0048   //12. /Wh       / E
#define reg_EXPORT_ACTIVE_ENERGY         0x004A   //13. /Wh       / E
  
uint16_t const Reg_elmer_easy[14] = { reg_VOLTAGE1,  reg_VOLTAGE2, reg_VOLTAGE3, reg_CURRENT1, reg_CURRENT2, reg_CURRENT3, reg_CURRENTSUM, reg_POWER1, reg_POWER2, reg_POWER3, reg_POWERTOTAL, 
                                      reg_FREQUENCY, reg_IMPORT_ACTIVE_ENERGY,   reg_EXPORT_ACTIVE_ENERGY };

float DATA_ELMER_easy [Elmer_of_Reg_easy] ;


/*
//SDM 630 registers
#define SDM630_VOLTAGE1                     0x0000                              //V
#define SDM630_VOLTAGE2                     0x0002                              //V
#define SDM630_VOLTAGE3                     0x0004                              //V
#define SDM630_CURRENT1                     0x0006                              //A
#define SDM630_CURRENT2                     0x0008                              //A
#define SDM630_CURRENT3                     0x000A                              //A
#define SDM630_CURRENTSUM                   0x0030                              //A
#define SDM630_POWER1                       0x000C                              //W
#define SDM630_POWER2                       0x000E                              //W
#define SDM630_POWER3                       0x0010                              //W
#define SDM630_POWERTOTAL                   0x0034                              //W
#define SDM630_VOLT_AMPS1                   0x0012                              //VA
#define SDM630_VOLT_AMPS2                   0x0014                              //VA
#define SDM630_VOLT_AMPS3                   0x0016                              //VA
#define SDM630_VOLT_AMPS_TOTAL              0x0038                              //VA
#define SDM630_VOLT_AMPS_REACTIVE1          0x0018                              //VAr
#define SDM630_VOLT_AMPS_REACTIVE2          0x001A                              //VAr
#define SDM630_VOLT_AMPS_REACTIVE3          0x001C                              //VAr
#define SDM630_VOLT_AMPS_REACTIVE_TOTAL     0x003C                              //VAr
#define SDM630_POWER_FACTOR1                0x001E
#define SDM630_POWER_FACTOR2                0x0020
#define SDM630_POWER_FACTOR3                0x0022
#define SDM630_POWER_FACTOR_TOTAL           0x003E
#define SDM630_PHASE_ANGLE1                 0x0024                              //Degrees
#define SDM630_PHASE_ANGLE2                 0x0026                              //Degrees
#define SDM630_PHASE_ANGLE3                 0x0028                              //Degrees
#define SDM630_PHASE_ANGLE_TOTAL            0x0042                              //Degrees
#define SDM630_VOLTAGE_AVERAGE              0x002A                              //V
#define SDM630_CURRENT_AVERAGE              0x002E                              //A
#define SDM630_FREQUENCY                    0x0046                              //HZ
#define SDM630_IMPORT_ACTIVE_ENERGY         0x0048                              //Wh
#define SDM630_EXPORT_ACTIVE_ENERGY         0x004A                              //Wh
#define SDM630_IMPORT_REACTIVE_ENERGY       0x004C                              //VARh
#define SDM630_EXPORT_REACTIVE_ENERGY       0x004E                              //VARh
#define SDM630_TOTAL_SYSTEM_POWER_DEMAND    0x0054                              //W
#define SDM630_MAXIMUM_TOTAL_SYSTEM_POWER   0x0056                              //W
#define SDM630_PHASE_1_LN_VOLTS_THD         0x00EA                              //%
#define SDM630_PHASE_2_LN_VOLTS_THD         0x00EC                              //%
#define SDM630_PHASE_3_LN_VOLTS_THD         0x00EE                              //%
#define SDM630_AVERAGE_VOLTS_THD            0x00F8                              //%
#define SDM630_PHASE_1_CURRENT_THD          0x00F0                              //%
#define SDM630_PHASE_2_CURRENT_THD          0x00F2                              //%
#define SDM630_PHASE_3_CURRENT_THD          0x00F4                              //%
#define SDM630_AVERAGE_CURRENT_THD          0x00FA                              //%
#define SDM630_IMPORT1                      0x015a                              //kWh
#define SDM630_IMPORT2                      0x015c                              //kWh
#define SDM630_IMPORT3                      0x015e                              //kWh
#define SDM630_EXPORT1                      0x0160                              //kWh
#define SDM630_EXPORT2                      0x0162                              //kWh
#define SDM630_EXPORT3                      0x0164                              //kWh
#define SDM630_TOTAL_ENERGY1                0x0166                              //kWh
#define SDM630_TOTAL_ENERGY2                0x0168                              //kWh
#define SDM630_TOTAL_ENERGY3                0x016a                              //kWh
*/
