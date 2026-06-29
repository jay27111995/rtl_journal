#include "Vmux2.h"
#include "verilated.h"
#include <cstdio>

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Vmux2* dut = new Vmux2;

    printf("Mux2 test:\n");
    for (int a = 0; a <= 1; a++) {
        for (int b = 0; b <= 1; b++) {
            for (int sel = 0; sel <= 1; sel++) {
                dut->a = a;
                dut->b = b;
                dut->sel = sel;
                dut->eval();
                int expected = sel ? b : a;
                printf("  a=%d b=%d sel=%d -> y=%d (expected %d) %s\n",
                       a, b, sel, dut->y, expected,
                       dut->y == expected ? "OK" : "FAIL");
            }
        }
    }

    delete dut;
    printf("PASS\n");
    return 0;
}
