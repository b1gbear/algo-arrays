//
// Created by Development on 03/05/2020.
//

#ifndef MYALGO_STRATEGYSHOWSTATS_H
#define MYALGO_STRATEGYSHOWSTATS_H

#include <iostream>

#include "Strategy.h"
#include "FullDataHolder.h"


class StrategyShowStats : public Strategy {
public:
    std::string getName() override {
        return "Pokaz statystyki";
    }

    template<typename T>
    void showStats(DataHolder<T> &dataHolder) {
        std::vector<T> &v = dataHolder.data;


        T min = 0;
        T max = 0;
        T sum = 0;

        if (!dataHolder.data.empty()) {

            min = v.at(0);
            max = v.at(0);

            for (int i = 0; i < v.size(); i++) {
                sum += v.at(i);
                if (v.at(i) < min)
                    min = v.at(i);
                if (v.at(i) > max)
                    max = v.at(i);
            }
        }
        cout << setw(20) << "Srednia: " << setw(20) << sum / v.size() << endl;
        cout << setw(20) << "Suma: " << setw(20) << sum << endl;
        cout << setw(20) << "Minimum: " << setw(20) << min << endl;
        cout << setw(20) << "Maksimum: " << setw(20) << max << endl;
        cout << setw(20) << "Ilosc  danych: " << setw(20) << v.size() << endl;

        dataHolder.min = min;
        dataHolder.max = max;
        dataHolder.sum = sum;
    }


    StrategyFeedback doAction(FullDataHolder &dataHolder) override {
        if (dataHolder.loadedDataType == DataType::NONE) {
            return StrategyFeedback::failed("Brak wczytanych danych");

        } else if (dataHolder.loadedDataType == DataType::FLOAT) {
            showStats(dataHolder.dataHolderFloat);
        } else if (dataHolder.loadedDataType == DataType::INT) {
            showStats(dataHolder.dataHolderInt);
        }

        return StrategyFeedback::success("Everything went ok");
    }
};


#endif //MYALGO_STRATEGYSHOWSTATS_H
