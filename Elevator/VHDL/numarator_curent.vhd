---------------------------------------------------------------------------------------------------
--
-- Title       : numarator_curent (2)
-- Design      : proiect_lift
-- Author      : George
-- Company     : UTCN
--
---------------------------------------------------------------------------------------------------
--
-- File        : numarator_curent.vhd
-- Generated   : Wed May  4 18:57:48 2022
-- From        : interface description file
-- By          : Itf2Vhdl ver. 1.20
--
---------------------------------------------------------------------------------------------------
--
-- Description : 
--
---------------------------------------------------------------------------------------------------

--{{ Section below this comment is automatically maintained
--   and may be overwritten
--{entity {numarator_curent} architecture {numarator_curent}}

library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.STD_LOGIC_UNSIGNED.all;
use IEEE.STD_LOGIC_ARITH.all;

entity numarator_curent is
	port(ETAJ: in std_logic_vector(3 downto 0);
	RESET: in STD_LOGIC; 
		 CLK: in STD_LOGIC; 
		 EN_NUM_2: in STD_LOGIC; 
		 SENS: in STD_LOGIC;
		 OUT_NUM_GENERAL: in STD_LOGIC_VECTOR (3 downto 0);
		 C: out STD_LOGIC;
		 OUT_NUM_CURENT: out STD_LOGIC_VECTOR (3 downto 0));
end numarator_curent;

--}} End of automatically maintained section

architecture numarator_curent of numarator_curent is
begin
	process(CLK, RESET, OUT_NUM_GENERAL, SENS)
	variable VAR: STD_LOGIC_VECTOR (0 to 3) := "0000";
	begin
		if RESET = '1' then
			var :="0000"; c<='1'; 
		end if;	  
		VAR:=OUT_NUM_GENERAL;
		if CLK'event and CLK = '1' and EN_NUM_2 = '1' then
				C <= '0';
			if SENS = '1' then
				if VAR < ETAJ then
					VAR	:= VAR + "0001";
				else
					C <= '1'; 
				end if;
				else if VAR	> ETAJ then
						VAR := VAR - "0001";
				else
					C <= '1'; 
				end if;
			end if;	  
		end if;
		OUT_NUM_CURENT <= VAR;
	end process;
	 -- enter your statements here --

end numarator_curent;
