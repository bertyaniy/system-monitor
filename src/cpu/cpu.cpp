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
    return cpu_info;
}

float CPU::get_cpu_usage() {
    std::vector<long> initial_cpu_times = get_cpu_times();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::vector<long> final_cpu_times = get_cpu_times();

    if (initial_cpu_times.size() != final_cpu_times.size()) {
        std::cerr << "Error: unable to calculate CPU usage" << std::endl;
        return 1.0;
    }

    long total_initial = std::accumulate(initial_cpu_times.begin(), initial_cpu_times.end(), 0L);
    long total_final = std::accumulate(final_cpu_times.begin(), final_cpu_times.end(), 0L);

    if (total_initial == total_final) {
        std::cerr << "Error: total CPU time did not change" << std::endl;
        return 2.0;
    }

    long usage_diff = total_final - total_initial;
    float usage_percentage = 100.0 * static_cast<float>(usage_diff) / (total_final - total_initial);

    return usage_percentage;
}

std::vector<long> CPU::get_cpu_times() {
    auto cpu_u_ifs = std::ifstream(cpu_usage_file);
    std::vector<long> cpu_times;

    std::string line, label;

    while (std::getline(cpu_u_ifs, line)) {
        std::stringstream ss{line};

        ss >> label;

        if (label == "cpu" && !parse_cpu_line(ss, cpu_times)) {
            break;
        }
    }

    cpu_u_ifs.close();
    return cpu_times;
}

bool CPU::parse_cpu_line(std::stringstream& ss, std::vector<long>& cpu_times) {
    std::string label;

    while (ss >> label) {
        if (label.find("cpu") == std::string::npos) {
            return false;
        }
    }

    long time;
    while (ss >> time) {
        cpu_times.push_back(time);
    }
    return true;
}