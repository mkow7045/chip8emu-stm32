#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "common.h"
#include "opcode.h"
#include <array>
#include <string>
#include <string_view>


class Interpreter
{
public:
    Interpreter();

    void loadGame(const uint8_t *game,const uint32_t size);

    void dumpMem();

    uint16_t fetchOpcode(uint8_t highByte, uint8_t lowByte);

    void executeCycles(int cycles);

    void randomizeNumber();

    void decreaseDT();

    void decreaseST();

    void debug(Opcode opcode);

    uint8_t getST() const{ return m_ST; }

    void setKey(uint8_t index, bool state);

private:
    std::string m_Path{};
    std::array<uint8_t, 4096> m_Mem{};
    uint16_t m_PC{0x200};
    uint8_t m_SP{};
    std::array<uint16_t, 16> m_Stack{};
    std::array<uint8_t, 16> m_Sprite{};
    std::array<uint8_t, 16> m_V{};
    uint16_t m_I{};
    uint8_t m_DT{};
    uint8_t m_ST{};
    uint8_t m_rngState{1};
    std::array<bool, 16> m_Keyboard{};
};


#endif
