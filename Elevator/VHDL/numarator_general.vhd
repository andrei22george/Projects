
---------------------------------------------------------------------------------------------------
--
-- Title       : numarator_general (1)
-- Design      : proiect_lift
-- Author      : George
-- Company     : UTCN
--
---------------------------------------------------------------------------------------------------
--
-- File        : numarator_general.vhd
-- Generated   : Wed May  4 18:46:11 2022
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
--{entity {numarator_general} architecture {numarator_general}}

library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity numarator_general is 
	port (RESET: in STD_LOGIC; 
		 POZ_SENS: in STD_LOGIC_VECTOR(3 downto 0);
		 CLK: in STD_LOGIC; 
		 EN_NUM_1: in STD_LOGIC; 
		 SENS: out STD_LOGIC;
		 OUT_NUM_GENERAL: out STD_LOGIC_VECTOR(3 downto 0));
end numarator_general;

--}} End of automatically maintained section

architecture numarator_general of numarator_general is
begin
	process(RESET, CLK, EN_NUM_1, POZ_SENS)
	variable VAR: STD_LOGIC_VECTOR(3 downto 0):="0000";
	variable SENS_AUX: STD_LOGIC := '1';
	begin
		
		if RESET = '1' then
			VAR := "0000";
		end if;
		if VAR = "0000" then
			SENS <= '1';
			SENS_AUX := '1';
		end if;
		if VAR = "1100" then 
			SENS <= '0'; 
			SENS_AUX := '0';
		end if;
		if(POZ_SENS(0)='1') then
			SENS_AUX:='0';
		end if;
		if (CLK'event and CLK = '1' and EN_NUM_1='1') then
			if SENS_AUX = '1' then
				VAR := VAR + "0001";
			else
				VAR := VAR - "0001";
			end if;
		end if;		
		SENS<=SENS_AUX;
		OUT_NUM_GENERAL <= VAR;
		end process;

	 -- enter your statements here --

end numarator_general;
