----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    16:47:24 02/08/2022 
-- Design Name: 
-- Module Name:    memorie_ram - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity ram_4x16 is
	port (A1_RAM: in STD_LOGIC_VECTOR (3 downto 0);
		  A2_RAM: in STD_LOGIC_VECTOR (3 downto 0);
		  WE: in STD_LOGIC;					  
		  RESET: in STD_LOGIC;
		  D_RAM: in STD_LOGIC_VECTOR (3 downto 0);
		  Y_RAM: out STD_LOGIC_VECTOR (3 downto 0));
end ram_4x16;

architecture Behavioral of ram_4x16 is
type MATRICE is array (0 to 15) of STD_LOGIC_VECTOR (3 downto 0);
begin
	process (WE, RESET, A1_RAM, A2_RAM, D_RAM)
	variable mem: MATRICE;
	begin						
		if(RESET = '1') then
			mem(0)  := "0000";
			mem(1)  := "0000";
			mem(2)  := "0000";
			mem(3)  := "0000";
			mem(4)  := "0000";
			mem(5)  := "0000";
			mem(6)  := "0000";
			mem(7)  := "0000";
			mem(8)  := "0000";
			mem(9)  := "0000";
			mem(10) := "0000";
			mem(11) := "0000";
			mem(12) := "0000";
			mem(13) := "0000";
			mem(14) := "0000";
			mem(15) := "0000";
		else
			if(WE = '1') then
				case A1_RAM is
					when "0000" => mem(0) := D_RAM;	   
					when "0001" => mem(1) := D_RAM;
					when "0010" => mem(2) := D_RAM;
					when "0011" => mem(3) := D_RAM;
					when "0100" => mem(4) := D_RAM; 
					when "0101" => mem(5) := D_RAM;
					when "0110" => mem(6) := D_RAM;
					when "0111" => mem(7) := D_RAM;	
					when "1000" => mem(8) := D_RAM;
					when "1001" => mem(9) := D_RAM;
					when "1010" => mem(10) := D_RAM;	 
					when "1011" => mem(11) := D_RAM;
					when "1100" => mem(12) := D_RAM;
					when others => mem(15) := "0000"; 
				end case;					
			else
				case A2_RAM is
					when "0000" => Y_RAM <= mem(0);
					when "0001" => Y_RAM <= mem(1);
					when "0010" => Y_RAM <= mem(2);
					when "0011" => Y_RAM <= mem(3); 
					when "0100" => Y_RAM <= mem(4);
					when "0101" => Y_RAM <= mem(5); 
					when "0110" => Y_RAM <= mem(6); 
					when "0111" => Y_RAM <= mem(7);
					when "1000" => Y_RAM <= mem(8);
					when "1001" => Y_RAM <= mem(9);
					when "1010" => Y_RAM <= mem(10);
					when "1011" => Y_RAM <= mem(11); 
					when "1100" => Y_RAM <= mem(12);
					when others => Y_RAM <= "0000";	
				end case;
			end if;	
		end if;
	end process;
end Behavioral;

