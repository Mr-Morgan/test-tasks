#include <iostream>
#include <cstring>
#include <bitset>

constexpr int high_bit_mp [] = {0xFFFF, 0x7FFF, 0x3FFF, 0x1FFF,
                                  0xFFF,  0x7FF,  0x3FF,  0x1FF,
                                  0xFF,   0x7F,   0x3F,   0x1F,
                                  0xF,    0x7,    0x3,    0x1};

short getdata(char *buf, int start, int len) {
    constexpr size_t bit {8}, bait {16};
    short data {0};
    //Определяем индекс символа буффера в котором находится
    size_t start_index {std::strlen(buf) - start/bit - 1},       //младший бит
           end_index   {std::strlen(buf) - (start+len)/bit - 1}; //старший бит
    if (!((start+len)%bit)) end_index++;

    //Собираем 16-ти битное число из 1-3-х 8-ми битных
    for (int i = start_index; i >= end_index; i--)
        //8 бит символа из буффера сдвигаем влево на 0, 8 или 16 бит, в зависимости от
        //индекса символа буффера если их 3, то биты первого символа влево не сдигаются
        //биты второго символа сдвигаются влево на 8 бит, третьего на 16, после чего
        //сдвигаются вправо на индекс младшего бита относительно символа из буффера
        data |= buf[i] << (start_index-i)*bit >> start%bit;

    //накладываем маску, чтобы обрезать лишние старшие биты
    data &= high_bit_mp[bait-len];

    //если старший бит искомого числа 1, то число отрицательное
    if ((data>>len-1)%2) {
        data ^= 1 << len-1;
        //если после затирания старшего бита остается 0, то устанавлимаем максимальное по модулю отрицательное значение
        if (!data) data = 1 << len-1;
        data = -data;
    }// if

    return data;
}// short getdata()

void putdata(char *buf, int start, int len, short value){
    constexpr size_t bit {8}, bait {16};
    //если число отрицательное, то его знак должен поменяться, а старший бит искомого числа должен стать 1
    if (value < 0) {
        value = -value;
        value ^= 1 << len-1;
    }// if

    //Определяем индекс символа буффера в котором находится
    size_t start_index {std::strlen(buf) - start/bit - 1},    //младший бит
        end_index   {std::strlen(buf) - (start+len)/bit - 1}; //старший бит
    if (!((start+len)%bit)) end_index++;

    for (int i = start_index; i >= end_index; i--) {
        if (start_index-i) {
            // определяем количество бит, которое необходимо записать в этот символ
            int delta_len = (len/bit)?bit:len%bit; // если len >= 8, то символ будет переписан целиком,
                                                            // иначе необходимо затереть только len%bit бит символа
            buf[i] = buf[i] >> delta_len << delta_len;      // затираем биты сдвигоми вправо за границу числа и обратно
            len -= delta_len;
        } else {
            // В "первом" символе буффера затираем все биты до start%bit
            buf[i] &= high_bit_mp[bait-start%bit];
            // сокращаем длину на колличество записанных бит
            len -= bit-start%bit;
        }// if
        // накладываем на очищенные биты фрагмент из заданного значения
        buf[i] |= value << start%bit >> (start_index-i)*bit;
    }// for
}// void putdata()

int main()
{
    std::bitset<8> in_bits;
    //Буффер для отладки
    //79 -- 72 71 -- 64 63 -- 56 55 -- 48 47 -- 40 39 -- 32 31 -- 24 23 -- 16 15 --  8 7 ---- 0
    //01100001 01000001 01100010 01000010 01100011 01000011 01100100 01000100 01100101 01000101
    // test case: s = 50, len = 12
    //                    61 - (0000)1000 10010000
    //01100001 01000001 01|100010 010000|10 01100011 01000011 01100100 01000100 01100101 01000101
    //----0--- ----1--- ----2---- ----3---- ----4--- ----5--- ----6--- ----7--- ----8--- ----9---
    //01100001010000010110001001000010011000110100001101100100010001000110010101000101
    //                     100010 010000
    //01100001 01000001 01|011010 010110|10 01100011 01000011 01100100 01000100 01100101 01000101
    //----0--- ----1--- ----2---- ----3---- ----4--- ----5--- ----6--- ----7--- ----8--- ----9---
    //01100001 01000001 01|100010 010000|10 01100011 01000011 01100100 01000100 01100101 01000101

    char *buf {"aAbBcCdDeE\0"};
    int start {50}, len{12};

    short r = getdata(buf, start, len);
    in_bits = r;
    std::cout << r << std::endl;

    char *new_buf = new char[] {"aAZZcUUDeE\0"};
    std::cout << new_buf << std::endl;
    for (int i = 0; i < std::strlen(new_buf); i++) {
        in_bits = new_buf[i];
        std::cout << in_bits << ' ';
    }// for
    std::cout << std::endl;

    putdata(new_buf, start, len, r);

    std::cout << new_buf << std::endl;
    for (int i = 0; i < std::strlen(new_buf); i++) {
        in_bits = new_buf[i];
        std::cout << in_bits << ' ';
    }// for
    std::cout << std::endl;

    return 0;
}// int main()
