/**
 * Program.h
 *
 * @author Patrick Lavigne
 */

#pragma once

#include <atomic>

#include "mpf/core/LogSink.h"
#include "mpf/core/SubsystemList.h"

namespace mpf::core {

    class Program {
    public:
        Program() = default;

        virtual ~Program() = default;

        [[noreturn]]
        void run();

    protected:

        [[nodiscard]]
        SubsystemList * subsystems();

        [[nodiscard]]
        virtual LogSink const * logSink() const = 0;

        virtual void initialize() = 0;

        virtual void setUp() = 0;

        virtual void beforeFirstLoop();

        virtual void afterEveryLoop();

        [[noreturn]]
        virtual void panic(char const * message) = 0;

    private:
        std::atomic_flag m_started = false;

        SubsystemList m_subsystems;

        void loop();
    };

} // namespace mpf::core
