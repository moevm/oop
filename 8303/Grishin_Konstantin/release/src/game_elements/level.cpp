#include "level.h"

#include <iostream>
#include <fstream>
#include <sstream>

Level::Level(){
    landscapes[0] = "empty";
    entities_lib[0] = "empty";
}


Level::Level(const Level& other){
    width = other.width;
    height = other.height;

    field = new unsigned int[width*height];
    for(size_t i = 0; i < width*height; i++){
        field[i] = other.field[i];
    }

    entites = other.entites;
}


Level::Level(Level&& other){
    field = other.field;
    entites = std::move(other.entites);
}


Level& Level::operator=(const Level &other){
    if(this != &other){
        width = other.width;
        height = other.height;

        field = new unsigned int[width*height];
        for(size_t i = 0; i < width*height; i++){
            field[i] = other.field[i];
        }

        entites = other.entites;
    }
    return *this;
}


Level& Level::operator=(Level &&other){
    field = other.field;
    entites = std::move(other.entites);
    return *this;
}


Level::Level(const std::string& file_name)
{
    landscapes[0] = "empty";
    entities_lib[0] = "empty";

    // open file
    std::ifstream file(file_name);

    if(!file.good())
        throw failure("can't open level file");

    // parse landscapes
    std::string id;
    while(id != "@" && file.good()){
        file >> id;
        if(id != "@")
            addLandscape(id);
    }
    id.clear();

    if(!file.good())  // better throw exception
        throw failure("level file landscapes reading error");

    // parse entities
    while(id != "@" && file.good()){
        file >> id;
        if(id != "@")
            addEntity(id);
    }

    if(!file.good())
        throw failure("level file entites reading error");

    // get size of field
    file >> width >> height;

    if(!file.good())
        throw failure("level file map size reading error");

    // allocate memory for field
    field = new unsigned int[width*height];
    for(size_t i = 0; i < width*height && file.good(); i++){
        size_t l;
        file >> l;
        if(l == 0){
            // do something, this is a bad case
        }

        field[i] = l;
    }

    if(!file.good())
        throw failure("level file map reading error");

    file >> id;
    if(id != "@")
        throw failure("level file identifier reading error");

    unsigned int e;
    while(file >> e){
//        unsigned int e;
//        file >> e;
        auto stats = new entity_stats;
        if(!readStats(file, e, *stats)){
            delete stats;
            stats = nullptr;
        }

        entites.emplace_back(e, stats);
    }

}


Level::~Level(){
    delete [] field;
}


void Level::addEntity(const std::string &id){
    entities_lib[entities_lib.size()] = id;
}


void Level::addLandscape(const std::string &id){
    landscapes[landscapes.size()] = id;
}


bool Level::readStats(std::ifstream &ifs, unsigned int entity, entity_stats &stats){
    if(entities_lib.count(entity) == 0 || entity == 0){
        ifs.ignore(256, '\n');
        return 0;
    }

    ifs >> stats.x >> stats.y;

    auto& id = entities_lib[entity];
    if(id == "unit_archer" || id == "unit_atrons"
    || id == "unit_knight" || id == "unit_troll"
    || id == "unit_wizard" || id == "unit_berserk")
    {
        stats.type = entity_stats::combat_stats;

        bool bTeam;
        ifs >> bTeam;
        if(bTeam == 1){
            stats.team = Team::Blu;
        } else {
            stats.team = Team::Red;
        }

        std::string input_stats;
        std::getline(ifs, input_stats);

        std::stringstream ss(input_stats);

        ss >> stats.combat.health >> stats.combat.steps >> stats.combat.extraDamage;
        return 1;
    }

    if(id == "unit_worker")
    {
        stats.type = entity_stats::worker_stats;

        bool bTeam;
        ifs >> bTeam;
        if(bTeam == 1){
            stats.team = Team::Blu;
        } else {
            stats.team = Team::Red;
        }

        std::string input_stats;
        std::getline(ifs, input_stats);

        std::stringstream ss(input_stats);

        ss >> stats.worker.health >> stats.worker.steps >> stats.worker.extraSteps
           >> stats.worker.target_x >> stats.worker.target_y;
        return 1;
    }

    if(id == "building_base" || id == "buildig_tower" || id == "building_barrack"){
        stats.type = entity_stats::building_stats;

        bool bTeam;
        ifs >> bTeam;
        if(bTeam == 1){
            stats.team = Team::Blu;
        } else {
            stats.team = Team::Red;
        }

        std::string input_stats;
        std::getline(ifs, input_stats);

        std::stringstream ss(input_stats);

        ss >> stats.building.health >> stats.building.rotation;
        return 1;
    }

    if(id == "object_barrel" || id == "object_rock"
    || id == "object_tree"  || id == "object_healing_poition"
    || id == "object_stamina_poition" || id == "object_strength_poition")
    {
        stats.type = entity_stats::object_stats;

        std::string input_stats;
        std::getline(ifs, input_stats);

        std::stringstream ss(input_stats);

        ss >> stats.object.durability;
        return 1;
    }

    ifs.ignore(256, '\n');
    return 0;
}


bool Level::printStats(std::ofstream &ofs, const std::pair<unsigned int, entity_stats *>& p)
{
    ofs << p.second->x << " " << p.second->y << " ";

    auto& id = entities_lib[p.first];
    if(id == "unit_archer" || id == "unit_atrons"
    || id == "unit_knight" || id == "unit_troll"
    || id == "unit_wizard" || id == "unit_berserk")
    {
        bool bTeam;

        if(p.second->team == Team::Blu){
            bTeam = 1;
        } else {
            bTeam = 0;
        }

        ofs << bTeam << " ";

        ofs << p.second->combat.health << " "
            << p.second->combat.steps << " "
            << p.second->combat.extraDamage << std::endl;
        return 1;
    }

    if(id == "unit_worker")
    {
        bool bTeam;

        if(p.second->team == Team::Blu){
            bTeam = 1;
        } else {
            bTeam = 0;
        }

        ofs << bTeam << " ";

        ofs << p.second->worker.health << " "
            << p.second->worker.steps << " "
            << p.second->worker.extraSteps << " "
            << p.second->worker.target_x << " "
            << p.second->worker.target_y << std::endl;
        return 1;
    }

    if(id == "building_base" || id == "buildig_tower" || id == "building_barrack"){
        bool bTeam;

        if(p.second->team == Team::Blu){
            bTeam = 1;
        } else {
            bTeam = 0;
        }

        ofs << bTeam << " ";

        ofs << p.second->building.health << " "
            << p.second->building.rotation << std::endl;
        return 1;
    }

    if(id == "object_barrel" || id == "object_rock"
    || id == "object_tree"  || id == "object_healing_poition"
    || id == "object_stamina_poition" || id == "object_strength_poition")
    {
        ofs << p.second->object.durability << std::endl;
        return 1;
    }

    return 0;
}


bool Level::loadFromFile(const std::string &file_name){

    try {
        Level new_level(file_name);

        std::swap(this->field, new_level.field);
        this->entites = std::move(new_level.entites);

    } catch (failure) {
        return 0;
    }
    return 1;
}


bool Level::saveToFile(const std::string &file_name){
    std::ofstream ofs(file_name);
    if(!ofs.is_open()){
        throw failure("error open file");
    }
    if(field == nullptr)
    {
        throw failure("empty level");
    }

    for(auto l: landscapes)
    {
        if(l.first > 0)
        {
            ofs << l.second << std::endl;
        }
    }
    ofs << "@" << std::endl;

    for(auto e: entities_lib)
    {
        if(e.first > 0)
        {
            ofs << e.second << std::endl;
        }
    }

    ofs << "@" << std::endl;

    ofs << width << " " << height << std::endl;
    for(size_t xy = 0, j = 0; xy < width * height; xy++)
    {
        ofs << field[xy] << "\t";
        if(++j == width)
        {
            ofs << std::endl;
            j = 0;
        }
    }

    ofs << "@" << std::endl;

    for(auto e: entites)
    {
        ofs << e.first << " ";
        printStats(ofs, e);
    }

    return 1;
}


Level Level::default_level_1(){
    Level level;
    level.addLandscape("landscape_plain");
    level.addLandscape("landscape_rough");
    level.addLandscape("landscape_canyon");

    level.addEntity("building_base");

    level.addEntity("object_barrel");
    level.addEntity("object_rock");
    level.addEntity("object_tree");

    level.addEntity("object_healing_poition");
    level.addEntity("object_stamina_poition");
    level.addEntity("object_strength_poition");

    level.width = 10;
    level.height = 10;
    level.field = new unsigned int[100];
    for(size_t i = 0; i < 100; i++){
        level.field[i] = 1;
    }

    // add special landscape
    std::vector<int> rough =
    {7,8,9,17,18,19,28,29,38,39,40,41,
    50,51,52,60,61,62,70,71,72,73,80,
    81,82,83,84,90,91,92,93,94};
    for(auto xy: rough)
        level.field[xy] = 2;
    rough.clear();

    std::vector<int> canyon =
    {5,15};
    for(auto xy: canyon)
        level.field[xy] = 3;
    canyon.clear();

    // blu base stats
    auto e_stats = new entity_stats;
    e_stats->x = 1;
    e_stats->y = 1;
    e_stats->team = Team::Blu;

    e_stats->type = entity_stats::building_stats;
    e_stats->building.health = 999;
    e_stats->building.rotation = 2; // down

    level.entites.emplace_back(1, e_stats);

    // red base stats
    e_stats = new entity_stats;
    e_stats->x = 8;
    e_stats->y = 8;
    e_stats->team = Team::Red;

    e_stats->type = entity_stats::building_stats;
    e_stats->building.health = 999;
    e_stats->building.rotation = 0; // down

    level.entites.emplace_back(1, e_stats);

    // add trees
    std::vector<int> trees =
    {0,1,2,9,13,14,20,26,27,31,37,38,39,42,43,44,
    53,54,55,64,65,75,79,85,86,89,97,98,99};

    for(auto xy: trees){
        int x = xy%10;
        int y = xy/10;

        e_stats = new entity_stats;
        e_stats->type = entity_stats::object_stats;
        e_stats->dflt = 1;

        e_stats->x = x;
        e_stats->y = y;
        e_stats->team = Team::Neutral;
        level.entites.emplace_back(4, e_stats);
    }
    trees.clear();

    // add rocks
    std::vector<int> rocks =
    {3,6,7,8,30,70,71,80,81,82,90,91,92,93,95,96};

    for(auto xy: rocks){
        int x = xy%10;
        int y = xy/10;

        e_stats = new entity_stats;
        e_stats->type = entity_stats::object_stats;
        e_stats->dflt = 1;

        e_stats->x = x;
        e_stats->y = y;
        e_stats->team = Team::Neutral;
        level.entites.emplace_back(3, e_stats);
    }
    rocks.clear();

    // add barrels
    std::vector<int> barrels =
    {16,17,18,28,52,60,61,63,69,72,83,94};

    for(auto xy: barrels){
        int x = xy%10;
        int y = xy/10;

        e_stats = new entity_stats;
        e_stats->type = entity_stats::object_stats;
        e_stats->dflt = 1;

        e_stats->x = x;
        e_stats->y = y;
        e_stats->team = Team::Neutral;
        level.entites.emplace_back(2, e_stats);
    }
    barrels.clear();

    std::vector<int> healing_poitions =
    {24, 48};

    for(auto xy: healing_poitions){
        int x = xy%10;
        int y = xy/10;

        e_stats = new entity_stats;
        e_stats->type = entity_stats::object_stats;
        e_stats->dflt = 1;

        e_stats->x = x;
        e_stats->y = y;
        e_stats->team = Team::Neutral;
        level.entites.emplace_back(5, e_stats);
    }

    healing_poitions.clear();

    std::vector<int> stamina_poitions =
    {23, 49};

    for(auto xy: stamina_poitions){
        int x = xy%10;
        int y = xy/10;

        e_stats = new entity_stats;
        e_stats->type = entity_stats::object_stats;
        e_stats->dflt = 1;

        e_stats->x = x;
        e_stats->y = y;
        e_stats->team = Team::Neutral;
        level.entites.emplace_back(6, e_stats);
    }

    stamina_poitions.clear();

    std::vector<int> strength_poitions =
    {19, 29, 40, 50};

    for(auto xy: strength_poitions){
        int x = xy%10;
        int y = xy/10;

        e_stats = new entity_stats;
        e_stats->type = entity_stats::object_stats;
        e_stats->dflt = 1;

        e_stats->x = x;
        e_stats->y = y;
        e_stats->team = Team::Neutral;
        level.entites.emplace_back(7, e_stats);
    }

    strength_poitions.clear();

    return level;
}


Level Level::default_level_2(){
    Level level;
    level.addLandscape("landscape_plain");
    level.addLandscape("landscape_rough");
    level.addLandscape("landscape_canyon");

    level.addEntity("building_base");

    level.addEntity("object_barrel");
    level.addEntity("object_rock");
    level.addEntity("object_tree");

    level.addEntity("object_healing_poition");
    level.addEntity("object_stamina_poition");
    level.addEntity("object_strength_poition");

    level.width = 10;
    level.height = 10;
    level.field = new unsigned int[100];
    for(size_t i = 0; i < 100; i++){
        level.field[i] = 1;
    }

    std::vector<int> rough =
    {70,79,80,81,88,89,90,91,92,97,98,99};
    for(auto xy: rough)
        level.field[xy] = 2;
    rough.clear();

    std::vector<int> canyon =
    {4,5,14,15,24,25,34,35,44,45,54,55};
    for(auto xy: canyon)
        level.field[xy] = 3;
    canyon.clear();

    // blu base stats
    auto e_stats = new entity_stats;
    e_stats->x = 1;
    e_stats->y = 1;
    e_stats->team = Team::Blu;

    e_stats->type = entity_stats::building_stats;
    e_stats->building.health = 999;
    e_stats->building.rotation = 2; // down

    level.entites.emplace_back(1, e_stats);

    // red base stats
    e_stats = new entity_stats;
    e_stats->x = 8;
    e_stats->y = 1;
    e_stats->team = Team::Red;

    e_stats->type = entity_stats::building_stats;
    e_stats->building.health = 999;
    e_stats->building.rotation = 0; // down

    level.entites.emplace_back(1, e_stats);

    // add trees
    std::vector<int> trees =
    {3,6,7,8,9,16,23,32,33,41,46,49,52,56,
    73,76,82,87,91,98};

    for(auto xy: trees){
        int x = xy%10;
        int y = xy/10;

        e_stats = new entity_stats;
        e_stats->type = entity_stats::object_stats;
        e_stats->dflt = 1;

        e_stats->x = x;
        e_stats->y = y;
        e_stats->team = Team::Neutral;
        level.entites.emplace_back(4, e_stats);
    }
    trees.clear();

    // add rocks
    std::vector<int> rocks =
    {0,1,2,10,19,26,29,37,39,51,53,58,64,
     65,69,74,75,84,85,94,95};

    for(auto xy: rocks){
        int x = xy%10;
        int y = xy/10;

        e_stats = new entity_stats;
        e_stats->type = entity_stats::object_stats;
        e_stats->dflt = 1;

        e_stats->x = x;
        e_stats->y = y;
        e_stats->team = Team::Neutral;
        level.entites.emplace_back(3, e_stats);
    }
    rocks.clear();

    // add barrels
    std::vector<int> barrels =
    {36,42,43,59,83,86,92,93,96,97};

    for(auto xy: barrels){
        int x = xy%10;
        int y = xy/10;

        e_stats = new entity_stats;
        e_stats->type = entity_stats::object_stats;
        e_stats->dflt = 1;

        e_stats->x = x;
        e_stats->y = y;
        e_stats->team = Team::Neutral;
        level.entites.emplace_back(2, e_stats);
    }
    barrels.clear();

    std::vector<int> healing_poitions =
    {62,67,71,78,80,89};

    for(auto xy: healing_poitions){
        int x = xy%10;
        int y = xy/10;

        e_stats = new entity_stats;
        e_stats->type = entity_stats::object_stats;
        e_stats->dflt = 1;

        e_stats->x = x;
        e_stats->y = y;
        e_stats->team = Team::Neutral;
        level.entites.emplace_back(5, e_stats);
    }

    healing_poitions.clear();

    std::vector<int> stamina_poitions =
    {63,66};

    for(auto xy: stamina_poitions){
        int x = xy%10;
        int y = xy/10;

        e_stats = new entity_stats;
        e_stats->type = entity_stats::object_stats;
        e_stats->dflt = 1;

        e_stats->x = x;
        e_stats->y = y;
        e_stats->team = Team::Neutral;
        level.entites.emplace_back(6, e_stats);
    }

    stamina_poitions.clear();

    std::vector<int> strength_poitions =
    {72,77,81,88};

    for(auto xy: strength_poitions){
        int x = xy%10;
        int y = xy/10;

        e_stats = new entity_stats;
        e_stats->type = entity_stats::object_stats;
        e_stats->dflt = 1;

        e_stats->x = x;
        e_stats->y = y;
        e_stats->team = Team::Neutral;
        level.entites.emplace_back(7, e_stats);
    }

    strength_poitions.clear();

    return level;
}
