// 4:1 Multiplexer - using always block
module mux4 (
    input  [3:0] d,     // 4 data inputs
    input  [1:0] sel,   // 2-bit select
    output reg y
);

// Combinational always block
always @(*) begin
    case (sel)
        2'b00: y = d[0];
        2'b01: y = d[1];
        2'b10: y = d[2];
        2'b11: y = d[3];
    endcase
end

endmodule
