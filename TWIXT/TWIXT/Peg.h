#pragma once
#include <cstdint>

class Peg
{
public:
	Peg(uint16_t line, uint16_t column, uint16_t type);

	void SetLine(const uint16_t& line);
	void SetColumn(const uint16_t& column);
	uint16_t GetLine() const;
	uint16_t GetColumn() const;

private:
	uint16_t  m_line;
	uint16_t  m_column;
	uint16_t m_type; //1=negru; 2=rosu;
};

//put pawn- scoti din vector pilonul
//initial toti sunt la -1; -1; si avem 2 vectori unu rosu, unu negru
