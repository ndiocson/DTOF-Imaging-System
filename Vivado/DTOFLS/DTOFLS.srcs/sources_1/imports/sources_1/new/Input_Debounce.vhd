----------------------------------------------------------------------------------
-- Company: N/A
-- Engineer: Nick Diocson
-- 
-- Create Date: 03/22/2021 09:40:35 PM
-- Design Name: Input Debounce
-- Module Name: Input_Debounce - Behavioral
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

entity Input_Debounce is
    Generic (
            CLK_FREQ        : positive := 1E8;  -- Clock frequency (default: 100 MHz)
            MAX_WAIT        : positive := 1E6   -- Cycles to count before dirving output (default: 10ms wait time)
            );
    Port ( 
            clk, aresetn, i : in std_logic;
            o              : out std_logic
            );
end entity Input_Debounce;

architecture Behavioral of Input_Debounce is

-- Counter Component Declaration
component Counter is
    Generic (
            CLK_FREQ    : positive := 1E8;  -- Clock frequency (default: 100 MHz)
            MAX_COUNT   : positive := 100   -- Maximum number of cycles to count to (default: 100)
            );
    Port ( 
            clk, reset  : in std_logic;
            max_reached : out std_logic
            );
end component Counter;

-- Internal signals
signal stop_count   : std_logic := '1';     -- Indicates when to reset the Counter component
signal wait_done    : std_logic := '0';     -- Indicates when the counter has completed
signal follow_in    : std_logic := '0';     -- Indicates when the output is allowed to follow the input

begin

    -- Instantiates a Counter to drive the wait_done signal
    wait_counter: Counter
        Generic Map (CLK_FREQ => CLK_FREQ, MAX_COUNT => MAX_WAIT)
        Port Map (clk => clk, reset => stop_count, max_reached => wait_done);
    
    -- Process that waits for input glitches to subside before driving an output
    debounce: process(aresetn, i, wait_done) is
    begin
        if (aresetn = '0') then
            stop_count <= '1';
            follow_in <= '0';
        else
            stop_count <= not i;
            if (wait_done = '1') then
                follow_in <= '1';
            else
                if (i = '0') then
                    follow_in <= '0';
                end if;
            end if;
        end if;
    end process debounce;
    
    -- Process that will drive the output to the input if the follow_in internal signal is toggled high
    follow_input: process(aresetn, follow_in) is
    begin
        if (aresetn = '0') then
            o <= '0';
        else
            if (follow_in = '1') then
                o <= i;
            else
                o <= '0';
            end if;
        end if;
    end process follow_input;

end architecture Behavioral;
