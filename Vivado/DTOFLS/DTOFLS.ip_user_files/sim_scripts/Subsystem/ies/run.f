-makelib ies_lib/xilinx_vip -sv \
  "C:/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/axi4stream_vip_axi4streampc.sv" \
  "C:/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/axi_vip_axi4pc.sv" \
  "C:/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/xil_common_vip_pkg.sv" \
  "C:/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/axi4stream_vip_pkg.sv" \
  "C:/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/axi_vip_pkg.sv" \
  "C:/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/axi4stream_vip_if.sv" \
  "C:/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/axi_vip_if.sv" \
  "C:/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/clk_vip_if.sv" \
  "C:/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/rst_vip_if.sv" \
-endlib
-makelib ies_lib/xpm -sv \
  "C:/Xilinx/Vivado/2020.2/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
  "C:/Xilinx/Vivado/2020.2/data/ip/xpm/xpm_fifo/hdl/xpm_fifo.sv" \
  "C:/Xilinx/Vivado/2020.2/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \
-endlib
-makelib ies_lib/xpm \
  "C:/Xilinx/Vivado/2020.2/data/ip/xpm/xpm_VCOMP.vhd" \
-endlib
-makelib ies_lib/xil_defaultlib \
  "../../../bd/Subsystem/ip/Subsystem_PmodOLED_0_0/Subsystem_PmodOLED_0_0_sim_netlist.vhdl" \
  "../../../bd/Subsystem/ip/Subsystem_axi_dma_0_0/Subsystem_axi_dma_0_0_sim_netlist.vhdl" \
-endlib
-makelib ies_lib/axi_lite_ipif_v3_0_4 \
  "../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/66ea/hdl/axi_lite_ipif_v3_0_vh_rfs.vhd" \
-endlib
-makelib ies_lib/lib_cdc_v1_0_2 \
  "../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/ef1e/hdl/lib_cdc_v1_0_rfs.vhd" \
-endlib
-makelib ies_lib/interrupt_control_v3_1_4 \
  "../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/a040/hdl/interrupt_control_v3_1_vh_rfs.vhd" \
-endlib
-makelib ies_lib/axi_gpio_v2_0_24 \
  "../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/4318/hdl/axi_gpio_v2_0_vh_rfs.vhd" \
-endlib
-makelib ies_lib/xil_defaultlib \
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
-endlib
-makelib ies_lib/proc_sys_reset_v5_0_13 \
  "../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/8842/hdl/proc_sys_reset_v5_0_vh_rfs.vhd" \
-endlib
-makelib ies_lib/xil_defaultlib \
  "../../../bd/Subsystem/ip/Subsystem_rst_clk_wiz_0_148M_0/sim/Subsystem_rst_clk_wiz_0_148M_0.vhd" \
  "../../../bd/Subsystem/ip/Subsystem_v_axi4s_vid_out_0_0/Subsystem_v_axi4s_vid_out_0_0_sim_netlist.vhdl" \
-endlib
-makelib ies_lib/v_tc_v6_2_1 \
  "../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/cd2e/hdl/v_tc_v6_2_vh_rfs.vhd" \
-endlib
-makelib ies_lib/xil_defaultlib \
  "../../../bd/Subsystem/ip/Subsystem_v_tc_0_0/sim/Subsystem_v_tc_0_0.vhd" \
-endlib
-makelib ies_lib/xlconcat_v2_1_4 \
  "../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/4b67/hdl/xlconcat_v2_1_vl_rfs.v" \
-endlib
-makelib ies_lib/xil_defaultlib \
  "../../../bd/Subsystem/ip/Subsystem_xlconcat_1_0/sim/Subsystem_xlconcat_1_0.v" \
-endlib
-makelib ies_lib/xlconstant_v1_1_7 \
  "../../../../DTOFLS.gen/sources_1/bd/Subsystem/ipshared/fcfc/hdl/xlconstant_v1_1_vl_rfs.v" \
-endlib
-makelib ies_lib/xil_defaultlib \
  "../../../bd/Subsystem/ip/Subsystem_xlconstant_0_0/sim/Subsystem_xlconstant_0_0.v" \
-endlib
-makelib ies_lib/xil_defaultlib \
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
-endlib
-makelib ies_lib/xil_defaultlib \
  glbl.v
-endlib

