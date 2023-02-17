library IEEE;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use IEEE.STD_LOGIC_1164.ALL; 

entity main is
	port(ETAJ: in STD_LOGIC_VECTOR (3 downto 0);  
	POZ_SENS: in STD_LOGIC_VECTOR (3 downto 0);
	SEL: in STD_LOGIC; 
	RESET: in STD_LOGIC; 
	CLK: in STD_LOGIC; 
	SENZOR_G_PERS: in STD_LOGIC; 
	VITEZA_IN: in STD_LOGIC; 	 
	ANOD_ETAJ: out STD_LOGIC_VECTOR (3 downto 0);
	CATOD_ETAJ: out STD_LOGIC_VECTOR (6 downto 0);
	USA_DESCHISA: out STD_LOGIC; 
	SENS: out STD_LOGIC; 
	G_PERS_ERR: out STD_LOGIC; 
	VITEZA_OUT: out STD_LOGIC);
end entity;	 

architecture main_architecture of main is	 

component divizor_frecventa is
	port (CLK: in STD_LOGIC;
	CLK_NOU: out STD_LOGIC);
end component;

component poarta_not is
	port(A: in STD_LOGIC; 
	B: out STD_LOGIC);
end component;	 

component poarta_and is 
	port(A, B: in STD_LOGIC; 
	Y: out STD_LOGIC);
end component;

component enable_clock is
	port(POZ_SENS: in STD_LOGIC_VECTOR (3 downto 0);
	SENS: in STD_LOGIC; 
	CLK_NUM: out STD_LOGIC);
end component;

component numarator_curent is
	port(ETAJ: in std_logic_vector(3 downto 0);
	RESET: in STD_LOGIC; 
	CLK: in STD_LOGIC; 
	EN_NUM_2: in STD_LOGIC; 
	SENS: in STD_LOGIC;
	OUT_NUM_GENERAL: in STD_LOGIC_VECTOR (3 downto 0);
	C: out STD_LOGIC;
	OUT_NUM_CURENT: out STD_LOGIC_VECTOR (3 downto 0));
end component;

component registru_deplasare_circular is
	port (clk, reset : in STD_LOGIC; 
	Y : out STD_LOGIC_VECTOR (3 downto 0));
end component;

component decodificator is
	port (INTRARI: in STD_LOGIC_VECTOR (3 downto 0); 
	IESIRI: out STD_LOGIC_VECTOR (6 downto 0));
end component;

component mux_16_1 is
	port(I0: in STD_LOGIC_VECTOR(3 downto 0);
	I1: in STD_LOGIC_VECTOR(3 downto 0);
	I2: in STD_LOGIC_VECTOR(3 downto 0);
	I3: in STD_LOGIC_VECTOR(3 downto 0);
	I4: in STD_LOGIC_VECTOR(3 downto 0);
	I5: in STD_LOGIC_VECTOR(3 downto 0);
	I6: in STD_LOGIC_VECTOR(3 downto 0);
	I7: in STD_LOGIC_VECTOR(3 downto 0); 
	I8: in STD_LOGIC_VECTOR(3 downto 0);
	I9: in STD_LOGIC_VECTOR(3 downto 0);
	I10: in STD_LOGIC_VECTOR(3 downto 0);
	I11: in STD_LOGIC_VECTOR(3 downto 0); 
	I12: in STD_LOGIC_VECTOR(3 downto 0);
	I13: in STD_LOGIC_VECTOR(3 downto 0);
	I14: in STD_LOGIC_VECTOR(3 downto 0);
	I15: in STD_LOGIC_VECTOR(3 downto 0);
	SEL: in STD_LOGIC_VECTOR(3 downto 0);
	Y: out STD_LOGIC_VECTOR(3 downto 0));
end component;

component timer_usi is
	port(CLK, RESET, SEL, DESCHIDE: in STD_LOGIC; 
	INCHIDE: out STD_LOGIC := '0');
end component;

component mux_2_1 is
	port (I0: in STD_LOGIC;
	I1 : in STD_LOGIC; 
	SEL: in STD_LOGIC; 
	MUX_OUT: out STD_LOGIC);
end component;

component afisor is
	port (CLK: in STD_LOGIC;
	RESET: in STD_LOGIC;
	BIST_D1: in STD_LOGIC_VECTOR (3 downto 0);
	BIST_D2: in STD_LOGIC_VECTOR (3 downto 0);
	ANOD: out STD_LOGIC_VECTOR (3 downto 0);
	CATOD: out STD_LOGIC_VECTOR (6 downto 0));
end component;		   

component ram_4x16 is
	port (A1_RAM: in STD_LOGIC_VECTOR (3 downto 0);
		  A2_RAM: in STD_LOGIC_VECTOR (3 downto 0);
		  WE: in STD_LOGIC;					  
		  RESET: in STD_LOGIC;
		  D_RAM: in STD_LOGIC_VECTOR (3 downto 0);
		  Y_RAM: out STD_LOGIC_VECTOR (3 downto 0));
end component;

component numarator_general is
	port (RESET: in STD_LOGIC;
	POZ_SENS: in STD_LOGIC_VECTOR(3 downto 0);
	CLK: in STD_LOGIC; 
	EN_NUM_1: in STD_LOGIC; 
	SENS: out STD_LOGIC;
	OUT_NUM_GENERAL: out STD_LOGIC_VECTOR(3 downto 0));
end component; 

component viteza is
	port(CLK, EN, RESET: in STD_LOGIC;
	SEC: in STD_LOGIC_VECTOR (3 downto 0);
	CLK_VITEZA: out STD_LOGIC;
	VIT_OUT: out STD_LOGIC_VECTOR(3 downto 0));
end component;


signal CLK_DIVIZAT: std_logic;
signal OUT_NUM_GENERAL: std_logic_vector (3 downto 0);--
signal OUT_NUM_CURENT: std_logic_vector (3 downto 0);--
signal Y_MUX_1: std_logic_vector (3 downto 0);--
signal Y_MUX_2: std_logic_vector (3 downto 0);--   
signal Y_POZ_SENS: std_logic_vector (3 downto 0);
signal OPRESTE: std_logic;		
signal SENS_INTERM: std_logic;	
signal CLK_NUM: std_logic;
signal EN_NUM_1: std_logic;--
signal EN_NUM_2: std_logic;--
signal VIT_OUT_1: std_logic_vector (3 downto 0);
signal VIT_OUT_3: std_logic_vector (3 downto 0);
signal CLK_VIT_1: std_logic;  
signal CLK_VIT_3: std_logic;
signal CLK_VITEZA: std_logic;
signal Y_VITEZA: std_logic; -- viteza selectata in functie de VITEZA_IN
signal nSENZOR_G_PERS: std_logic;

begin		 
	nSENZOR_G_PERS <= not SENZOR_G_PERS;
	--pm_div: divizor_frecventa port map (CLK, CLK_DIVIZAT);
	pm_ram: ram_4x16 port map(ETAJ, OUT_NUM_GENERAL, SEL, RESET, POZ_SENS, Y_POZ_SENS);
	pm_ud: enable_clock port map (POZ_SENS, SENS_INTERM, CLK_NUM);
	pm_and: poarta_and port map (CLK_NUM, nSENZOR_G_PERS, EN_NUM_1);
	pm_num_gen: numarator_general port map(RESET, POZ_SENS, CLK, EN_NUM_1, SENS_INTERM, OUT_NUM_GENERAL);
	pm_not: poarta_not port map(EN_NUM_1, EN_NUM_2);
	pm_v1: viteza port map (CLK, EN_NUM_2, RESET, "0011", CLK_VIT_1, VIT_OUT_1);
	pm_v3: viteza port map (CLK, EN_NUM_2, RESET, "0111", CLK_VIT_3, VIT_OUT_3);
	pm_mux_viteza: mux_2_1 port map (CLK_VIT_1, CLK_VIT_3, VITEZA_IN, Y_VITEZA);
	pm_and_viteza: poarta_and port map (CLK, Y_VITEZA, CLK_VITEZA);
	pm_num_cur: numarator_curent port map (ETAJ, CLK, EN_NUM_2, RESET, SENS_INTERM, OUT_NUM_GENERAL, OPRESTE, OUT_NUM_CURENT);
	pm_mux_2: mux_16_1 port map ("0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "0000", "0001", "0010", "1111", "1111", "1111", OUT_NUM_CURENT, Y_MUX_2);
	pm_mux_1: mux_16_1 port map ("0000","0000","0000","0000","0000","0000","0000","0000","0000","0000", "0001", "0001", "0001", "1111", "1111", "1111", OUT_NUM_CURENT, Y_MUX_1);	 
	pm_afisor: afisor port map (CLK, RESET, Y_MUX_1, Y_MUX_2, ANOD_ETAJ, CATOD_ETAJ); 
	pm_usi: timer_usi port map (CLK, RESET, SEL, OPRESTE, USA_DESCHISA);
	VITEZA_OUT <= VITEZA_IN;
	SENS <= SENS_INTERM;
	G_PERS_ERR <= SENZOR_G_PERS; 
end main_architecture;