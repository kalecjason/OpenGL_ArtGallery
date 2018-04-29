#ifndef FILE_READER_H
#define FILE_READER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class FileReader
{
public:
	//get content from passed file as string
	static std::string FileReader::getContents(std::string path);
};
#endif // !FILE_READER_H