EXENAME = main
HEADERS = game.hpp interactive.hpp demo.hpp unit_types.hpp
OBJFILES = cell.o pos.o map.o unit.o interactive.o demo.o unit_types.o main.o
LDLIBS = -lm

all: $(EXENAME)

$(OBJFILES): $(HEADERS)

$(EXENAME): $(OBJFILES)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

clean:
	$(RM) $(EXENAME) $(OBJFILES)
