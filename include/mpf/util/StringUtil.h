/**
 * StringUtil.h
 *
 * @author Patrick Lavigne
 */

#pragma once

#include <cstdint>
#include <cstddef>
#include <string_view>
#include <array>
#include <charconv>
#include <span>
#include <concepts>

namespace mpf::util {

    class StringUtil {
        static constexpr std::array HexChars{
                '0',
                '1',
                '2',
                '3',
                '4',
                '5',
                '6',
                '7',
                '8',
                '9',
                'A',
                'B',
                'C',
                'D',
                'E',
                'F'
        };

        static constexpr std::string_view const AppendIfTooLong = "...";

        inline static std::array<char, 64> numberBuff { 0 };

        inline static std::array<char, 8> bitsBuff { 0 };

        static bool appendString(std::string_view string, size_t * numberBufferPos);

        static void addTooLongStringSuffix();

        static void addTooLongStringSuffix(std::span<char> out);

    public:
        template<std::integral CanCastToByteT>
        static std::string_view toHex(CanCastToByteT value) {
            return toHex(static_cast<uint8_t>(value));
        }

        static std::string_view toHex(uint8_t byte);

        static size_t toHex(std::span<uint8_t> bytes, std::span<char> out, std::string_view separator = " ");

        static std::string_view toHex(std::span<uint8_t> bytes, std::string_view separator = " ");

        static std::string_view toHex(std::span<std::byte> bytes, std::string_view separator = " ");

        template<std::integral CanCastToShortT>
        static std::string_view shortToHex(CanCastToShortT value) {
            return shortToHex(static_cast<uint16_t>(value));
        }

        static std::string_view shortToHex(uint16_t value);

        template<std::integral CanCastToLongT>
        static std::string_view longToHex(CanCastToLongT value) {
            return longToHex(static_cast<uint32_t>(value));
        }

        static std::string_view longToHex(uint32_t value);

        template<std::integral CanCastToLongLongT>
        static std::string_view longLongToHex(CanCastToLongLongT value) {
            return longLongToHex(static_cast<uint64_t>(value));
        }

        static std::string_view longLongToHex(uint64_t value);

        static void longLongToHex(uint64_t value, std::span<char> out);

        static std::string_view toBits(uint8_t byte);

        static std::string_view formatTicks(uint64_t ticks);

        template<std::integral IntT>
        static std::string_view toString(IntT integerValue) {
            if (auto [ptrToEnd, errorCode] = std::to_chars(numberBuff.data(),
                                                           numberBuff.data() + numberBuff.size(),
                                                           integerValue);
                    errorCode == std::errc()) {
                return { numberBuff.data(), ptrToEnd };
            }
            return "ERR";
        }

        template<std::floating_point FloatT>
        static std::string_view toString(FloatT const doubleValue) {
            if (auto [ptrToEnd, errorCode] = std::to_chars(numberBuff.data(),
                                                           numberBuff.data() + numberBuff.size(),
                                                           doubleValue);
                    errorCode == std::errc()) {
                return { numberBuff.data(), ptrToEnd };
            } else {
                return "ERR";
            }
        }

        static void padEnd(char *buff, char padChar, uint8_t count);

        static size_t copyToFixedLengthBuffer(std::string_view const & stringView, char * dest, size_t destLength);

        StringUtil() = delete;

        ~StringUtil() = delete;
    };

}
