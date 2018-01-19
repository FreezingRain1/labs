#pragma once

#include <iostream>
#include <map>
using namespace std;

class IniParser {

private:
     map <string, map <string, string>> table;

public:
	

	 IniParser();

	~IniParser();

	void Initialize(const string  &filename);

	bool IsHaveSection(const string  &section_name) const;

	bool IsHaveParam(const string  &section_name, const string  &param_name) const;

	template <typename S>
	S GetValue(string const &section_name, string const &param_name) const;

protected:
	void parser(ifstream &file);
	
};