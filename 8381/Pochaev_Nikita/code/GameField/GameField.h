#ifndef OOP_GAMEFIELD_H
#define OOP_GAMEFIELD_H

#include "IGameField.h"
#include "InformationHeaders/commandPar.h"
#include "AuxiliaryFunctionality/Exceptions/fieldexception.h"
#include "Game/Saving/SaveStuctures.h"
#include "Bases/BaseMaster.h"
#include "Bases/HellBaseBuilder.h"
#include "Bases/HumanBaseBuilder.h"

class GameField : public UnitObserver, public IGameField, public std::enable_shared_from_this<GameField>
{
public:
    ~GameField() = default;
    GameField(size_t width_, size_t height_);
    GameField(const GameField& field);
    GameField(GameField&& field) noexcept;
    GameField& operator= (const GameField& field);
    GameField& operator= (GameField&& field) noexcept;

    [[nodiscard]] size_t getWidth() const override;
    [[nodiscard]] size_t getHeight() const override;

    /**
     * Type definitions simplify working
     * with STL containers and iterator types
     */
    typedef GameFieldIterator<std::shared_ptr<Cell>> iterator;
    typedef GameFieldIterator<const std::shared_ptr<Cell>> const_iterator;

    iterator begin();
    iterator end();

    [[nodiscard]] const_iterator begin() const;
    [[nodiscard]] const_iterator end() const;

    void addUnit(const std::shared_ptr<Unit> &unit, size_t x, size_t y) override;
    void addBase(const std::shared_ptr<GameBase> &base, size_t x, size_t y) override;
    void delUnit(size_t x, size_t y) override;
    bool isCellFreeForUnit(size_t x, size_t y) override;
    bool isCellFreeForBase(size_t x, size_t y) override;
    void informationAboutCell(size_t x, size_t y) override;
    std::shared_ptr<GameBase> getBaseByCoords(size_t x, size_t y) override;
    std::shared_ptr<Unit> getUnitByCoords(size_t x, size_t y) override;
    /**
     * @brief thatIsOnCell
     * @param x
     * @param y
     * @param items
     * @return the number of objects for which information needs to be provided
     */
    size_t thatIsOnCell(size_t x, size_t y, std::vector<eRequest> items);

    void moveUnit(std::shared_ptr<Unit> &sender, size_t x, size_t y) override;
    void moveUnit(size_t xSource, size_t ySource, size_t xDest, size_t yDist) override;
    void meleeAttackUnit(std::shared_ptr<Unit> &sender, size_t x, size_t y) override;
    void meleeAttackUnit(size_t xSource, size_t ySource, size_t xDest, size_t yDest) override;
    void updateAfterDeath(std::shared_ptr<Unit> corpse, size_t x, size_t y) override;

    void getTotalInformation() override;
    std::string getInfAboutBase(size_t xDest, size_t yDest) override;
    std::string getInfAboutUnit(size_t xDest, size_t yDest) override;

    // memento pattern
    std::shared_ptr<FieldParametersMemento> createMemento();
    void restoreMemento(std::shared_ptr<FieldParametersMemento> memento);

private:
    cds::Array2D<std::shared_ptr<Cell>> cellMatrix;
    size_t unitsCount{};
    size_t maxUnitsCount{};
    size_t baseCount{};
    size_t maxBaseCount{MAX_BASE_ON_FIELD_QUANTITY};
    size_t width{};
    size_t height{};

    void clearUnitByCoords(Coords oldCoords);
};

#endif //OOP_GAMEFIELD_H
