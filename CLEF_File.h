#ifndef CLEF_FILE_H
#define CLEF_FILE_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "widgets.h"

class CLEF_File {

public:
	CLEF_File();
	CLEF_File(const std::string &);
	~CLEF_File();
	void setFilePath(const std::string &);
	const std::string& getFilePath() const;
	void parse(CDesign *)const;
	void detectCell(std::ifstream &, std::vector<CCell>::iterator)const;
	void detectLayer(std::ifstream &, std::vector<CCell>::iterator)const;
	void detectPin(std::ifstream &, std::vector<CPin>::iterator, std::string&)const;
private:
	std::string m_file_path;
};

#endif