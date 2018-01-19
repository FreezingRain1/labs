#pragma once
#include <set>
#include <list>
#include<vector>
#include <iostream>
#include <fstream>
#include <string>
template <class T>
class Statistic_Set
{
public:
    Statistic_Set() = default;
    void Add_num(T num)
    {
        Set_num.push_back(num);
        change_set_AVG = true;
        caching(num);
        if (Set_num.empty())
        {
            last_max = num;
            last_min = num;
        }
        if (num>last_max)
        {
            last_max = num;
        }
        if (num<last_min)
        {
            last_min = num;
        }
        for (const auto &i: Set_num)
            {
                std::cout<<i<<' ';
            }
        std::cout<<std::endl;
    }
    void Add_num(const std::vector<T> &vec_data)
    {
        for (const auto &i: vec_data)
        {
                Add_num(i);
        }
    }
    void Add_num(const std::multiset<T> &mul_data)
    {
        for (const auto &i: mul_data)
        {
            Add_num(i);
        }
    }

    void Add_num(const std::list<T> &list_data)
    {
        for (const auto &i: list_data)
        {
                Add_num(i);
        }
    }
    void Add_num_from_file(std::string &file_name)
    {
        std::fstream fs;
        fs.open(file_name);
        if (fs.is_open())
        {
            T num;
            while (!fs.eof())
            {
                fs >> num;
                Add_num(num);
            }
        }
    }
    void Add_nums (const Statistic_Set &other_set)
    {
        for (const auto &i: other_set.Set_num)
        {
            Add_num(i);
        }
    }
    T Get_max() const
    {
        return last_max;
    }
    T Get_min() const
    {
        return last_min;
    }
    float Get_AVG() const
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
    int Get_count_under(float &value) const
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
    int Get_count_above(float &value) const
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
    ~Statistic_Set()
    {
        Set_num.clear();
    }
private:
    std::vector <T> Set_num;
    mutable float last_AVG;
    mutable bool change_set_AVG = true;
    mutable T last_min, last_max;
    mutable float last_val_under, last_val_above;
    mutable int last_count_under = 0, last_count_above = 0;
    void caching(const T &num) const{
        if (Set_num.empty())
        {
            last_val_under = num;
            last_val_above = num;
            last_count_under = 0;
            last_count_above = 0;
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
};
