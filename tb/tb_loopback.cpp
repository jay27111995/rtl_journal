#include "Vloopback.h"
#include "verilated.h"
#include <cstdio>

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Vloopback* dut = new Vloopback;

    printf("Encoder/Decoder loopback test:\n");
    for (int i = 0; i < 4; i++) {
        dut->in = i;
        dut->eval();
        printf("  in=%d -> out=%d %s\n", i, dut->out,
               dut->in == dut->out ? "OK" : "FAIL");
    }

    delete dut;
    printf("PASS\n");
    return 0;
}
