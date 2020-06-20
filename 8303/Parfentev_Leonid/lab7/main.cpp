#include <string.h>

#include <stdexcept>
#include <iostream>
#include <fstream>

#include "demo.hpp"

#include "event_printer.hpp"
#include "game_driver.hpp"
#include "game_rules.hpp"
#include "exceptions.hpp"


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

Game *
loadGame(const std::string &load_fn)
{
    std::ifstream f {load_fn};
    if (!f) {
        throw NoSavegameFile {load_fn};
    }
    auto *tab = RestorerTable::defaultTable();
    Storable *s = tab->restore(f);
    delete tab;

    if (auto *lg = dynamic_cast<Game *>(s)) {
        return lg;
    } else {
        delete s;
        throw InvalidSaveFileContents {load_fn, f.tellg()};
    }
}

int
run_game(int argc, char **argv)
{
    std::vector<EventPrinter *> loggers {};
    bool have_stdout = false;

    const char *load_fn = nullptr;

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
        } else if (!strcmp(argv[i], "-load")) {
            load_fn = argv[++i];
        } else {
            std::cerr << "Unknown option: " << argv[i] << "\n";
            return 1;
        }
    }

    GameDriver<DefaultRules> drv {};

    for (auto *logger: loggers) {
        drv.addLogger(logger);
    }

    if (!have_stdout) {
        drv.setPrinter(new EventPrinter {std::cout});
    }

    if (load_fn) {
        try {
            drv.resetFrom(loadGame(load_fn));
        } catch (std::exception &e) {
            std::cerr << "An error occurred while loading savegame:\n"
                      << e.what() << "\n";
            return 1;
        }
    } else {
        drv.reset();
    }

    drv.run();

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
