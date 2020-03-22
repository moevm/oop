#include "Mediator.h"
#include "Field.h"
#include "Tower.h"
#include "Unit.h"
#include "NeutralObject.h"
#include "LogerAdapter.h"


Mediator::Mediator(std::shared_ptr<Field> field) {
	this->field = field;
}

Mediator::Mediator()
{
}


Mediator::~Mediator() {

}

void Mediator::setField(std::shared_ptr<Field> field)
{
	this->field = field;
}

void Mediator::reactOnUnitMove(int x, int y, std::shared_ptr<Unit> unit) {
	bool isStepDone = false;
	int currY = unit->getY();
	switch (unit->getKind()) {
	case HUMAN:
		for (int i = y; i < currY; i++) {
			if (i > 0 && i < field->getHeight()) {
				if (!isStepDone && !field->getCell(x, i)->hasUnit() && !field->getCell(x, i)->hasTower()) {
					field->getCell(x, i)->setUnit(unit);
					field->getCell(x, unit->getY())->setUnit(nullptr);
					unit->setY(i);
					isStepDone = true;
					if (field->getCell(x, i)->hasObj()) {
						field->getCell(x, i)->getObj()->affectOnUnit(unit);
					}
					loger->logAboutUnitMove(x, i);
				}
				else if (isStepDone && field->getCell(i, x)->hasObj()) {
					field->getCell(x, i)->getObj()->affectOnUnit(unit);
				}
			}
		}
		field->printField();
		return;
		break;
	case ZOMBY:
		for (int i = y; i > currY; i--) {
			if (i > 0 && i < field->getHeight()) {
				if (!isStepDone && !field->getCell(x, i)->hasUnit() && !field->getCell(x, i)->hasTower()) {
					field->getCell(x, i)->setUnit(unit);
					field->getCell(x, unit->getY())->setUnit(nullptr);
					unit->setY(i);
					isStepDone = true;
					if (field->getCell(x, i)->hasObj()) {
						field->getCell(x, i)->getObj()->affectOnUnit(unit);
					}
					loger->logAboutUnitMove(x, i);
				}
				else if (isStepDone && field->getCell(i, x)->hasObj()) {
					field->getCell(x, i)->getObj()->affectOnUnit(unit);
				}
			}
		}
		field->printField();
		return;
		break;
	default:
		break;
	}
	std::cout << "\nДвигаться некуда\n";
}

void Mediator::reactOnUnitAttack(int damage, std::shared_ptr<Unit> unit, std::vector<Point>& points, bool isSigleAttack) {
	for (int i = 0; i < points.size(); i++) {
		if (points[i].x >= 0 && points[i].x < field->getWidth() && points[i].y >= 0 && points[i].y < field->getHeight()) {
			std::shared_ptr<FieldCell> target = field->getCell(points[i].x, points[i].y);
			if (target->getUnit() != nullptr && target->getUnit()->getKind() != unit->getKind()) {
				target->getUnit()->damageUnit(damage);
				loger->logAboutUnitAttack(unit->getX(), unit->getY());
				loger->logAboutUnitDamage(points[i].x, points[i].y, unit->getOwnDamage() + unit->getLandDamage() + unit->getWeapon()->getDamage());
				if (target->getUnit()->getHP() <= 0) {
					loger->logAboutUnitDeath(points[i].x, points[i].y);
					target->getUnit()->notifyObservers();
					target->setUnit(nullptr);
					unit->notifyAboutKill();
					field->printField();
				}
				else {
					loger->logUnitStatus(target->getUnit());
				}
				if (isSigleAttack) {
					break;
				}
			}
			else if (target->getTower() != nullptr){
				loger->logAboutUnitAttack(unit->getX(), unit->getY());
				loger->logAboutTowerDamage(points[i].x, points[i].y, unit->getOwnDamage() + unit->getLandDamage() + unit->getWeapon()->getDamage());
				target->getTower()->damageTower(damage);
				if (target->getTower()->getHP() <= 0) {
					loger->logAboutTowerDeath(points[i].x, points[i].y);
					target->setTower(nullptr);
					unit->notifyAboutKill();
					field->printField();
				}
				else {
					loger->logTowerStatus(target->getTower());
				}
				if (isSigleAttack) {
					break;
				}
			}
		}
	}
}

void Mediator::reactOnTowerAttack(std::shared_ptr<Tower> tower)
{
	if (tower->getY() > 0) {
		if (field->getCell(tower->getX(), tower->getY() - 1)->hasUnit()) {
			field->getCell(tower->getX(), tower->getY() - 1)->getUnit()->damageUnit(tower->getDamage());
		}
	}
	if (tower->getY() < field->getHeight() - 1) {
		if (field->getCell(tower->getX(), tower->getY() + 1)->hasUnit()) {
			field->getCell(tower->getX(), tower->getY() + 1)->getUnit()->damageUnit(tower->getDamage());
		}
	}
}

std::shared_ptr<LogerAdapter> Mediator::getLoger()
{
	return loger;
}

void Mediator::setLoger(std::shared_ptr<LogerAdapter> loger)
{
	this->loger = loger;
}
