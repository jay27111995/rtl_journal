// Decoder: 2-bit → 4-bit one-hot
module decoder2to4 (
    input  [1:0] in,
    output reg [3:0] out
);
    always @(*) begin
        case (in)
            2'b00: out = 4'b0001;
            2'b01: out = 4'b0010;
            2'b10: out = 4'b0100;
            2'b11: out = 4'b1000;
        endcase
    end
endmodule

// Encoder: 4-bit one-hot → 2-bit
module encoder4to2 (
    input  [3:0] in,
    output reg [1:0] out
);
    always @(*) begin
        case (in)
            4'b0001: out = 2'b00;
            4'b0010: out = 2'b01;
            4'b0100: out = 2'b10;
            4'b1000: out = 2'b11;
            default: out = 2'b00;
        endcase
    end
endmodule

// Connect them: should get same value back
module loopback (
    input  [1:0] in,
    output [1:0] out
);
    wire [3:0] onehot;
    
    decoder2to4 dec (.in(in), .out(onehot));
    encoder4to2 enc (.in(onehot), .out(out));
endmodule
