#pragma once
#include <vector>
#include <string>

#include "Room.h"
#include "Utils.h"

namespace smarthome
{
class SmartHome
{
public:
    SmartHome() : ownerName_("Unknown") {}
    explicit SmartHome(const std::string& owner) : ownerName_(owner) {}

    void addRoom(Room room)
    {
        rooms_.push_back(std::move(room));
    }

    std::vector<Room>& rooms() { return rooms_; }
    const std::vector<Room>& rooms() const { return rooms_; }

    void updateAll()
    {
        for (auto& room : rooms_)
            room.updateDevices();
    }

private:
    std::string ownerName_;
    std::vector<Room> rooms_;
};
}
