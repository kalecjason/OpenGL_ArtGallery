#include "FileReader.h"

//inspired by Shader.h from learnopengl.com
std::string FileReader::getContents(std::string path) {
	std::string str;
	std::ifstream file;

	// ensures ifstream object can throw exceptions:
	file.exceptions(std::ifstream::badbit);

	try
	{
		// Open file
		file.open(path);

		std::stringstream stream;
		// Read file's buffer contents into stream
		stream << file.rdbuf();

		// close file handler
		file.close();

		// Convert stream into string
		str = stream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::FILEREADER::FILE_NOT_SUCCESFULLY_READ:\"" << path << "\"" << std::endl;
	}
	return str;
}