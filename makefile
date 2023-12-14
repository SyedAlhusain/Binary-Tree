CXX = g++
CXXFLAGS = -Wall
mytest: mytest.cpp fleet.cpp
	$(CXX) $(CXXFLAGS) mytest.cpp fleet.cpp -o mytest

run:
	valgrind ./mytest
