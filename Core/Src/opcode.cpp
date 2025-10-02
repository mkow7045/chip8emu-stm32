#include "opcode.h"
#include "common.h"

Opcode::Opcode(uint16_t opcode)
    : m_Full {opcode}
    , m_Type {static_cast<uint8_t>((opcode & 0xF000) >> 12)}
    , m_x{ static_cast<uint8_t>((opcode & 0x0F00) >> 8) }
    , m_y{ static_cast<uint8_t>((opcode & 0x00F0) >> 4) }
    , m_n { static_cast<uint8_t>(opcode & 0x000F)}
    , m_nn{ static_cast<uint8_t>(opcode & 0x00FF) }
    , m_nnn { static_cast<uint16_t>(opcode & 0x0FFF)}
{
}
