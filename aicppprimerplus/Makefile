OBJECTS = aimain.exe

include ./ailibs/Makefile_template

LOCALFLAGS := -I.

aimain.exe : aiqueue.o aimain.o
	$(CXX) $(CXXFLAGS) $(LOCALFLAGS) $^ -o $@
