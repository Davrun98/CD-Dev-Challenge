
#include "tdConvert.h"  // TD conversions
#include "td.h"
#include "director.h"


// defined director modes
#define __STANDBY   0   // director standby position (0 training, 0 elevation)
#define __POSITION  1   // command the director to an incoming TD position

void main(void)
{
    double  dTraining   = 0.0;
    double  dElevation  = 0.0;
    double  dRange      = 0.0;
    
    while(TRUE)
    {
        // Read the Target Data from external source
        getTD(dTraining, dElevation, dRange);
        
        // Convert from TD to director relative data
        tdConvert(dTraining, dElevation, dRange);
        
        switch(gDirctorMode)
        {
            case __STANDBY:
                commandDirector(0, 0);
                break;
                
            case __POSITION:
                // Command the director to the converted TD
                commandDirector(gdTraining, gdElevation);
                break;
        }
    }
}