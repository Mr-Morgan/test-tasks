#include <iostream>
#include <algorithm>
#include <string>
/* Test case:
 * Input
 * 2
 * Volozh,Arcady,Yurievich,11,2,1964
 * Segalovich,Ilya,Valentinovich,13,9,1964
 * Output
 * 710 64F
*/
class CandidateData {
    // Размер алфавита 26 символов в верхнем регистре, 26 в нижнем
    static constexpr int alphabet {52};
    // Счетчик различных символов в ФИО
    int count_diff_char; 
    // Сумма цифр дня и месяца рождения
    int sum_numb_birth;
    // Индекс первой буквы фамилии в алфавите 
    int first_ch_ab_index;
    // Массив целых чисел (сколько раз встретился каждый символ)
    int char_map[alphabet] = {};
    // Значение шифра
    std::string cypher {"000"};
    // метод для расчета "шифра" по полям класса
    void calc_cypher();
public:
    CandidateData():count_diff_char(0), sum_numb_birth(0), first_ch_ab_index(0) {}
    // Метод возвращающий значение шифра
    std::string get_cypher() const;
    // метод для заполнения полей класса
    bool set_data(std::string data);
};// CandidateData

std::string CandidateData::get_cypher() const {
    return cypher;
}// std::string CandidateData::get_cypher() const

bool CandidateData::set_data(std::string data) {
    //f,i,o,d,m,y
    constexpr int fio_done {3}; 	//количество запятых обозначающих конец ФИО
    constexpr int dm_done {5}; 		//количество запятых обозначающих конец даты и месяца рождения
    constexpr int up_low_shift {'Z'-'a'+1}; // сдвиг в таблице ASCII между символами верхнего и нижнего регистра, для заполнения char_map
    int count_comma {0};		//Счетчик запятых
    //Расчет индекса первой буквы фамилии в алфавите
    first_ch_ab_index = data[0] - 'A' + 1;  
    int i = 0;	//итератор для чтения строки по-символьно
    // Заполнение char_map - подсчет сколько раз встретился каждый символ
    while (count_comma < fio_done) {
        if (data[i] == ',') count_comma++;
        else {
            // Расчет индекса алфавита для текущего символа
            int map_index = ((isupper(data[i]))?0:up_low_shift) - 'A' + data[i];
            char_map[map_index]++;
        }// if()
        i++;
    }// while()
    // Количество различных символов в ФИО = количеству не нулевых элементов массива char_map
    count_diff_char = std::count_if(char_map, char_map+alphabet, [](int i){ return i != 0;});
    // Расчет суммы цифр дня и месяца рождения
    while (count_comma < dm_done) {
        if (data[i] == ',') count_comma++;
        else sum_numb_birth += static_cast<int>(data[i] - '0');
        i++;
    }// while()
    // Расчет "шифра" по полям класса
    calc_cypher();
    //false - если есть пустое поле; true - если все поля заполнены
    return count_diff_char && sum_numb_birth && first_ch_ab_index; 
}// bool CandidateData::set_data()

void CandidateData::calc_cypher() {
    constexpr int numb_digits {3}; 	//количество символов в отете
    constexpr int basis {16};	//основание системы перевода
    // Расчет десятичного числа для шифра
    int dec = count_diff_char + 64*sum_numb_birth + 256*first_ch_ab_index;
    // Перевод десятичного числа в систему исчесления с основанием basis
    for (int i = 0; dec && i < numb_digits; i++) {
        char ch = static_cast<char>(((dec%basis < 10)?'0':'A'-10) + dec%basis); //при рефакторинге обратный перевод в символ выделить в отдельный метод - char numToChar(int num)
        cypher[numb_digits-i-1] = ch;
        dec /= basis;
    }// for ()
    return;
}// std::string CandidateData::calc_cypher()

int main()
{
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::string candidate_data;
        std::cin >> candidate_data;
        CandidateData cd;
        cd.set_data(candidate_data);
        std::cout << cd.get_cypher() << ' ';
    }// for()
    return 0;
}// int main()
