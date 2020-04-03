#include "command.h"
#include "uifacade.h"

GameCommand::GameCommand(UIFacade *facade, Game *game, RequestType type, std::vector<int> param, ILogAdapter *logger)
    : game(game), type(type), param(param), logger(logger) {
    facadeMediator = new FacadeMediator(facade, this);
}

std::vector<int> GameCommand::exec()
{
    std::vector<int> answer;
    if (type == GAME_INFO)
    {
        answer.push_back(static_cast<int>(game->getField()->getWidth()));
        answer.push_back(static_cast<int>(game->getField()->getHeight()));
        answer.push_back(static_cast<int>(game->getField()->getItemCounter()));
        answer.push_back(static_cast<int>(game->getField()->getItemLimit()));
        answer.push_back(static_cast<int>(game->getBases().size()));
    } else if (type == BASE_INFO)
    {
        if (param.front() >= 0)
        {
            unsigned number = static_cast<unsigned>(param.front()) - 1;
            if (number < game->getBases().size())
            {
                std::vector<int> request = {param.front()};
                Base *base = game->getBaseByNumber(number);
                FieldCommand fCom(facadeMediator, game->getField(), FIND, param, logger, base);
                answer = fCom.exec();
                BaseCommand bCom(facadeMediator, base, type, param, logger);
                for (auto i : bCom.exec())
                    answer.push_back(i);
                logger->pushLog(BASE_UPDATE, answer);
                return answer;
            }
        }
    } else if (type == LAND_INFO || type == ITEMS_INFO)
    {
        FieldCommand fCom(facadeMediator, game->getField(), type, param, logger);
        return fCom.exec();
    } else if (type == GETXY)
    {
        FieldCommand fCom(facadeMediator, game->getField(), type, param, logger);
        FieldItem *item = fCom.findItem(param[0], param[1]);
        if (item == nullptr)
        {
            answer.push_back(11);
            return answer;
        }
        answer.push_back(item->getType());
        if (item->getType() == BASE)
        {
            for (unsigned i=0; i<game->getBases().size(); i++)
            {
                if (game->getBases()[i] == item)
                {
                    answer.push_back(static_cast<int>(i));
                }
            }
        } else if (item->getType() < BASE)
        {
            for (auto i : game->getUnits())
            {
                if (i == item)
                {
                    answer.push_back(i->getCharacteristics().getPower());
                    answer.push_back(i->getCharacteristics().getMove());
                    answer.push_back(i->getCharacteristics().getSpread());
                    answer.push_back(i->getCharacteristics().getBonus());
                    answer.push_back(i->getAttackSkills().getPower());
                    answer.push_back(i->getAttackSkills().getMove());
                    answer.push_back(i->getAttackSkills().getSpread());
                    answer.push_back(i->getAttackSkills().getBonus());
                    answer.push_back(i->getSecuritySkills().getPower());
                    answer.push_back(i->getSecuritySkills().getMove());
                    answer.push_back(i->getSecuritySkills().getSpread());
                    answer.push_back(i->getSecuritySkills().getBonus());
                    answer.push_back(static_cast<int>(i->getBaseNumber() + 1));
                }
            }
        }
    } else if (type == ATTACK)
    {
        FieldCommand fCom(facadeMediator, game->getField(), type, param, logger);
        FieldItem *item = fCom.findItem(param[0], param[1]);
        answer = param;
        if (item == nullptr)
        {
            facadeMediator->sendString(type, "Error! Field cell is empty");
        }
        for (auto i : game->getUnits())
        {
            if (i == item)
            {
                answer.push_back(i->attack(param[2], param[3]));
                answer.push_back(item->getType());
                if (!answer.back())
                    answer.push_back(static_cast<int>(game->getField()->getItemCounter()));
                logger->pushLog(UNIT_ATTACK, answer);
                return answer;
            }
        }
        facadeMediator->sendString(type, "Attacker is not unit");
    } else if (type == ADD)
    {
        if (param.front() == BASE)
        {
            game->createBase("player", 100, static_cast<unsigned>(param[1]), static_cast<unsigned>(param[2]));
            answer.push_back(static_cast<int>(game->getBases().size()));
            answer.push_back(param[1]);
            answer.push_back(param[2]);
            answer.push_back(static_cast<int>(game->getField()->getItemCounter()));
            logger->pushLog(BASE_ADD, answer);
        }
        else if (param.front() >= CHEST && param.front() <= DATA)
        {
            unsigned x = static_cast<unsigned>(param[1]);
            unsigned y = static_cast<unsigned>(param[2]);
            game->createNeutral(x, y, static_cast<NeutralType>(param[0]));
            answer = param;
            answer.push_back(static_cast<int>(game->getField()->getItemCounter()));
            logger->pushLog(NEUTRAL_ADD, answer);
        }
        else
        {
            unsigned number = static_cast<unsigned>(param[1]) - 1;
            Base *base = game->getBaseByNumber(number);
            BaseCommand bCom(facadeMediator, base, type, param, logger);
            return bCom.exec();
        }
    } else if (type == MOVE)
    {
        FieldCommand fCom(facadeMediator, game->getField(), type, param, logger);
        FieldItem *item = fCom.findItem(param[0], param[1]);
        for (auto i : game->getUnits())
        {
            if (i == item)
            {
                i->move(param[2], param[3]);
                answer.push_back(1);
                param.push_back(item->getType());
                logger->pushLog(UNIT_MOVE, param);
                return answer;
            }
        }
        answer.push_back(0);
    }
    return answer;
}

BaseCommand::BaseCommand(IFacadeMediator *facade, Base *base, RequestType type, std::vector<int> param, ILogAdapter *logger, FieldItem* toFind)
    : base(base), type(type), param(param), toFind(toFind), facadeMediator(facade), logger(logger) {}

std::vector<int> BaseCommand::exec()
{
    std::vector<int> answer;
    if (type == BASE_INFO)
    {
        answer.push_back(static_cast<int>(base->getStability()));
        answer.push_back(static_cast<int>(base->getUnitCounter()));
        answer.push_back(static_cast<int>(base->getUnitLimit()));
        for (auto i : base->getUnitList())
        {
            answer.push_back(i->getType());
        }
    } else if (type == ADD)
    {
        unsigned x = static_cast<unsigned>(param[2]);
        unsigned y = static_cast<unsigned>(param[3]);
        IUnit *unit = base->createUnit(x, y, static_cast<UnitType>(param[0]));
        logger->pushLog(UNIT_ADD, param);
        facadeMediator->sendString(type, "Added unit:\n" + unit->shortName());
    }
    return answer;
}

FieldCommand::FieldCommand(IFacadeMediator *facade, Field *field, RequestType type, std::vector<int> param, ILogAdapter *logger, FieldItem *toFind)
    : field(field), type(type), param(param), toFind(toFind), facadeMediator(facade), logger(logger) {}

std::vector<int> FieldCommand::exec()
{
    std::vector<int> answer;
    if (type == LAND_INFO)
    {
        answer.push_back(static_cast<int>(field->getWidth()));
        answer.push_back(static_cast<int>(field->getHeight()));
        for (unsigned i=0; i<field->getWidth(); i++)
        {
            for (unsigned j=0; j<field->getHeight(); j++)
            {
                answer.push_back(field->getLandType(i, j));
            }
        }
    } else if (type == ITEMS_INFO)
    {
        answer.push_back(static_cast<int>(field->getWidth()));
        answer.push_back(static_cast<int>(field->getHeight()));
        FieldItem *item;
        for (unsigned i=0; i<field->getWidth(); i++)
        {
            for (unsigned j=0; j<field->getHeight(); j++)
            {
                item = field->getItem(i, j);
                if (item != nullptr)
                    answer.push_back(item->getType());
                else
                    answer.push_back(11);
            }
        }
    }
    else if (type == FIND && toFind != nullptr)
    {
        for (unsigned i=0; i<field->getWidth(); i++)
        {
            for (unsigned j=0; j<field->getHeight(); j++)
            {
                if (field->getItem(i, j) == toFind)
                {
                    answer.push_back(static_cast<int>(i));
                    answer.push_back(static_cast<int>(j));
                }
            }
        }
    }
    return answer;
}

FieldItem *FieldCommand::findItem(int x, int y)
{
    unsigned xU = static_cast<unsigned>(x);
    unsigned yU = static_cast<unsigned>(y);
    return field->getItem(xU, yU);
}
