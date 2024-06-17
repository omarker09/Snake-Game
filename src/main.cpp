#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <cstring>

namespace fs = std::experimental::filesystem;

bool isOpen = true;

bool create_directory(std::string& path) {
	return fs::create_directories(path);
}

bool create_file(std::string& path_file, std::string content) {
	std::ofstream file(path_file);
	if (file)
		file << content;
		return true;
	return false;
}

void Emmit(std::string& path, std::string& file_name, std::string& file_content) {
	std::string base_path = path;
	std::string dir_path = base_path + "\\NewOPP";
	std::string file_path = dir_path + "\\" + file_name;
	std::string full_path = base_path + dir_path;
	std::string content = file_content;

	if (create_directory(dir_path))
		std::cout << "Directory Created at " << dir_path << std::endl;

	if (create_file(file_path, content))
		std::cout << "File Created at " << file_path << std::endl;
}

int main(int argc, char* argv[]) {
	std::string path = "";
	std::string file_name = "";
	std::string file_content = "";

	std::cout << "Enter path to create directory : ";
	std::cin >> path;

	std::cout << "Enter file name like ( example.txt, main.py etc ..) : ";
	std::cin >> file_name;

	std::cout << "Type the file content : ";
	std::cin >> file_content;

	while (isOpen) {
		while (path.empty())
		{
			std::cout << "Enter path to create directory : ";
			std::cin >> path;
			isOpen = false;
		}
		while (file_name.empty()) {
				std::cout << "Enter file name like ( example.txt, main.py etc ..) : ";
				std::cin >> file_name;
				isOpen = false;
		}
		while (file_name.empty()) {
			std::cout << "Type the file content : ";
			std::cin >> file_content;
			isOpen = false;
			}
		isOpen = false;
	}

	Emmit(path, file_name,file_content);
	return 0;
}