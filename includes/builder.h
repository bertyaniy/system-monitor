#ifndef BUILDER_H
#define BUILDER_H

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include "../includes/memory.h"

class Builder {
    public: 
        Builder();
        void update_loop();
        void output_builder(Memory::Memory_Info memory_info);

    private:
        Memory memory;
        int cycle_counter;
};


#endif