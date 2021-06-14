-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2020.2 (win64) Build 3064766 Wed Nov 18 09:12:45 MST 2020
-- Date        : Sat Mar 27 23:51:41 2021
-- Host        : LAPTOP-7SKEHFFM running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode synth_stub
--               d:/PERSONAL/Projects/DTOFLS/DTOFLS.gen/sources_1/bd/Subsystem/ip/Subsystem_Input_Debounce_1_3/Subsystem_Input_Debounce_1_3_stub.vhdl
-- Design      : Subsystem_Input_Debounce_1_3
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xc7z010clg400-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity Subsystem_Input_Debounce_1_3 is
  Port ( 
    clk : in STD_LOGIC;
    aresetn : in STD_LOGIC;
    i : in STD_LOGIC;
    o : out STD_LOGIC
  );

end Subsystem_Input_Debounce_1_3;

architecture stub of Subsystem_Input_Debounce_1_3 is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "clk,aresetn,i,o";
attribute x_core_info : string;
attribute x_core_info of stub : architecture is "Input_Debounce,Vivado 2020.2";
begin
end;
