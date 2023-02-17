library	IEEE;
use IEEE.std_logic_unsigned.all;
use IEEE.std_logic_1164.all;
use IEEE.STD_LOGIC_ARITH.all;	

entity poarta_and is 
	port(A, B: in STD_LOGIC;
	Y: out STD_LOGIC);
end poarta_and;

architecture poarta_si of poarta_and is 
begin
	Y <= A and B;
end poarta_si;
