#include "thread.h"

int main()
{
    std::string file_name, out_file_name;
    //std::cin>>file_name>>out_file_name;
    file_name = "d://tests//in.txt";
    out_file_name = "d://tests//out.txt";
    threader t1(file_name, out_file_name);
    t1.threader_function();
    return 0;
}
