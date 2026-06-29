// 2:1 Multiplexer - combinational logic
module mux2 (
    input  a,
    input  b,
    input  sel,
    output y
);

// Continuous assignment - combinational
assign y = sel ? b : a;

endmodule
