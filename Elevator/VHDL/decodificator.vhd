---------------------------------------------------------------------------------------------------
--
-- Title       : decodificator
-- Design      : proiect_lift
-- Author      : George
-- Company     : UTCN
--
---------------------------------------------------------------------------------------------------
--
-- File        : decodificator.vhd
-- Generated   : Wed May  4 17:15:11 2022
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
--{entity {decodificator} architecture {decodificator}}

library IEEE;
use IEEE.STD_LOGIC_1164.all;  
use IEEE.STD_LOGIC_UNSIGNED.all;
use IEEE.STD_LOGIC_ARITH.all;

entity decodificator is
	port (INTRARI: in STD_LOGIC_VECTOR (3 downto 0);
	IESIRI: out STD_LOGIC_VECTOR (6 downto 0));
end decodificator;

--}} End of automatically maintained section

architecture decodificator of decodificator is
begin

	 -- enter your statements here --
	process(INTRARI)
	begin						   --gfedcba
		case INTRARI is		       --6543210
			when "0000" => IESIRI <="1000000"; -- 0
			when "0001" => IESIRI <="1001111"; -- 1
			when "0010" => IESIRI <="0100100"; -- 2
			when "0011" => IESIRI <="0000110"; -- 3
			when "0100" => IESIRI <="0010001"; -- 4
			when "0101" => IESIRI <="0010010"; -- 5
			when "0110" => IESIRI <="0000011"; -- 6
			when "0111" => IESIRI <="1111000"; -- 7
			when "1000" => IESIRI <="0000000"; -- 8
			when "1001" => IESIRI <="0010000"; -- 9
			when others => IESIRI <="1111111"; -- NULL
		end case;
	end process;
end decodificator;
