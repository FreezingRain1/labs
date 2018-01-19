#include "StatisticSet.h"
#include <stdlib.h>
int main()
{
    int num;
    int menu_choose = 0;
    Statistic_Set<double> p;
    std::vector<double> vec_data = {1, 3, 4, 8, -10};
    p.Add_num(vec_data);
    std::cout<<p.Get_max()<<std::endl;
    std::multiset<double> mul_data = {20, 3, 7};
    p.Add_num(mul_data);
    std::list<double> list_data = {19, 17};
    p.Add_num(list_data);
    std::string file_name;
    std::cout<<"Input file_name"<<std::endl;
    std::cin>>file_name;
    p.Add_num_from_file(file_name);
    Statistic_Set<double> p0;
    std::vector<double> vec_data1 = {14, 678, 20};
    p0.Add_num(vec_data1);
    p.Add_nums(p0);
    do
    {
    std::cout<<"1 - Add"<<std::endl;
    std::cout<<"2 - GetMax"<<std::endl;
    std::cout<<"3 - GetMin"<<std::endl;
    std::cout<<"4 - GetAVG"<<std::endl;
    std::cout<<"5 - GetCountUnder"<<std::endl;
    std::cout<<"6 - GetCountAbove"<<std::endl;
    std::cout<<"7 - Exit"<<std::endl;
    std::cin>>menu_choose;
    switch (menu_choose)
    {
    case 1:
        std::cout<<"Input the element";
        std::cin>>num;
        p.Add_num(num);
        system("PAUSE");
        system("cls");
        break;
    case 2:
        std::cout<<p.Get_max()<<std::endl;
        system("PAUSE");
        system("cls");
        break;
    case 3:
        std::cout<<p.Get_min()<<std::endl;
        system("PAUSE");
        system("cls");
        break;
    case 4:
        std::cout<<p.Get_AVG()<<std::endl;
        system("PAUSE");
        system("cls");
        break;
    case 5:
        std::cout<<"Input border element"<<std::endl;
        float value;
        std::cin>>value;
        std::cout<<p.Get_count_under(value)<<std::endl;
        system("PAUSE");
        system("cls");
        break;
    case 6:
        std::cout<<"Input border element"<<std::endl;
        float value1;
        std::cin>>value1;
        std::cout<<p.Get_count_above(value1)<<std::endl;
        system("PAUSE");
        system("cls");
        break;
    case 7:
        system("cls");
        break;
    }
    } while (menu_choose != 7);
    return 0;
}
