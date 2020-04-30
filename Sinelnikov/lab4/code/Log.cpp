//
// Created by max on 29.04.20.
//

#include "Log.h"

void Log::setState(bool state) {
    this->state = state;
}

bool Log::getState() {
    return this->state;
}

void FileLog::write(string text) {
    if(this->getState())
        file << text;
}

void TerminalLog::write(string text) {
    if(this->getState())
        cout << text;
}
