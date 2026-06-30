// Traffic light FSM
// GREEN (10 cycles) -> YELLOW (3 cycles) -> RED (10 cycles) -> repeat
module traffic_light (
    input  logic clk,
    input  logic rst,
    output logic green,
    output logic yellow,
    output logic red
);

// State definition
typedef enum logic [1:0] {
    S_GREEN  = 2'b00,
    S_YELLOW = 2'b01,
    S_RED    = 2'b10
} state_t;

state_t state, next_state;
logic [3:0] count;           // timer counter
logic timer_done;

// Timer: counts down each state's duration
always_ff @(posedge clk or posedge rst) begin
    if (rst)
        count <= 4'd10;      // start with GREEN duration
    else if (timer_done)
        // Load next state's duration
        case (next_state)
            S_GREEN:  count <= 4'd10;
            S_YELLOW: count <= 4'd3;
            S_RED:    count <= 4'd10;
            default:  count <= 4'd10;
        endcase
    else
        count <= count - 1;
end

assign timer_done = (count == 1);

// State register (sequential)
always_ff @(posedge clk or posedge rst) begin
    if (rst)
        state <= S_GREEN;
    else
        state <= next_state;
end

// Next state logic (combinational)
always_comb begin
    case (state)
        S_GREEN:  next_state = timer_done ? S_YELLOW : S_GREEN;
        S_YELLOW: next_state = timer_done ? S_RED    : S_YELLOW;
        S_RED:    next_state = timer_done ? S_GREEN  : S_RED;
        default:  next_state = S_GREEN;
    endcase
end

// Output logic
assign green  = (state == S_GREEN);
assign yellow = (state == S_YELLOW);
assign red    = (state == S_RED);

endmodule
