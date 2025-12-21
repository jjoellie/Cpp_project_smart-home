#pragma once

#include <vector>
#include <fstream>
#include <stdexcept>
#include "Room.h"

namespace smarthome
{
class SmartHome
{
public:
    SmartHome(const std::string& owner) : owner_(owner) {}

    void addRoom(Room&& room)
    {
        rooms_.push_back(std::move(room));
    }

    std::vector<Room>& rooms() { return rooms_; }
    const std::vector<Room>& rooms() const { return rooms_; }

    void updateAll()
    {
        for (auto& r : rooms_)
            r.updateDevices();
    }

    // Vraag 38 & 39: file I/O + exception handling
    void saveToFile(const std::string& path)
    {
        std::ofstream out(path);
        if (!out)
            throw std::runtime_error("Cannot open file");

        out << "SmartHome owner: " << owner_ << "\n";
    }

private:
    std::string owner_;
    std::vector<Room> rooms_;
};
}
