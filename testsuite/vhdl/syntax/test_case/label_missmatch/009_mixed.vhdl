library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.NUMERIC_STD.all;
entity testbench is
end entity test_bench; -- testbench vs. test_bench

architecture BENCH of testbench is
  signal MM : STD_LOGIC;
  signal A, B, C : STD_LOGIC_VECTOR(2 downto 0);
begin
  Stimuli: process
  begin
    for i in 0 to 2**7-1 loop 
      wait for 10 NS;
    end loop;
    wait;
end process Stim; -- Stimuli vs. Stim

end architecture bench_test; -- BENCH vs. bench_test

