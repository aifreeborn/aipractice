OBJECTS = aitest.exe

include ../Makefile_template

LOCALFLAGS := -I.

aitest.exe : aitest.o AIPerson.o
	$(CXX) $(CXXFLAGS) $(LOCALFLAGS) $^ -o $@
