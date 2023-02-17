library	IEEE;
use IEEE.std_logic_unsigned.all;
use IEEE.std_logic_1164.all;
use IEEE.STD_LOGIC_ARITH.all;	

entity registru_inel is
	port (CLK, RESET: in STD_LOGIC;
	Y: out STD_LOGIC_VECTOR (3 downto 0));
end registru_inel;

architecture registru_inel of registru_inel is
signal ANOD: STD_LOGIC_VECTOR (3 downto 0):="1111";
begin
	process (CLK)
	begin
		if CLK'event and CLK='1' then
			if RESET = '1' then
				ANOD <="1111";
			else
				if ANOD="1111" then
					ANOD<="1110";
				elsif ANOD="1110" then
					ANOD <= "1101";
				elsif ANOD="1101" then
					ANOD <= "1011";
				elsif ANOD="1011" then
					ANOD <= "0111";
				elsif ANOD="0111" then
					ANOD <= "1111";
				end if;
			end if;
		end if;
	end process; 
	Y <= ANOD;
end registru_inel;
