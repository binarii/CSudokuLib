#ifndef CSUDOKU_FORMATOPTIONS_H
#define CSUDOKU_FORMATOPTIONS_H

#include <string>
#include <map>

class FormatOptions : public std::map<std::string, const std::string> {
public:
    FormatOptions() : std::map<std::string, const std::string>{
            {"\\n", "\n"},
            {"\\t", "\t"}} { }

    template<typename T>
    void add(const std::string &k, const T v);
};

template<typename T>
void FormatOptions::add(const std::string &k, const T v) {
    insert(std::make_pair("{{" + k + "}}", std::to_string(v)));
}

template<>
void FormatOptions::add<std::string>(const std::string &k, const std::string v) {
    insert(std::make_pair("{{" + k + "}}", v));
}

#endif //CSUDOKU_FORMATOPTIONS_H
