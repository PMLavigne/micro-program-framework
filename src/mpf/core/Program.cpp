/**
 * Program.cpp
 *
 * @author Patrick Lavigne
 */

#include "mpf/core/Program.h"
#include "mpf/core/Logging.h"

namespace mpf::core {

    void Program::run() {
        if (m_started.test_and_set()) {
            panic("Attempted to start program twice!");
        }

        initialize();

        Logger::setLogSink(logSink());

        m_subsystems.initialize();

        setUp();

        m_subsystems.setUp();

        beforeFirstLoop();

        while (true) {
            loop();
        }
    }

    [[nodiscard]]
    SubsystemList* Program::subsystems() {
        return &m_subsystems;
    }

    void Program::beforeFirstLoop() {
        // Does nothing by default, override if needed
    }

    void Program::afterEveryLoop() {
        // Does nothing by default, override if needed
    }

    void Program::loop() {
        m_subsystems.work();
        afterEveryLoop();
    }
} // namespace mpf::core
