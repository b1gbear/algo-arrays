//
// Created by Development on 03/05/2020.
//

#ifndef MYALGO_STRATEGYBENCHMARK_H
#define MYALGO_STRATEGYBENCHMARK_H

#include <string>
#include <cstring>
#include "Strategy.h"

namespace benchmark {

    class Timer {
        std::chrono::nanoseconds startp = std::chrono::high_resolution_clock::duration::zero();
        std::chrono::nanoseconds sum = std::chrono::high_resolution_clock::duration::zero();
    public:

        Timer() {}

        void start() {
            std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();

            auto duration = now.time_since_epoch();

            startp = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
        }


        void stop() {
            std::chrono::time_point<std::chrono::high_resolution_clock> stop = std::chrono::high_resolution_clock::now();

            auto duration = stop.time_since_epoch();

            auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);

            sum += (nanoseconds - startp);
        }

        std::chrono::nanoseconds get() {
            return sum;
        }
    };

    class StrategyBenchmark : public Strategy {
        std::string getName() override {
            return "Pomiar czasu";
        }

        StrategyFeedback doAction(FullDataHolder &dataHolder) override {

            FullDataHolder mockDataHolder;


            std::map<std::string, std::vector<std::chrono::nanoseconds>> mapvect;


            std::vector<std::string> vect;

//        vect.emplace_back(std::string("bubble"));
            vect.emplace_back(std::string("count"));
            vect.emplace_back(std::string("heap"));
            vect.emplace_back(std::string("quick-left"));
            vect.emplace_back(std::string("quick-right"));
            vect.emplace_back(std::string("quick-mid"));
            vect.emplace_back(std::string("quick-ideal"));


            const int seed = 1705311660;

            std::default_random_engine generatorInteger(seed);
            std::uniform_int_distribution<int32_t> distribution(-10000000,
                                                                1000000);


            for (const auto &entry: vect) {
                mapvect.insert(std::make_pair(entry, std::vector<std::chrono::nanoseconds>()));
            }

            auto skipBubble = false;
            if (!skipBubble) {
                int R = 50;
                int num = 100;
                int MAX = 5000;
                size_t delta = MAX / num;
                int *data = new int[MAX];
                vector<int> bubbleN;
                vector<std::chrono::nanoseconds> bubbleTimes;

                for (size_t currentCount = delta, i = 0; currentCount <= MAX; currentCount += delta,i++) {
                    std::cout << "bubble" << currentCount << " on " << MAX << std::endl;
                    using namespace algo::sort::bubble;
                    bubbleN.emplace_back(currentCount);
                    for (int r = 0; r < R; r++) {

                        std::vector<int> collection;
                        collection.reserve(MAX);
                        for (int v = 0; v < currentCount; v++) {
                            auto val = distribution(generatorInteger);
                            collection.push_back(val);
                        }

                        std::copy(collection.data(), collection.data() + currentCount, data);

                        Timer timer = Timer();

                        timer.start();
                        bubbleSort(data, 0, currentCount - 1);
                        timer.stop();

//                        std::cout << "r  = " << r << " i = " << i << " bubbleTimes.size() = " << bubbleTimes.size() << std::endl;
                        if(i < bubbleTimes.size()){
                            bubbleTimes[i] = (bubbleTimes[i] + timer.get());
                        }else{
                            bubbleTimes.emplace_back(timer.get());
                        }
                    }
                }

                std::cout << "bubleSize" << bubbleTimes.size() << std::endl;

                ofstream bubbleFile("bubble.csv");
                bubbleFile << "bubble" << endl;
                bubbleFile << bubbleTimes.size() << endl;

                for (size_t i = 0; i < bubbleTimes.size(); i++) {
                    bubbleFile << bubbleN[i] << "," << bubbleTimes[i].count() << std::endl;
                }


            }


            // Config
            size_t MAX = 1000000;
            int R = 50;
            size_t num = 100;
            size_t delta = MAX / num;

            int *data = new int[MAX];
            int *dataForIdeal = new int[MAX];

            std::vector<size_t> nVector;

            for (size_t i = delta; i <= MAX; i += delta) {
                nVector.push_back(i);
            }

            for (size_t currentSize = delta,i = 0; currentSize <= MAX; currentSize += delta,i++) {
                std::cout << "current index is " << currentSize << " on step =  " << delta << " on max = " << MAX << endl;
                for (int r = 0; r < R; r++) {
                    std::cout << "current repeat is " << r + 1 << " on max " << R << endl;

                    std::vector<int> collection;
                    collection.reserve(MAX);
                    for (int v = 0; v < currentSize; v++) {
                        auto val = distribution(generatorInteger);
                        collection.push_back(val);
                    }

                    {
                        std::copy(collection.data(), collection.data() + currentSize, data);
                        Timer timer = Timer();
                        timer.start();
                        auto unq = std::unique_ptr<algo::sort::count::KeyHelper<int>>(new algo::sort::count::KeyHelperInteger());
                        unq->init(data, currentSize);
                        algo::sort::count::countSort(
                                data,
                                0,
                                currentSize - 1,
								unq.get()
                        );
                        timer.stop();
                        addTime(mapvect, i, timer, "count");

                    }

                    {
                        std::copy(collection.data(), collection.data() + currentSize, data);
                        Timer timer = Timer();
                        timer.start();
                        algo::sort::heap::heapSort(data, 0, currentSize - 1);
                        timer.stop();
                        addTime(mapvect, i, timer, "heap");

                    }


                    {
                        std::copy(collection.data(), collection.data() + currentSize, data);

                        Timer timer = Timer();
                        timer.start();
                        algo::sort::quick::lQuickSort(data, 0, currentSize - 1);
                        timer.stop();
                        addTime(mapvect, i, timer, "quick-left");
                    }

                    {
//                    std::cout << "quick-right" << std::endl;
                        std::copy(collection.data(), collection.data() + currentSize, data);
                        Timer timer = Timer();
                        timer.start();
                        algo::sort::quick::rQuickSort(data, 0, currentSize - 1);
                        timer.stop();
                        addTime(mapvect, i, timer, "quick-right");
                    }

                    {
//                    std::cout << "quick-mid" << std::endl;
                        std::copy(collection.data(), collection.data() + currentSize, data);
                        Timer timer = Timer();
                        timer.start();
                        algo::sort::quick::mQuickSort(data, 0, currentSize - 1);
                        timer.stop();
                        addTime(mapvect, i, timer, "quick-mid");

                    }


                    {
//                    std::cout << "quick-ideal" << std::endl;
                        std::copy(collection.data(), collection.data() + currentSize, dataForIdeal);
                        Timer timer = Timer();
                        timer.start();
                        algo::sort::quick::iQuickSort(dataForIdeal, data, 0, currentSize - 1);
                        timer.stop();
                        addTime(mapvect, i, timer, "quick-ideal");

                    }
                }


            }


            ofstream file("benchmark.csv");

            for (int j = 0; j < vect.size(); j++) {
                std::cout << vect[j];
                file << vect[j];

                if (j < vect.size() - 1) {
                    std::cout << ",";
                    file << ",";
                } else {
                    std::cout << std::endl;
                    file << std::endl;

                }
            }
            file << std::to_string(R) << std::endl;
            // TODO: AD N
            for (int nVectIndex = 0; nVectIndex < nVector.size(); nVectIndex++) {
                std::cout << "idx" << nVectIndex << std::endl;
                file << std::to_string(nVector[nVectIndex]) << ",";
                for (int j = 0; j < vect.size(); j++) {
                    std::cout << "j" << j << std::endl;
                    auto data = std::chrono::duration_cast<std::chrono::nanoseconds>(
                            mapvect[vect[j]][nVectIndex]).count();
                    file << std::to_string(data);

                    if (j < vect.size() - 1) {
                        file << ",";
                    } else {
                        file << std::endl;
                    }
                }
            }

            return StrategyFeedback::success("Everything went ok");
        }

        void addTime(map<std::string, std::vector<std::chrono::nanoseconds>> &mapvect, int i, Timer &timer,
                     const std::string &label) {
            if (i < mapvect.at(label).size()) {
                mapvect.at(label)[i] = mapvect.at(label)[i] + timer.get();
            } else {
                mapvect.at(label).emplace_back(timer.get());
            }
        }

    };
}
#endif //MYALGO_STRATEGYEXIT_H
