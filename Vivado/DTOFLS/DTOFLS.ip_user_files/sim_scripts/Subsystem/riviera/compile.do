vlib work
vlib riviera

vlib riviera/xilinx_vip
vlib riviera/xpm
vlib riviera/xil_defaultlib
vlib riviera/axi_lite_ipif_v3_0_4
vlib riviera/lib_cdc_v1_0_2
vlib riviera/interrupt_control_v3_1_4
vlib riviera/axi_gpio_v2_0_24
vlib riviera/proc_sys_reset_v5_0_13
vlib riviera/v_tc_v6_2_1
vlib riviera/xlconcat_v2_1_4
vlib riviera/xlconstant_v1_1_7

vmap xilinx_vip riviera/xilinx_vip
vmap xpm riviera/xpm
vmap xil_defaultlib riviera/xil_defaultlib
vmap axi_lite_ipif_v3_0_4 riviera/axi_lite_ipif_v3_0_4
vmap lib_cdc_v1_0_2 riviera/lib_cdc_v1_0_2
vmap interrupt_control_v3_1_4 riviera/interrupt_control_v3_1_4
vmap axi_gpio_v2_0_24 riviera/axi_gpio_v2_0_24
vmap proc_sys_reset_v5_0_13 riviera/proc_sys_reset_v5_0_13
vmap v_tc_v6_2_1 riviera/v_tc_v6_2_1
vmap xlconcat_v2_1_4 riviera/xlconcat_v2_1_4
vmap xlconstant_v1_1_7 riviera/xlconstant_v1_1_7

vlog -work xilinx_vip  -sv2k12 "+incdir+C:/Xilinx/Vivado/2020.2/data/xilinx_vip/include" \
"C:/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/axi4stream_vip_axi4streampc.sv" \
"C:/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/axi_vip_axi4pc.sv" \
"C:/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/xil_common_vip_pkg.sv" \
"C:/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/axi4stream_vip_pkg.sv" \
"C:/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/axi_vip_pkg.sv" \
"C:/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/axi4stream_vip_if.sv" \
"C:/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/axi_vip_if.sv" \
"C:/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/clk_vip_if.sv" \
"C:/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/rst_vip_if.sv" \

vlog -work xpm  -sv2k12 "+incdir+../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/ec67/hdl" "+incdir+../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/7860/hdl" "+incdir+../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/d0f7" "+incdir+../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/34f8/hdl" "+incdir+C:/Xilinx/Vivado/2020.2/data/xilinx_vip/include" \
"C:/Xilinx/Vivado/2020.2/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
"C:/Xilinx/Vivado/2020.2/data/ip/xpm/xpm_fifo/hdl/xpm_fifo.sv" \
"C:/Xilinx/Vivado/2020.2/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \

vcom -work xpm -93 \
"C:/Xilinx/Vivado/2020.2/data/ip/xpm/xpm_VCOMP.vhd" \

vcom -work xil_defaultlib -93 \
"../../../bd/Subsystem/ip/Subsystem_PmodOLED_0_0/Subsystem_PmodOLED_0_0_sim_netlist.vhdl" \
"../../../bd/Subsystem/ip/Subsystem_axi_dma_0_0/Subsystem_axi_dma_0_0_sim_netlist.vhdl" \

vcom -work axi_lite_ipif_v3_0_4 -93 \
"../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/66ea/hdl/axi_lite_ipif_v3_0_vh_rfs.vhd" \

vcom -work lib_cdc_v1_0_2 -93 \
"../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/ef1e/hdl/lib_cdc_v1_0_rfs.vhd" \

vcom -work interrupt_control_v3_1_4 -93 \
"../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/a040/hdl/interrupt_control_v3_1_vh_rfs.vhd" \

vcom -work axi_gpio_v2_0_24 -93 \
"../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/4318/hdl/axi_gpio_v2_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -93 \
"../../../bd/Subsystem/ip/Subsystem_axi_gpio_1_0/sim/Subsystem_axi_gpio_1_0.vhd" \
"../../../bd/Subsystem/ip/Subsystem_axi_gpio_2_0/sim/Subsystem_axi_gpio_2_0.vhd" \
"../../../bd/Subsystem/ip/Subsystem_xbar_0/Subsystem_xbar_0_sim_netlist.vhdl" \
"../../../bd/Subsystem/ip/Subsystem_axi_vdma_0_0/Subsystem_axi_vdma_0_0_sim_netlist.vhdl" \
"../../../bd/Subsystem/ip/Subsystem_clk_wiz_0_0/Subsystem_clk_wiz_0_0_sim_netlist.vhdl" \
"../../../bd/Subsystem/ip/Subsystem_processing_system7_0_0/Subsystem_processing_system7_0_0_sim_netlist.vhdl" \
"../../../bd/Subsystem/ip/Subsystem_xbar_1/Subsystem_xbar_1_sim_netlist.vhdl" \
"../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/d57c/src/ClockGen.vhd" \
"../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/d57c/src/SyncAsync.vhd" \
"../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/d57c/src/SyncAsyncReset.vhd" \
"../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/d57c/src/DVI_Constants.vhd" \
"../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/d57c/src/OutputSERDES.vhd" \
"../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/d57c/src/TMDS_Encoder.vhd" \
"../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/d57c/src/rgb2dvi.vhd" \
"../../../bd/Subsystem/ip/Subsystem_rgb2dvi_0_0/sim/Subsystem_rgb2dvi_0_0.vhd" \

vcom -work proc_sys_reset_v5_0_13 -93 \
"../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/8842/hdl/proc_sys_reset_v5_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -93 \
"../../../bd/Subsystem/ip/Subsystem_rst_clk_wiz_0_148M_0/sim/Subsystem_rst_clk_wiz_0_148M_0.vhd" \
"../../../bd/Subsystem/ip/Subsystem_v_axi4s_vid_out_0_0/Subsystem_v_axi4s_vid_out_0_0_sim_netlist.vhdl" \

vcom -work v_tc_v6_2_1 -93 \
"../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/cd2e/hdl/v_tc_v6_2_vh_rfs.vhd" \

vcom -work xil_defaultlib -93 \
"../../../bd/Subsystem/ip/Subsystem_v_tc_0_0/sim/Subsystem_v_tc_0_0.vhd" \

vlog -work xlconcat_v2_1_4  -v2k5 "+incdir+../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/ec67/hdl" "+incdir+../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/7860/hdl" "+incdir+../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/d0f7" "+incdir+../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/34f8/hdl" "+incdir+C:/Xilinx/Vivado/2020.2/data/xilinx_vip/include" \
"../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/4b67/hdl/xlconcat_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/ec67/hdl" "+incdir+../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/7860/hdl" "+incdir+../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/d0f7" "+incdir+../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/34f8/hdl" "+incdir+C:/Xilinx/Vivado/2020.2/data/xilinx_vip/include" \
"../../../bd/Subsystem/ip/Subsystem_xlconcat_1_0/sim/Subsystem_xlconcat_1_0.v" \

vlog -work xlconstant_v1_1_7  -v2k5 "+incdir+../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/ec67/hdl" "+incdir+../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/7860/hdl" "+incdir+../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/d0f7" "+incdir+../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/34f8/hdl" "+incdir+C:/Xilinx/Vivado/2020.2/data/xilinx_vip/include" \
"../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/fcfc/hdl/xlconstant_v1_1_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/ec67/hdl" "+incdir+../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/7860/hdl" "+incdir+../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/d0f7" "+incdir+../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/34f8/hdl" "+incdir+C:/Xilinx/Vivado/2020.2/data/xilinx_vip/include" \
"../../../bd/Subsystem/ip/Subsystem_xlconstant_0_0/sim/Subsystem_xlconstant_0_0.v" \

vcom -work xil_defaultlib -93 \
"../../../bd/Subsystem/ip/Subsystem_Input_Debounce_0_0/sim/Subsystem_Input_Debounce_0_0.vhd" \
"../../../bd/Subsystem/ip/Subsystem_Input_Debounce_0_1/sim/Subsystem_Input_Debounce_0_1.vhd" \
"../../../bd/Subsystem/ip/Subsystem_Input_Debounce_1_0/sim/Subsystem_Input_Debounce_1_0.vhd" \
"../../../bd/Subsystem/ip/Subsystem_Input_Debounce_1_1/sim/Subsystem_Input_Debounce_1_1.vhd" \
"../../../bd/Subsystem/ip/Subsystem_Input_Debounce_1_2/sim/Subsystem_Input_Debounce_1_2.vhd" \
"../../../bd/Subsystem/ip/Subsystem_Input_Debounce_1_3/sim/Subsystem_Input_Debounce_1_3.vhd" \
"../../../bd/Subsystem/ip/Subsystem_Input_Debounce_1_4/sim/Subsystem_Input_Debounce_1_4.vhd" \
"../../../bd/Subsystem/ip/Subsystem_axi_gpio_1_1/sim/Subsystem_axi_gpio_1_1.vhd" \
"../../../bd/Subsystem/ip/Subsystem_axi_gpio_1_2/sim/Subsystem_axi_gpio_1_2.vhd" \
"../../../bd/Subsystem/ip/Subsystem_axi_gpio_1_3/sim/Subsystem_axi_gpio_1_3.vhd" \
"../../../bd/Subsystem/ip/Subsystem_axi_gpio_4_0/sim/Subsystem_axi_gpio_4_0.vhd" \
"../../../bd/Subsystem/ip/Subsystem_axi_gpio_4_1/sim/Subsystem_axi_gpio_4_1.vhd" \
"d:/PERSONAL/Projects/DTOFLS/DTOFLS.gen/sources_1/bd/Subsystem/ip/Subsystem_imageProcessTop_0_0/Subsystem_imageProcessTop_0_0_sim_netlist.vhdl" \
"../../../bd/Subsystem/ip/Subsystem_auto_us_0/Subsystem_auto_us_0_sim_netlist.vhdl" \
"../../../bd/Subsystem/ip/Subsystem_auto_us_1/Subsystem_auto_us_1_sim_netlist.vhdl" \
"../../../bd/Subsystem/ip/Subsystem_auto_pc_0/Subsystem_auto_pc_0_sim_netlist.vhdl" \
"../../../bd/Subsystem/ip/Subsystem_auto_pc_1/Subsystem_auto_pc_1_sim_netlist.vhdl" \
"../../../bd/Subsystem/sim/Subsystem.vhd" \

vlog -work xil_defaultlib \
"glbl.v"

