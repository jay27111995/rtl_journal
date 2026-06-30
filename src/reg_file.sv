// Register file: 4 registers x 8 bits
// 2 read ports (combinational), 1 write port (sequential)
module reg_file (
    input  logic clk,
    input  logic wr_en,
    input  logic [1:0] wr_addr,
    input  logic [7:0] wr_data,
    input  logic [1:0] rd_addr1,
    input  logic [1:0] rd_addr2,
    output logic [7:0] rd_data1,
    output logic [7:0] rd_data2
);

logic [7:0] regs [0:3];

// Write (sequential - on clock edge)
always_ff @(posedge clk) begin
    if (wr_en)
        regs[wr_addr] <= wr_data;
end

// Read (combinational - instant)
assign rd_data1 = regs[rd_addr1];
assign rd_data2 = regs[rd_addr2];

endmodule
