#include <vector>
#include <chrono>
#include <thread>
#include "ConsoleInterface.h"
#include "StrategyFileLoad.h"
#include "StrategyShowData.h"
#include "StrategyFileSave.h"
#include "StrategyShowStats.h"
#include "StrategySortQuick.h"
#include "StrategySortBubble.h"
#include "StrategyExit.h"
#include "StrategyFileGenerate.h"
#include "StrategyConclusions.h"
#include "StrategySortCount.h"
#include "StrategySortHeap.h"
#include "ConsoleInterfaceWithAuthorship.h"
#include "StrategyBenchmark.h"



int main(int argc, char* argv[]){
    FullDataHolder dataHolder;

    std::vector<Strategy*> strategies;
    strategies.emplace_back(new StrategyFileGenerate());
    strategies.emplace_back(new StrategyFileLoad());
    strategies.emplace_back(new StrategyFileSave());
    strategies.emplace_back(new StrategyShowData());
    strategies.emplace_back(new StrategyShowStats());
    strategies.emplace_back(new algo::sort::bubble::StrategySortBubble());
    strategies.emplace_back(new algo::sort::quick::StrategySortQuick());
    strategies.emplace_back(new algo::sort::count::StrategySortCount());
    strategies.emplace_back(new algo::sort::heap::StrategySortHeap());
    strategies.emplace_back(new benchmark::StrategyBenchmark());
    strategies.emplace_back(new StrategyConclusions());
    strategies.emplace_back(new StrategyExit());
    ConsoleInterfaceWithAuthorship con(strategies, dataHolder);

    con.visitingCard();

#ifdef __linux
    std::this_thread::sleep_for(std::chrono::milliseconds(1200));
#endif
    con.run();

    // Remove pointers
    for(auto & strategy : strategies){
        delete strategy;
    }
}
