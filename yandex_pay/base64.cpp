#include "base64.h"

char base64_map[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                     'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                     'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                     'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};

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
    char suffix;
    for (int i = 0; i < text.length(); i++) {
        char prefix = text[i];
        switch((i+1)%3) {
        case 0:
            prefix >>= 6;
            text_b64 += base64_map[prefix | suffix];

            suffix = text[i];
            suffix <<= 2;
            suffix >>= 2;
            text_b64 += base64_map[suffix];
            break;

        case 1:
            prefix >>= 2;
            text_b64 += base64_map[prefix];

            suffix = text[i];
            suffix <<= 4;
            suffix &= ~(1 << 6);
            suffix &= ~(1 << 7);
            if (i == text.length()-1) text_b64 += base64_map[suffix];
            break;

        case 2:
            prefix >>= 4;
            text_b64 += base64_map[prefix | suffix];

            suffix = text[i];
            suffix <<= 2;
            suffix &= ~(1 << 6);
            suffix &= ~(1 << 7);
            if (i == text.length()-1) text_b64 += base64_map[suffix];
            break;
        }// switch()
    }// for ()

    for (int i = text.length()%3; i < 3; i++) text_b64 += '=';

    return text_b64;
}// string encode()

std::string decode(const std::string& text_b64) {
    std::string text {""};

    return text;
}// std::string decode()
