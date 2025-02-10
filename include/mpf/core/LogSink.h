/**
 * LogSink.h
 *
 * @author Patrick Lavigne
 */

#pragma once

#include <string_view>

namespace mpf::core {
    class LogSink {
    public:
        LogSink() = default;

        virtual ~LogSink() = default;

        virtual void writeTimeStamp() const = 0;

        virtual void write(std::string_view const & message) const = 0;

        virtual void flush() const = 0;
    };
}
