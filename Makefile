# -lpcrecpp
#
CXX=g++
# CXXFLAGS = -g -std=c++11 -stdlib=libstdc++ -lpcrecpp -Wall -pedantic -I.
CXXFLAGS = -g -std=c++11 -lpcrecpp -Wall -pedantic  -I.
INC_DIR = include
SRC_DIR = src
OBJ_DIR = obj

test: $(SRC_DIR)/main.cpp 
	$(CXX) $(CXXFLAGS) $(SRC_DIR)/main.cpp -o test 

# $(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
# 	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/main.cpp -o $(OBJ_DIR)/main.o -lpcrecpp
clean:
	rm -rf $(OBJ_DIR)/*.o
	rm -rf test
