/**
 * Your UndergroundSystem object will be instantiated and called as such:
 * UndergroundSystem* obj = new UndergroundSystem();
 * obj->checkIn(id,stationName,t);
 * obj->checkOut(id,stationName,t);
 * double param_3 = obj->getAverageTime(startStation,endStation);
 */
#include <bits/stdc++.h>
using namespace std;

class UndergroundSystem {
    struct CheckInInfo {
        string station;
        int time;
    };

    // id -> check-in info
    unordered_map<int, CheckInInfo> in;

    // "start#end" -> {totalTime, count}
    unordered_map<string, pair<long long, long long>> stats;

    static string key(const string& a, const string& b) {
        return a + "#" + b;
    }

public:
    UndergroundSystem() {}

    void checkIn(int id, string stationName, int t) {
        in[id] = {stationName, t};
    }

    void checkOut(int id, string stationName, int t) {
        auto it = in.find(id);
        const string& start = it->second.station;
        int startTime = it->second.time;

        long long duration = (long long)t - startTime;
        string k = key(start, stationName);

        auto &p = stats[k];
        p.first += duration;   // total time
        p.second += 1;         // trip count

        in.erase(it);
    }

    double getAverageTime(string startStation, string endStation) {
        auto &p = stats[key(startStation, endStation)];
        return (double)p.first / (double)p.second;
    }
};
