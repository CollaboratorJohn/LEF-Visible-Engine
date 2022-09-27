#include "CLEF_File.h"
#include <fstream>

CLEF_File::CLEF_File() {}

CLEF_File::CLEF_File(const std::string &file_path) :m_file_path(file_path)  {}

CLEF_File::~CLEF_File() {};


const std::string& CLEF_File::getFilePath() const {
	return m_file_path;
}

void CLEF_File::setFilePath(const std::string & path) {
	m_file_path = path;
}

void CLEF_File::parse(CDesign* design) const {
	std::ifstream input(m_file_path);
	std::string line;

	if (!input.is_open()) {
		std::cout << "couldn't open file!!! Wrong path\n";
	}
	while (input >> line)
	{
		if (line == "MACRO") {
			CCell newCell;
			design->addCell(newCell);
			detectCell(input, design->getCellIterator());
		}
	}
}

void CLEF_File::detectCell(std::ifstream &  , const std::vector<CCell>::iterator cell)const {
	std::string line;
	stream >> line;
	unsigned count = 1;
	cell->setName(line);
	while (stream >> line) {
		if (line == "PIN" | line == "OBS") {
			if (line == "PIN")
				++count;
			detectLayer(stream, cell);
		} else {
			if (line == "END") {
				--count;
				if (!count){
					return;
				}
			}
		}
	}
}


void CLEF_File::detectLayer(std::ifstream & stream, const std::vector<CCell>::iterator cell)const {
	std::string line, line_ = "", pin_name;
	stream >> line;

	double coordinate;

	if (line == "LAYER"){
		line = "OBS";
		line_ = "LAYER";
	}

	pin_name = line;
	while (stream >> line) {
		if (line_ == "LAYER" || line == "LAYER"){
			if (line_ == "LAYER"){
				line_ = "";
			} else {
				stream >> line;
			}
			
			// CLayer& layer = cell.getLayer(line);
			auto layer = cell->getLayerIterator(line);
			layer->setParent(cell);

			//prepare pin
			CPin pin;
			pin.setParent(layer);

			pin.setName(pin_name);
			pin.setLayerName(line);
			
			layer->addPolygons(pin);
			detectPin(stream, layer->getPinIterator(), line);

			if (line == "LAYER") {
				line_ = "LAYER";
				continue;
			}
			if (line == "END") {
				return;
			}
		} else {
			if (line == "END")
				return;
		}
	}
}

void CLEF_File::detectPin(std::ifstream & stream, const std::vector<CPin>::iterator pin, std::string& line)const {
	double coordinate;

	while (stream >> line) {
		if (line == "RECT") {
			CRectangle newRectangle;
			newRectangle.setParent(pin);

			CCoordinate ur;
			CCoordinate dl;
			stream >> coordinate;
			dl.setX(coordinate);
			stream >> coordinate;
			dl.setY(coordinate);
			stream >> coordinate;
			ur.setX(coordinate);
			stream >> coordinate;
			ur.setY(coordinate);

			newRectangle.setDL(dl);
			newRectangle.setUR(ur);
			pin->addPolygon(newRectangle);

			auto rect = pin->getRectIterator();
			HashRect::getInstance()->setRectHash(rect);
		}
		else {
			if (line == "LAYER" || line == "END") {
				return;
			}

		}
	}
}