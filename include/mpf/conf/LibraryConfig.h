/**
 * LibraryConfig.h
 *
 * @author Patrick Lavigne
 */
#pragma once

#include <string>
#include <cstdint>

namespace mpf::conf {
    struct library_config_data_t {
        std::string_view const LibraryName;
        std::string_view const VersionString;
        std::uint32_t const VersionMajor;
        std::uint32_t const VersionMinor;
        std::uint32_t const VersionPatch;
    };

    library_config_data_t const & getLibraryConfig();
}
