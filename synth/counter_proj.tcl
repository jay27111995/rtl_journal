# Create project
project_new -overwrite counter_proj

# Set device (Cyclone V - common dev board chip)
set_global_assignment -name FAMILY "Cyclone V"
set_global_assignment -name DEVICE 5CSEMA5F31C6

# Add source file
set_global_assignment -name SYSTEMVERILOG_FILE ../src/counter.v

# Set top module
set_global_assignment -name TOP_LEVEL_ENTITY counter

# Run synthesis
load_package flow
execute_module -tool map

# Show resource usage
project_close
