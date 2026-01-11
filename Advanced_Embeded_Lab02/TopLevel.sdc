create_clock -name {INPUT_CLOCK} -period 20.000 [get_ports {INPUT_CLOCK}]
derive_pll_clocks
derive_clock_uncertainty