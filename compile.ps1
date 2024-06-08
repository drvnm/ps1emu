C:\Users\venum\Downloads\x86_64-8.1.0-release-posix-seh-rt_v6-rev0\mingw64\bin\g++.exe -std=c++2a main.cpp  `
bios/bios.cpp `
common/defs.cpp `
cpu/cpu.cpp `
cpu/registers.cpp `
cpu/cpu_instructions/instruction.cpp `
cpu/cpu_instructions/loads.cpp `
cpu/cpu_instructions/setup_opcodes.cpp `
cpu/cpu_instructions/alu.cpp `
memorymapper/memorymapper.cpp `
imgui/imgui.cpp `
imgui/imgui_demo.cpp `
imgui/imgui_draw.cpp `
imgui/imgui_widgets.cpp `
imgui/imgui_impl_sdl2.cpp `
imgui/imgui_impl_sdlrenderer2.cpp `
imgui/imgui_tables.cpp `
-I"./include/SDL2" `
-I"./include/imgui" `
-I"./include/fmt" `
-L"./lib" -Wall -lmingw32 `
-L"./imgui" `
-lSDL2main -lSDL2 `
 -o main.exe ; ./main.exe