#ifndef IOBUFFER_H
#define IOBUFFER_H

#include <cstring>
#include <stdexcept>

class ioBuffer
{
    char* buf;
    unsigned shift_bait {0};
    static constexpr unsigned head_begin {0};
    static constexpr unsigned fixed_begin {10};
    static constexpr unsigned variable_begin {16};
    static constexpr int high_bit_mp [] = {0xFFFF, 0x7FFF, 0x3FFF, 0x1FFF,
                                           0xFFF,  0x7FF,  0x3FF,  0x1FF,
                                           0xFF,   0x7F,   0x3F,   0x1F,
                                           0xF,    0x7,    0x3,    0x1};

public:
    ioBuffer(char* buffer, unsigned shift = 0);
    ioBuffer(const ioBuffer& iobuf);

    unsigned getshift() const { return shift_bait; }
    void setshift(unsigned shift);

    char* getbuf() const { return buf; }
    void setbuf(char* buffer);

    short getdata(char *buf, int start, int len);
    void putdata(char *buf, int start, int len, short value);

    unsigned gethead(char* head_buf);
    unsigned getfixed(char* fixed_buf);
    unsigned getvariable(char* variable_buf);
};// ioBuffer

#endif // IOBUFFER_H
