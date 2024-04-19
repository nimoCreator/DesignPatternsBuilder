#pragma once

#ifndef _ARGUMENTSPARSER_H_
#define _ARGUMENTSPARSER_H_

#include <string>
#include <vector>

class ArgumentsParser
{
private:
    std::vector <std::string> items;
    std::string programPath;

public:
    ArgumentsParser(int argc, char* argv[], bool to_lower_case = false) {
        programPath = std::string(argv[0]);
        if (to_lower_case) 
            transform(programPath.begin(), programPath.end(), programPath.begin(), ::tolower);
        for (int i = 1; i < argc; i++) {
            items.push_back(std::string(argv[i]));
            if(to_lower_case)
                transform(programPath.begin(), programPath.end(), programPath.begin(), ::tolower);
        }
    }

    const std::string& getParamArg(const std::string& param) const {
        static const std::string empty("");
        auto it = std::find(this->items.begin(), this->items.end(), param);
        if (it != this->items.end() && ++it != this->items.end()) {
            return *it;
        }
        return empty;
    }

    bool cmdParamExists(const std::string& param) const {
        return std::find(this->items.begin(), this->items.end(), param)
            != this->items.end();
    }

    const std::string& getProgramPath() const {
        return programPath; 
    }

};

#endif // !_ARGUMENTSPARSER_H_



