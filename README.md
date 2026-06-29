# RTL Journal

Verilog/SystemVerilog learning examples.

## Modules

| Module | Description |
|--------|-------------|
| `counter.v` | 4-bit counter with synchronous reset |
| `timer.v` | Prescaler - toggles output every 100 clocks |
| `mux2.v` | 2:1 mux using `assign` (continuous assignment) |
| `mux4.v` | 4:1 mux using `always @(*)` (combinational block) |

## Concepts

### Sequential vs Combinational

- **Sequential**: `always @(posedge clk)` - uses flip-flops, state changes on clock edge
- **Combinational**: `assign` or `always @(*)` - pure logic, no storage

### Non-blocking vs Blocking

- `<=` (non-blocking): Use in sequential logic - all assignments happen simultaneously
- `=` (blocking): Use in combinational logic - assignments happen in order
