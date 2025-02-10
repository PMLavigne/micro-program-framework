/**
 * SubsystemList.cpp
 *
 * @author Patrick Lavigne
 */

#include "mpf/core/SubsystemList.h"
#include "mpf/core/Subsystem.h"

namespace mpf::core {

    void SubsystemList::initialize() const {
        for (Subsystem &subsystem: *this) {
            subsystem.initialize();
        }
    }

    void SubsystemList::setUp() const {
        for (Subsystem &subsystem: *this) {
            subsystem.setUp();
        }
    }

    void SubsystemList::work() const {
        for (Subsystem &subsystem: *this) {
            if (subsystem.hasWork()) {
                subsystem.work();
            }
        }
    }

}
