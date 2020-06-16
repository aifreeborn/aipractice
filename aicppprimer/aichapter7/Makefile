OBJECTS = aitest.exe

include ../Makefile_template

LOCALFLAGS := -I.

aitest.exe : aitest.o AISales_data.o
	$(CXX) $(CXXFLAGS) $(LOCALFLAGS) $^ -o $@
