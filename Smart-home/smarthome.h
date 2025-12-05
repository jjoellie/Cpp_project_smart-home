#pragma once
#include <vector>
#include <string>
#include <utility>

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
    const std::vector<Room>& getRooms() const { return rooms_; }

    void updateAll()
    {
        for (auto& r : rooms_)
            r.updateDevices();
    }

private:
    std::string ownerName_;
    std::vector<Room> rooms_;
};
