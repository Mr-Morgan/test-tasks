#include <iostream>
#include <sstream>
#include <string>
#include <map>

/* Test case:
 * Input
8
50 7 25 3632 A
14 23 52 212372 S
15 0 5 3632 C
14 21 30 212372 A
50 7 26 3632 C
14 21 30 3632 A
14 21 40 212372 B
14 23 52 3632 B
 * Output
156 142
*/

class RocketData {
    std::map<int,char> rock_data;
    int time {0};
public:
    RocketData() {}
    RocketData(int d, char st) { rock_data[d] = st; }
    void add_rd(int d, char st) { rock_data[d] = st; }
    int get_time() const { return time; }
    void calc_time();
};// RocketData

void RocketData::calc_time() {
    int first {0}, last {0};
    for (auto d: rock_data) {
        if (d.second == 'A') {
            first = d.first;
            last = 0;
        } else if (d.second == 'C' || d.second == 'S') last = d.first;
        if (first && last) time += last-first;
    }// for()
}//void calc_time()

class LogParser {
    std::map<int,RocketData> log;
    std::string sort_time_all_rocket {""};
public:
    void set_log (const std::string &str_log);
    std::string get_sort_time () const { return sort_time_all_rocket; }
    void calc_time_all_rocket();
};// LogParser

void LogParser::set_log (const std::string &str_log) {
    constexpr int day_to_hour {1440};
    constexpr int hour_to_min {60};
    int date {0}, id, d, h, m;
    char stat;
    std::stringstream ss;
    ss << str_log;
    ss >> d >> h >> m >> id >> stat;
    date = d*day_to_hour + h*hour_to_min + m;
    if (log.find(id) != log.end()) log.at(id).add_rd(date, stat);
    else log[id] = RocketData(date,stat);
}// void set_log ()

void LogParser::calc_time_all_rocket() {
    for (auto l: log) {
        l.second.calc_time();
        sort_time_all_rocket += std::to_string(l.second.get_time()) + " ";
    }// for()
}// void calc_time_all_rocket ()

int main()
{
    int log_size;
    std::cin >> log_size;
    LogParser lp;
    for (int i = 0; i <= log_size; i++) {
        std::string log_data;
        std::getline(std::cin,log_data);
        if (log_data.length()) lp.set_log(log_data);
    }// for()
    lp.calc_time_all_rocket();
    std::cout << lp.get_sort_time();
    return 0;
}// int main()
