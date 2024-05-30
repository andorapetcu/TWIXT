#pragma once
#include <string>
#include <vector>
#include "Peg.h"
#include <string_view>

template<typename InputType>
class Player
{
public:
    Player(std::string_view name, uint16_t color)
        : m_name{ name }
        , m_color{ color }
    {
    }

    ~Player() {}

    void GetNextAction();
    const std::string& GetName() const;
    uint16_t GetColor() const;
    void SetName(std::string_view name);
    void SetColor(uint16_t color);

private:
    std::string m_name;
    uint16_t m_color;
};