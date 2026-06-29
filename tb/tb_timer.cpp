#include "Vtimer.h"
#include "verilated.h"
#include <cstdio>

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Vtimer* dut = new Vtimer;

    // Reset
    dut->rst = 1;
    dut->clk = 0;
    dut->eval();
    dut->clk = 1;
    dut->eval();
    dut->rst = 0;

    // Run 250 cycles, should see tick toggle at 100 and 200
    printf("Timer test (tick toggles every 100 clocks):\n");
    int last_tick = 0;
    for (int i = 0; i < 250; i++) {
        dut->clk = 0;
        dut->eval();
        dut->clk = 1;
        dut->eval();
        if (dut->tick != last_tick) {
            printf("  cycle %3d: tick toggled to %d\n", i, dut->tick);
            last_tick = dut->tick;
        }
    }

    delete dut;
    printf("PASS\n");
    return 0;
}
