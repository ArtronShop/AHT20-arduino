#ifndef __AHT20_H__
#define __AHT20_H__

#include "Arduino.h"
#include "Wire.h"

class AHT20 {
    
    public:
        AHT20();

        bool begin() ;
        bool read(float*, float*) ;
};

extern AHT20 aht;

#endif
