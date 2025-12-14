#pragma once
#include <vector>

namespace smarthome
{
template <typename Container, typename Predicate>
auto filterCopy(const Container& container, Predicate pred)
{
    Container result;
    for (const auto& item : container)
    {
        if (pred(item))
            result.push_back(item);
    }
    return result;
}
}
