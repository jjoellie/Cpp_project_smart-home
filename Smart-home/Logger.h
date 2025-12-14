#pragma once
#include <cstring>
#include <fstream>
#include <stdexcept>
#include <string>

namespace smarthome {

class Logger
{
public:
    Logger() : Logger("smarthome.log") {}

    explicit Logger(const std::string& file)
        : file_(file), bufferSize_(256), buffer_(new char[bufferSize_])
    {
        std::memset(buffer_, 0, bufferSize_);
    }

    Logger(const Logger& other)
        : file_(other.file_), bufferSize_(other.bufferSize_), buffer_(new char[bufferSize_])
    {
        std::memcpy(buffer_, other.buffer_, bufferSize_);
    }

    ~Logger()
    {
        delete[] buffer_;
        buffer_ = nullptr;
    }

    void log(const std::string& msg) const
    {
        std::ofstream out(file_, std::ios::app);
        if (!out) throw std::runtime_error("Cannot open log file: " + file_);
        out << msg << "\n";
    }

    const std::string& file() const { return file_; }

    friend std::ostream& operator<<(std::ostream& os, const Logger& l)
    {
        os << "Logger(file=" << l.file_ << ", bufferSize=" << l.bufferSize_ << ")";
        return os;
    }

private:
    std::string file_;
    size_t bufferSize_;
    char* buffer_;
};

}

