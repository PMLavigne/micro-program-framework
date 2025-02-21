/**
 * FixedPackedString.h
 *
 * @author Patrick Lavigne
 */

#pragma once

#include <cassert>
#include <string_view>
#include <concepts>
#include <format>
#include <limits>
#include <algorithm>

// ReSharper disable once CppUnusedIncludeDirective
#include <compare>

#include "mpf/util/macros.h"

namespace mpf::core {
    template <std::unsigned_integral auto maxLength, class CharT = char, class LenT = decltype(maxLength)>
    class PACKED FixedPackedString {
        static_assert(maxLength > 0, "Max length must be greater than 0");

    public:
        using LengthT = LenT;

        using CharacterT = CharT;

        using StringViewT = std::basic_string_view<CharacterT>;

        static constexpr LengthT MaxLength = maxLength;

        FixedPackedString() = default;

        constexpr explicit(false) FixedPackedString(StringViewT const& str) noexcept :
            m_length(std::min(maxLength, static_cast<LengthT>(str.size()))) {
            std::copy(str.cbegin(), str.cbegin() + m_length,  m_data.begin());
        }

        template <class... ArgsT>
        explicit FixedPackedString(std::format_string<ArgsT...> const& formatString, ArgsT&&... args) {
            m_length = static_cast<LengthT>(std::format_to_n(m_data.begin(),
                                                             maxLength,
                                                             formatString,
                                                             std::forward<ArgsT>(args)...).size);

        }

        // ReSharper disable once CppNonExplicitConversionOperator
        // NOLINTNEXTLINE(*-explicit-constructor)
        explicit(false) operator StringViewT() const {
            return StringViewT{m_data.data(), m_length};
        }

        constexpr bool operator==(FixedPackedString const& other) const noexcept {
            return *this <=> other == std::strong_ordering::equal;
        }

        constexpr auto operator<=>(FixedPackedString const& other) const noexcept {
            if (m_length != other.m_length) {
                return m_length <=> other.m_length;
            }

            if (m_length == 0) {
                return std::strong_ordering::equal;
            }

            return static_cast<StringViewT>(*this) <=> static_cast<StringViewT>(other);
        }

        FixedPackedString& operator=(StringViewT const& str) {
            assert(str.size() <= std::numeric_limits<LengthT>::max());
            m_length = std::min(maxLength, str.size());
            std::copy(str.cbegin(), str.cbegin() + m_length, m_data.begin());
            return *this;
        }


        template <typename CopyCharacterT, size_t arraySize>
        void copyTo(std::array<CopyCharacterT, arraySize> & buff) const {
            copyTo<CopyCharacterT, arraySize>(std::span<CopyCharacterT, arraySize>(buff));
        }

        template <typename CopyCharacterT, size_t spanExtent = std::dynamic_extent>
        void copyTo(std::span<CopyCharacterT, spanExtent> buff) const {
            static_assert(sizeof(CopyCharacterT) == sizeof(CharacterT),
                          "Cannot copy to a buffer with a different character size");
            if (buff.empty()) {
                return;
            }
            size_t const charsToCopy = std::min(static_cast<size_t>(m_length), buff.size() - 1);
            if (charsToCopy > 0) {
                std::copy(m_data.cbegin(), m_data.cbegin() + charsToCopy, buff.begin());
            }
            buff[charsToCopy] = '\0';
        }

        [[nodiscard]]
        LengthT length() const noexcept {
            return m_length;
        }

    private:
        LengthT m_length = 0;

        std::array<CharacterT, maxLength> m_data {};
    };
}

