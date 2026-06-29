// 8-bit shift register (Serial In, Parallel Out)
module shift_reg (
    input  clk,
    input  rst,
    input  serial_in,
    output [7:0] parallel_out
);

reg [7:0] data;

always @(posedge clk or posedge rst) begin
    if (rst)
        data <= 8'b0;
    else
        data <= {data[6:0], serial_in};
end

assign parallel_out = data;

endmodule
