#include "Peg.h"
Peg::Peg(uint16_t line, uint16_t column, uint16_t type)
: m_line(line)
, m_column(column)
, m_type(type)
{

}

uint16_t Peg::GetLine() const
{
	return m_line;
}

uint16_t Peg::GetColumn() const
{
	return m_column;
}

void Peg::SetLine(const uint16_t& line)
{
	m_line = line;
}

void Peg::SetColumn(const uint16_t& column)
{
	m_column = column;
}