#pragma once
#include <string>
#include <vector>
#include <memory>
#include <iostream>

#include "Device.h"

class Room
{
public:
    Room(const std::string& name)
        : name_(name)
    {}

    std::string getName() const { return name_; }

    // Composition — the Room OWNS the devices
    void addDevice(std::unique_ptr<Device> device)
    {
        devices_.push_back(std::move(device));
    }

    const std::vector<std::unique_ptr<Device>>& getDevices() const
    {
        return devices_;
    }

    void updateDevices()
    {
        for (auto& d : devices_)
            d->update();
    }

    void printDevices() const
    {
        std::cout << "Room: " << name_ << "\n";
        for (const auto& d : devices_)
        {
            std::cout << "  - ";
            d->printInfo();
            std::cout << "\n";
        }
    }

private:
    std::string name_;
    std::vector<std::unique_ptr<Device>> devices_;
};
