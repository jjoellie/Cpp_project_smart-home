#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Devices.h"

namespace smarthome
{
class Room
{
public:
    // Vraag 12: default constructor
    Room() : name_("Unknown") {}

    // Vraag 13: parameterized constructor
    explicit Room(const std::string& name) : name_(name) {}

    // Vraag 14: copy constructors intentionally disabled
    Room(const Room&) = delete;
    Room& operator=(const Room&) = delete;

    // Move allowed
    Room(Room&&) = default;
    Room& operator=(Room&&) = default;

    ~Room() = default;

    // Vraag 23 & 29: const references
    const std::string& getName() const { return name_; }

    // Vraag 36: container usage
    std::vector<std::unique_ptr<Device>>& getDevices() { return devices_; }
    const std::vector<std::unique_ptr<Device>>& getDevices() const { return devices_; }

    void addDevice(std::unique_ptr<Device> device)
    {
        devices_.push_back(std::move(device));
    }

    void updateDevices()
    {
        for (auto& d : devices_)
            d->update();
    }

private:
    std::string name_;
    std::vector<std::unique_ptr<Device>> devices_;
};
}
