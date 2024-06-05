#include <SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

#include "memorymapper/memorymapper.h"
#include "bios/bios.h"
#include "cpu/cpu.h"
#include "debugger/debugger.h"

int main(int argc, char* argv[])
{
    Debugger debugger = Debugger();
    setup_opcodes();
    Bios bios = Bios("bin/SCPH1001.BIN");
    MemoryMapper memoryMapper = MemoryMapper(bios);
    CPU cpu = CPU(memoryMapper);

    SDL_Init(SDL_INIT_VIDEO);

    // almost full screen

    SDL_Window* window = SDL_CreateWindow("PS1 Emulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1680, 1050, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // init imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    bool running = true;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }

        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // CPu WINDOW --
        // STEP AND PAUSE BUTTONS
        // REGISTER VIEW (collapsable) and doesnt take the whole window
        // Flag checkboxes

        ImGui::Begin("CPU");
        if(ImGui::Button("Step"))
        {
            debugger.do_step = true;
        }
        ImGui::SameLine();
        if(ImGui::Button("Step Mode"))
        {
            debugger.step_mode = !debugger.step_mode;
        }
        ImGui::SameLine();
        ImGui::Button("Pause");

        
        ImGui::Spacing();
        // CURRENT INSTUCTION BEING EXECUTED
        ImGui::Text("Instruction: %s", get_formatted_instruction(cpu.currentInstruction).c_str());

        // Registers in the same window (COLLAPSABLE)
        // some white space
        if (ImGui::CollapsingHeader("Registers"))
        {
            // registers in a grid layout USING FOR LOOP
            ImGui::Columns(2, "Registers");
            ImGui::Text("Register");
            ImGui::NextColumn();
            ImGui::Text("Value");
            ImGui::NextColumn();
            ImGui::Text("PC");
            ImGui::NextColumn();
            ImGui::Text("0x%08X", cpu.registers.pc);
            ImGui::NextColumn();
            for (int i = 0; i < 32; i++)
            {
                ImGui::Text("R%d", i);
                ImGui::NextColumn();
                ImGui::Text("0x%08X", cpu.registers.get_register(i));
                ImGui::NextColumn();
            }

        }


        ImGui::End();
        // next to this, horizontal tab with 2 tabs, instruction view and memory view
        ImGui::Begin("Memory");
        if (ImGui::BeginTabBar("MemoryTabs"))
        {
            if (ImGui::BeginTabItem("Instructions"))
            {
                // show instructions
                ImGui::Text("Instructions");
                // loop through memory and display instructions
                for (int i = 0; i < 25; i++)
                {
                    uint32_t program_counter = cpu.registers.pc + i * 4;
                    uint32_t instruction = cpu.load32(program_counter);
                    std::string formatted_instruction = get_formatted_instruction(Instruction(instruction));
                    ImGui::Text("0x%08X: %s", program_counter, formatted_instruction.c_str());
                }
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Memory"))
            {
                // show memory
                ImGui::Text("Memory");
                // loop through memory and display in chunks of 4 bytes
                for (int i = 0; i < 25; i++)
                {
                    uint32_t program_counter = cpu.registers.pc + i * 4;
                    uint32_t instruction = cpu.load32(program_counter);
                    ImGui::Text("0x%08X: 0x%08X", program_counter, instruction);
                }
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }

        ImGui::End();


        ImGui::Render();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
        SDL_RenderPresent(renderer);


        if (debugger.step_mode && debugger.do_step)
        {
            cpu.step();
            debugger.do_step = false;
        }
    }

    return 0;

}
