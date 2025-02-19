/**
 * Types.h
 *
 * @author Patrick Lavigne
 */

#pragma once
#include <concepts>

namespace mpf::concepts {

    template<typename ValueT>
    concept Numeric = std::integral<ValueT> || std::floating_point<ValueT>;

}
