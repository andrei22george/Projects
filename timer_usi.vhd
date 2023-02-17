library	IEEE;
use IEEE.std_logic_1164.all;
use IEEE.STD_LOGIC_ARITH.all;
use IEEE.STD_LOGIC_UNSIGNED.all;

entity TIMER_USI is
	port(CLK, RESET, SEL, DESCHIDE: in STD_LOGIC;
	INCHIDE: out STD_LOGIC);
end TIMER_USI;

architecture timer_usi of timer_usi is 
signal counter: integer:=0;
signal inchide_s: std_logic:='0';
signal keep_open: std_logic;
begin
	process(CLK, RESET, SEL)
	begin	  
		if(DESCHIDE = '1') then
			inchide_s <= '0';
		end if;
		if(not keep_open='1') then
			counter <= 0;
		end if;
		if(RESET='1') then
			counter<=0;
			inchide_s<='0';
		end if;
		if (SEL='1') then
			keep_open<='1';
			counter<=0;
		end if;
		if(clk'event and clk='1') then
			if(keep_open='1') then
				if(counter=3)	then
					inchide_s<='1';
					counter<=0;
					keep_open<='0';
				else
					counter<=counter+1;
				end if;
			end if;
		end if;
	end process;
	INCHIDE<= inchide_s;
end timer_usi;