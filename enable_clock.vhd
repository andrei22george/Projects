library	IEEE;
use IEEE.std_logic_unsigned.all;
use IEEE.std_logic_1164.all;

entity enable_clock is
	port(POZ_SENS: in STD_LOGIC_VECTOR (3 downto 0); 
	SENS: in STD_LOGIC; 
	CLK_NUM: out STD_LOGIC);
end enable_clock;

architecture enable_clock of enable_clock is

signal CLOCK_VALUE: STD_LOGIC := '0';

begin
	process (POZ_SENS, sens)
	begin
		if SENS = '1' then
			case POZ_SENS is
				when "1000" => CLOCK_VALUE <= '1';
				when "0110" => CLOCK_VALUE <= '0'; 
				when "0101" => CLOCK_VALUE <= '0'; 
				when "1110" => CLOCK_VALUE <= '0';
				when others => CLOCK_VALUE <= '0';
			end case;
		else
			case POZ_SENS is
				when "1000" => CLOCK_VALUE <= '0';
				when "0110" => CLOCK_VALUE <= '1'; 
				when "0101" => CLOCK_VALUE <= '1'; 
				when "1110" => CLOCK_VALUE <= '0';
				when others => CLOCK_VALUE <= '0';
			end case;
		end if;
	end process; 
	CLK_NUM <= CLOCK_VALUE;
end enable_clock;
		