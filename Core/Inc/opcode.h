#ifndef OPCODE_H
#define OPCODE_H
#include "common.h"

class Opcode
{
public:
    Opcode(uint16_t opcode);


    uint16_t full() const { return m_Full; }
    uint16_t nnn() const { return m_nnn; }
    uint8_t type() const { return m_Type; }
    uint8_t x() const { return m_x; }
    uint8_t y() const { return m_y; }
    uint8_t n() const { return m_n; }
    uint8_t nn() const { return m_nn; }
private:
    uint16_t m_Full{};
    uint16_t m_nnn{};
    uint8_t m_Type{};
    uint8_t m_x{};
    uint8_t m_y{};
    uint8_t m_n{};
    uint8_t m_nn{};
};

#endif
