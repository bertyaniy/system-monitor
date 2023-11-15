#ifndef MEMORY_H
#define MEMORY_H


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Memory {
    public: 
        Memory();
        struct Memory_Info {
            float mem_total;
            float mem_available;
            float mem_used;
        };
        Memory_Info get_memory_info();

    private:
        const char* mem_info_file;
        const double factor;
};


#endif