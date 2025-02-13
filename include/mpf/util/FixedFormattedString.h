/**
 * FixedFormattedString.h
 *
 * @author Patrick Lavigne
 */

#pragma once

#include <array>
#include <format>
#include <utility>

namespace mpf::util {

    template <size_t buffSize, typename CharT = char>
    class FixedFormattedString {
        static_assert(buffSize > 0, "Buffer size must be greater than 0");

    public:
        [[nodiscard]]
        static constexpr size_t bufferSize() {
            return buffSize;
        }

        FixedFormattedString() :
            m_asStringView(m_buffer.begin(), m_buffer.begin()) {
            m_buffer[0] = '\0';
        }

        template <class... ArgsT>
        explicit FixedFormattedString(std::format_string<ArgsT...> const& formatString, ArgsT&&... args) :
            m_asStringView(m_buffer.begin(),
                           std::format_to_n(m_buffer.begin(),
                                            m_buffer.size() - 1,
                                            formatString,
                                            std::forward<ArgsT>(args)...).out) {
            m_buffer[m_asStringView.size()] = '\0';
        }

        // ReSharper disable once CppNonExplicitConversionOperator
        // NOLINTNEXTLINE(*-explicit-constructor)
        explicit(false) operator std::basic_string_view<CharT> const&() const {
            return m_asStringView;
        }

        // ReSharper disable once CppNonExplicitConversionOperator
        // NOLINTNEXTLINE(*-explicit-constructor)
        explicit(false) operator CharT const*() const {
            return m_asStringView.data();
        }

        [[nodiscard]]
        size_t size() const {
            return m_asStringView.size();
        }

        template <class... ArgsT>
        void format(std::format_string<ArgsT...> const& formatString, ArgsT&&... args) {
            m_asStringView = {
                    m_buffer.begin(),
                    std::format_to_n(m_buffer.begin(),
                                     m_buffer.size() - 1,
                                     formatString,
                                     std::forward<ArgsT>(args)...).out
                };
            m_buffer[m_asStringView.size()] = '\0';
        }

    private :
        std::array<CharT, buffSize> m_buffer{0};
        std::basic_string_view<CharT> m_asStringView;
    };

} // namespace mpf::util
