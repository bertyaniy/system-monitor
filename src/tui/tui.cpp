#include "../includes/tui.h"

TUI::TUI(): memory(), cpu() {};

int TUI::generate_screen(Memory::Memory_Info memory_info, CPU::CPU_Info cpu_info) {

    memory_info = memory.get_memory_info();
    cpu_info = cpu.get_cpu_info();

    using namespace ftxui;
    
    auto screen = ScreenInteractive::Fullscreen();

    auto cpu_name_label = text(L"CPU Model") | bold | border;
    auto cpu_usage_label = text(L"CPU Usage") | bold | border;

    auto memory_used_label = text(L"Memory used") | bold | border;

    auto cpu_name_value = text(cpu_info.name);
    auto cpu_usage_value = gauge(cpu_info.usage);

    auto memory_value = gauge(memory_info.mem_used);


    Element body = vbox({
        hbox({
            text(L"System Monitoring") | border,
        }), 
        separator(),
        hbox({
            vbox({cpu_name_label, cpu_usage_label, memory_used_label}) | border,
            vbox({cpu_name_value, cpu_usage_value, memory_value}) | border,
        }) | border,
    });

    auto container = Container::Vertical({
        Renderer([&body] { return body; })
    });

    screen.Loop(container);


    return EXIT_SUCCESS;
}

