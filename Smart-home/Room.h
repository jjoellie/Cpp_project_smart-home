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
    Room() : name_("Unknown") {}
    explicit Room(const std::string& name) : name_(name) {}

    Room(const Room&) = delete;
    Room& operator=(const Room&) = delete;

    Room(Room&&) = default;
    Room& operator=(Room&&) = default;

    ~Room() = default;

    const std::string& getName() const
    {
        return name_;
    }

    std::vector<std::unique_ptr<Device>>& getDevices()
    {
        return devices_;
    }

    const std::vector<std::unique_ptr<Device>>& getDevices() const
    {
        return devices_;
    }

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
