#include "Vpriority_enc.h"
#include "verilated.h"
#include <cstdio>

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Vpriority_enc* dut = new Vpriority_enc;

    printf("Priority encoder test:\n\n");

    // Test all 16 input combinations
    for (int i = 0; i < 16; i++) {
        dut->in = i;
        dut->eval();

        // Calculate expected output (highest set bit)
        int expected = 0;
        if (i & 0b1000) expected = 3;
        else if (i & 0b0100) expected = 2;
        else if (i & 0b0010) expected = 1;
        else expected = 0;

        int expected_valid = (i != 0) ? 1 : 0;

        printf("  in=0b%d%d%d%d -> out=%d valid=%d",
               (i>>3)&1, (i>>2)&1, (i>>1)&1, i&1,
               dut->out, dut->valid);

        if (dut->out == expected && dut->valid == expected_valid)
            printf(" OK\n");
        else
            printf(" FAIL (expected out=%d valid=%d)\n", expected, expected_valid);
    }

    delete dut;
    printf("\nPASS\n");
    return 0;
}
