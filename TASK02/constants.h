// constants.h - the ONLY place where fares, surcharge and limits are defined
#pragma once

enum class Zone { Inner, Middle, Outer };

constexpr int ZONE_COUNT = 3;
constexpr long long BASE_FARE_PAISE[ZONE_COUNT] = {1000, 2000, 3000}; // Rs 10, 20, 30
constexpr int PEAK_SURCHARGE_PERCENT = 20;
constexpr long long MIN_BALANCE_PAISE = 5000;                          // Rs 50
constexpr int MORNING_PEAK_START = 8,  MORNING_PEAK_END = 10;          // [8,10)
constexpr int EVENING_PEAK_START = 17, EVENING_PEAK_END = 20;          // [17,20)
constexpr int STUDENT_CONCESSION_PERCENT = 50;                         // assumption
constexpr int SENIOR_CONCESSION_PERCENT  = 50;                         // assumption
