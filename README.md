# RTL Journal

Verilog/SystemVerilog learning examples.

## Structure

```
src/           # Verilog/SystemVerilog modules
tb/            # Verilator C++ testbenches
```

## Modules

| Module | Description |
|--------|-------------|
| `counter.v` | 4-bit counter with asynchronous reset |
| `timer.v` | Prescaler - toggles output every 100 clocks |
| `mux2.v` | 2:1 mux using `assign` (continuous assignment) |
| `mux4.v` | 4:1 mux using `always @(*)` (combinational block) |
| `encoder_decoder.v` | Encoder, decoder, and loopback demo |
| `shift_reg.v` | 8-bit serial-in parallel-out shift register |
| `priority_enc.sv` | 4-bit priority encoder (SystemVerilog) |
| `traffic_light.sv` | Traffic light FSM with timer (SystemVerilog) |
| `reg_file.sv` | 4x8-bit register file, 2 read + 1 write port |
| `fifo.sv` | 8-entry FIFO with full/empty flags |

## Running Tests

Requires Verilator. On systems with modules:

```bash
module load verilator/5.024
cd tb
./run_tests.sh
```

Or run individual tests:

```bash
cd tb
verilator --cc ../src/counter.v --top-module counter --exe tb_counter.cpp --build -j 0
./obj_dir/Vcounter
```

## Concepts

### Sequential vs Combinational

- **Sequential**: `always_ff @(posedge clk)` - uses flip-flops, state changes on clock edge
- **Combinational**: `assign` or `always_comb` - pure logic, no storage

### Non-blocking vs Blocking

- `<=` (non-blocking): Use in sequential logic - all assignments happen simultaneously
- `=` (blocking): Use in combinational logic - assignments happen in order

### Verilog vs SystemVerilog

- Verilog: `reg`, `wire`, `always @(*)`
- SystemVerilog: `logic`, `always_comb`, `always_ff`, `typedef enum`
