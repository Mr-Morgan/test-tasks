#include "base64.h"

const char base64_map[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                           'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                           'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                           'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
constexpr int two_bit {0x03}, four_bit {0x0f}, six_bit {0x3f};

std::string encode(const std::string& text) {
    // преобразовать входные символы (из каждых трёх символов сделать 4)
    // разбиением бит с 8-рок на 6-ки
    // в каком случае нужно добавлять пустые восьмерки?
    // если остаток от деления количества символов входной строки на 3 не равен 0
    // len%3 = 1 - нужно добавить два символа в конце (два знака =) в результирующую строку
    // len%3 = 2 - добавить один симаол в конце

    // если рассмотреть тройки символов исходной строки, то
    // первый из тройки необходимо сдвинуть вправо на 2 бита
    // второй сдвинуть на 4 бита 5-й и 6-й биты взять у предудущего символа с позиции 1 и 2
    // третий сдвинуть на 6 бит 3-6 биты взять у предыдущего символа с позиций 1-4
    // четвертый симфол результирующей строки - это первые 6 бит третьего символа
    std::string text_b64 {""};
    for (int i = 0; i < text.length(); i++) {
        switch ((i+1)%3) {
        case 1:
            text_b64 += base64_map[text[i] >> 2];
            if (i == text.length()-1) text_b64 += base64_map[0];
            break;
        case 2:
            text_b64 += base64_map[((text[i-1] & two_bit) << 4) + (text[i] >> 4)];
            if (i == text.length()-1) text_b64 += base64_map[0];
            break;
        case 0:
            text_b64 += base64_map[((text[i-1] & four_bit) << 2) + (text[i] >> 6)];
            text_b64 += base64_map[text[i] & six_bit];
            break;
        }// switch()
    }// for ()
    for (int i = text.length()%3; i < 3; i++) text_b64 += '=';
    return text_b64;
}// std::string encode()

char mbIndex(const char ch) {
    //mapBase64ToIndex
    constexpr char ab_size {26};
    constexpr char plus_ind {62};
    constexpr char slesh_ind {63};
    if (isupper(ch)) return (ch-'A');
    else if (islower(ch)) return (ch-'a'+ab_size);
    else if (isdigit(ch)) return (ch-'0'+ab_size+ab_size);
    else if (ch == '+') return plus_ind;
    else if (ch == '/') return slesh_ind;
    return ch;
}// char mapBase64ToIndex()

std::string decode(const std::string& text_b64) {
    std::string text {""};
    for (int i = 0; i < text_b64.length(); i++) {
        switch ((i+1)%4) {
        case 1:
            text += mbIndex(text_b64[i]) << 2 | (mbIndex(text_b64[i+1]) >> 4) & two_bit;
            break;
        case 2:
            text += mbIndex(text_b64[i]) << 4 | (mbIndex(text_b64[i+1]) >> 2) & four_bit;
            break;
        case 3:
            text += mbIndex(text_b64[i]) << 6 | mbIndex(text_b64[i+1]) & six_bit;
            break;
        }// switch ()
    }// for ()
    text.resize(static_cast<size_t>(text_b64.length()/4*3));
    while (text.back() == '=') text.pop_back();
    return text;
}// std::string decode()
