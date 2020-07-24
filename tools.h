//
// Created by Development on 03/05/2020.
//

#ifndef UNTITLED_TOOLS_H
#define UNTITLED_TOOLS_H

#include <algorithm>
#include <cctype>
#include <locale>
namespace util {
// trim from start (in place)
    static inline void ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
            return !std::isspace(ch);
        }));
    }

// trim from end (in place)
    static inline void rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
            return !std::isspace(ch);
        }).base(), s.end());
    }

// trim from both ends (in place)
    static inline std::string trim(std::string s) {

        auto pos = s.find('#');
        if (pos != std::string::npos) {
            s = s.substr(0, pos);
        }
        ltrim(s);
        rtrim(s);
        return s;
    }

    std::string algo_lower(std::string sourceString) {

        std::string destinationString;

        // Allocate the destination space
        destinationString.resize(sourceString.size());

        // Convert the source string to lower case
        // storing the result in destination string
        std::transform(sourceString.begin(),
                       sourceString.end(),
                       destinationString.begin(),
                       ::tolower);

        return destinationString;
    }

    class Timer {
        std::chrono::nanoseconds startp = std::chrono::high_resolution_clock::duration::zero();
        std::chrono::nanoseconds sum = std::chrono::high_resolution_clock::duration::zero();
        FullDataHolder &dataHolder;
    public:

        Timer(FullDataHolder &dataHolder) : dataHolder(dataHolder) {
            dataHolder.timeMeasurements.clear();
        }

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
            dataHolder.timeMeasurements.emplace_back(sum);
        }

        std::chrono::nanoseconds get() {
            return sum;
        }
    };
}
#endif //UNTITLED_TOOLS_H
