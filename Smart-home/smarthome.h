#ifndef SMARTHOME_H
#define SMARTHOME_H

#include <vector>
#include <string>
#include <iostream>

#include "Room.h"

class SmartHome
{
public:
    SmartHome(const std::string& ownerName)
        : ownerName_(ownerName)
    {
    }

    void addRoom(const Room& room)
    {
        rooms_.push_back(room);
    }

    std::vector<Room>& getRooms()
    {
        return rooms_;
    }

    const std::vector<Room>& getRooms() const
    {
        return rooms_;
    }

    void updateAll()
    {
        for (auto& room : rooms_)
            room.updateDevices();
    }

    void printOverview() const
    {
        std::cout << "SmartHome of " << ownerName_ << "\n";
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

#endif
