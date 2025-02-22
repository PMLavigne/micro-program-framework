/**
 * StringUtil.cpp
 *
 * @author Patrick Lavigne
 */

#include "mpf/util/StringUtil.h"

#include <cstring>

namespace mpf::util {

    std::string_view StringUtil::toHex(uint8_t const byte) {
        numberBuff[0] = HexChars[(byte & 0xF0U) >> 4U];
        numberBuff[1] = HexChars[byte & 0x0FU];
        return {numberBuff.data(), 2};
    }

    size_t StringUtil::toHex(std::span<uint8_t> bytes, std::span<char> out, std::string_view separator) {
        size_t resultLength = 0;
        bool firstLoop = true;
        for (uint8_t const currentByte : bytes) {
            if (firstLoop) {
                firstLoop = false;
            } else if (!separator.empty()) {
                appendString(separator, &resultLength);
                if (resultLength >= out.size()) {
                    addTooLongStringSuffix(out);
                    return resultLength;
                }
            }
            out[resultLength] = HexChars[(currentByte & 0xF0U) >> 4];
            ++resultLength;
            if (resultLength >= out.size()) {
                addTooLongStringSuffix(out);
                return resultLength;
            }
            out[resultLength] = HexChars[currentByte & 0x0FU];
            ++resultLength;
            if (resultLength >= out.size()) {
                addTooLongStringSuffix(out);
                return resultLength;
            }
        }
        return resultLength;
    }

    std::string_view StringUtil::toHex(std::span<uint8_t> const bytes, std::string_view const separator) {
        return { numberBuff.begin(), toHex(bytes, numberBuff, separator) };
    }

    std::string_view StringUtil::toHex(std::span<std::byte> const bytes, std::string_view const separator) {
        size_t resultLength = 0;
        bool firstLoop = true;
        for (std::byte const currentByte : bytes) {
            if (firstLoop) {
                firstLoop = false;
            } else if (!separator.empty()) {
                appendString(separator, &resultLength);
                if (resultLength >= numberBuff.size()) {
                    addTooLongStringSuffix();
                    return {numberBuff.data(), numberBuff.size()};
                }
            }
            numberBuff[resultLength] = HexChars[std::to_integer<uint8_t>((currentByte & std::byte{0xF0U}) >> 4)];
            ++resultLength;
            if (resultLength >= numberBuff.size()) {
                addTooLongStringSuffix();
                return {numberBuff.data(), numberBuff.size()};
            }
            numberBuff[resultLength] = HexChars[std::to_integer<uint8_t>(currentByte & std::byte{0x0FU})];
            ++resultLength;
            if (resultLength >= numberBuff.size()) {
                addTooLongStringSuffix();
                return {numberBuff.data(), numberBuff.size()};
            }
        }
        return {numberBuff.data(), resultLength};
    }

    std::string_view StringUtil::shortToHex(uint16_t const val) {
        numberBuff[0] = HexChars[(val & 0xF000U) >> 12U];
        numberBuff[1] = HexChars[(val & 0x0F00U) >> 8U];
        numberBuff[2] = HexChars[(val & 0x00F0U) >> 4U];
        numberBuff[3] = HexChars[val & 0x000FU];
        return {numberBuff.data(), 4};
    }

    std::string_view StringUtil::longToHex(uint32_t const val) {
        numberBuff[0] = HexChars[(val & 0xF0000000U) >> 28U];
        numberBuff[1] = HexChars[(val & 0x0F000000U) >> 24U];
        numberBuff[2] = HexChars[(val & 0x00F00000U) >> 20U];
        numberBuff[3] = HexChars[(val & 0x000F0000U) >> 16U];
        numberBuff[4] = HexChars[(val & 0x0000F000U) >> 12U];
        numberBuff[5] = HexChars[(val & 0x00000F00U) >> 8U];
        numberBuff[6] = HexChars[(val & 0x000000F0U) >> 4U];
        numberBuff[7] = HexChars[val & 0x0000000FU];
        return {numberBuff.data(), 8};
    }

    std::string_view StringUtil::longLongToHex(uint64_t const value) {
        longLongToHex(value, numberBuff);
        return {numberBuff.data(), 16};
    }

    void StringUtil::longLongToHex(uint64_t const value, std::span<char> out) {
        if (out.empty()) {
            return;
        }
        out[0] = HexChars[(value & 0xF000000000000000ULL) >> 60U];
        if (out.size() == 1) {
            return;
        }
        out[1] = HexChars[(value & 0x0F00000000000000ULL) >> 56U];
        if (out.size() == 2) {
            return;
        }
        out[2] = HexChars[(value & 0x00F0000000000000ULL) >> 52U];
        if (out.size() == 3) {
            return;
        }
        out[3] = HexChars[(value & 0x000F000000000000ULL) >> 48U];
        if (out.size() == 4) {
            return;
        }
        out[4] = HexChars[(value & 0x0000F00000000000ULL) >> 44U];
        if (out.size() == 5) {
            return;
        }
        out[5] = HexChars[(value & 0x00000F0000000000ULL) >> 40U];
        if (out.size() == 6) {
            return;
        }
        out[6] = HexChars[(value & 0x000000F000000000ULL) >> 36U];
        if (out.size() == 7) {
            return;
        }
        out[7] = HexChars[(value & 0x0000000F00000000ULL) >> 32U];
        if (out.size() == 8) {
            return;
        }
        out[8] = HexChars[(value & 0x00000000F0000000ULL) >> 28U];
        if (out.size() == 9) {
            return;
        }
        out[9] = HexChars[(value & 0x000000000F000000ULL) >> 24U];
        if (out.size() == 10) {
            return;
        }
        out[10] = HexChars[(value & 0x0000000000F00000ULL) >> 20U];
        if (out.size() == 11) {
            return;
        }
        out[11] = HexChars[(value & 0x00000000000F0000ULL) >> 16U];
        if (out.size() == 12) {
            return;
        }
        out[12] = HexChars[(value & 0x000000000000F000ULL) >> 12U];
        if (out.size() == 13) {
            return;
        }
        out[13] = HexChars[(value & 0x0000000000000F00ULL) >> 8U];
        if (out.size() == 14) {
            return;
        }
        out[14] = HexChars[(value & 0x00000000000000F0ULL) >> 4U];
        if (out.size() == 15) {
            return;
        }
        out[15] = HexChars[value & 0x000000000000000FULL];
    }

    size_t StringUtil::copyToFixedLengthBuffer(std::string_view const& stringView,
                                               char* const dest,
                                               size_t const destLength) {
        size_t copiedBytes = 0;
        for (; copiedBytes < stringView.length() && copiedBytes < destLength; ++copiedBytes) {
            dest[copiedBytes] = stringView[copiedBytes];
        }
        for (size_t iter = copiedBytes; iter < destLength; ++iter) {
            dest[iter] = 0;
        }
        return copiedBytes;
    }

    std::string_view StringUtil::toBits(uint8_t const byte) {
        for (uint8_t iter = 0; iter < 8; ++iter) {
            bitsBuff[iter] = byte & (1U << (7U - iter)) ? '1' : '0';
        }
        return {bitsBuff.data(), 8};
    }

    std::string_view StringUtil::formatTicks(uint64_t const ticks) {
        if (auto [ptrToEnd, errorCode] = std::to_chars(numberBuff.data(),
                                                       numberBuff.data() + numberBuff.size(),
                                                       ticks);
            errorCode == std::errc()) {
            char fractionalPart[6] {'0'};
            std::string_view const unformattedResult = {numberBuff.data(), ptrToEnd};

            size_t fractionalPartPos = 6;
            for (size_t iter = unformattedResult.length() - 1; iter > 0; --iter) {
                --fractionalPartPos;
                fractionalPart[fractionalPartPos] = unformattedResult[iter];
                if (fractionalPartPos <= 0) {
                    break;
                }
            }

            if (unformattedResult.length() <= 6) {
                numberBuff[0] = '0';
                numberBuff[1] = '.';
                for (uint8_t iter = 0; iter < 6; ++iter) {
                    numberBuff[2 + iter] = fractionalPart[iter];
                }
                ptrToEnd = numberBuff.data() + 8;
            } else {
                ptrToEnd -= 6;
                *ptrToEnd = '.';
                ++ptrToEnd;
                for (uint8_t iter = 0;
                     iter < 6 && static_cast<size_t>(ptrToEnd - numberBuff.data()) < numberBuff.size();
                     ++iter) {
                    *ptrToEnd = fractionalPart[iter];
                    ++ptrToEnd;
                }
            }

            return {numberBuff.data(), ptrToEnd};
        }
        return "ERR";
    }

    bool StringUtil::appendString(std::string_view const string, size_t* const numberBufferPos) {
        for (char const currentChar : string) {
            if (*numberBufferPos >= numberBuff.size()) {
                return false;
            }
            numberBuff[*numberBufferPos] = currentChar;
            ++*numberBufferPos;
        }
        return true;
    }

    void StringUtil::addTooLongStringSuffix() {
        addTooLongStringSuffix(numberBuff);
    }

    void StringUtil::addTooLongStringSuffix(std::span<char> out) {
        size_t appendPos = (out.size() - AppendIfTooLong.size()) - 1;
        for (char const currentChar : AppendIfTooLong) {
            out[appendPos] = currentChar;
            ++appendPos;
        }
    }
}
