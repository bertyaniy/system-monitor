#ifndef CPU_H
#define CPU_H

#include <iostream>

class CPU {
    public:
        CPU();
        struct CPU_Info {
            char* name;
            float speed;
            float usage;
        };
        CPU_Info get_cpu_info();
    
    private:
        const double factor;
};

#endif