#pragma once
#include <vector>
#include <string>
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

    std::vector<Room>& getRooms() { return rooms_; }

private:
    std::string ownerName_;
    std::vector<Room> rooms_;
};
