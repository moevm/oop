#include "Graphic.h"

graphic::graphic() {
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

}

void graphic::setTextColor(int text, int background) {
	SetConsoleTextAttribute(hConsole, (WORD)((background << 4) | text));

}

void graphic::setTitle() {
	SetConsoleTitle(L"Very good game!\0");
	
}

void graphic::info(unit* camera_men) {
	camera_men->get_info();
	cout << "\t This land will hurt you: " << camera_men->beware();
	printf("\n\n");
	(static_cast<base*>(camera_men->get_base()))->get_info();
}



void graphic::camera(field& F, player* tmp, bool inf) {
	unit* camera_men = tmp->get_tmp_unit();


		for (int m = 0; m < 1000; m++) {
			cout << " ";
		}
		int tmp_x, tmp_y;

		tmp_x = camera_men->get_x();
		tmp_y = camera_men->get_y();
		system("cls");



		setTextColor(lightRed);
		cout << "Game does not support Russian and refuses to work!!!  Change language to English to play\n";
		setTextColor();
		cout << "\tmove :wasd, change unit: 123, save: c, load: l, create unit: r, exit: 0\n";

		setTextColor(yellow);
		cout << "PLAYER " << tmp->get_name() << " number " << tmp->get_base()->get_number() << "\n\n";
		setTextColor();
		for (int i = tmp_y - 3; i < tmp_y + 3; i++) {
			cout << "\t";
			for (int j = tmp_x - 4; j < tmp_x + 5; j++) {

				if (i < 0 || j < 0 || i >= F.get_y_size() || j >= F.get_x_size()) cout << "";
				else if (F.get_cell(j, i)->is_base()) {
					setTextColor(15, F.get_cell(j, i)->get_background());
					if(F.get_cell(j, i)->get_base()->get_number() != camera_men->get_base_number())
						setTextColor(lightRed, F.get_cell(j, i)->get_background());

					cout << F.get_cell(j, i)->get_base()->get_name();
					setTextColor();
				}
				else if (F.get_cell(j, i)->get_unit_type() != None) {
					setTextColor(lightRed, F.get_cell(j, i)->get_background());
					if (F.get_cell(j, i)->get_unit()->get_base_number() == camera_men->get_base_number())
						setTextColor(15, F.get_cell(j, i)->get_background());
					if(F.get_cell(j, i)->get_unit() == camera_men)
						setTextColor(11, F.get_cell(j, i)->get_background());

					cout << (static_cast<unit*>(F.get_cell(j, i)->get_unit()))->get_name();
					setTextColor();
				}
				else if (F.get_cell(j, i)->get_item_type() != Non) {
					setTextColor(13, F.get_cell(j, i)->get_background());
					cout << F.get_cell(j, i)->get_item()->get_name();
					setTextColor();
				}
				else {
					setTextColor(F.get_cell(j, i)->get_color(), F.get_cell(j, i)->get_background());
					cout << F.get_cell(j, i)->get_land_icon();
					setTextColor();
				}  

			}
			printf("\n");

		}
		printf("\n");
		if (inf) {
			info(camera_men);
		}
	
}

void graphic::help() {
	system("cls");
	setTextColor(yellow);
	cout << "Here is everething about this game!\n";
	cout << "GAME KNOWS ONLY ENGLISH! other lenguages will be ignored ;)\n";
	setTextColor();
	cout << "This game is for 2 players\n";
	cout << "\tEvery player has own base and units\n";
	cout << "\tMaximum you can have 3 units. Every one of them has some stats: hp, armor, attack and level\n";
	cout << "\tEvery unit are some animal-type: mammal(wolf, hyena), bird(duck, crow) or amphibia(frog, lizard)\n";
	cout << "\tOn the map they look like their first letters: w, h, d, c, f, l\n";
	setTextColor(10);
	cout << "Every map-cell has some landscape: sunflower field ☼, mountain ^, lake ~, lance forest ♠\n";
	setTextColor();
	cout << "\tMammals hurts in lakes and heal in lance forests\n";
	cout << "\tBirds hurts in lance forestd and heal in mountains\n";
	cout << "\tAmphibias hurts in mountains and heal in lakes\n";
	setTextColor(lightRed);
	cout << "Bases looks like this ▲ when it's alive and like this X when it's hp = 0\n";
	setTextColor();
	cout << "\tYour base can create units if you press 'r' while game is on and it's alive\n";
	cout << "\tYou can change your current unit by pressing: 1, 2, 3, but only if it's alive\n";
	cout << "\tYour units and base are white and your cerrent unit are light blue\n";
	cout << "\tOther payers units and are red\n";
	setTextColor(13);
	cout << "In some map-cells you can find items: heart , xp-bottle $, armor-piece * and zatochka ♦\n";
	setTextColor();
	cout << "\tAll of them colored pink and give you: +4hp, +20xp, +1armor, +1attack if you don't have maximum for your level\n";
	setTextColor(yellow);
	cout << "You can move by pressing w - go up, a - go left, d - go right, s - go down\n";
	setTextColor();
	cout << "\tNeather you can attack bases and units (not yours)\n\tJust try to move in cell, where is alredy something: you will attack it\n";
	cout << "\tBut if you are weaker - you can hurt youself\n";
	cout << "\tWhen smbd attack you - your armor protect you, but it slowly break down (-1 per attack)\n";
	setTextColor(11);
	cout << "You can save your game by pressing c and load it by pressing l\n";
	setTextColor(10);
	cout << "There is 2 levels small-size and big-size\n";
	setTextColor(12);
	cout << "And 2 gamemodes: normal and hardcore\n";
	setTextColor();
	cout << "\tIn normal each of you have 5 moves per raund and you win if other players-base is dead\n";
	cout << "\tIn hardcore you have 3 moves per raund, bases are already dead and you win if other-players units are dead\n";
	setTextColor(11);
	cout << "Press any key to return to menu!\n";
	setTextColor();
	char in;

	in = _getch();
	system("cls");

}

