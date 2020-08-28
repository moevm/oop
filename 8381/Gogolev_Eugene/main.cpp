#include "stl.hpp"
#include "ui.hpp"
#include "game.hpp"
#include "game_rule.hpp"
#include "exceptions/saving_exception.hpp"
#include "exceptions/loading_exception.hpp"
#include "loggers/terminal_logger.hpp"
#include "loggers/file_logger.hpp"


int main () {
    UI ui;
    GameRule gameRule;
    LoggerProxy* logger = new LoggerProxy(new FileLogger("log.txt"));
    Game game = Game(&gameRule, &ui);
    game.setLogger(logger);

    string buffer;
    while (true) {
        cin >> buffer;
        Unit* ru = gameRule.getCitadel(RED);
        if (ru == nullptr) break;
        int prx = ru->getTargetX();
        int pry = ru->getTargetY();
        Unit* bu = gameRule.getCitadel(BLUE);
        if (bu == nullptr) break;
        int pbx = bu->getTargetX();
        int pby = bu->getTargetY();

        if (buffer == "q") {
            break;
        }
        else if (buffer == "save") {
            ofstream os;
            os.open ("backup.data");
            if (!os) {
                throw savingException("Can't open file");
            }
            else {
                game.save(os);
                os.close();
                logger->log("Game saved.");
                cout << "Game saved." << endl;
            }
            continue;
        }
        else if (buffer == "load") {
            ifstream is;
            is.open ("backup.data");
            if (!is) {
                throw loadingException("Can't open file");
            }
            else {
                game.load(is);
                is.close();
                logger->log("Game loaded.");
                cout << "Game loaded." << endl;
            }
            continue;
        }
        else if (buffer == "w") {
            game.setTarget(RED, prx, pry - 1);
        }
        else if (buffer == "a") {
            game.setTarget(RED, prx - 1, pry);
        }
        else if (buffer == "s") {
            game.setTarget(RED, prx, pry + 1);
        }
        else if (buffer == "d") {
            game.setTarget(RED, prx + 1, pry);
        }
        else if (buffer == "i") {
            game.setTarget(BLUE, pbx, pby - 1);
        }
        else if (buffer == "j") {
            game.setTarget(BLUE, pbx - 1, pby);
        }
        else if (buffer == "k") {
            game.setTarget(BLUE, pbx, pby + 1);
        }
        else if (buffer == "l") {
            game.setTarget(BLUE, pbx + 1, pby);
        }

        //ui.clear();
        game.update();
        ui.showFrame();

        if (gameRule.isGameEnded()) break;
    }

    if (gameRule.isGameEnded()) {
        cout << "Game ended" << endl;
    }
    else {
        cout << "Game stoped" << endl;
    }

    return 0;
}
