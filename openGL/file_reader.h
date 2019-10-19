#pragma once
#include <string>
#include <iostream>
using namespace std;

enum f_name {
	FULL,
	PROJECT
};

struct file_reader {
	string get_directory_path();
	string read(const char* path, f_name type);
	
};