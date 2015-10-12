#ifndef CSUDOKU_STRINGUTILS_H
#define CSUDOKU_STRINGUTILS_H

#include <map>
#include <string>

std::string replace_all_dict(std::string str, std::map<std::string, const std::string> &map) {
    for (auto pair : map) {
        std::string::size_type pos = 0;
        while ((pos = str.find(pair.first, pos)) != std::string::npos) {
            str.replace(pos, pair.first.size(), pair.second);
            pos++;
        }
    }

    return str;
}


#endif //CSUDOKU_STRINGUTILS_H
