//
// Created by Development on 03/05/2020.
//

#ifndef MYALGO_STRATEGYSORTBUBBLE_H
#define MYALGO_STRATEGYSORTBUBBLE_H

#include <iostream>
#include <vector>

#include "Strategy.h"
#include "FullDataHolder.h"

namespace algo {
    namespace sort {
        namespace bubble {

            template<typename T>
            static void bubbleSort(T* vector, size_t start, size_t stop) {
                size_t n = stop+1;
                bool sorted;
                do {
                    sorted = true;
                    for (int i = start; i < stop; i++) {
                        if (vector[i] > vector[i + 1]) {
                            T temp = vector[i];
                            vector[i] = vector[i + 1];
                            vector[i + 1] = temp;
                            if (sorted) sorted = false;
                        }
                    }
                    n--;
                } while (!sorted);

            }

            template<typename T>
            static void doExecute(DataHolder<T> &dataHolder, util::Timer &timer, int repeats) {
                size_t num;

                if (repeats == 0) {
                    num = 1;
                } else {
                    num = dataHolder.measureRepeats;
                }
                for (int i = 0; i < num; i++) {
                    if (repeats != 0)
                        cout << "Powtorzenie numer: " << i + 1 << " na " << dataHolder.measureRepeats << endl;
                    cout << flush;
                    dataHolder.dataSorted = dataHolder.data;
                    timer.start();
                    bubbleSort(dataHolder.dataSorted.data()  , 0, dataHolder.dataSorted.size() - 1);
                     timer.stop();
                }
            }


            class StrategySortBubble : public Strategy {
            public:
                std::string getName() override {
                    return "Sortowanie babelkowe";
                }

                StrategyFeedback doAction(FullDataHolder &dataHolder) override {
                    util::Timer timer(dataHolder);

                    if (dataHolder.loadedDataType == DataType::NONE) {
                        return StrategyFeedback::failed("Brak wczytanych danych");
                    } else if (dataHolder.loadedDataType == DataType::FLOAT) {
                        doExecute(dataHolder.dataHolderFloat, timer, 0);
                    } else if (dataHolder.loadedDataType == DataType::INT) {
                        doExecute(dataHolder.dataHolderInt, timer, 0);
                    }
                    return StrategyFeedback::success().timed(timer.get());
                }
            };

        }
    }
}
#endif //MYALGO_STRATEGYSORTBUBBLE_H
