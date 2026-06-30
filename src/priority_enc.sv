// 4-bit priority encoder
// Outputs index of highest-priority active input
module priority_enc (
    input  logic [3:0] in,
    output logic [1:0] out,
    output logic valid
);

assign valid = |in;

always_comb begin
    if (in[3])
        out = 2'b11;
    else if (in[2])
        out = 2'b10;
    else if (in[1])
        out = 2'b01;
    else
        out = 2'b00;
end

endmodule
