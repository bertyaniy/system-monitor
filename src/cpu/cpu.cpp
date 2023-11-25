#include "../includes/cpu.h"

CPU::CPU(): cpu_info_file("/proc/cpuinfo"), cpu_usage_file("/proc/stat"), factor(1024.0) {}

CPU::CPU_Info CPU::get_cpu_info() {
    CPU_Info cpu_info;
    
    auto cpu_i_ifs = std::ifstream(cpu_info_file);

    if (!cpu_i_ifs.good()) {
        std::cerr << "Error: unable to get CPU info" << std::endl;
        return cpu_info;
    }

    std::string line, label;
    std::string name;
    std::uint64_t value;

    while (std::getline(cpu_i_ifs, line)) {
        std::stringstream ss{line};

        ss >> label >> name;

        if (label == "model" && name == "name") { 
            std::getline(ss >> std::ws, name);

            size_t pos = name.find_first_not_of(" \t:");
            if (pos != std::string::npos) {
                name = name.substr(pos);
            }

            cpu_info.name = name;
            break;
        }
    }

    cpu_i_ifs.close();
    cpu_info.usage = get_cpu_usage();
    std::cout << cpu_info.usage << std::endl;
    return cpu_info;
}

float CPU::get_cpu_usage() {
    auto cpu_u_ifs = std::ifstream(cpu_usage_file);

    std::string line;
    std::getline(cpu_u_ifs, line);

    std::stringstream ss{line};
    std::string label;

    ss >> label;
    if (label != "cpu") {
        return 1.0f;
    }

    int user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
    ss >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;
    
    int idle_time = idle + iowait;
    int total_time = user + nice + system + idle + iowait + irq + softirq + steal;

    static int prev_idle_time = idle_time;
    static int prev_total_time = total_time;

    int idle_time_delta = idle_time - prev_idle_time;
    int total_time_delta = total_time - prev_total_time;

    prev_idle_time = idle_time;
    prev_total_time = total_time;

    float usage = 100.0f * (1.0f - (idle_time_delta / static_cast<float>(total_time_delta)));

    return usage;

}