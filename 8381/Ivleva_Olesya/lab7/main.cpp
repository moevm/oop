#include "unittests.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    if (argc != 1)
    {
        if (string(argv[1]) == "test")
        {
            Field_Test ftest(new Adapter(0));
            cout << ftest.create_test() << endl;
            cout << ftest.move_test() << endl;
            cout << ftest.move_test_ok() << endl;
            cout << ftest.add_test() << endl;
            cout << ftest.limit_test() << endl;
            cout << ftest.delete_test() << endl;
            cout << ftest.health_test() << endl;
            cout << ftest.game_test() << endl;
            return 0;
        }
        cout << "Invalid parameter" << endl;
        return 0;
    }
    else
    {
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        return a.exec();
    }
}
