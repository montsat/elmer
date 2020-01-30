double CML_odber, CML_den, CML, setCML, CML_null;
double CML_odesli, CML_rozdil;
char chCML[13], chCML_den[10]; 

#define ID_CML      0x05
#define CML_of_Reg  2

#define reg_CML_odber         0x000C      //  0. 
#define reg_CML               0x0048      //  1.

uint16_t const Reg_CML[2] = {
  reg_CML_odber,
  reg_CML,
};

float  DATA_CML [CML_of_Reg] ;

/*
//SDM 120 registers
#define SDM120C_VOLTAGE                     0x0000                              //V
#define SDM120C_CURRENT                     0x0006                              //A
#define SDM120C_POWER                       0x000C                              //W
#define SDM120C_ACTIVE_APPARENT_POWER       0x0012                              //VA
#define SDM120C_REACTIVE_APPARENT_POWER     0x0018                              //VAR
#define SDM120C_POWER_FACTOR                0x001E                              //
#define SDM120C_FREQUENCY                   0x0046                              //Hz
#define SDM120C_IMPORT_ACTIVE_ENERGY        0x0048                              //Wh
#define SDM120C_EXPORT_ACTIVE_ENERGY        0x004A                              //Wh
#define SDM120C_TOTAL_ACTIVE_ENERGY         0x0156                              //Wh
*/
