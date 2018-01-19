#include "IniParser.h"
#include <iostream> 
#include <string>
#include "Except.h"

using namespace std;

int main(){
	try {
		IniParser my;
		my.Initialize("lab01_input_correct_09.ini");
		cout << my.IsHaveSection("DEMODS") << endl;
		cout << my.IsHaveParam("DEMODS", "BufferLenSeconds") << endl;
		cout << my.GetValue<double>("DEMODS", "BufferLenSeconds") << endl;
		cout << my.GetValue<int>("DEMODS", "StartDataPort") << endl;
		cout << my.GetValue<string>("DEMODS", "FileName") << endl;
	}
	catch (myexcept &e) {
		cout << e.what()<<endl;
	}
	system("pause");
}