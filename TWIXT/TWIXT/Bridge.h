#pragma once
#include <cstdint>

class Bridge
{
public:
	Bridge(uint16_t line1, uint16_t line2, uint16_t column1, uint16_t column2);
	
	void SetLine1(const uint16_t& line1);
	void SetLine2(const uint16_t& line2);
	void SetColumn1(const uint16_t& column1);
	void SetColumn2(const uint16_t& column2);
	uint16_t GetLine1() const;
	uint16_t GetLine2() const;
	uint16_t GetColumn1() const;
	uint16_t GetColumn2() const;

private:
	uint16_t m_line1;
	uint16_t m_line2;
	uint16_t m_column1;
	uint16_t m_column2;
};