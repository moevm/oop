EXENAME = main
HEADERS = point.hpp placeable.hpp rectmap.hpp map.hpp pathfinder.hpp   \
	unit.hpp common_policies.hpp melee_units.hpp ranged_units.hpp      \
	catapult_units.hpp demo.hpp
OBJFILES = point.o rectmap.o map.o pathfinder.o unit.o demo.o main.o
LDLIBS = -lm

all: $(EXENAME)

$(OBJFILES): $(HEADERS)

$(EXENAME): $(OBJFILES)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

clean:
	$(RM) $(EXENAME) $(OBJFILES)
