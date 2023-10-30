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
    static constexpr int alphabet {52};
    int count_diff_char; //count_if() с лямбдой-условием
    int sum_numb_birth;
    int first_ch_ab_index;
    int char_map[alphabet] = {};
    std::string cypher {"000"};
public:
    CandidateData():count_diff_char(0), sum_numb_birth(0), first_ch_ab_index(0) {}
    std::string get_cypher() const;
    bool set_data(std::string data);
    void calc_cypher();
};// CandidateData

std::string CandidateData::get_cypher() const {
    return cypher;
}// std::string CandidateData::get_cypher() const

bool CandidateData::set_data(std::string data) {
    //f,i,o,d,m,y
    constexpr int fio_done {3};
    constexpr int dm_done {5};
    constexpr int up_low_shift {'Z'-'a'+1};
    int count_comma {0};
    first_ch_ab_index = data[0] - 'A' + 1;
    int i = 0;
    while (count_comma < fio_done) {
        if (data[i] == ',') count_comma++;
        else {
            int map_index = ((isupper(data[i]))?0:up_low_shift) - 'A' + data[i];
            char_map[static_cast<int>(map_index)]++;
        }// if()
        i++;
        }// while()
    count_diff_char = std::count_if(char_map, char_map+alphabet, [](int i){ return i != 0;});
    while (count_comma < dm_done) {
        if (data[i] == ',') count_comma++;
        else sum_numb_birth += static_cast<int>(data[i] - '0');
        i++;
    }// while()
    calc_cypher();
    return count_diff_char || sum_numb_birth || first_ch_ab_index;
}// bool CandidateData::set_data()

void CandidateData::calc_cypher() {
    constexpr int numb_digits {3};
    constexpr int hec_basis {16};
    int dec = count_diff_char + 64*sum_numb_birth + 256*first_ch_ab_index;
    for (int i = 0; dec && i < numb_digits; i++) {
        char ch = static_cast<char>(((dec%hec_basis < 10)?'0':'A'-10) + dec%hec_basis);
        cypher[numb_digits-i-1] = ch;
        dec /= hec_basis;
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
