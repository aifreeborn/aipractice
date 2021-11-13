OBJECTS = aimain.exe

include ./ailibs/Makefile_template

LOCALFLAGS := -I.

aimain.exe : aimain.o
	$(CXX) $(CXXFLAGS) $(LOCALFLAGS) $^ -o $@
