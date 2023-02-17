/* 
 * This sketch shows how the Nicla board could be used to scan / classify certian gases of interest 
 * using the on-board BME688 4-in-1 evnironmental sensor cluster
 *
*/

#include "Arduino.h"
#include "Arduino_BHY2.h"

SensorBSEC2 bsec2(SENSOR_ID_BSEC2);

const uint8_t BSEC2CONFIG[] =      
//With this example configuration, the BSEC2 library is able to classify 2 types of gases:
//gas 0: ambient regular air in a room
//gas 1: alcohol in a container
//note that the data collected for training the classifying algorithm was rather limited, 
//thus the example config string for classifying might not work for your particular settings,
//for optimal results, please collect the data in your settings of interest and generate the config string using the AI studio accordingly
//generally speaking, more data under different scenarios yields better performance
     {0,0,2,2,189,1,0,0,0,0,0,0,213,8,0,0,52,0,1,0,0,168,19,73,64,49,119,76,0,192,40,72,0,192,40,72,137,65,0,191,205,204,204,190,0,0,64,191,225,122,148,190,10,0,3,0,216,85,0,100,0,0,96,64,23,183,209,56,28,0,2,0,0,244,1,150,0,50,0,0,128,64,0,0,32,65,144,1,0,0,112,65,0,0,0,63,16,0,3,0,10,215,163,60,10,215,35,59,10,215,35,59,13,0,5,0,0,0,0,0,100,254,131,137,87,88,0,9,0,7,240,150,61,0,0,0,0,0,0,0,0,28,124,225,61,52,128,215,63,0,0,160,64,0,0,0,0,0,0,0,0,205,204,12,62,103,213,39,62,230,63,76,192,0,0,0,0,0,0,0,0,145,237,60,191,251,58,64,63,177,80,131,64,0,0,0,0,0,0,0,0,93,254,227,62,54,60,133,191,0,0,64,64,12,0,10,0,0,0,0,0,0,0,0,0,173,6,11,0,0,0,2,231,201,67,189,125,37,201,61,179,41,106,189,97,167,196,61,84,172,113,62,155,213,214,61,133,10,114,61,62,67,214,61,56,97,57,62,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,42,215,83,190,42,215,83,62,0,0,0,0,0,0,0,0,97,101,165,61,88,151,51,190,184,89,165,62,240,207,20,191,47,208,53,63,177,43,63,190,176,56,145,189,228,194,10,191,173,194,44,191,0,0,0,0,146,253,150,61,217,5,157,59,36,134,171,190,159,38,128,59,58,78,29,189,204,88,63,191,210,42,125,190,59,171,228,190,78,165,243,190,0,0,0,0,171,98,187,188,83,234,57,191,66,87,75,62,209,91,130,62,133,244,221,61,242,192,118,190,13,13,52,62,235,86,146,62,147,48,2,191,0,0,0,0,80,192,203,190,252,170,134,189,5,138,208,62,255,220,147,62,184,119,166,62,192,231,125,189,181,36,79,190,124,71,210,62,55,239,13,191,0,0,0,0,226,139,200,189,182,220,91,190,113,205,238,189,235,255,228,190,201,16,66,63,123,50,149,61,80,26,112,62,66,108,128,62,233,205,253,190,0,0,0,0,223,117,24,189,133,115,60,62,197,48,0,189,60,64,194,61,189,86,246,61,185,197,54,189,133,63,90,190,239,233,46,190,14,247,19,191,0,0,0,0,193,26,240,62,151,185,23,190,33,105,234,190,5,24,166,190,197,45,23,63,196,211,145,190,178,103,164,190,125,36,6,191,234,28,114,190,0,0,0,0,136,73,125,62,234,189,27,62,200,69,225,189,15,56,142,190,188,47,134,190,174,248,193,190,221,81,161,190,152,89,51,189,86,157,105,61,0,0,0,0,116,72,209,190,237,104,63,189,60,50,39,189,40,194,15,191,232,34,133,62,163,192,193,61,38,90,147,189,198,159,7,191,240,239,146,61,0,0,0,0,93,146,86,61,185,23,6,62,12,52,10,62,9,82,26,191,186,80,1,63,130,184,195,190,43,204,83,62,73,27,220,189,254,195,200,189,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,63,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,63,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,63,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,63,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,63,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,63,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,63,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,63,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,63,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,63,9,53,212,189,25,224,132,190,0,0,0,0,0,0,0,0,133,45,39,63,65,50,45,191,0,0,0,0,0,0,0,0,76,73,7,62,150,167,209,189,0,0,0,0,0,0,0,0,242,163,107,63,193,223,173,62,0,0,0,0,0,0,0,0,192,205,68,190,213,103,28,63,0,0,0,0,0,0,0,0,60,148,171,62,151,246,154,189,0,0,0,0,0,0,0,0,162,104,218,62,88,44,237,190,0,0,0,0,0,0,0,0,253,226,216,62,249,223,161,189,0,0,0,0,0,0,0,0,168,65,13,190,119,123,179,190,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,160,184,18,72,125,52,223,75,204,85,211,75,119,27,192,75,83,228,150,73,122,154,142,73,133,214,135,73,145,149,237,71,56,196,2,72,221,197,11,72,0,0,0,0,0,0,0,0,0,0,0,0,158,236,10,72,35,30,221,75,206,136,209,75,14,146,190,75,218,105,148,73,65,65,140,73,150,149,133,73,206,248,222,71,219,117,246,71,96,19,4,72,0,0,128,63,0,0,128,63,0,0,128,63,0,0,0,87,1,254,0,2,1,5,48,117,100,0,44,1,112,23,151,7,132,3,197,0,92,4,144,1,64,1,64,1,144,1,48,117,48,117,48,117,48,117,100,0,100,0,100,0,48,117,48,117,48,117,100,0,100,0,48,117,48,117,8,7,8,7,8,7,8,7,8,7,100,0,100,0,100,0,100,0,48,117,48,117,48,117,100,0,100,0,100,0,48,117,48,117,100,0,100,0,255,255,255,255,255,255,255,255,255,255,44,1,44,1,44,1,44,1,44,1,44,1,44,1,44,1,44,1,44,1,44,1,44,1,44,1,44,1,255,255,255,255,255,255,255,255,255,255,8,7,8,7,8,7,8,7,8,7,8,7,8,7,8,7,8,7,8,7,8,7,8,7,8,7,8,7,255,255,255,255,255,255,255,255,255,255,112,23,112,23,112,23,112,23,112,23,112,23,112,23,112,23,112,23,112,23,112,23,112,23,112,23,112,23,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,220,5,220,5,220,5,255,255,255,255,255,255,220,5,220,5,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,48,117,0,1,0,5,0,2,0,10,0,30,0,5,0,5,0,5,0,5,0,5,0,5,0,64,1,100,0,100,0,100,0,200,0,200,0,200,0,64,1,64,1,64,1,10,0,0,0,0,95,8,0,0
};

void setup()
{
  Serial.begin(115200);
  while(!Serial);

  BHY2.begin();
  sensortec.bhy2_bsec2_setConfigString(BSEC2CONFIG, sizeof(BSEC2CONFIG)/sizeof(BSEC2CONFIG[0]));
  bsec2.begin();
}

void loop()
{
  // Update function should be continuously polled
  BHY2.update(100);

  if (bsec2.getNewDataFlag()) {
    bsec2.setNewDataFlag(false);

    Serial.println(bsec2.toString());
  }
}
