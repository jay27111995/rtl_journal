#include "Vuart_loopback.h"
#include "verilated.h"
#include <cstdio>

void tick(Vuart_loopback* dut) {
    dut->clk = 0; dut->eval();
    dut->clk = 1; dut->eval();
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Vuart_loopback* dut = new Vuart_loopback;

    // Reset
    dut->rst = 1;
    dut->tx_start = 0;
    tick(dut);
    dut->rst = 0;
    tick(dut);

    printf("UART Loopback Test\n\n");

    // Test several bytes
    uint8_t test_bytes[] = {0xA5, 0x55, 0xFF, 0x00, 0x42};
    int num_tests = sizeof(test_bytes) / sizeof(test_bytes[0]);

    for (int t = 0; t < num_tests; t++) {
        uint8_t tx_byte = test_bytes[t];
        printf("Sending 0x%02X: ", tx_byte);

        // Start transmission
        dut->tx_data = tx_byte;
        dut->tx_start = 1;
        tick(dut);
        dut->tx_start = 0;

        // Wait for transmission and reception
        int cycles = 0;
        int received = 0;
        while (cycles < 500) {
            tick(dut);
            cycles++;
            if (dut->rx_valid) {
                received = 1;
                break;
            }
        }

        if (received) {
            printf("received 0x%02X", dut->rx_data);
            if (dut->rx_data == tx_byte)
                printf(" - PASS\n");
            else
                printf(" - FAIL (expected 0x%02X)\n", tx_byte);
        } else {
            printf("TIMEOUT - FAIL\n");
        }

        // Wait for idle
        while (dut->tx_busy)
            tick(dut);
        
        // A few idle cycles
        for (int i = 0; i < 10; i++)
            tick(dut);
    }

    delete dut;
    printf("\nDone.\n");
    return 0;
}
