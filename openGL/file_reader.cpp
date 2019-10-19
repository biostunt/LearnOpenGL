#include "file_reader.h"
#include <string>
#include <iostream>
#include <windows.h>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
using namespace std;

string file_reader::get_directory_path() {
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	string::size_type pos = string(buffer).find_last_of("\\/");
	return string(buffer).substr(0, pos);
}

string file_reader::read(const char* path, f_name type) {
	string p = "";
	switch (type) {
		case FULL:
			p = path;
			break;
		case PROJECT:
			p = file_reader::get_directory_path() + path;
	}

	string line;
	string data = "";
	ifstream f(p);
	if (f.is_open())
	{
		while (getline(f, line))
		{
			data = data + line + ' ';
		}
		f.close();
	}
	return data;
}
