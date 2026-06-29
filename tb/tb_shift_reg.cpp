#include "Vshift_reg.h"
#include "verilated.h"
#include <cstdio>

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Vshift_reg* dut = new Vshift_reg;

    // Reset
    dut->rst = 1;
    dut->clk = 0; dut->eval();
    dut->clk = 1; dut->eval();
    dut->rst = 0;

    // Shift in byte 0xA5 = 10100101 (MSB first)
    uint8_t byte_to_send = 0xA5;
    printf("Shift register test: sending 0x%02X\n\n", byte_to_send);

    for (int i = 7; i >= 0; i--) {
        int bit = (byte_to_send >> i) & 1;
        dut->serial_in = bit;
        dut->clk = 0; dut->eval();
        dut->clk = 1; dut->eval();
        printf("  bit %d: in=%d  parallel_out=0b%08b (0x%02X)\n",
               7-i, bit, dut->parallel_out, dut->parallel_out);
    }

    printf("\nFinal: 0x%02X", dut->parallel_out);
    if (dut->parallel_out == byte_to_send)
        printf(" - PASS\n");
    else
        printf(" - FAIL (expected 0x%02X)\n", byte_to_send);

    delete dut;
    return 0;
}
