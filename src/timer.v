// Timer - toggles tick output every 100 clock cycles
module timer (
    input  clk,
    input  rst,
    output reg tick
);

reg [6:0] count;  // 7 bits for 0-99

always @(posedge clk or posedge rst) begin
    if (rst) begin
        count <= 0;
        tick  <= 0;
    end
    else if (count == 99) begin
        count <= 0;
        tick  <= ~tick;  // toggle
    end
    else begin
        count <= count + 1;
    end
end

endmodule
