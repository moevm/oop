#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include <map>
#include <utility>
#include <exception>

#include "game_elements/team.h"

class Level
{
    friend class Field;

public:
    struct failure: public std::exception{
        const char *msg;
        failure(const char *msg):msg(msg){}
        const char * what() const throw(){
            return msg;
        }
    };

    struct entity_stats{
        enum Type{
            worker_stats,
            combat_stats,
            building_stats,
            object_stats
        };

        struct WorkerSt{
            float health;
            float steps;
            float extraSteps;

            int target_x;
            int target_y;
        };

        struct CombatSt{
            float health;
            float steps;
            float extraDamage;
        };

        struct BuildingSt{
            float health;
            int rotation;
        };

        struct ObjectSt{
            int durability;
        };

        Team team;
        Type type;
        bool dflt = 0;

        int x = 0;  // position
        int y = 0;  //
        union{
            WorkerSt    worker;
            CombatSt    combat;
            BuildingSt  building;
            ObjectSt    object;
        };
    };

private:
    //level definers
    std::map<unsigned int, std::string> landscapes;
    std::map<unsigned int, std::string> entities_lib;

    size_t width, height;
    unsigned int* field = nullptr;    // landscapes
    std::vector<std::pair<unsigned int, entity_stats*>> entites;

    int redPoints = 0;
    int bluPoints = 0;

private:
    void addEntity(const std::string& id);
    void addLandscape(const std::string& id);
    bool readStats(std::ifstream& ifs, unsigned int entity, entity_stats& stats);
    bool printStats(std::ofstream& ofs, const std::pair<unsigned int, entity_stats*>& p);
    Level();

public:
    Level(const std::string& file_name);
    Level(const Level& other);
    Level(Level&& other);

    Level& operator=(const Level& other);
    Level& operator=(Level&& other);

    ~Level();

    bool saveToFile(const std::string& file_name);
    bool loadFromFile(const std::string& file_name);

    static Level default_level_1();
    static Level default_level_2();
};

#endif // LEVEL_H
