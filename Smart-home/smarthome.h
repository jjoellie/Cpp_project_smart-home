#pragma once

#include <vector>
#include <string>
#include <memory>
#include <stdexcept>

#include "Room.h"

// Vraag 27: everything in namespace
namespace smarthome
{

class SmartHome
{
public:
    // Vraag 13 & 16: parameterized constructor + init list
    explicit SmartHome(const std::string& owner)
        : owner_(owner)
    {}

    // Vraag 12: default constructor
    SmartHome() : SmartHome("Unknown") {}

    // Vraag 20: useful member function
    void addRoom(Room&& room)
    {
        rooms_.push_back(std::move(room));
    }


    // Vraag 23 & 29 & 30: getters + const references
    std::vector<Room>& getRooms()
    {
        return rooms_;
    }

    const std::vector<Room>& getRooms() const
    {
        return rooms_;
    }
    // ==================================================

    // Vraag 18: polymorphism usage
    void updateAll()
    {
        for (auto& room : rooms_)
            room.updateDevices();
    }

private:
    std::string owner_;
    std::vector<Room> rooms_;   // Vraag 36: container class
};

} // namespace smarthome
