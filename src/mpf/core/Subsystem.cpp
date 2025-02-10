/**
 * Subsystem.cpp
 *
 * @author Patrick Lavigne
 */

#include "mpf/core/Subsystem.h"
#include "mpf/core/SubsystemList.h"

namespace mpf::core {

    void Subsystem::initialize() {
        // Default empty, override if needed
    }

    void Subsystem::setUp() {
        // Default empty, override if needed
    }

    Subsystem::Subsystem(SubsystemList * const list) noexcept {
        if (list != nullptr) {
            list->registerSubsystem(this);
        }
    }
}
