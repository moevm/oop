EXENAME = main
HEADERS = map.hpp unit.hpp interactive.hpp demo.hpp unit_types.hpp event.hpp
OBJFILES = map.o unit.o interactive.o demo.o unit_types.o event.o main.o
LDLIBS = -lm

all: $(EXENAME)

$(OBJFILES): $(HEADERS)

$(EXENAME): $(OBJFILES)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

clean:
	$(RM) $(EXENAME) $(OBJFILES)
