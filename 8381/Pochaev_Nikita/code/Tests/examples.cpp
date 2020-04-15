#include "examples.h"
#include <iostream>
#include "memory"
#include "GameField/GameField.h"
#include "Bases/HumanBase.h"
#include "Bases/BaseMaster.h"
#include "Bases/HellBaseBuilder.h"
#include "Bases/HellBase.h"
#include "AuxiliaryFunctionality/TextColoring.h"
#include "Units/Creatures/Archer.h"
#include "GameField/GameFieldProxy.h"
#include "Bases/HumanBaseBuilder.h"

/**
 * ------------------------------------------
 *                  TEST FOR:
 * ------------------------------------------
 * 1. Creation of field and base;
 * 2. Total information and accounting of field and bases;
 * 3. Composition unit adding and moving;
 * 4. Correct unit accounting.
 */
void fieldBasedTest()
{
    // Create field
    std::shared_ptr<GameField> field = std::make_shared<GameField>(6, 6);

    std::cout << ANSIColor::coloredString("Field information at the beginning.", ANSIColor::FG_YELLOW) << std::endl;
    field->getTotalInformation();

    // Check base creation - "Build pattern"
    BaseMaster master;
    HellBaseBuilder hellBaseBuilder;
    master.setBaseBuilder(&hellBaseBuilder);
    master.constructBase();
    std::shared_ptr<GameBase> hellBase = master.getBase();

    // Check base adding
    field->addBase(hellBase, 1, 1);
    std::cout << ANSIColor::coloredString("Field information after base adding.", ANSIColor::FG_YELLOW) << std::endl;
    field->getTotalInformation();
    std::cout << ANSIColor::coloredString("Cell information after base adding (1; 1).", ANSIColor::FG_YELLOW) << std::endl;
    field->informationAboutCell(1, 1);

    /*
     * Check legion creation - comment it or squad check
     * Impossible to create a CompositeUnit in the same base
     * because cell is busy
     */

    // hellBase->createLegion();
    // field->informationAboutCell(1, 1);
    // field->addCompositeUnit();

    // Check squad creation
    std::shared_ptr<CompositeUnit> squad = hellBase->createSquad(eUnitsType::WIZARD, 3);
    // TODO: it have to do Game class -> will be implemented in 3d LR
    field->addUnit(squad, 1, 1);
    std::cout << ANSIColor::coloredString("Cell/Base information after squad adding (1; 1).", ANSIColor::FG_YELLOW) << std::endl;
    field->informationAboutCell(1, 1);
    std::cout << ANSIColor::coloredString("Field information after squad adding.", ANSIColor::FG_YELLOW) << std::endl;
    field->getTotalInformation();

    squad->move(2, 1);
    std::cout << ANSIColor::coloredString("Cell/Base information after squad moving (2; 1).", ANSIColor::FG_YELLOW) << std::endl;
    field->informationAboutCell(2, 1);
    std::cout << ANSIColor::coloredString("Cell/Base information of last cell (1; 1).", ANSIColor::FG_YELLOW) << std::endl;
    field->informationAboutCell(1, 1);
}

/**
 * ------------------------------------------
 *                  TEST FOR:
 * ------------------------------------------
 * 1. Correct unit observer work with
 * notification of field and base;
 * 2. Correct unit accounting in base.
 */
void ObserverDeathTest()
{
    std::shared_ptr<GameField> field = std::make_shared<GameField>(6, 6);
    std::cout << ANSIColor::coloredString("Field information before unit adding.", ANSIColor::FG_YELLOW) << std::endl;
    field->getTotalInformation();
    BaseMaster master;
    HellBaseBuilder hellBaseBuilder;
    master.setBaseBuilder(&hellBaseBuilder);
    master.constructBase();
    std::shared_ptr<GameBase> hellBase = master.getBase();
    field->addBase(hellBase, 1, 1);

    std::shared_ptr<Unit> succubus = hellBase->getUnit(eUnitsType::SHOOTER);
    field->addUnit(succubus, 1, 1);
    std::cout << ANSIColor::coloredString("Field information after unit adding.", ANSIColor::FG_YELLOW) << std::endl;
    field->getTotalInformation();
    std::cout << ANSIColor::coloredString("Cell information before unit death.", ANSIColor::FG_YELLOW) << std::endl;
    field->informationAboutCell(1, 1);
    succubus->takeDamage(20);
    std::cout << ANSIColor::coloredString("Cell information after unit death.", ANSIColor::FG_YELLOW) << std::endl;
    field->informationAboutCell(1, 1);
}

/**
 * ------------------------------------------
 *                  TEST FOR:
 * ------------------------------------------
 * 1. Correct work of neutral objects;
 * 2. Correct work of field proxy.
 */
void landscapeTest()
{
    std::shared_ptr<GameFieldProxy> field = std::make_shared<GameFieldProxy>(6, 6);

    std::cout << ANSIColor::coloredString("Field information before unit adding.", ANSIColor::FG_YELLOW) << std::endl;
    field->getTotalInformation();

    BaseMaster master;
    HellBaseBuilder hellBaseBuilder;
    master.setBaseBuilder(&hellBaseBuilder);
    master.constructBase();
    std::shared_ptr<GameBase> hellBase = master.getBase();
    field->addBase(hellBase, 1, 1);

    std::shared_ptr<Unit> cavalry = hellBase->getUnit(eUnitsType::CAVALRY);

    field->addUnit(cavalry, 1, 1);
    std::cout << ANSIColor::coloredString("Field information after unit and base adding.", ANSIColor::FG_YELLOW) << std::endl;
    field->getTotalInformation();
    std::cout << ANSIColor::coloredString("Cell information after unit adding.", ANSIColor::FG_YELLOW) << std::endl;
    field->informationAboutCell(1, 1);

    try
    {
        cavalry->move(2, 1);
    }
    catch (const std::exception& e)
    {
        std::cout << ANSIColor::coloredString(e.what(),  ANSIColor::FG_RED) << std::endl;
    }

    std::cout << ANSIColor::coloredString("Cell information after correct move.", ANSIColor::FG_YELLOW) << std::endl;
    try
    {
        cavalry->move(2, 2);
    }
    catch (const std::exception& e)
    {
        std::cout << ANSIColor::coloredString(e.what(),  ANSIColor::FG_RED) << std::endl;
    }

    field->informationAboutCell(2, 2);
    std::cout << ANSIColor::coloredString("Old cell information after correct move.", ANSIColor::FG_YELLOW) << std::endl;
    field->informationAboutCell(1, 1);
}

/**
 * ------------------------------------------
 *                  TEST FOR:
 * ------------------------------------------
 * Unit interaction
 */

void unitInteractionTest()
{
    std::shared_ptr<GameFieldProxy> field = std::make_shared<GameFieldProxy>(6, 6);

    BaseMaster master;
    HellBaseBuilder hellBaseBuilder;
    HumanBaseBuilder humanBaseBuilder;
    master.setBaseBuilder(&hellBaseBuilder);
    master.constructBase();
    std::shared_ptr<GameBase> hellBase = master.getBase();
    master.setBaseBuilder(&humanBaseBuilder);
    master.constructBase();
    std::shared_ptr<GameBase> humanBase = master.getBase();
    field->addBase(hellBase, 1, 1);
    field->addBase(humanBase, 1, 2);

    field->getTotalInformation();

    std::shared_ptr<Unit> cerberus = hellBase->getUnit(eUnitsType::CAVALRY);
    std::shared_ptr<Unit> knight = humanBase->getUnit(eUnitsType::CAVALRY);

    field->addUnit(cerberus, 1, 1);
    field->addUnit(knight, 1, 2);

    std::cout << ANSIColor::coloredString("Knight state before attack.", ANSIColor::FG_YELLOW) << std::endl;
    field->informationAboutCell(1, 2);

    std::cout << ANSIColor::coloredString("Knight's condition after being attacked.", ANSIColor::FG_YELLOW) << std::endl;
    cerberus->carryOutMeleeAttack(1, 2);
    field->informationAboutCell(1, 2);
}
