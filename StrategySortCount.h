//
// Created by Development on 03/05/2020.
//

#ifndef MYALGO_STRATEGYSORTCOUNT_H
#define MYALGO_STRATEGYSORTCOUNT_H

#include <iostream>
#include <vector>
#include <memory>

#include "Strategy.h"
#include "FullDataHolder.h"
#include "tools.h"


namespace algo {
    namespace sort {
        namespace count {


            template<class T>
            class KeyHelper {
            public:
                virtual KeyHelper<T> &init(T* vector,size_t n) {std::cout<<"0x0";return *this; };

                virtual size_t convertValueTo(T value) { std::cout<<"0x0";return (size_t) 0; };

                virtual size_t getSize() { std::cout<<"0x0";return (size_t) 0; };
            };


            class KeyHelperInteger : public KeyHelper<int> {

                long min = 0;
                long max = 0;
            public:
                KeyHelperInteger &init(int *vector,size_t n) override {
                    if (n > 0) {
                        min = vector[0];
                        max = vector[0];
                        for (size_t i = 0; i < n;i++) {
                            int val = vector[i];
                            if (val > max)
                                max = val;
                            if (val < min)
                                min = val;
                        }
                    }
                    return *this;
                };

                size_t getSize() override {
					auto val = (size_t)(max - min +1) ;
                    return val;
                }

                size_t convertValueTo(int value) override {
                    return value - min;
                };
            };

            class KeyHelperFloat : public KeyHelper<float> {
                int min = 0;
                int max = 0;
            public:
                KeyHelperFloat &init(float *vector,size_t n) override {
                    if (n > 0) {
                        min = vector[0];
                        max = vector[0];
                        for (size_t i = 0; i < n ; i++) {
                            int castedVal = static_cast<int>(vector[i]);
                            if (castedVal > max)
                                max = castedVal;
                            if (castedVal < min)
                                min = castedVal;
                        }
                    }
                    return *this;
                };

                size_t getSize() override {
                    return max - min + 1;
                }

                size_t convertValueTo(float value) override {
                    return static_cast<int>(value) - min;
                };
            };


            template<typename T>
            static void countSort(T* v, size_t start, size_t stop,  KeyHelper<T>* keyHelper) {



                int S = stop;
                size_t news = keyHelper->getSize();



                size_t *countArray =  new size_t[ news ];

                T* valuesArray = new T[ news ];

                // Zerowanie
                for (int i = 0; i < keyHelper->getSize(); i++) {
                    countArray[i] = 0;
                }

                // Liczenie
                for (int i = start; i < S; i++) {
                    size_t matchIndex = keyHelper->convertValueTo(v[i]);
                    valuesArray[matchIndex] = v[i];
                    countArray[matchIndex]++;
                }

                // Wstawianie
                size_t idx = 0;
                for (int i = 0; i < keyHelper->getSize(); i++) {
                    while (countArray[i] > 0) {
                        v[idx] = valuesArray[i];
                        ++idx;
                        --countArray[i];
                    }
                }

                delete[] countArray;
                delete[] valuesArray;
            }

            template<typename T>
            static void
            dataExecutorMethod(DataHolder<T> &dataHolder,  util::Timer &timer, KeyHelper<T>* keyHelper, int repeats) {

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

                    auto kh = keyHelper->init(dataHolder.dataSorted.data(),dataHolder.dataSorted.size() );

                    countSort(
                            dataHolder.dataSorted.data(),
                            0,
                            dataHolder.dataSorted.size() - 1,
							keyHelper

                    );

                    timer.stop();
                }
            }


            class StrategySortCount : public Strategy {
            public:
                std::string getName() override {
                    return "Sortowanie przez zliczanie";
                }


                StrategyFeedback doAction(FullDataHolder &dataHolder) override {
                    util::Timer timer(dataHolder);

                    if (dataHolder.loadedDataType == DataType::NONE) {
                        return StrategyFeedback::failed("Brak wczytanych danych");
                    } else if (dataHolder.loadedDataType == DataType::FLOAT) {
                    	auto pFloat = std::unique_ptr<KeyHelper<float>>( new KeyHelperFloat() );
                        dataExecutorMethod(dataHolder.dataHolderFloat, timer, dynamic_cast<KeyHelper<float>*>(pFloat.get()) ,0);
                    } else if (dataHolder.loadedDataType == DataType::INT) {
                    	auto pInt = std::unique_ptr<KeyHelper<int>>(new KeyHelperInteger() );
                        dataExecutorMethod(dataHolder.dataHolderInt, timer, dynamic_cast<KeyHelper<int>*>(pInt.get()),0);
                    }

                    return StrategyFeedback::success().timed(timer.get());
                }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-auto"


#pragma clang diagnostic pop
            };
        }
    }
}

#endif //MYALGO_STRATEGYSORTBUBBLE_H
