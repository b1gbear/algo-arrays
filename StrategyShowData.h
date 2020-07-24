//
// Created by Development on 03/05/2020.
//

#ifndef MYALGO_STRATEGYSHOWDATA_H
#define MYALGO_STRATEGYSHOWDATA_H
#include <iostream>

#include "Strategy.h"
using namespace std;

class StrategyShowData : public Strategy {
    std::string getName() override {
        return "Pokaz dane";
    }

    StrategyFeedback doAction(FullDataHolder &dataHolder) override {
        if (dataHolder.loadedDataType == DataType::NONE) {
            return StrategyFeedback::failed("Brak wczytanych danych");
        } else if (dataHolder.loadedDataType == DataType::FLOAT) {
            cout << "float" << endl;
            for (int i = 0; i < 100; i++) {
                std::cout << dataHolder.dataHolderFloat.data.at(i) << endl;
            }
        } else if (dataHolder.loadedDataType == DataType::INT) {
            cout << "int" << endl;

            for (int i = 0; i < 200; i++) {
                std::cout << setw(3) << i << dataHolder.dataHolderInt.data.at(i) << endl;
            }
        }
        cout << "Wyswietlono pierwsze 200 pozycji" << endl;
        return StrategyFeedback::success("Everything went ok");
    }
};


#endif //MYALGO_STRATEGYSHOWDATA_H
