#pragma once
#include <vector>
#include <string>
#include <iostream>

#include "Room.h"

class SmartHome
{
public:
    SmartHome(const std::string& ownerName)
        : ownerName_(ownerName)
    {}

    void addRoom(Room room)
    {
        rooms_.push_back(std::move(room));
    }

    void updateAll()
    {
        for (auto& room : rooms_)
            room.updateDevices();
    }

    void printOverview() const
    {
        std::cout << "SmartHome of " << ownerName_ << "\n\n";
        for (const auto& room : rooms_)
        {
            room.printDevices();
            std::cout << "\n";
        }
    }

private:
    std::string ownerName_;
    std::vector<Room> rooms_;
};
