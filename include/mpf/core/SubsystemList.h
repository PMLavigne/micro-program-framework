/**
 * SubsystemList.h
 *
 * @author Patrick Lavigne
 */

#pragma once

#include <cstddef>

#include "mpf/types/List.h"
#include "mpf/core/Subsystem.h"

namespace mpf::core {
    class SubsystemList final : private types::List<Subsystem> {
        friend class Subsystem;

        void registerSubsystem(Subsystem *const subsystem) {
            addItem(subsystem);
        }

    public:
        SubsystemList() noexcept = default;

        SubsystemList(SubsystemList const &) = delete;

        SubsystemList(SubsystemList &&) = delete;

        ~SubsystemList() override = default;

        void initialize() const;

        void setUp() const;

        void work() const;

        [[nodiscard]]
        size_t getRegisteredSubsystemCount() const {
            return getSize();
        }
    };

}
