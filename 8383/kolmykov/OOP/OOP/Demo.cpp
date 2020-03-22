#include "Demo.h"
#include "LogerAdapter.h"


Demo::Demo()
{
}


Demo::~Demo()
{
}


void Demo::start(bool isLoad) {
	if (!isLoad) {
		std::shared_ptr<LogerAdapter> loger(new LogerAdapter(std::shared_ptr<LogerProxy>(new FileLoger(std::shared_ptr<Loger>(new Loger)))));
		std::shared_ptr<Field> field(new Field(20, 20));
		std::shared_ptr<Mediator> mediator(new Mediator(field));
		mediator->setLoger(loger);
		field->setMediator(mediator);
		std::shared_ptr<Facade> facadeH(new Facade(Kind::HUMAN, field));
		std::shared_ptr<Facade> facadeZ(new Facade(Kind::ZOMBY, field));
		field->printField();
		system("pause");////////////////////////////////////////////////////////////////////////////
		facadeH->setTower(0, 19, std::shared_ptr<UnitFactory>(new HumanWithSwordFactory()));
		system("pause");
		facadeZ->setTower(19, 0, std::shared_ptr<UnitFactory>(new BitingZombyFactory()));
		system("pause");
		facadeH->setTower(1, 19, std::shared_ptr<UnitFactory>(new HumanWithGunFactory()));
		system("pause");
		facadeZ->setTower(18, 0, std::shared_ptr<UnitFactory>(new SpitToEnemyZombyFactory()));
		system("pause");
		facadeH->setTower(2, 19, std::shared_ptr<UnitFactory>(new HumanOnBikeFactory()));
		system("pause");
		facadeZ->setTower(17, 0, std::shared_ptr<UnitFactory>(new KamikadzeZombyFactory()));
		system("pause");///////////////////////////////////////////////////////////////////////////
		facadeH->create(2, 19, 19, 18);
		system("pause");
		facadeZ->create(19, 0, 0, 1);
		system("pause");
		facadeH->create(1, 19, 15, 18);
		system("pause");
		facadeZ->create(18, 0, 15, 1);
		system("pause");
		facadeH->create(2, 19, 18, 18);
		system("pause");
		facadeZ->create(17, 0, 1, 1);
		system("pause");//////////////////////////////////////////////////////////////////////////////

		Saver saver(field);
		saver.save();
	}

	else {
		std::shared_ptr<LogerAdapter> loger(new LogerAdapter(std::shared_ptr<LogerProxy>(new FileLoger(std::shared_ptr<Loger>(new Loger)))));
		std::shared_ptr<Mediator> mediator(new Mediator());
		mediator->setLoger(loger);

		Loader loader(mediator);
		std::shared_ptr<Field> field = loader.load();
		mediator->setField(field);

		std::shared_ptr<Facade> facadeH(new Facade(Kind::HUMAN, field));
		std::shared_ptr<Facade> facadeZ(new Facade(Kind::ZOMBY, field));
		field->printField();
		system("pause");

		facadeH->move(19, 18);
		system("pause");
		facadeH->move(19, 15);
		system("pause");
		facadeH->move(19, 12);
		system("pause");
		facadeH->move(19, 9);
		system("pause");
		facadeH->move(19, 6);
		system("pause");
		facadeH->move(19, 3);
		system("pause");/////////////////////////////////////////////////////////////////////////////
		facadeH->attack(19, 1);
		system("pause");
		facadeH->attack(19, 1);
		system("pause");
		facadeH->attack(19, 1);
		system("pause");
		facadeH->attack(19, 1);
		system("pause");
		facadeH->attack(19, 1);
		system("pause");
		facadeH->attack(19, 1);
		system("pause");
		facadeH->attack(19, 1);
		system("pause");///////////////////////////////////////////////////////////////////////////////
		facadeH->move(15, 19);
		facadeZ->move(15, 1);
		system("pause");
		facadeH->move(15, 18);
		facadeZ->move(15, 2);
		system("pause");
		facadeH->move(15, 17);
		facadeZ->move(15, 3);
		system("pause");
		facadeH->move(15, 16);
		facadeZ->move(15, 4);
		system("pause");
		facadeH->move(15, 15);
		facadeZ->move(15, 5);
		system("pause");
		facadeH->move(15, 14);
		facadeZ->move(15, 6);
		system("pause");
		facadeH->move(15, 13);
		facadeZ->move(15, 7);
		system("pause");
		facadeH->move(15, 12);
		facadeZ->move(15, 8);
		system("pause");
		facadeZ->attack(15, 9);
		facadeH->attack(15, 11);
		system("pause");///////////////////////////////////////////////////////////////////////////////
	}
}