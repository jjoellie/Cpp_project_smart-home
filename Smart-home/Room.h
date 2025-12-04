#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>

#include "Device.h"

class Room
{
public:
    Room(const std::string& name) : name_(name) {}

    std::string getName() const
    {
        return name_;
    }

    void addDevice(std::unique_ptr<Device> device)
    {
        device_.push_back(std::move(device));
    }

    const std::vector<std::unique_ptr<Device>>& getDevices() const
    {
        return device_;
    }
    void updateDevices()
    {
        for (auto& d : device_)
        {
            if (d)
                d->update();
        }
    }

    void printDevices() const
    {
        std::cout << "Room: " << name_ << "\n";
        for (const auto& d : device_)
        {
            if (d)
            {
                std::cout << "  - ";
                d->printInfo();
                std::cout << "\n";
            }
        }
    }

private:
    std::string name_;
    std::vector<std::unique_ptr<Device>> device_;
};

#endif
