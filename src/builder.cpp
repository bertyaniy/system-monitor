#include "../includes/builder.h"
#include "../includes/memory.h"

Builder::Builder(): memory(), cpu(), cycle_counter(0) {}

void Builder::update_loop() {
    Memory::Memory_Info memory_info = memory.get_memory_info();
    CPU::CPU_Info cpu_info = cpu.get_cpu_info();

    if (cycle_counter >= 1) {
        for (int i = 0; i < 7; ++i) {
            std::cout << "\033[F"; // ANSI escape code to move the cursor up one line
            std::cout << "\033[K"; // ANSI escape code to clear the line
        }
    }
    
    output_builder(memory_info, cpu_info);

    cycle_counter++;

    std::this_thread::sleep_for(std::chrono::seconds(1));
    update_loop();
}

void Builder::output_builder(Memory::Memory_Info memory_info, CPU::CPU_Info cpu_info) {
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "Memory total: " << memory_info.mem_total << std::endl;
    std::cout << "Memory used: " << memory_info.mem_used << std::endl;
    std::cout << "Memory available: " << memory_info.mem_available << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "CPU Model name: " << cpu_info.name << std::endl;
    std::cout << "CPU Usage: " << cpu_info.usage << std::endl;
}