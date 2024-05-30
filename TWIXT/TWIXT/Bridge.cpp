#include "Bridge.h"
Bridge::Bridge(uint16_t line1, uint16_t line2, uint16_t column1, uint16_t column2)
: m_line1(line1)
, m_line2(line2)
, m_column1(column1)
, m_column2(column2)
{

}

uint16_t Bridge::GetLine1() const
{
	return m_line1;
}

uint16_t Bridge::GetLine2() const
{
	return m_line2;
}

uint16_t Bridge::GetColumn1() const
{
	return m_column1;
}

uint16_t Bridge::GetColumn2() const
{
	return m_column2;
}

void Bridge::SetLine1(const uint16_t& line1)
{
	m_line1 = line1;
}

void Bridge::SetLine2(const uint16_t& line2)
{
	m_line2 = line2;
}

void Bridge::SetColumn1(const uint16_t& column1)
{
	m_column1 = column1;
}

void Bridge::SetColumn2(const uint16_t& column2)
{
	m_column2 = column2;
}