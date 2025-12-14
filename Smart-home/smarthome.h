#pragma once
#include "Logger.h"
#include "Room.h"
#include <atomic>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <thread>
#include <vector>

namespace smarthome {

class SmartHome
{
public:
    SmartHome() : SmartHome("Unknown Owner") {}

    explicit SmartHome(const std::string& ownerName)
        : ownerName_(ownerName),
        running_(false),
        updateIntervalMs_(1000),
        logger_("smarthome.log")
    {}

    SmartHome(const SmartHome& other)
        : ownerName_(other.ownerName_),
        rooms_(other.rooms_),
        running_(false),
        updateIntervalMs_(other.updateIntervalMs_),
        logger_(other.logger_)
    {}

    ~SmartHome()
    {
        stopBackgroundUpdates();
    }

    const std::string& owner() const { return ownerName_; }

    void addRoom(Room room)
    {
        rooms_.push_back(std::move(room));
    }

    std::vector<Room>& rooms() { return rooms_; }
    const std::vector<Room>& rooms() const { return rooms_; }

    void setUpdateIntervalMs(int ms) { updateIntervalMs_ = ms; }

    int countDevicesByType(const std::string& type) const
    {
        int count = 0;
        for (const auto& r : rooms_)
        {
            auto matches = smarthome::filterCopy(r.devices(), [&](const std::unique_ptr<Device>& d) {
                return d && d->typeName() == type;
            });
            count += static_cast<int>(matches.size());
        }
        return count;
    }

    void updateAll(double dt = 1.0)
    {
        for (auto& r : rooms_)
            r.updateDevices(dt);
    }

    void startBackgroundUpdates()
    {
        if (running_) return;
        running_ = true;

        worker_ = std::thread([this]() {
            try
            {
                logger_.log("Background thread started.");
                while (running_)
                {
                    this->updateAll(1.0);

                    std::this_thread::sleep_for(std::chrono::milliseconds(updateIntervalMs_));
                }
                logger_.log("Background thread stopped.");
            }
            catch (const std::exception& e)
            {
                try { logger_.log(std::string("Thread exception: ") + e.what()); } catch (...) {}
            }
        });
    }

    void stopBackgroundUpdates()
    {
        if (!running_) return;
        running_ = false;
        if (worker_.joinable()) worker_.join();
    }

    void saveToFile(const std::string& path) const
    {
        std::ofstream out(path);
        if (!out) throw std::runtime_error("Cannot write file: " + path);

        out << "OWNER=" << ownerName_ << "\n";
        out << "ROOMS=" << rooms_.size() << "\n";

        for (const auto& r : rooms_)
        {
            out << "ROOM=" << r.name() << "\n";
            out << "DEVICES=" << r.devices().size() << "\n";
            for (const auto& d : r.devices())
            {
                if (!d) continue;
                out << "D=" << d->typeName() << "," << int(d->deviceId()) << "," << d->name() << "," << d->roomName() << "," << (d->isOn() ? 1 : 0) << "\n";
            }
        }
    }

private:
    std::string ownerName_;
    std::vector<Room> rooms_;

    std::atomic<bool> running_;
    int updateIntervalMs_;
    std::thread worker_;

    Logger logger_;
};

}
