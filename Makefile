# -lpcrecpp
#
CXX=g++
# CXXFLAGS = -g -std=c++11 -stdlib=libstdc++ -lpcrecpp -Wall -pedantic -I.
CXXFLAGS = -g -std=c++11 -Wall -pedantic -I.
INC_DIR = include
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

$(BIN_DIR)/test: | $(BIN_DIR) $(OBJ_DIR) $(SRC_DIR)/main.cpp $(OBJ_DIR)/util.o
	$(CXX) $(CXXFLAGS) $(SRC_DIR)/main.cpp -lpcrecpp -o $(BIN_DIR)/test $(OBJ_DIR)/util.o

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/util.o: $(SRC_DIR)/util.cpp $(INC_DIR)/util.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/util.cpp -o $(OBJ_DIR)/util.o

clean:
	rm -rf $(OBJ_DIR)/*.o
	rm -rf $(BIN_DIR)/*
