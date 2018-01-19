/*#include "StatisticSet.h"

void Statistic_Set::Add_num(const int &num){
    Set_num.push_back(num);
    change_set_AVG = true;
    Statistic_Set::caching(num);
    for (const auto &i: Set_num)
    {
        std::cout<<i<<' ';
    }
    std::cout<<std::endl;
}

void Statistic_Set::Add_num(const std::vector<int> &vec_data)
{
    for (const auto &i: vec_data)
    {
        Statistic_Set::Add_num(i);
    }
}

void Statistic_Set::Add_num(const std::multiset<int> &mul_data)
{
    for (const auto &i: mul_data)
    {
        Statistic_Set::Add_num(i);
    }
}

void Statistic_Set::Add_num(const std::list<int> &list_data)
{
    for (const auto &i: list_data)
    {
        Statistic_Set::Add_num(i);
    }
}

void Statistic_Set::Add_num_from_file(std::string &file_name)
{
    std::fstream fs;
    fs.open(file_name);
    if (fs.is_open())
    {
        int num;
        while (!fs.eof())
        {
            fs >> num;
            Statistic_Set::Add_num(num);
        }
    }
}

void Statistic_Set::Add_nums (const Statistic_Set &other_set)
{
    for (const auto &i: other_set.Set_num)
    {
        Statistic_Set::Add_num(i);
    }
}
int Statistic_Set::Get_max() const
{
    return max;
}
int Statistic_Set::Get_min() const
{
    return min;
}

float Statistic_Set::Get_AVG() const
{
    if (!change_set_AVG)
    {
        return last_AVG;
    }
    else
    {
        float AVG = 0;
        for (const auto i: Set_num)
        {
            AVG+=(float)i;
        }
        AVG=AVG/Set_num.size();
        change_set_AVG = false;
        last_AVG = AVG;
        return AVG;
    }
}

int Statistic_Set::Get_count_under(int &value) const
{
    if (value==last_val_under)
    {
        return last_count_under;
    }
    last_val_under = value;
    int count = 0;
    for (const auto i: Set_num)
    {
        if (i<value)
        {
            count++;
        }
    }
    last_count_under = count;
    return count;
}

int Statistic_Set::Get_count_above(int &value) const
{
    if (value==last_val_above)
    {
        return last_count_above;
    }
    last_val_above = value;
    int count = 0;
    for (const auto i: Set_num)
    {
        if (i>value)
        {
            count++;
        }
    }
    last_count_above = count;
    return count;
}

void Statistic_Set::caching(const int &num) const
{
    if (Set_num.empty())
    {
        max = num;
        min = num;
        last_val_under = num;
        last_val_above = num;
        last_count_under = 0;
        last_count_above = 0;
    }
    if (num>max)
    {
        max = num;
    }
    if (num<min)
    {
        min = num;
    }
    if (num<last_val_under)
    {
        last_count_under++;
    }
    if (num>last_val_above)
    {
        last_count_above++;
    }
}
Statistic_Set::~Statistic_Set()
{
    Set_num.clear();
}*/


