#include "Vuart_loopback.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include <cstdio>

vluint64_t sim_time = 0;

void tick(Vuart_loopback* dut, VerilatedVcdC* tfp) {
    dut->clk = 0; 
    dut->eval(); 
    tfp->dump(sim_time++);
    
    dut->clk = 1; 
    dut->eval(); 
    tfp->dump(sim_time++);
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);
    
    Vuart_loopback* dut = new Vuart_loopback;
    VerilatedVcdC* tfp = new VerilatedVcdC;
    dut->trace(tfp, 99);
    tfp->open("uart_wave.vcd");

    // Reset
    dut->rst = 1;
    dut->tx_start = 0;
    tick(dut, tfp);
    dut->rst = 0;
    tick(dut, tfp);

    printf("UART Loopback Test (with waveform)\n\n");

    // Test one byte with full trace
    uint8_t tx_byte = 0xA5;
    printf("Sending 0x%02X: ", tx_byte);

    // Start transmission
    dut->tx_data = tx_byte;
    dut->tx_start = 1;
    tick(dut, tfp);
    dut->tx_start = 0;

    // Wait for transmission and reception
    int cycles = 0;
    int received = 0;
    while (cycles < 500) {
        tick(dut, tfp);
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
            printf(" - FAIL\n");
    } else {
        printf("TIMEOUT - FAIL\n");
    }

    // A few more idle cycles for waveform
    for (int i = 0; i < 50; i++)
        tick(dut, tfp);

    tfp->close();
    delete tfp;
    delete dut;
    
    printf("\nWaveform saved to uart_wave.vcd\n");
    printf("View with: surfer uart_wave.vcd\n");
    return 0;
}
