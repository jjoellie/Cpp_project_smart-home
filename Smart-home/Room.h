#pragma once
#include <string>
#include <vector>
#include <memory>

#include "Device.h"

class Room
{
public:
    Room(const std::string& name)
        : name_(name)
    {}

    std::string getName() const { return name_; }

    void addDevice(std::unique_ptr<Device> d)
    {
        devices_.push_back(std::move(d));
    }

    const std::vector<std::unique_ptr<Device>>& getDevices() const
    {
        return devices_;
    }

    std::vector<std::unique_ptr<Device>>& getDevices()
    {
        return devices_;
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
