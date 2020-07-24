//
// Created by us on 20.06.2020.
//

#ifndef MYALGO_CONSOLEINTERFACEWITHAUTHORSHIP_H
#define MYALGO_CONSOLEINTERFACEWITHAUTHORSHIP_H


#include "ConsoleInterface.h"

class ConsoleInterfaceWithAuthorship : public ConsoleInterface {
public:
    explicit ConsoleInterfaceWithAuthorship(vector<Strategy *> &strategies, FullDataHolder &dataHolder) : ConsoleInterface(strategies,dataHolder) {}

protected:
    void authorship(size_t real_len) const override {
        string info2 ("hardcoded.info ");
        cout << vertical << printTimes(' ', real_len) << vertical << endl;
        cout << vertical << printTimes(' ', real_len - info2.length()) << info2 << vertical << endl;
    }

};


#endif //MYALGO_CONSOLEINTERFACEWITHAUTHORSHIP_H
