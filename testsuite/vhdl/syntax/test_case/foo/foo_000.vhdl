library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.NUMERIC_STD.all;
entity testbench is
end entity testbench;

architecture BENCH of testbench is
  signal MM : STD_LOGIC;
  signal A, B, C : STD_LOGIC_VECTOR(2 downto 0);
begin
  Stim: process
--    variable V : UNSIGNED(8 downto 0);
  begin
    for i in 0 to 2**7-1 loop 
      --(MM,A,B) <= STD_LOGIC_VECTOR(TO_UNSIGNED(i,7));
      wait for 10 NS;
    end loop;
    wait;
end process Stim;

block_label :
    BLOCK IS 
    BEGIN
    END BLOCK block_label_wrong; -- label mismatch


  D : --entity work.EX_MAX_MIN(A1)
  entity work_EX_MAX_MIN(A1)
    port map (MM, A, B, C);

end architecture BENCH;

