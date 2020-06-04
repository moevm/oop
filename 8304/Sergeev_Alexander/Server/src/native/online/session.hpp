#ifndef LOGIC_SESSION_HPP
#define LOGIC_SESSION_HPP

#include "../base/includes.hpp"
#include "../game/abstract_game.hpp"
#include "../states/choosing.hpp"
#include "../states/playing.hpp"
#include "../states/holding.hpp"

namespace online {
    // JSON
    namespace j_session {
        const std::string type = TOSTRING(session); // : string
        const std::string session_name = TOSTRING(session_name); // : string?
        const std::string players_uid = TOSTRING(players_uid); // : list<int>?
        const std::string state = TOSTRING(state); // : string
        const std::string game = TOSTRING(game); // : abstract_game?
    }

    class session : public ihandler {
        friend class states::choosing;
        friend class states::holding;
        friend class states::playing;

    private:
        std::string session_name;
        std::set<int> players_uid;
        std::unique_ptr<ihandler> state;
        std::unique_ptr<game::abstract_game> game;

    public:
        explicit session (const std::string& nsession_name);
        const std::string& type () const override;

        std::string get_session_name ();
        int get_player_count ();
        void get_session_info (json& output);
        void get_game_info (json& output);

        void game_update (json& output) override;
        void game_load (json& input, json& output) override;
        void game_save (json& output) override;
        void game_join (int player_uid, json& output) override;
        void game_quit (int player_uid, json& output) override;
        void game_play (json& output) override;
        void game_pause (json& output) override;
        void game_stop (json& output) override;
        void game_setup (json& input, json& output) override;
        void game_signal (json& input, json& output) override;

    private:
        void transition_to (std::unique_ptr<ihandler> nstate);
    };
}

#endif //LOGIC_SESSION_HPP
