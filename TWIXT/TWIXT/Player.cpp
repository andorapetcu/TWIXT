#include <iostream>
#include "Player.h"

template<typename InputType>
void Player<InputType>::GetNextAction()
{
    std::cout << m_name << ", where do you want to put your peg?\n";

    std::cout << "row and column: ";
    InputType row;
    std::cin >> row;
    InputType column;
    std::cin >> column;
}

template<typename InputType>
const std::string& Player<InputType>::GetName() const
{
    return m_name;
}

template<typename InputType>
uint16_t Player<InputType>::GetColor() const
{
    return m_color;
}

template<typename InputType>
void Player<InputType>::SetName(std::string_view name)
{
    m_name = name;
}

template<typename InputType>
void Player<InputType>::SetColor(uint16_t color)
{
    m_color = color;
}
