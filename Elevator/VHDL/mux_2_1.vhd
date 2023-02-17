---------------------------------------------------------------------------------------------------
--
-- Title       : mux_2_1
-- Design      : proiect_lift
-- Author      : George
-- Company     : UTCN
--
---------------------------------------------------------------------------------------------------
--
-- File        : mux_2_1.vhd
-- Generated   : Wed May  4 17:59:58 2022
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
--{entity {mux_2_1} architecture {mux_2_1}}

library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity mux_2_1 is	 
	port (I0: in STD_LOGIC;
		  I1: in STD_LOGIC;
	      SEL: in STD_LOGIC; 
		  MUX_OUT: out STD_LOGIC);
end mux_2_1;

--}} End of automatically maintained section

architecture mux_2_1 of mux_2_1 is
begin
	 process(I0, I1, SEL)
		begin
		if SEL='0' then
			MUX_OUT <= I0;
		else
			MUX_OUT <= I1;
		end if;
		end process;
end mux_2_1;
