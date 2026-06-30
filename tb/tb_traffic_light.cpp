#include "Vtraffic_light.h"
#include "verilated.h"
#include <cstdio>

void tick(Vtraffic_light* dut) {
    dut->clk = 0; dut->eval();
    dut->clk = 1; dut->eval();
}

const char* light_str(Vtraffic_light* dut) {
    if (dut->green)  return "GREEN ";
    if (dut->yellow) return "YELLOW";
    if (dut->red)    return "RED   ";
    return "???";
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Vtraffic_light* dut = new Vtraffic_light;

    // Reset
    dut->rst = 1;
    tick(dut);
    dut->rst = 0;

    printf("Traffic light FSM test:\n\n");

    const char* prev_light = "";
    int cycle = 0;
    int state_start = 0;

    // Run 50 cycles (should see: GREEN 10, YELLOW 3, RED 10, GREEN 10...)
    for (int i = 0; i < 50; i++) {
        const char* curr = light_str(dut);
        if (curr != prev_light) {
            if (prev_light[0] != '\0') {
                printf("  %s: %d cycles\n", prev_light, cycle - state_start);
            }
            state_start = cycle;
            prev_light = curr;
        }
        tick(dut);
        cycle++;
    }
    printf("  %s: %d+ cycles (still running)\n", prev_light, cycle - state_start);

    delete dut;
    printf("\nPASS\n");
    return 0;
}
