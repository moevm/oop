#ifndef LOGIC_CHOOSING_HPP
#define LOGIC_CHOOSING_HPP

#include "../base/includes.hpp"

namespace online { class session; }

namespace states {
    // JSON
    namespace j_choosing {
        const std::string type = TOSTRING(choosing);
    }

    class choosing : public ihandler {
    private:
        online::session& session;
    public:
        explicit choosing (online::session& context);
        const std::string& type () const override;
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
    };
}


#endif //LOGIC_CHOOSING_HPP
