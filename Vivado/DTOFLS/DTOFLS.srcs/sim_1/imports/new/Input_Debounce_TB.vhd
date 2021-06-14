----------------------------------------------------------------------------------
-- Company: N/A
-- Engineer: Nick Diocson
-- 
-- Create Date: 03/23/2021 08:04:26 PM
-- Design Name: Input Debounc Testbench
-- Module Name: Input_Debounce_TB - Behavioral
-- Project Name: D-TOF Imaging System
-- Target Devices: Zynq-7010
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity Input_Debounce_TB is
end entity Input_Debounce_TB;

architecture Behavioral of Input_Debounce_TB is

component Input_Debounce is
    Generic (
            CLK_FREQ        : positive := 1E8;  -- Clock frequency (default: 100 MHz)
            MAX_WAIT        : positive := 1E6   -- Cycles to count before dirving output (default: 10ms wait time)
            );
    Port ( 
            clk, aresetn, i : in std_logic;
            o              : out std_logic
            );
end component Input_Debounce;

-- Constants
constant CLK_PERIOD : time := 10ns;
constant CLK_FREQ   : positive := 1E8;
constant MAX_WAIT   : positive := 1E6;

-- Input signals
signal clk          : std_logic := '0';
signal aresetn      : std_logic := '1';
signal i            : std_logic := '0';

-- Output signals
signal o            : std_logic := '0';

begin

    -- Instantiate device under test
    DUT: Input_Debounce
        Generic Map(
            CLK_FREQ => CLK_FREQ, 
            MAX_WAIT => MAX_WAIT)
        Port Map(
            clk => clk, 
            aresetn => aresetn, 
            i => i, 
            o => o);

    -- Process to drive the input clk signal
    drive_clk: process is 
    begin
        clk <= '1';
        wait for CLK_PERIOD / 2;
        clk <= '0';
        wait for CLK_PERIOD / 2;
    end process drive_clk;
    
    -- Process to stimulate the input signals of the DUT
    stimulus: process is
    begin
        aresetn <= '0';
        wait for 1000us;
        aresetn <= '1';
        i <= '1';
        wait for 125us;
        i <= '0';
        wait for 100us;
        i <= '1';
        wait for 150us;
        i <= '0';
        wait for 225us;
        i <= '1';
        wait for 50us;
        i <= '0';
        wait for 170us;
        i <= '1';
        wait for 50ms;
        i <= '0';
        wait for 1000us;
    end process stimulus;

end architecture Behavioral;
