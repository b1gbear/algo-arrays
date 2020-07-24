//
// Created by Development on 03/05/2020.
//

#ifndef MYALGO_STRATEGYSORTHEAP_H
#define MYALGO_STRATEGYSORTHEAP_H

#include <iostream>
#include <vector>

#include "Strategy.h"
#include "FullDataHolder.h"
#include "tools.h"


namespace algo {
    namespace sort {
        namespace heap {


            inline size_t iParent(size_t i) { return (i - 1) / 2; }

            inline size_t iLeftChild(size_t i) { return 2 * i + 1; }

            inline size_t iRightChild(size_t i) { return 2 * i + 2; }


            template<typename T>
            static void siftDown(T *pT, int start, int anEnd) {
                int root = start;
                while (iLeftChild(root) <= anEnd) {
                    size_t child = iLeftChild(root);
                    size_t swap = root;
                    if (pT[swap] < pT[child])
                        swap = root;
                    if (child + 1 <= anEnd && pT[swap] < pT[child + 1])
                        swap = child + 1;
                    if (swap == root) {
                        return;
                    } else {
                        std::swap(pT[root], pT[swap]);
                        root = swap;
                    }
                }

            }

            template<typename T>
            static void heapify(T* vector, int count) {

                int start = iParent(count - 1);

                while (start > 0) {
                    siftDown(vector, start, count - 1);
                    start--;
                    if (start == 0) {
                        break;
                    }
                }
            }

            template<typename T>
            static void heapSort(T* v, size_t start, int stop) {
                heapify(v, stop);

                int end = stop - 1;

                while (end > 0) {
                    swap(v[end], v[0]);
                    end--;
                    siftDown(v, 0, end);
                }
            }


            template<typename T>
            static void dataHolderExecute(DataHolder<T> dataHolder,  util::Timer &timer, int repeats) {

                size_t num;

                if (repeats == 0) {
                    num = 1;
                } else {
                    num = dataHolder.measureRepeats;
                }

                for (int i = 0; i < num; i++) {
                    if (repeats != 0) {
                        std::cout << "Powtorzenie numer: " << i + 1 << " na " << dataHolder.measureRepeats << std::endl;
                        std::cout << std::flush;
                    }
                    dataHolder.dataSorted = dataHolder.data;
                    timer.start();

                    heapSort(dataHolder.dataSorted.data(), 0, dataHolder.dataSorted.size() - 1);
                    timer.stop();
//                    std::cout << "time " << timer.get().count() << std::endl;
                }

            }


            class StrategySortHeap : public Strategy {
            public:
                std::string getName() override {
                    return "Sortowanie stogowe";
                }

                StrategyFeedback doAction(FullDataHolder &dataHolder) override {
                    util::Timer timer(dataHolder);


                    if (dataHolder.loadedDataType == DataType::NONE) {
                        return StrategyFeedback::failed("Brak wczytanych danych");
                    } else if (dataHolder.loadedDataType == DataType::FLOAT) {
                        dataHolderExecute(dataHolder.dataHolderFloat, timer, 0);
                    } else if (dataHolder.loadedDataType == DataType::INT) {
                        dataHolderExecute(dataHolder.dataHolderInt, timer, 0);
                    }

                    return StrategyFeedback::success().timed(timer.get());
                }


            };

        }
    }
}
#endif //MYALGO_STRATEGYSORTBUBBLE_H
