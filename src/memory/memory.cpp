#include "../includes/memory.h"

Memory::Memory() : mem_info_file("/proc/meminfo"), factor(1024.0) {}

Memory::Memory_Info Memory::get_memory_info() {
    Memory_Info memory_info;

    auto ifs = std::ifstream(mem_info_file);

    if (!ifs.good()) {
        std::cerr << "Error: unable to get meminfo file" << std::endl;
    }

    std::string line, label;
    std::uint64_t value;

    while (std::getline(ifs, line)) {
        std::stringstream ss{line};

        ss >> label >> value;

        if (label == "MemTotal:") {
            memory_info.mem_total = value / factor;
        }

        if (label == "MemAvailable:") {
            memory_info.mem_available = value / factor;
        }

        memory_info.mem_used = memory_info.mem_total - memory_info.mem_available;
    }

    return memory_info;
}