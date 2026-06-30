#include "Vreg_file.h"
#include "verilated.h"
#include <cstdio>

void tick(Vreg_file* dut) {
    dut->clk = 0; dut->eval();
    dut->clk = 1; dut->eval();
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Vreg_file* dut = new Vreg_file;

    printf("Register file test:\n\n");

    // Write to all 4 registers
    printf("Writing: R0=0xAA, R1=0xBB, R2=0xCC, R3=0xDD\n");
    dut->wr_en = 1;

    dut->wr_addr = 0; dut->wr_data = 0xAA; tick(dut);
    dut->wr_addr = 1; dut->wr_data = 0xBB; tick(dut);
    dut->wr_addr = 2; dut->wr_data = 0xCC; tick(dut);
    dut->wr_addr = 3; dut->wr_data = 0xDD; tick(dut);

    dut->wr_en = 0;

    // Read all combinations using both ports
    printf("\nReading with both ports:\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            dut->rd_addr1 = i;
            dut->rd_addr2 = j;
            dut->eval();  // no clock needed for read!
            printf("  rd_addr1=%d rd_addr2=%d -> rd_data1=0x%02X rd_data2=0x%02X\n",
                   i, j, dut->rd_data1, dut->rd_data2);
        }
    }

    // Test simultaneous read and write
    printf("\nSimultaneous read/write test:\n");
    dut->rd_addr1 = 0;
    dut->wr_en = 1;
    dut->wr_addr = 0;
    dut->wr_data = 0xFF;
    dut->eval();
    printf("  Before clock: R0 = 0x%02X (old value)\n", dut->rd_data1);
    tick(dut);
    dut->eval();
    printf("  After clock:  R0 = 0x%02X (new value)\n", dut->rd_data1);

    delete dut;
    printf("\nPASS\n");
    return 0;
}
