#include <OneWire.h>
#include <DallasTemperature.h>

#define dallas      15 //2

// ********** DALLAS teplota ********************************************
#define TempRes12 12  // set the resolution to 10 bit (resolution for ds18b20 9, 10, 11, 12)
OneWire oneWire(dallas);
DallasTemperature sensors(&oneWire);
DeviceAddress panel   = { 0x28, 0xFF, 0xC1, 0x1A, 0x64, 0x16, 0x04, 0x98 };
DeviceAddress batt1   = { 0x28, 0xFF, 0xC1, 0x1A, 0x64, 0x16, 0x04, 0x91 };
DeviceAddress batt2   = { 0x28, 0xFF, 0xC1, 0x1A, 0x64, 0x16, 0x04, 0x92 };
unsigned int err_dallas;
double t_panel, t_bat1, t_bat2, teplota, vlhkost;

void setupDALLAS(){/********************************** SETUP CIDLA *****************************************************************************/
     sensors.begin(); sensors.setResolution(TempRes12);
}/*============================================================================================================================================*/

void doDALLAS() { sensors.requestTemperatures(); err_dallas = 0;
        t_panel = sensors.getTempC(panel); if ( t_panel < -80 ) { t_panel = 0.0; err_dallas = 1; } 
        //t_bat1  = sensors.getTempC(batt1); if ( t_bat1  < -80 ) { t_bat1  = 0.0; err_dallas = 1; }
        //t_bat2  = sensors.getTempC(batt2); if ( t_bat2  < -80 ) { t_bat2  = 0.0; err_dallas = 1; }
}/*============================================================================================================================================*/
