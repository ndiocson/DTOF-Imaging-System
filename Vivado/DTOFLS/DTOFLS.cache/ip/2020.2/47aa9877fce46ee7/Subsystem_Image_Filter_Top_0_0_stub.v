// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.2 (win64) Build 3064766 Wed Nov 18 09:12:45 MST 2020
// Date        : Thu Apr  1 16:27:20 2021
// Host        : LAPTOP-7SKEHFFM running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix
//               decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ Subsystem_Image_Filter_Top_0_0_stub.v
// Design      : Subsystem_Image_Filter_Top_0_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7z010clg400-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* x_core_info = "Image_Filter_Top,Vivado 2020.2" *)
module decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix(axi_clk, axi_reset_n, ready_in, valid_in, 
  data_in, intr_out, ready_out, valid_out, data_out)
/* synthesis syn_black_box black_box_pad_pin="axi_clk,axi_reset_n,ready_in,valid_in,data_in[7:0],intr_out,ready_out,valid_out,data_out[7:0]" */;
  input axi_clk;
  input axi_reset_n;
  input ready_in;
  input valid_in;
  input [7:0]data_in;
  output intr_out;
  output ready_out;
  output valid_out;
  output [7:0]data_out;
endmodule
