#ifndef LOGIC_INTERFACES_HPP
#define LOGIC_INTERFACES_HPP

#include "third_party_includes.hpp"

namespace ent { class unit; }
namespace ent { class unit_prototype; }
namespace game { class abstract_game; }


/// For json serialization
/// Ignores N_S | mutable marked fields (manual)
class iserializable {
public:
    /// Saves object state into package
    virtual void serialize (json& package) const = 0;
    /// Restores object state from package
    virtual void deserialize (json& package) = 0;
    virtual ~iserializable () = default;
};

class iserializable_public {
public:
    /// Returns public data of the object into package
    virtual void serialize_public (json& package) const = 0;
    virtual ~iserializable_public () = default;
};


/// For polymorphic deserialization (json_tools::unpack_***)
class ityped {
public:
    /// Must return j_{class_name}::type
    virtual const std::string& type () const = 0;
    virtual ~ityped () = default;
};

/// For unit's behaviours
class icomponent : public ityped {
public:
    /// Packs enemy visible data into the package
    virtual void serialize_public(const ent::unit& owner, json& package) const = 0;
    /// Initializes unit_prototype while manual adding components
    virtual void setup_prototype (ent::unit_prototype& prototype) = 0;
    /// Signal from sender to owner in the game's update()
    virtual void command (ent::unit& sender, ent::unit& owner, game::abstract_game& context, json& input) = 0;
    /// Signal from user to owner in the game's signal()
    virtual void signal (ent::unit& owner, game::abstract_game& context, json& input) = 0;
    /// Updates the owner state in the game's update()
    virtual void update (ent::unit& owner, game::abstract_game& context) = 0;
    virtual ~icomponent () = default;
};


/// For game loop purposes
class ihandler : public ityped {
public:
    /// Game loop
    virtual void game_update (json& output) = 0;
    /// Restores game from input
    virtual void game_load (json& input, json& output) = 0;
    /// Serializes game into output
    virtual void game_save (json& output) = 0;
    /// Adds user into the session
    virtual void game_join (int player_uid, json& output) = 0;
    /// Removes user from the session
    virtual void game_quit (int player_uid, json& output) = 0;
    /// Starts the game
    virtual void game_play (json& output) = 0;
    /// Pauses the game
    virtual void game_pause (json& output) = 0;
    /// Stops the game
    virtual void game_stop (json& output) = 0;
    /// Creates the game from the input rules TODO API for game creating
    virtual void game_setup (json& input, json& output) = 0;
    /// Signal from user
    virtual void game_signal (json& input, json& output) = 0;
    virtual ~ihandler () = default;
};

// Not implemented:

/// For flushing memory before returning into object pool
// TODO in unit_factory
class idisposable {
public:
    virtual void dispose () = 0;
    virtual ~idisposable () = default;
};


#endif //LOGIC_INTERFACES_HPP