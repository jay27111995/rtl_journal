// FIFO: 8 entries x 8 bits
// First In, First Out buffer
module fifo #(
    parameter DEPTH = 8,
    parameter WIDTH = 8
)(
    input  logic clk,
    input  logic rst,
    input  logic wr_en,
    input  logic [WIDTH-1:0] wr_data,
    input  logic rd_en,
    output logic [WIDTH-1:0] rd_data,
    output logic full,
    output logic empty
);

logic [WIDTH-1:0] mem [0:DEPTH-1];
logic [$clog2(DEPTH):0] wr_ptr, rd_ptr;  // extra bit for full/empty detection

// Pointer update (sequential)
always_ff @(posedge clk or posedge rst) begin
    if (rst) begin
        wr_ptr <= 0;
        rd_ptr <= 0;
    end else begin
        if (wr_en && !full)
            wr_ptr <= wr_ptr + 1;
        if (rd_en && !empty)
            rd_ptr <= rd_ptr + 1;
    end
end

// Write (sequential)
always_ff @(posedge clk) begin
    if (wr_en && !full)
        mem[wr_ptr[$clog2(DEPTH)-1:0]] <= wr_data;
end

// Read (combinational - always visible)
assign rd_data = mem[rd_ptr[$clog2(DEPTH)-1:0]];

// Full: MSB differs, lower bits same (write is one lap ahead)
assign full  = (wr_ptr[$clog2(DEPTH)] != rd_ptr[$clog2(DEPTH)]) &&
               (wr_ptr[$clog2(DEPTH)-1:0] == rd_ptr[$clog2(DEPTH)-1:0]);

// Empty: pointers equal
assign empty = (wr_ptr == rd_ptr);

endmodule
