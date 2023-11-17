#include "iobuffer.h"

ioBuffer::ioBuffer(char *buffer, unsigned shift): buf(buffer), shift_bait(shift)
{
    if (std::strlen(buf)-shift_bait < fixed_begin) throw std::runtime_error("Invalid buffer!\n");
}// ioBuffer()

ioBuffer::ioBuffer(const ioBuffer &iobuf) : buf(iobuf.getbuf()), shift_bait(iobuf.getshift())
{

}// ioBuffer()

void ioBuffer::setshift(unsigned int shift)
{
    if (std::strlen(buf)-shift < fixed_begin) throw std::runtime_error("Invalid buffer!\n");
    else shift_bait = shift;
}// void setshift

void ioBuffer::setbuf(char *buffer)
{
    if (std::strlen(buffer)-shift_bait < fixed_begin) throw std::runtime_error("Invalid buffer!\n");
    else buf = buffer;
}// void setbuf()

short ioBuffer::getdata(char *buf, int start, int len)
{
    constexpr size_t bit {8}, bait {16};
    start += shift_bait*bit;

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

void ioBuffer::putdata(char *buf, int start, int len, short value)
{
    constexpr size_t bit {8}, bait {16};
    start += shift_bait*bit;

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

unsigned ioBuffer::gethead(char *head_buf)
{
    head_buf = buf + std::strlen(buf)-shift_bait-fixed_begin;
    return fixed_begin;
}// unsigned gethead()

unsigned ioBuffer::getfixed(char *fixed_buf)
{
    fixed_buf = buf + std::strlen(buf)-shift_bait-variable_begin;
    return variable_begin-fixed_begin;
}// unsigned getfixed()

unsigned ioBuffer::getvariable(char *variable_buf)
{
    variable_buf = buf;
    return std::strlen(buf)-shift_bait-variable_begin;
}// unsigned getvariable()


