#pragma once
#include "Device.h"
#include <memory>
#include <string>
#include <vector>

namespace smarthome {

class Room
{
public:
    Room() : Room("Unnamed Room") {}

    explicit Room(const std::string& name)
        : name_(name), visited_(false)
    {}

    Room(const Room& other)
        : name_(other.name_), visited_(other.visited_)
    {
        devices_.reserve(other.devices_.size());
        for (const auto& d : other.devices_)
            devices_.push_back(d ? d->clone() : nullptr);
    }

    ~Room() = default;

    const std::string& name() const { return name_; }
    bool visited() const { return visited_; }

    void setVisited(bool v = true) { visited_ = v; }

    void addDevice(std::unique_ptr<Device> d)
    {
        devices_.push_back(std::move(d));
    }

    const std::vector<std::unique_ptr<Device>>& devices() const { return devices_; }
    std::vector<std::unique_ptr<Device>>& devices() { return devices_; }

    void updateDevices(double dt = 1.0)
    {
        for (auto& d : devices_)
            if (d) d->update(dt);
    }

private:
    std::string name_;
    std::vector<std::unique_ptr<Device>> devices_;
    bool visited_;
};

}
