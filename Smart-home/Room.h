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

    // Composition: Room BEZIT de devices
    void addDevice(std::unique_ptr<Device> device)
    {
        devices_.push_back(std::move(device));
    }

    const std::vector<std::unique_ptr<Device>>& getDevices() const
    {
        return devices_;
    }
