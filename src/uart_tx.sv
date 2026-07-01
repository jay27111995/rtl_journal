// UART Transmitter
// Sends 8-bit data as serial: START(0) + 8 data bits (LSB first) + STOP(1)
// 16 clocks per bit
module uart_tx (
    input  logic clk,
    input  logic rst,
    input  logic [7:0] data,
    input  logic start,
    output logic tx,
    output logic busy
);

typedef enum logic [1:0] {
    IDLE  = 2'b00,
    START = 2'b01,
    DATA  = 2'b10,
    STOP  = 2'b11
} state_t;

state_t state;
logic [7:0] shift_reg;
logic [2:0] bit_cnt;
logic [3:0] baud_cnt;

always_ff @(posedge clk or posedge rst) begin
    if (rst) begin
        state <= IDLE;
        tx <= 1;
        busy <= 0;
    end else begin
        case (state)
            IDLE: begin
                tx <= 1;
                if (start) begin
                    shift_reg <= data;
                    baud_cnt <= 15;
                    busy <= 1;
                    state <= START;
                end
            end
            START: begin
                tx <= 0;
                if (baud_cnt == 0) begin
                    baud_cnt <= 15;
                    bit_cnt <= 0;
                    state <= DATA;
                end else
                    baud_cnt <= baud_cnt - 1;
            end
            DATA: begin
                tx <= shift_reg[0];
                if (baud_cnt == 0) begin
                    shift_reg <= {1'b0, shift_reg[7:1]};
                    baud_cnt <= 15;
                    if (bit_cnt == 7)
                        state <= STOP;
                    else
                        bit_cnt <= bit_cnt + 1;
                end else
                    baud_cnt <= baud_cnt - 1;
            end
            STOP: begin
                tx <= 1;
                if (baud_cnt == 0) begin
                    busy <= 0;
                    state <= IDLE;
                end else
                    baud_cnt <= baud_cnt - 1;
            end
        endcase
    end
end

endmodule
