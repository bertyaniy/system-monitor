#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <numeric>
#include <thread>
#include <chrono>

class CPU {
    public:
        CPU();
        struct CPU_Info {
            std::string name;
            float usage;
        };
        
        CPU_Info get_cpu_info();
        float get_cpu_usage();
        std::vector<long> get_cpu_times();
        bool parse_cpu_line(std::stringstream& ss, std::vector<long>& cpu_times);
    
    private:
        const char* cpu_info_file;
        const char* cpu_usage_file;
        const double factor;
};

#endif