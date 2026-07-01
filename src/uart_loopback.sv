// UART Loopback - connects TX to RX for testing
module uart_loopback (
    input  logic clk,
    input  logic rst,
    input  logic [7:0] tx_data,
    input  logic tx_start,
    output logic [7:0] rx_data,
    output logic rx_valid,
    output logic tx_busy
);

wire serial;

uart_tx tx_inst (
    .clk(clk),
    .rst(rst),
    .data(tx_data),
    .start(tx_start),
    .tx(serial),
    .busy(tx_busy)
);

uart_rx rx_inst (
    .clk(clk),
    .rst(rst),
    .rx(serial),
    .data(rx_data),
    .valid(rx_valid)
);

endmodule
