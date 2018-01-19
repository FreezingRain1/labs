#include "factorization.h"

factorization::~factorization()
{
    multipliers.clear();
}

void factorization::factorization_value(uint64_t value)
{
    multipliers.clear();
    uint64_t i = 2, count = 0;
    double val_sqrt = sqrt(value);
    while ((value!=1) && (i<=val_sqrt))
    {
        if (value % i == 0)
        {
            count++;
            value/=i;
        }
        else
        {
            if (count > 0)
            {
                multipliers.push_back(std::make_pair(i, count));
            }
            i++;
            count = 0;
        }
    }
    if (value == 1)
    {
        multipliers.push_back(std::make_pair(i, count));
    }
    else
    {
        multipliers.push_back(std::make_pair(value, 1));
    }
   /* for (const auto &j: multipliers)
    {
        std::cout<<j.first<<' '<<j.second<<std::endl;
    }*/
}

std::string factorization::uint64_t_to_string(const uint64_t &value) const
{
    std::ostringstream tmp;
    tmp << value;
    return tmp.str();
}

uint64_t factorization::check() const
{
    uint64_t value = 1;
    for (const auto &i: multipliers)
    {
        value*=pow(i.first, i.second);
    }
    return value;
}

std::string factorization::generate_str()
{
    multipliers_str = " = ";
    for (const auto &j: multipliers)
    {
        multipliers_str+=uint64_t_to_string(j.first);
        if (j.second!=1)
        {
            multipliers_str+="^";
            multipliers_str+=uint64_t_to_string(j.second);
        }
        multipliers_str+=" * ";
    }
    multipliers_str.erase(multipliers_str.end() - 3, multipliers_str.end());
    return multipliers_str;
    //std::cout<<check()<<multipliers_str<<std::endl;
}

/*void factorization::write(std::ofstream &fout) const
{
    fout<<check()<<multipliers_str<<"\n";
}

void factorization::initialization()
{
    std::ifstream fin(input);
    std::ofstream fout(output);
    uint64_t val;
    fin>>val;
    while (!fin.eof())
    {
        factorization_value(val);
        generate_str();
        write(fout);
        fin>>val;
    }
    fin.close();
    fout.close();
}*/
