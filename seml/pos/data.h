#pragma once

#include <map>

#include "types.h"
#include "world.h"

struct ZombieStats {
    int alive_count = 0;
    int total_count = 0;
    float min_x = 9999.0f;
    float max_x = -9999.0f;
    std::map<int, int> histogram; // int(x) -> count

    void merge(const ZombieStats& other)
    {
        alive_count += other.alive_count;
        total_count += other.total_count;
        if (other.alive_count > 0) {
            if (other.min_x < min_x)
                min_x = other.min_x;
            if (other.max_x > max_x)
                max_x = other.max_x;
        }
        for (const auto& [k, v] : other.histogram) {
            histogram[k] += v;
        }
    }
};

// Key: (wave_index, zombie_type)
using StatsKey = std::pair<int, pvz_emulator::object::zombie_type>;
using StatsMap = std::map<StatsKey, ZombieStats>;

struct PosTable {
    StatsMap stats;
    int repeat = 0;

    void update(const StatsMap& local_stats)
    {
        for (const auto& [key, val] : local_stats) {
            stats[key].merge(val);
        }
        repeat++;
    }

    void merge(const PosTable& other)
    {
        for (const auto& [key, val] : other.stats) {
            stats[key].merge(val);
        }
        repeat += other.repeat;
    }
};

struct TimeStats {
    int arrived_count = 0;
    int total_count = 0;
    int min_tick = 999999;
    int max_tick = -1;
    std::map<int, int> histogram; // tick -> count

    void merge(const TimeStats& other)
    {
        arrived_count += other.arrived_count;
        total_count += other.total_count;
        if (other.arrived_count > 0) {
            if (other.min_tick < min_tick)
                min_tick = other.min_tick;
            if (other.max_tick > max_tick)
                max_tick = other.max_tick;
        }
        for (const auto& [k, v] : other.histogram) {
            histogram[k] += v;
        }
    }
};

using TimeMap = std::map<StatsKey, TimeStats>;

struct TimeTable {
    TimeMap stats;
    int repeat = 0;

    void update(const TimeMap& local_stats)
    {
        for (const auto& [key, val] : local_stats) {
            stats[key].merge(val);
        }
        repeat++;
    }

    void merge(const TimeTable& other)
    {
        for (const auto& [key, val] : other.stats) {
            stats[key].merge(val);
        }
        repeat += other.repeat;
    }
};
