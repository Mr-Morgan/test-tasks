#include <iostream>
#include "base64.h"

int main ()
{
    //std::string text_to_decode {"0JjQt9GD0YfQuNGC0YwgQysrINC30LAgMjEg0LTQtdC90Yw=="};
    /*TEST CASE*/
    std::string text_to_encode {"ABCDEFG HIJKLMNOP"};
    std::string text_to_decode {"QUJDREVGRyBISUpLTE1OT1A="};

    std::cout << encode(text_to_encode) << std::endl;
    std::cout << text_to_decode << std::endl;

    (encode(text_to_encode) == text_to_decode)? std::cout << "true" << std::endl: std::cout << "false" << std::endl;

    std::cout << decode(text_to_decode) << std::endl;
    std::cout << text_to_encode << std::endl;

    (decode(text_to_decode) == text_to_encode)? std::cout << "true" << std::endl: std::cout << "false" << std::endl;

    return 0;
}// int main ()
