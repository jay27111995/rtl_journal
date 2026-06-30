#!/bin/bash
# Build and run all testbenches

set -e
cd "$(dirname "$0")"

run_test() {
    local name=$1
    local top=$2
    local src=$3
    echo "=== Testing $name ==="
    verilator --cc ../src/$src --top-module $top --exe tb_${name}.cpp --build -j 0
    ./obj_dir/V${top}
    echo ""
}

run_test counter counter counter.v
run_test timer timer timer.v
run_test mux2 mux2 mux2.v
run_test mux4 mux4 mux4.v
run_test loopback loopback encoder_decoder.v
run_test shift_reg shift_reg shift_reg.v
run_test priority_enc priority_enc priority_enc.sv
run_test traffic_light traffic_light traffic_light.sv
run_test reg_file reg_file reg_file.sv
run_test fifo fifo fifo.sv

echo "=== All tests passed ==="
