#include "units.h"
#include <SFML/Graphics.hpp>


#include "weapon.h"

Entity::Entity(const Point &pos, int health){
    position = pos;
    iHealth = health;
    bAlive = true;
}


Point Entity::pos() const{
    return position;
}


Entity::Attack Entity::attackType() const{
    return attack_type;
}


Entity::Unit Entity::unitType() const{
    return unit_type;
}


int Entity::health() const{
    return iHealth;
}


bool Entity::isAlive() const{
    return bAlive;
}


void Entity::select(){
    selected = true;
}


void Entity::deselect(){
    selected = false;
}


bool Entity::selected_p() const{
    return selected;
}


int Entity::remainigSteps() const{
    return iRemainedSteps;
}


Melee::Melee(Point pos, int health, int damage, int steps): Entity(pos, health)
{
    attack_type = Entity::Attack::Melee;
    unit_type = Entity::Unit::Infantry;

    weapon = new Club(Shell::Type::siege, 10, damage, 0.1f);

    iMaxSteps = steps;
    iRemainedSteps = steps;
}


void Melee::draw(sf::RenderTarget *target, int cell_size){
    sf::CircleShape unit_shape(cell_size*0.4f);
    unit_shape.setOrigin(unit_shape.getRadius(), unit_shape.getRadius());
    unit_shape.setPosition(3 + cell_size/2.f + position.x * (3+cell_size), 3 + cell_size/2.f + position.y * (3+cell_size));
    unit_shape.setFillColor(sf::Color::Red);

    target->draw(unit_shape);

    if(selected_p()){
        sf::CircleShape spotter(cell_size*0.1f);
        spotter.setOrigin(spotter.getRadius(), spotter.getRadius());
        spotter.setPosition(unit_shape.getPosition());
        spotter.setFillColor(sf::Color::Black);
        target->draw(spotter);
    }
}


void Melee::damage(int dmg){
    // play damage animation
    // ...

    // decrease health
    iHealth -= dmg;
    if(iHealth <= 0)
        bAlive = false;
}


void Melee::move(const Point &offset){
    // play move animation
    // ...

    // change position, decrease remaining steps
    position += offset;
    iRemainedSteps -= (abs(offset.x) + abs(offset.y));
}


void Melee::fire(Entity *enemy){
    // play attack animation
    // ...

    // damage enemy
    enemy->damage(weapon->attack().iDamage);
}


void Melee::nextStep(){
    // play next step animation
    // ...

    // damage it's weapon
    // ...

    // update steps
    iRemainedSteps = iMaxSteps;
}


Range::Range(Point pos, int health, int steps, int inner_range, int outer_range):
    Entity(pos, health)
{
    attack_type = Entity::Attack::Range;
    unit_type = Entity::Unit::Infantry;

    iMaxSteps = steps;
    iRemainedSteps = steps;

    weapon = new Club(Shell::Type::straight, 10, 10, 1.f);
    iAttackRange = outer_range;
    iBlindZone = inner_range;
}


void Range::draw(sf::RenderTarget *target, int cell_size){
    sf::CircleShape unit_shape(cell_size*0.4f);
    unit_shape.setOrigin(unit_shape.getRadius(), unit_shape.getRadius());
    unit_shape.setPosition(3 + cell_size/2.f + position.x * (3+cell_size), 3 + cell_size/2.f + position.y * (3+cell_size));
    unit_shape.setFillColor(sf::Color(255, 120, 0));

    target->draw(unit_shape);

    if(selected_p()){
        sf::CircleShape spotter(cell_size*0.1f);
        spotter.setOrigin(spotter.getRadius(), spotter.getRadius());
        spotter.setPosition(unit_shape.getPosition());
        spotter.setFillColor(sf::Color::Black);
        target->draw(spotter);
    }
}


void Range::damage(int dmg){
    // play damage animation
    // ...

    // decrease health
    iHealth -= dmg;
    if(iHealth <= 0)
        bAlive = false;
}


void Range::move(const Point &offset){
    // play move animation
    // ...

    // change position, decrease remaining steps
    position += offset;
    iRemainedSteps -= (abs(offset.x) + abs(offset.y));
}


void Range::fire(Entity *enemy){
    // play attack animation
    // ...

    // damage enemy
    enemy->damage(weapon->attack().iDamage);
}


void Range::nextStep(){
    // play next step animation
    // ...

    // damage it's weapon
    // ...

    // update steps
    iRemainedSteps = iMaxSteps;
}


int Range::attackRange() const{
    return iAttackRange;
}


int Range::blindZone() const{
    return iBlindZone;
}


// Absent
Absent::Absent(Point pos, int health, int steps):
    Entity(pos, health)
{
    attack_type = Entity::Attack::Absent;
    unit_type = Entity::Unit::Peace;

    iMaxSteps = steps;
    iRemainedSteps = steps;
}


void Absent::draw(sf::RenderTarget *target, int cell_size){
    sf::CircleShape unit_shape(cell_size*0.3f);
    unit_shape.setOrigin(unit_shape.getRadius(), unit_shape.getRadius());
    unit_shape.setPosition(3 + cell_size/2.f + position.x * (3+cell_size), 3 + cell_size/2.f + position.y * (3+cell_size));
    unit_shape.setFillColor(sf::Color(120, 240, 30));

    target->draw(unit_shape);

    if(selected_p()){
        sf::CircleShape spotter(cell_size*0.1f);
        spotter.setOrigin(spotter.getRadius(), spotter.getRadius());
        spotter.setPosition(unit_shape.getPosition());
        spotter.setFillColor(sf::Color::Black);
        target->draw(spotter);
    }
}


void Absent::damage(int dmg){
    // play get damaged animation
    // ...

    // decrease health
    iHealth -= dmg;
    if(iHealth <= 0)
        bAlive = false;
}


void Absent::move(const Point &offset){
    // play move animation
    // ...

    // change position, decrease remaining steps
    position += offset;
    iRemainedSteps -= (abs(offset.x) + abs(offset.y));
}


void Absent::fire(Entity *enemy){
    // wierd thing. delete
}


void Absent::nextStep(){
    // play next step animation
    // ...

    // damage it's weapon
    // ...

    // update steps
    iRemainedSteps = iMaxSteps;
}
