library ieee;
use ieee.std_logic_1164.all;

entity rsff is 
    port(
        E1, E2 : in     std_logic;
        Q1, Q2 : buffer std_logic);
end rsff;

architecture netlist of rsff is
    component nand2
        port(a, b : in  std_logic;
             c    : out std_logic);
    end component;
begin
    U1: nand2
        port map (E1, Q2, Q1);
    U2: nand2
        port map (E2, Q1, Q2);
end netlist;
