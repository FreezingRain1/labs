#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

class factorization
{
public:
    explicit factorization (const std::string &in, const std::string &out)
    {
        input = in;
        output = out;
    }
    ~factorization ();
   // void initialization ();
    void factorization_value (uint64_t);
    std::string generate_str();
    uint64_t check() const;
private:
    std::vector<std::pair<uint64_t, uint64_t>> multipliers;
    std::string multipliers_str;
    std::string input, output;
    std::string uint64_t_to_string(const uint64_t &value) const;


   // void write(std::ofstream &fout) const;
};
