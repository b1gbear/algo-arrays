//
// Created by Development on 03/05/2020.
//

#ifndef MYALGO_STRATEGYSORTQUICK_H
#define MYALGO_STRATEGYSORTQUICK_H

#include <iostream>

#include "Strategy.h"
#include "FullDataHolder.h"
#include "StrategyExit.h"
#include "StrategySortBubble.h"

namespace algo {
    namespace sort {
        namespace quick {
            enum class QSDecision {
                LEFT, MID, RIGHT, IDEAL
            };

            template<typename T>
            static void quickSort(std::vector<T> &v, size_t left, size_t right, QSDecision decision = QSDecision::MID,
                                  std::vector<T> *preSorted = nullptr) {
                if (left >= right) {
                    return;
                }
                if (right - left < 100) {
                    algo::sort::bubble::bubbleSort(v.data(), left, right);
                    return;
                }
                size_t mid = (left + right) / 2;
                bool noSwap = false;
                if (decision == QSDecision::LEFT) {

                } else if (decision == QSDecision::MID) { std::swap(v[left], v[mid]); }
                else if (decision == QSDecision::RIGHT) { std::swap(v[left], v[right]); }
                else {
                    noSwap = true;
                }

                size_t last = left;

                for (size_t i = left + 1; i <= right; i++) {
                    if (v[i] < (noSwap ? preSorted->at(mid) : v[left])) {
                        std::swap(v[i], v[++last]);
                    }
                }

                if (!noSwap) {
                    std::swap(v[left], v[last]);
                }
                if (last > left) {
                    quickSort(v, left, last - 1, decision, preSorted);
                }
                if (last < right) {
                    quickSort(v, last + 1, right, decision, preSorted);
                }
            }

            template<typename T>
            inline void rswap(T &a, T &b) {
                T val = a;
                a = b;
                b = val;
            }

            template<typename T>
            static void iQuickSort(T *v, T *presorted, size_t left, size_t right) {
                if (left >= right) {
                    return;
                }

                size_t mid = (left + right) / 2;

                size_t last = left;

                for (size_t i = left + 1; i <= right; i++) {
                    if (v[i] < presorted[mid]) {
                        std::swap(v[i], v[++last]);
                    }
                }

                if (last > left) {
                    iQuickSort(v, presorted, left, last - 1);
                }
                if (last < right) {
                    iQuickSort(v, presorted, last + 1, right);
                }
            }


            template<typename T>
            static void mQuickSort(T *v, size_t left, size_t right) {
                if (left >= right) {
                    return;
                }

//                if (right - left < 12   ) {
//                    algo::sort::bubble::bubbleSort(v, left, right);
//                    return;
//                }

                size_t mid = (left + right) / 2;
                {
                    T val = v[left];
                    v[left] = v[mid];
                    v[mid] = val;
                }
                size_t last = left;

                for (size_t i = left + 1; i <= right; i++) {
                    if (v[i] < v[left]) {
                        ++last;
                        T val2 = v[last];
                        v[last] = v[i];
                        v[i] = val2;
                    }
                }

                {
                    T val3 = v[last];
                    v[last] = v[left];
                    v[left] = val3;
                }

                if (last > left) {
                    mQuickSort(v, left, last - 1);
                }

                if (last < right) {
                    mQuickSort(v, last + 1, right);
                }

            }

            template<typename T>
            static void lQuickSort(T *v, size_t left, size_t right) {
                if (left >= right) {
                    return;
                }
                if (right - left < 100) {
                    algo::sort::bubble::bubbleSort(v, left, right);
                    return;
                }
                size_t mid = (left + right) / 2;

                size_t last = left;

                for (size_t i = left + 1; i <= right; i++) {
                    if (v[i] < v[left]) {
                        ++last;
                        auto temp = v[last];
                        v[last] = v[i];
                        v[i] = temp;
                    }
                }

                {
                    auto temp = v[last];
                    v[last] = v[left];
                    v[left] = temp;
                }
                if (last > left) {
                    lQuickSort(v, left, last - 1);
                }
                if (last < right) {
                    lQuickSort(v, last + 1, right);
                }
            }

            template<typename T>
            static void rQuickSort(T *v, size_t left, size_t right) {
                if (left >= right) {
                    return;
                }
                if (right - left < 100) {
                    algo::sort::bubble::bubbleSort(v, left, right);
                    return;
                }
                size_t mid = (left + right) / 2;
                {
                    auto temp = v[right];
                    v[right] = v[left];
                    v[left] = temp;
                }
                size_t last = left;

                for (size_t i = left + 1; i <= right; i++) {
                    if (v[i] < v[left]) {
                        ++last;
                        auto temp = v[last];
                        v[last] = v[i];
                        v[i] = temp;
                    }
                }

                {
                    auto temp2 = v[last];
                    v[last] = v[left];
                    v[left] = temp2;
                }

                if (last > left) {
                    rQuickSort(v, left, last - 1);
                }
                if (last < right) {
                    rQuickSort(v, last + 1, right);
                }
            }


            template<typename T>
            static void doExecutor(DataHolder<T> &dataHolder,  util::Timer &timer, const QSDecision &qsDecision, int repeats) {
                vector<T> idealSorted = dataHolder.data;

                if (qsDecision == QSDecision::IDEAL) {
                    idealSorted = dataHolder.data;
                    quickSort(idealSorted, 0, idealSorted.size() - 1, QSDecision::MID);
                }

                size_t num;

                if (repeats == 0) {
                    num = 1;
                } else {
                    num = dataHolder.measureRepeats;
                }


                for (int i = 0; i < num; i++) {
                    if (repeats != 0)
                        cout << "Powtorzenie numer: " << i + 1 << " na " << dataHolder.measureRepeats << endl;
                    dataHolder.dataSorted = dataHolder.data;
                    timer.start();
                    if (qsDecision == QSDecision::IDEAL)
                        quickSort(dataHolder.dataSorted, 0, dataHolder.dataSorted.size() - 1, qsDecision, &idealSorted);
                    else
                        quickSort(dataHolder.dataSorted, 0, dataHolder.dataSorted.size() - 1, qsDecision);

                    timer.stop();
                }

            }


            static void genericExecutor(FullDataHolder &dataHolder,  util::Timer &timer, QSDecision qsDecision) {
                if (dataHolder.loadedDataType == DataType::FLOAT) {
                    doExecutor(dataHolder.dataHolderFloat, timer, qsDecision, 0);
                } else if (dataHolder.loadedDataType == DataType::INT) {
                    doExecutor(dataHolder.dataHolderInt, timer, qsDecision, 0);
                }
            }


            class StrategyLeft : public Strategy {
                std::string getName() override { return "Lewy pivot"; }

                StrategyFeedback doAction(FullDataHolder &dataHolder) override {
                    if (dataHolder.loadedDataType == DataType::NONE) {
                        return StrategyFeedback::failed("Brak wczytanych danych");
                    }
                    util::Timer timer(dataHolder);
                    genericExecutor(dataHolder, timer, QSDecision::LEFT);
                    return StrategyFeedback::success("Everything went ok").timed(timer.get());
                }
            };

            class StrategyMid : public Strategy {
                std::string getName() override { return "Srodkowy pivot"; }

                StrategyFeedback doAction(FullDataHolder &dataHolder) override {
                    if (dataHolder.loadedDataType == DataType::NONE) {
                        return StrategyFeedback::failed("Brak wczytanych danych");
                    }
                    util::Timer timer(dataHolder);
                    genericExecutor(dataHolder, timer, QSDecision::MID);
                    return StrategyFeedback::success("Everything went ok").timed(timer.get());
                }

            };

            class StrategyRight : public Strategy {
                std::string getName() override { return "Prawy pivot"; }

                StrategyFeedback doAction(FullDataHolder &dataHolder) override {
                    if (dataHolder.loadedDataType == DataType::NONE) {
                        return StrategyFeedback::failed("Brak wczytanych danych");
                    }
                    util::Timer timer(dataHolder);
                    genericExecutor(dataHolder, timer, QSDecision::RIGHT);
                    return StrategyFeedback::success("Everything went ok").timed(timer.get());
                }
            };

            class StrategyMedian : public Strategy {
                std::string getName() override { return "Mediana pivot (idealny)"; }

                StrategyFeedback doAction(FullDataHolder &dataHolder) override {
                    if (dataHolder.loadedDataType == DataType::NONE) {
                        return StrategyFeedback::failed("Brak wczytanych danych");
                    }
                    util::Timer timer(dataHolder);
                    genericExecutor(dataHolder, timer, QSDecision::IDEAL);
                    return StrategyFeedback::success("Everything went ok").timed(timer.get());
                }
            };

            class StrategySortQuick : public Strategy {
                vector<Strategy *> strategies;
            public:
                StrategySortQuick() {
                    strategies.emplace_back(new StrategyFileLoad());
                    strategies.emplace_back(new StrategyLeft());
                    strategies.emplace_back(new StrategyMid());
                    strategies.emplace_back(new StrategyRight());
                    strategies.emplace_back(new StrategyMedian());
                    strategies.emplace_back(new StrategyExit());
                }

                std::string getName() override {
                    return "Sortowanie szybkie";
                }

                StrategyFeedback doAction(FullDataHolder &dataHolder) override {
                    auto con = ConsoleInterface(strategies, dataHolder);
                    con.run();
                    return StrategyFeedback::success().setWait(false);
                }

                ~StrategySortQuick() override {
                    for (auto &strategy : strategies) {
                        delete strategy;
                    }
                }
            };
        }
    }
}
#endif //MYALGO_STRATEGYSORTQUICK_H
