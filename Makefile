CXX=g++ 
CXXFLAGS=-std=c++14 -Wall -O -g -MMD -Werror=vla # use -MMD to generate dependencies
SOURCES=$(wildcard *.cc)   # list of all .cc files in the current directory
OBJECTS=${SOURCES:.cc=.o}  # .o files depend upon .cc files with same names
DEPENDS=${OBJECTS:.o=.d}   # .d file is list of dependencies for corresponding .cc file
EXEC=constructor

# First target in the makefile is the default target.
# Note that the LIBFLAGS must come last in the command
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC)

component.o: component.cc component.h 
	$(CXX) -c $(CXXFLAGS) component.cc

controller.o: controller.cc controller.h player.h component.h
	$(CXX) -c $(CXXFLAGS) controller.cc

player.o: player.cc player.h
	$(CXX) -c $(CXXFLAGS) player.cc

startup.o: startup.cc startup.h controller.h
	$(CXX) -c $(CXXFLAGS) startup.cc

view.o: view.cc view.h controller.h component.h
	$(CXX) -c $(CXXFLAGS) view.cc
	
main.o: main.cc startup.h controller.h view.h controller.cc
	$(CXX) -c $(CXXFLAGS) main.cc

-include ${DEPENDS}

.PHONY: clean
clean:
	rm  -f $(OBJECTS) $(DEPENDS) $(EXEC)