CXX = g++.exe
CXXFLAGS = \
	-Wall \
	-static-libgcc \
	-static-libstdc++ \
	-ID:/boost_1_82_0/include/boost-1_82 \
	-ID:/boost_1_82_0/lib

OBJDIR = obj
BIN = bin\Dateinamen.exe
OBJ = $(OBJDIR)\main.o

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^  -LD:\boost_1_82_0\lib -lboost_filesystem-mgw13-mt-d-x64-1_82 -lboost_system-mgw13-mt-d-x64-1_82

$(OBJDIR)\main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

.PHONEY: clean
clean:
	-if exist $(BIN) del $(BIN)
	-if exist $(OBJ) del $(OBJ)
