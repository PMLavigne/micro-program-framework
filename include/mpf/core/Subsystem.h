/**
 * Subsystem.h
 *
 * @author Patrick Lavigne
 */

#pragma once

#include "mpf/core/List.h"

namespace mpf::core {

    class SubsystemList;

    class Subsystem : public List<Subsystem>::Item {

    public:
        Subsystem(Subsystem const &) = delete;

        Subsystem(Subsystem &&) = delete;

        ~Subsystem() override = default;

        virtual void initialize();

        virtual void setUp();

        [[nodiscard]]
        virtual bool hasWork() const = 0;

        virtual void work() = 0;

    protected:
        explicit Subsystem(SubsystemList * list) noexcept;
    };

}
