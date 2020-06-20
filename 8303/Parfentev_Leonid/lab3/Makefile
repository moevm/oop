EXENAME = main
HEADERS = point.hpp placeable.hpp rectmap.hpp map.hpp pathfinder.hpp   \
	unit.hpp common_policies.hpp melee_units.hpp ranged_units.hpp      \
	catapult_units.hpp demo.hpp event.hpp base.hpp object_w_health.hpp \
	landscape.hpp landscape_types.hpp neutral_object.hpp               \
	neutral_object_types.hpp unit_factory.hpp game.hpp                 \
    object_print.hpp event_printer.hpp iostream_player.hpp             \
	mediator.hpp zombie_collector.hpp
OBJFILES = point.o rectmap.o map.o pathfinder.o unit.o demo.o main.o   \
	 event.o base.o game.o object_print.o iostream_player.o mediator.o
LDLIBS = -lm

all: $(EXENAME)

$(OBJFILES): $(HEADERS)

$(EXENAME): $(OBJFILES)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

clean:
	$(RM) $(EXENAME) $(OBJFILES)
