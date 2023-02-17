---------------------------------------------------------------------------------------------------
--
-- Title       : afisor
-- Design      : proiect_lift
-- Author      : George
-- Company     : UTCN
--
---------------------------------------------------------------------------------------------------
--
-- File        : afisor.vhd
-- Generated   : Wed May  4 16:43:17 2022
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
--{entity {afisor} architecture {afisor}}

library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.STD_LOGIC_UNSIGNED.all;
use IEEE.STD_LOGIC_ARITH.all;

entity afisor is
	port (CLK: in STD_LOGIC;
	RESET: in STD_LOGIC;
	BIST_D1: in STD_LOGIC_VECTOR (3 downto 0);
	BIST_D2: in STD_LOGIC_VECTOR (3 downto 0);
	ANOD: out STD_LOGIC_VECTOR (3 downto 0);
	CATOD: out STD_LOGIC_VECTOR (6 downto 0));
end afisor;

--}} End of automatically maintained section

architecture afisor of afisor is

component divizor_frecventa is
	port (CLK: in STD_LOGIC;
	CLK_NOU: out STD_LOGIC);
end component;

component mux_16_1 is
	port (I0: in STD_LOGIC_VECTOR(3 downto 0);
	I1: in STD_LOGIC_VECTOR (3 downto 0);
	I2: in STD_LOGIC_VECTOR (3 downto 0);
	I3: in STD_LOGIC_VECTOR (3 downto 0);
	I4: in STD_LOGIC_VECTOR (3 downto 0);
	I5: in STD_LOGIC_VECTOR (3 downto 0);
	I6: in STD_LOGIC_VECTOR (3 downto 0);
	I7: in STD_LOGIC_VECTOR (3 downto 0);
	I8: in STD_LOGIC_VECTOR (3 downto 0);
	I9: in STD_LOGIC_VECTOR (3 downto 0);
	I10: in STD_LOGIC_VECTOR (3 downto 0);
	I11: in STD_LOGIC_VECTOR (3 downto 0);
	I12: in STD_LOGIC_VECTOR (3 downto 0);
	I13: in STD_LOGIC_VECTOR (3 downto 0);
	I14: in STD_LOGIC_VECTOR (3 downto 0);
	I15: in STD_LOGIC_VECTOR (3 downto 0);
	SEL: in STD_LOGIC_VECTOR (3 downto 0);
	Y: out STD_LOGIC_VECTOR (3 downto 0));
end component;

component registru_inel is
	port (CLK: in STD_LOGIC;
	RESET: in STD_LOGIC;
	Y: out STD_LOGIC_VECTOR (3 downto 0));
end component;

component decodificator is
	port (INTRARI: in STD_LOGIC_VECTOR (3 downto 0);
	IESIRI: out STD_LOGIC_VECTOR (6 downto 0));
end component;

signal SELECTIE_MUX: STD_LOGIC_VECTOR (3 downto 0);
signal OUTPUT_MUX: STD_LOGIC_VECTOR (3 downto 0);
signal CLK_DIV: STD_LOGIC;

begin

	 -- enter your statements here --						  
	--DIV: divizor_frecventa port map(CLK, CLK_DIV);
	DECOD:   decodificator port map (OUTPUT_MUX, CATOD);
	MULTIPLEXOR: mux_16_1 port map( "0000", "0000", "0000", "0000", "0000", "0000", "0000", "1111", "0000",
	"0000", "0000", "1111", "0000", BIST_D1, BIST_D2, "0000", SELECTIE_MUX, OUTPUT_MUX);
	REGISTRU: registru_inel port map(CLK, RESET, SELECTIE_MUX);
	ANOD <= SELECTIE_MUX;
end afisor;
