#ifndef BASE64_H
#define BASE64_H

#include <string>

std::string encode(const std::string& text);
std::string decode(const std::string& text_b64);

#endif // BASE64_H
