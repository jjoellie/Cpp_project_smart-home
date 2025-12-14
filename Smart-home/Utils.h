#pragma once
#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>

namespace smarthome {

template <typename T>
inline T clampValue(const T& v, const T& lo, const T& hi)
{
    return std::max(lo, std::min(v, hi));
}

template <typename Container, typename Pred>
inline std::vector<typename Container::value_type> filterCopy(const Container& c, Pred p)
{
    std::vector<typename Container::value_type> out;
    for (const auto& x : c)
        if (p(x)) out.push_back(x);
    return out;
}

}
