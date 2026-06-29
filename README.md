# RTL Journal

Verilog/SystemVerilog learning examples.

## Structure

```
src/           # Verilog modules
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

- **Sequential**: `always @(posedge clk)` - uses flip-flops, state changes on clock edge
- **Combinational**: `assign` or `always @(*)` - pure logic, no storage

### Non-blocking vs Blocking

- `<=` (non-blocking): Use in sequential logic - all assignments happen simultaneously
- `=` (blocking): Use in combinational logic - assignments happen in order
