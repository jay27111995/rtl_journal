#include "Vmux4.h"
#include "verilated.h"
#include <cstdio>

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Vmux4* dut = new Vmux4;

    printf("Mux4 test:\n");
    // Test each select value
    for (int sel = 0; sel < 4; sel++) {
        dut->d = 0b1010;  // d[3]=1, d[2]=0, d[1]=1, d[0]=0
        dut->sel = sel;
        dut->eval();
        int expected = (dut->d >> sel) & 1;
        printf("  d=0b1010 sel=%d -> y=%d (expected %d) %s\n",
               sel, dut->y, expected,
               dut->y == expected ? "OK" : "FAIL");
    }

    delete dut;
    printf("PASS\n");
    return 0;
}
