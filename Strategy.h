//
// Created by Development on 03/05/2020.
//

#ifndef UNTITLED_STRATEGY_H
#define UNTITLED_STRATEGY_H

#include <chrono>
#include "FullDataHolder.h"

using namespace std;

enum class StrategyCode {
    SCREAM = -2, FAILED, EXIT, SUCCESS
};

class StrategyFeedback {
private:

    StrategyCode code;
    std::string message;
    bool wait = true;
    bool vTimed = false;
    std::chrono::nanoseconds mTime;
public:
    StrategyFeedback(StrategyCode code, string message) : code(code), message(std::move(message)) {}

    static StrategyFeedback scream(string message) {
        return StrategyFeedback(StrategyCode::SCREAM, std::move(message));
    }

    static StrategyFeedback failed(string message) {
        return StrategyFeedback(StrategyCode::FAILED, std::move(message));
    }

    static StrategyFeedback exit(string message) {
        return StrategyFeedback(StrategyCode::EXIT, std::move(message));
    }

    static StrategyFeedback success(string message) {
        return StrategyFeedback(StrategyCode::SUCCESS, std::move(message));
    }
    static StrategyFeedback success( ) {
        return StrategyFeedback(StrategyCode::SUCCESS, "");
    }

    StrategyCode getCode() const {
        return code;
    }

    const string &getMessage() const {
        return message;
    }

    bool isWait() const {
        return wait;
    }

    StrategyFeedback& setWait(bool mWait) {
        wait = mWait;
        return *this;
    }

    StrategyFeedback& timed(std::chrono::nanoseconds time){
        vTimed = true;
        mTime = time;
        return *this;
    }

    const chrono::nanoseconds &getTime() const {
        return mTime;
    }

    bool isTimed() const {
        return vTimed;
    }
};


class Strategy {

public:
    virtual std::string getName() = 0;
    virtual StrategyFeedback doAction(FullDataHolder &dataHolder) = 0;
    virtual ~Strategy()= default;
};


#endif //UNTITLED_STRATEGY_H
