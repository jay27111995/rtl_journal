// UART Receiver
// Receives serial data: START(0) + 8 data bits (LSB first) + STOP(1)
// 16 clocks per bit, samples in middle
module uart_rx (
    input  logic clk,
    input  logic rst,
    input  logic rx,
    output logic [7:0] data,
    output logic valid
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
        valid <= 0;
        data <= 0;
    end else begin
        valid <= 0;
        
        case (state)
            IDLE: begin
                if (rx == 0) begin
                    baud_cnt <= 7;      // half bit time to get to middle
                    state <= START;
                end
            end
            START: begin
                if (baud_cnt == 0) begin
                    if (rx == 0) begin  // confirm valid start bit
                        baud_cnt <= 15;
                        bit_cnt <= 0;
                        state <= DATA;
                    end else
                        state <= IDLE;  // false start
                end else
                    baud_cnt <= baud_cnt - 1;
            end
            DATA: begin
                if (baud_cnt == 0) begin
                    shift_reg <= {rx, shift_reg[7:1]};  // shift in from left
                    baud_cnt <= 15;
                    if (bit_cnt == 7)
                        state <= STOP;
                    else
                        bit_cnt <= bit_cnt + 1;
                end else
                    baud_cnt <= baud_cnt - 1;
            end
            STOP: begin
                if (baud_cnt == 0) begin
                    if (rx == 1) begin  // valid stop bit
                        data <= shift_reg;
                        valid <= 1;
                    end
                    state <= IDLE;
                end else
                    baud_cnt <= baud_cnt - 1;
            end
        endcase
    end
end

endmodule
