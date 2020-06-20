#include <string.h>

#include <iostream>
#include <fstream>

#include "demo.hpp"

#include "player.hpp"
#include "iostream_player.hpp"
#include "event_printer.hpp"
#include "base.hpp"
#include "map.hpp"
#include "factory_table.hpp"

void
run_demos(void)
{
    std::cout << "Demo 1\n";
    demo1();

    std::cout << "\nDemo 2\n";
    demo2();

    std::cout << "\nDemo 3\n";
    demo3();

    std::cout << "\nDemo 4\n";
    demo4();

    std::cout << "\nDemo 5\n";
    demo5();

    std::cout << "\nDemo 6\n";
    demo6();

    std::cout << "\nDemo 7\n";
    demo7();

    std::cout << "\nDemo 8\n";
    demo8();

    std::cout << "\nDemo 9\n";
    demo9();
}

int
run_game(int argc, char **argv)
{
    std::vector<LoggingEventPrinter *> loggers {};
    bool have_stdout = false;

    for (int i = 1; i < argc; ++i) {
        if (!strcmp(argv[i], "-log")) {
            char *fn = argv[++i];
            if (!strcmp(fn, "-")) {
                loggers.push_back(new LoggingEventPrinter {std::cout});
                have_stdout = true;
            } else {
                auto *of = new std::ofstream {fn};
                if (!*of) {
                    std::cerr << "Failed to open file: " << fn << "\n";
                    return 1;
                }
                loggers.push_back(new LoggingEventPrinter {of});
            }
        } else {
            std::cerr << "Unknown option: " << argv[i] << "\n";
            return 1;
        }
    }

    Map *map = new Map {10, 10};

    Game g {map};

    for (auto *logger: loggers) {
        g.logSink()->subscribe(logger);
    }

    EventPrinter *pr = nullptr;
    if (!have_stdout) {
        pr = new EventPrinter {std::cout};
        g.subscribe(pr);
    }

    Base *b1 = new Base {};
    map->addBase(b1, {1, 1});
    g.addBase(b1);

    Base *b2 = new Base {};
    map->addBase(b2, {8, 8});
    g.addBase(b2);

    auto *p1 = new IostreamPlayer {"Player 1"};
    p1->setOstream(std::cout);
    p1->setIstream(std::cin);
    g.setPlayer(0, p1);

    auto *p2 = new IostreamPlayer {"Player 2"};
    p2->setOstream(std::cout);
    p2->setIstream(std::cin);
    g.setPlayer(1, p2);

    while (g.playersCount())
        g.spin();

    for (auto *logger: loggers) {
        g.logSink()->unsubscribe(logger);
        delete logger;
    }

    if (pr) {
        g.unsubscribe(pr);
        delete pr;
    }

    return 0;
}

int
main(int argc, char **argv)
{
    if (argc == 2
        && !strcmp(argv[1], "-demo")) {
        run_demos();
        return 0;
    }

    return run_game(argc, argv);
}
