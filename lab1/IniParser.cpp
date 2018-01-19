#include <iostream>
#include <string>
#include <fstream>
#include "IniParser.h"
#include <map>
#include "Except.h"

using namespace std;

IniParser::IniParser() {

}

IniParser::~IniParser() {
	table.clear();
}

void IniParser::Initialize(const string  &filename) {
	ifstream fin(filename);
	if (!fin.is_open()) {
		throw NoFile("File not open or not read");
	} else
	IniParser::parser(fin);
}

void IniParser::parser(ifstream &file) {

	int i1, i2 = 0; 
	int n1 = 0;
	string s, section, name, value;

	while (getline(file, s)) {
		int i = 0;
		while ((i = s.find(' ')) != string::npos)
			s.erase(i, 1);

		int p2 = s.find(";");
		if (p2 != s.npos) {
			s.erase(p2, (s.length() - p2));
		}

		i1 = s.find("[");
		i2 = s.find("]");

		if (i1 != s.npos && i2 != s.npos) {
			section = s.substr((i1 + 1), (i1 + (i2 - i1 - 1)));
		}

		n1 = s.find("=");
		if (n1 != s.npos) {
			name = s.substr(0, n1);
			int p1 = n1 + 1;
			int p2 = s.find("\0");
			if (p2 != s.npos) {
				value = s.substr(p1, (p2 - 1));
			}

		}

		table[section][name] = value;

	}
}

bool IniParser::IsHaveSection(const string  &section_name) const {
	auto n= table.find(section_name);
	if (n != table.end()) {
		return true;
	}
	else {
	throw NoSection("Section not find");
	return false;
	}
}

bool IniParser::IsHaveParam(const string  &section_name, const string  &param_name) const  {
	auto n = table.find(section_name);
	if (n != table.end()) {
		auto n1 = n->second.find(param_name);
		if (n1 != n->second.end()) {
			return true;
		}
		else {
		throw NoParam("Value not find");
		return false;
		}
	}
	else {
	throw NoSection("Section not find");
	return false;
	}
}


template <>
string IniParser::GetValue<string>(string const &section_name, string const &param_name) const {

	string value = table.find(section_name)->second.find(param_name)->second;
	return value;

}

template <>
int IniParser::GetValue<int>(string const &section_name, string const &param_name) const {

	string value = table.find(section_name)->second.find(param_name)->second;
	int n = stoi(value);
	return n;

}

template <>
double IniParser::GetValue<double>(string const &section_name, string const &param_name) const {

	string value = table.find(section_name)->second.find(param_name)->second;
	double n = stod(value);
	return n;

}