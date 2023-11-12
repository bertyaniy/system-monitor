#ifndef BUILDER_H
#define BUILDER_H

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include "../includes/memory.h"
#include "../includes/cpu.h"    

class Builder {
    public: 
        Builder();
        void update_loop();
        void output_builder(Memory::Memory_Info memory_info, CPU::CPU_Info cpu_info);

    private:
        Memory memory;
        CPU cpu;
        int cycle_counter;
};


#endif