---------------------------------------------------------------------------------------------------
--
-- Title       : divizor_frecventa
-- Design      : proiect_lift
-- Author      : George
-- Company     : UTCN
--
---------------------------------------------------------------------------------------------------
--
-- File        : divizor_frecventa.vhd
-- Generated   : Wed May  4 17:19:51 2022
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
--{entity {divizor_frecventa} architecture {divizor_frecventa}}

library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.STD_LOGIC_UNSIGNED.all;

entity divizor_frecventa is
	port(CLK : in STD_LOGIC; 
	CLK_NOU: out STD_LOGIC);
end divizor_frecventa;

--}} End of automatically maintained section

architecture divizor_frecventa of divizor_frecventa is	   
	signal COUNTER: integer :=1;
	signal tmp: STD_LOGIC := '0';
begin
	
	 -- enter your statements here --
	process(CLK)
	begin
		if (CLK'event and CLK = '1') then
			COUNTER <= COUNTER + 1;
		end if;
		if(COUNTER = 100000) then
			tmp <= not tmp;
			COUNTER <= 1;
		end if;
		CLK_NOU<= tmp;
	end process;
end divizor_frecventa;
