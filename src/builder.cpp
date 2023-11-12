#include "../includes/builder.h"
#include "../includes/memory.h"

Builder::Builder(): memory(), cycle_counter(0) {}

void Builder::update_loop() {
    Memory::Memory_Info memory_info = memory.get_memory_info();

    if (cycle_counter >= 1) {
        for (int i = 0; i < 3; ++i) {
            std::cout << "\033[F"; // ANSI escape code to move the cursor up one line
            std::cout << "\033[K"; // ANSI escape code to clear the line
        }
    }
    
    output_builder(memory_info);

    cycle_counter++;

    std::this_thread::sleep_for(std::chrono::seconds(1));
    update_loop();
}

void Builder::output_builder(Memory::Memory_Info memory_info) {
    std::cout << "Memory total: " << memory_info.mem_total << std::endl;
    std::cout << "Memory used: " << memory_info.mem_used << std::endl;
    std::cout << "Memory available: " << memory_info.mem_available << std::endl;
}