#define ID_solar      0x01
#define Solar_of_Reg  4

int     vyroba;
double  REACTIVE, IMP_ENE, EXP_ENE;
double vyr_den, vyr_null, sol_odesli, sol_rozdil;
char   chvyr_den[10];  char chsolar[10];
int    pomzap;
double mezicas, doba;  unsigned long zacatek, konec;

#define Reg_ActivePower         0x000C      //  0. 
#define Reg_ReactiveAppPower    0x0018      //  1.
#define Reg_ImportEnergy        0x0048      //  2.
#define Reg_ExportEnergy        0x004A      //  3.

uint16_t const Reg_solar[4] = {
  Reg_ActivePower,
  Reg_ReactiveAppPower, 
  Reg_ImportEnergy,
  Reg_ExportEnergy,  
};

float  DATA_SOLAR [Solar_of_Reg] ;



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
