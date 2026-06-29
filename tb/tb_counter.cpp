#include "Vcounter.h"
#include "verilated.h"
#include <cstdio>

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Vcounter* dut = new Vcounter;

    // Reset
    dut->rst = 1;
    dut->clk = 0;
    dut->eval();
    dut->clk = 1;
    dut->eval();
    dut->rst = 0;

    // Count 20 cycles
    printf("Counter test:\n");
    for (int i = 0; i < 20; i++) {
        dut->clk = 0;
        dut->eval();
        dut->clk = 1;
        dut->eval();
        printf("  cycle %2d: count = %d\n", i, dut->count);
    }

    delete dut;
    printf("PASS\n");
    return 0;
}
