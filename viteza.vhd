---------------------------------------------------------------------------------------------------
--
-- Title       : viteza
-- Design      : proiect_lift
-- Author      : George
-- Company     : UTCN
--
---------------------------------------------------------------------------------------------------
--
-- File        : viteza.vhd
-- Generated   : Wed May  4 18:16:55 2022
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
--{entity {viteza} architecture {viteza}}

library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity viteza is
	port(CLK, EN, RESET: in STD_LOGIC;
		 SEC: in STD_LOGIC_VECTOR (3 downto 0);
		 CLK_VITEZA: out STD_LOGIC;
		 VIT_OUT: out STD_LOGIC_VECTOR(3 downto 0));
end viteza;

--}} End of automatically maintained section

architecture viteza of viteza is
begin
	process (CLK, EN, RESET, SEC)
	variable vit: STD_LOGIC_VECTOR (0 to 3);
	begin
		CLK_VITEZA <= '0';
		if RESET = '1' then
			vit := "0000";
		end if;
		if (CLK'event and CLK = '1' and EN = '1') then
			if (vit = SEC) then
				vit := "0000";
				CLK_VITEZA <= '1';
			else
				vit := vit + "0001";
			--clk_out <='0';
			end if;
		end if;
		VIT_OUT <= vit;
	end process;
end viteza;
