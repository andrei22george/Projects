library	IEEE;
use IEEE.std_logic_unsigned.all;
use IEEE.std_logic_1164.all;
use IEEE.STD_LOGIC_ARITH.all;	

entity poarta_not is
	port(A: in STD_LOGIC; 
	B: out STD_LOGIC);
end poarta_not;

architecture poarta_not of poarta_not is
begin
	B <= not A;
end poarta_not;
