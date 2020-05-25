//
// Created by max on 30.04.20.
//

#include "Proxy.h"

void Proxy::changeLogType(Field* f, TerminalLog* terminal_log,FileLog* file_log) {
    int command;
    cout << "Выберите тип логирования\n";
    cout << "-1 - без логирования\n";
    cout << "0 - терминал\n";
    cout << "1 - файл\n";
    cin >> command;
    switch (command){
        case -1:
            f->setLog(terminal_log);
            f->getLog()->setState(false);
            break;
        case 0:
            f->setLog(terminal_log);
            f->getLog()->setState(true);
            break;
        case 1:
            f->setLog(file_log);
            f->getLog()->setState(true);
            break;
        default:
            f->setLog(terminal_log);
            f->getLog()->setState(true);
            break;
    }
}
