#include "mainwindow.h"
#include "limits.h"

#define TEST_NUM 5

class Field_Test {
private:
    Field *field = nullptr;
    Base *base = nullptr;
    Adapter *adapter;
public:
    Field_Test(Adapter *adapter) : adapter(adapter) {}
    string create_test() {
        string output = "Class Field: create testing\n";
        unsigned testInput[TEST_NUM][2] = {
            { 1000000, 1 },
            { 1, 1000000 },
            { 0, 5 },
            { 5, 0 },
            { 0, 0 }
        };
        for (unsigned i=0; i<TEST_NUM; i++) {
            try {
                field = new Field(testInput[i][0], testInput[i][1], adapter);
                if (field->get_width() != testInput[i][1])
                    output += "FAIL (wrong width)\n";
                else if (field->get_height() != testInput[i][0])
                    output += "FAIL (wrong height)\n";
                else {
                    output += "PASS\n";
                }
                delete field;
            } catch (exception err) {
                output += "FAIL ";
                output += err.what();
                output += "\n";
            }
         }
        return output;
    }
    string move_test() {
        string output = "Class Field: move testing\n";
        string logs;
        field = new Field(10, 10, adapter);
        for(unsigned i = 0; i < 10; i++){
            for(unsigned j = 0; j < 10; j++){
                Land* landsc = new Proxy("R");
                field->add_land(i, j, landsc);
            }
        }
        IObserver *observer = new Base(field, adapter);
        field->add_item(1, 1, new Dragons_red(observer), logs);
        unsigned t[TEST_NUM][4] = {
            { 1, 1, 10, 3 },
            { 10, 1, 5, 0 },
            { INT_MAX, 0, 0, 0 },
            { 0, 0, 0, 10 },
            { INT_MAX, INT_MAX, INT_MAX, INT_MAX },
        };
        for (unsigned i=0; i<TEST_NUM; i++) {
            try {
                field->move_unit(t[i][0], t[i][1], t[i][2], t[i][3], logs);
                output += "FAIL\n";
            } catch (Coord_Error err) {
                output += "PASS\n";  //Ошибка поймана, все хорошо
            }
        }
        return output;
    }

    string move_test_ok(){
        string output = "Class Field: move testing ok\n";
        string logs;
        field = new Field(10, 10, adapter);
        for(unsigned i = 0; i < 10; i++){
            for(unsigned j = 0; j < 10; j++){
                Land* landsc = new Proxy("R");
                field->add_land(i, j, landsc);
            }
        }
        IObserver *observer = new Base(field, adapter);
        field->add_item(1, 1, new Dragons_red(observer), logs);
        unsigned t[3][4] = {
            { 1, 1, 2, 3 },
            { 2, 3, 5, 0 },
            { 5, 0, 0, 0 }
        };
        for (unsigned i=0; i<3; i++) {
            try {
                field->move_unit(t[i][0], t[i][1], t[i][2], t[i][3], logs);
                if(field->who_I(t[i][2], t[i][3]) == "D_R")
                    output += "PASS\n";
                else
                    output += "FAIL\n"; // На новом месте не наш юнит
            } catch (Coord_Error err) {
                output += "FAIL\n";  //Ошибка поймана, но не должна
            }
        }
        return output;
    }

    string add_test(){
        string output = "Class Field: add testing\n";
        string logs;
        field = new Field(10, 10, adapter);
        for(unsigned i = 0; i < 10; i++){
            for(unsigned j = 0; j < 10; j++){
                Land* landsc = new Proxy("R");
                field->add_land(i, j, landsc);
            }
        }
        unsigned t[3][2] = {
            { 10, 1 },
            { 0, 3 },
            { INT_MAX, INT_MAX }
        };
        IObserver *observer = new Base(field, adapter);
        field->add_item(0, 3, new Dragons_red(observer), logs);
        for (unsigned i=0; i<3; i++) {
            try {
                field->add_item(t[i][0], t[i][1], new Dragons_red(observer), logs);
                output += "FAIL\n";
            } catch (Coord_Error err) {
                output += "PASS\n";  //Ошибка поймана, но не должна
            }
        }
        return output;
    }

    string limit_test(){
        string output = "Class Base: limit testing\n";
        string logs;
        field = new Field(10, 10, adapter);
        for(unsigned i = 0; i < 10; i++){
            for(unsigned j = 0; j < 10; j++){
                Land* landsc = new Proxy("R");
                field->add_land(i, j, landsc);
            }
        }
        unsigned t[6][2] = {
            { 1, 1 },
            { 1, 2 },
            { 1, 3 },
            { 1, 4 },
            { 1, 5 },
            { 1, 6 },
        };
        Base *base = new Base(field, adapter);
        for (unsigned i=0; i<5; i++) {
            base->add_red_dr(t[i][0], t[i][1], logs);
        }
        try {
            base->add_red_dr(t[6][0], t[6][1], logs);
            output += "FAIL\n";
        } catch (Limit_Exception err) {
            output += "PASS\n";  //Ошибка поймана, все хорошо
        }
        return output;
    }

    string delete_test(){
        string output = "Class Base: delete testing\n";
        string logs;
        field = new Field(10, 10, adapter);
        for(unsigned i = 0; i < 10; i++){
            for(unsigned j = 0; j < 10; j++){
                Land* landsc = new Proxy("R");
                field->add_land(i, j, landsc);
            }
        }
        Base *observer = new Base(field, adapter);
        Item *dragon = new Dragons_red(observer);
        field->add_item(0, 3, dragon, logs);
        try {
            observer->delete_unit(dragon);
            for (auto i : observer->get_units()){
                if (i == dragon)
                    output += "FAIL\n";
                return output;
            }
            output += "PASS\n";
        } catch (Limit_Exception err) {
            output += "FAIL\n";  //Ошибка поймана, но не должна
        }
        return output;
    }

    string health_test(){
        string output = "Class Unit: health testing\n";
        string logs;
        field = new Field(10, 10, adapter);
        for(unsigned i = 0; i < 10; i++){
            for(unsigned j = 0; j < 10; j++){
                Land* landsc = new Proxy("R");
                field->add_land(i, j, landsc);
            }
        }
        Base *observer = new Base(field, adapter);
        Item *dragon = new Dragons_red(observer);
        field->add_item(0, 3, dragon, logs);
        try {
            dragon->setHealth(-100);
            output += "FAIL\n"; //Ошибка не поймана, плохо
        } catch (Limit_Exception err) {
            output += "PASS\n"; //Ошибка поймана, все хорошо
        }
        return output;
    }

    string game_test(){
        string output = "Class Game: create & players change & win testing\n";
        string logs;
        Adapter *adapter = new Adapter(0);
        vector<Base*> bases;
        Game<Easy_rule, 2> *game = Game<Easy_rule,2>::getInstance(bases, field, adapter, logs);
        if (bases.size() == 2)
            output += "PASS\n";
        else {
            output += "FAIL\n";
        }
        if (game->get_now_player() == 1)
            output += "PASS\n";
        else {
            output += "FAIL\n";
        }
        game->next_player();
        game->next_player();
        if (game->get_now_player() == 1)
            output += "PASS\n";
        else {
            output += "FAIL\n";
        }
        vector<unsigned int> test_item = {4, 1};
        game->update_now_item(test_item);
        if (game->check_win(1) == 1 && game->check_win(2) == 1)
            output += "PASS\n";
        else {
            output += "FAIL\n";
        }
        test_item = {0, 3};
        game->update_now_item(test_item);
        if (game->check_win(1) == 0 && game->check_win(2) == 2)
            output += "PASS\n";
        else {
            output += "FAIL\n";
        }
        return output;
    }
};
