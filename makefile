COMPILER = g++
TARGET = lef_def_parser
OBJS = main.o CCell.o CCoordinate.o CDesign.o CLayer.o CPin.o CLEF_File.o CRectangle.o HashRect.o

$(TARGET): $(OBJS)
	$(COMPILER) -o $(TARGET) $(OBJS)

main.o: main.cpp CLEF_File.h widgets.h
	$(COMPILER) -c main.cpp -o main.o -std=c++14

CLEF_File.o: CLEF_File.cpp CLEF_File.h
	$(COMPILER) -c CLEF_File.cpp -o CLEF_File.o -std=c++14

HashRect.o: HashRect.cpp widgets.h 
	$(COMPILER) -c HashRect.cpp -o HashRect.o -std=c++14

CCell.o: CCell.cpp widgets.h
	$(COMPILER) -c CCell.cpp -o CCell.o -std=c++14

CCoordinate.o: CCoordinate.cpp widgets.h
	$(COMPILER) -c CCoordinate.cpp -o CCoordinate.o -std=c++14

CDesign.o: CDesign.cpp widgets.h
	$(COMPILER) -c CDesign.cpp -o CDesign.o -std=c++14

CLayer.o: CLayer.cpp widgets.h
	$(COMPILER) -c CLayer.cpp -o CLayer.o -std=c++14

CPin.o: CPin.cpp widgets.h
	$(COMPILER) -c CPin.cpp -o CPin.o -std=c++14

CRectangle.o: CRectangle.cpp widgets.h
	$(COMPILER) -c CRectangle.cpp -o CRectangle.o -std=c++14

.PHONY: clean
clean:
	rm -f *.o lef_def_parser
