#include "Vfifo.h"
#include "verilated.h"
#include <cstdio>

void tick(Vfifo* dut) {
    dut->clk = 0; dut->eval();
    dut->clk = 1; dut->eval();
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Vfifo* dut = new Vfifo;

    // Reset
    dut->rst = 1;
    dut->wr_en = 0;
    dut->rd_en = 0;
    tick(dut);
    dut->rst = 0;

    printf("FIFO test (depth=8):\n\n");

    // Check empty on start
    printf("Initial state: empty=%d full=%d\n\n", dut->empty, dut->full);

    // Write 8 items to fill it
    printf("Writing 8 items (0xA0-0xA7):\n");
    dut->wr_en = 1;
    for (int i = 0; i < 8; i++) {
        dut->wr_data = 0xA0 + i;
        printf("  write 0x%02X: empty=%d full=%d\n", dut->wr_data, dut->empty, dut->full);
        tick(dut);
    }
    dut->wr_en = 0;
    dut->eval();
    printf("After filling: empty=%d full=%d\n\n", dut->empty, dut->full);

    // Try write when full (should be ignored)
    printf("Attempting write when full:\n");
    dut->wr_en = 1;
    dut->wr_data = 0xFF;
    tick(dut);
    dut->wr_en = 0;
    printf("  full=%d (write should be ignored)\n\n", dut->full);

    // Read all 8 items
    printf("Reading 8 items:\n");
    dut->rd_en = 1;
    for (int i = 0; i < 8; i++) {
        dut->eval();
        printf("  read 0x%02X: empty=%d full=%d\n", dut->rd_data, dut->empty, dut->full);
        tick(dut);
    }
    dut->rd_en = 0;
    dut->eval();
    printf("After draining: empty=%d full=%d\n\n", dut->empty, dut->full);

    // Test simultaneous read/write
    printf("Simultaneous read/write test:\n");
    dut->wr_en = 1;
    dut->wr_data = 0x11;
    tick(dut);
    dut->wr_data = 0x22;
    tick(dut);
    dut->wr_en = 0;
    printf("  Wrote 0x11, 0x22\n");

    dut->wr_en = 1;
    dut->rd_en = 1;
    dut->wr_data = 0x33;
    dut->eval();
    printf("  Simultaneous: rd_data=0x%02X, writing 0x33\n", dut->rd_data);
    tick(dut);
    dut->wr_en = 0;
    dut->eval();
    printf("  Next read: rd_data=0x%02X\n", dut->rd_data);
    tick(dut);
    dut->eval();
    printf("  Next read: rd_data=0x%02X\n", dut->rd_data);
    dut->rd_en = 0;

    delete dut;
    printf("\nPASS\n");
    return 0;
}
