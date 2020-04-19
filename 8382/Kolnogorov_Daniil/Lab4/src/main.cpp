#include "Game/game.hpp"
#include "Logging/formatter_time.hpp"
#include "Logging/logger_file.hpp"
#include "Logging/logger_terminal.hpp"
#include "UI/render.hpp"
#include <cstdlib>
#include <ctime>

// TODO rewrite the entire program

int main() {
    srand(time(NULL));

    Game game = Game();

    // game.set_logger(new LoggerFile("log.txt"));
    game.set_logger(new LoggerTerminal());
    game.set_log_formatter(new FormatterTime());

    Renderer renderer = Renderer(&game);

    while (game.is_running()) {
        renderer.render();
    }

    renderer.close();

    return 0;
}
