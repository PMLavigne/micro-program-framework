/**
 * Logging.h
 *
 * @author Patrick Lavigne
 */

#pragma once

#include <format>
#include <string_view>

#include "mpf/core/LogSink.h"

#ifndef MPF_LOG_VALUE
#define MPF_LOG_VALUE 0
#endif

#define MPF_LOG_LEVEL_NONE None
#define MPF_LOG_VALUE_NONE 0
#define MPF_LOG_LEVEL_ERROR Error
#define MPF_LOG_VALUE_ERROR 1
#define MPF_LOG_LEVEL_WARN Warn
#define MPF_LOG_VALUE_WARN 2
#define MPF_LOG_LEVEL_INFO Info
#define MPF_LOG_VALUE_INFO 3
#define MPF_LOG_LEVEL_DEBUG Debug
#define MPF_LOG_VALUE_DEBUG 4
#define MPF_LOG_LEVEL_TRACE Trace
#define MPF_LOG_VALUE_TRACE 5

#if MPF_LOG_VALUE == MPF_LOG_VALUE_NONE
#define MPF_LOG_LEVEL MPF_LOG_LEVEL_NONE
#elif MPF_LOG_VALUE == MPF_LOG_VALUE_ERROR
#define MPF_LOG_LEVEL MPF_LOG_LEVEL_ERROR
#define MPF_DEBUG_LOGGING_ENABLED
#elif MPF_LOG_VALUE == MPF_LOG_VALUE_WARN
#define MPF_LOG_LEVEL MPF_LOG_LEVEL_WARN
#define MPF_DEBUG_LOGGING_ENABLED
#elif MPF_LOG_VALUE == MPF_LOG_VALUE_INFO
#define MPF_LOG_LEVEL MPF_LOG_LEVEL_INFO
#define MPF_DEBUG_LOGGING_ENABLED
#elif MPF_LOG_VALUE == MPF_LOG_VALUE_DEBUG
#define MPF_LOG_LEVEL MPF_LOG_LEVEL_DEBUG
#define MPF_DEBUG_LOGGING_ENABLED
#elif MPF_LOG_VALUE == MPF_LOG_VALUE_TRACE
#define MPF_LOG_LEVEL MPF_LOG_LEVEL_TRACE
#define MPF_DEBUG_LOGGING_ENABLED
#else
#define MPF_LOG_LEVEL MPF_LOG_LEVEL_NONE
#endif

#if MPF_LOG_VALUE >= MPF_LOG_VALUE_ERROR
#define MPF_LOG_LEVEL_ERROR_ENABLED
#endif
#if MPF_LOG_VALUE >= MPF_LOG_VALUE_WARN
#define MPF_LOG_LEVEL_WARN_ENABLED
#endif
#if MPF_LOG_VALUE >= MPF_LOG_VALUE_INFO
#define MPF_LOG_LEVEL_INFO_ENABLED
#endif
#if MPF_LOG_VALUE >= MPF_LOG_VALUE_DEBUG
#define MPF_LOG_LEVEL_DEBUG_ENABLED
#endif
#if MPF_LOG_VALUE >= MPF_LOG_VALUE_TRACE
#define MPF_LOG_LEVEL_TRACE_ENABLED
#endif

#define LOGGER(tag)                                                                                                    \
    static inline std::string_view _LOGGER_TAG { #tag }

#define MPF_DO_NOTHING ((void)0)

#if MPF_LOG_VALUE >= MPF_LOG_VALUE_ERROR
#define ERROR(msg, ...) mpf::core::Logger::Error::println(_LOGGER_TAG, (msg)__VA_OPT__(, ) __VA_ARGS__)
#define ERRORN(msg, ...) mpf::core::Logger::Error::print(_LOGGER_TAG, (msg)__VA_OPT__(, ) __VA_ARGS__)
#define ERRORC(msg, ...) mpf::core::Logger::Error::printlnc((msg)__VA_OPT__(, ) __VA_ARGS__)
#define ERRORCN(msg, ...) mpf::core::Logger::Error::printc((msg)__VA_OPT__(, ) __VA_ARGS__)
#define ERRORCRLF() mpf::core::Logger::Error::newLine()
#define ERRORF() mpf::core::Logger::Error::flush()
#else
#define ERROR(msg, ...) MPF_DO_NOTHING
#define ERRORN(msg, ...) MPF_DO_NOTHING
#define ERRORC(msg, ...) MPF_DO_NOTHING
#define ERRORCN(msg, ...) MPF_DO_NOTHING
#define ERRORCRLF() MPF_DO_NOTHING
#define ERRORF() MPF_DO_NOTHING
#endif

#if MPF_LOG_VALUE >= MPF_LOG_VALUE_WARN
#define WARN(msg, ...) mpf::core::Logger::Warn::println(_LOGGER_TAG, (msg)__VA_OPT__(, ) __VA_ARGS__)
#define WARNN(msg, ...) mpf::core::Logger::Warn::print(_LOGGER_TAG, (msg)__VA_OPT__(, ) __VA_ARGS__)
#define WARNC(msg, ...) mpf::core::Logger::Warn::printlnc((msg)__VA_OPT__(, ) __VA_ARGS__)
#define WARNCN(msg, ...) mpf::core::Logger::Warn::printc((msg)__VA_OPT__(, ) __VA_ARGS__)
#define WARNCRLF() mpf::core::Logger::Warn::newLine()
#define WARNF() mpf::core::Logger::Warn::flush()
#else
#define WARN(msg, ...) MPF_DO_NOTHING
#define WARNN(msg, ...) MPF_DO_NOTHING
#define WARNC(msg, ...) MPF_DO_NOTHING
#define WARNCN(msg, ...) MPF_DO_NOTHING
#define WARNCRLF() MPF_DO_NOTHING
#define WARNF() MPF_DO_NOTHING
#endif

#if MPF_LOG_VALUE >= MPF_LOG_VALUE_INFO
#define INFO(msg, ...) mpf::core::Logger::Info::println(_LOGGER_TAG, (msg)__VA_OPT__(, ) __VA_ARGS__)
#define INFON(msg, ...) mpf::core::Logger::Info::print(_LOGGER_TAG, (msg)__VA_OPT__(, ) __VA_ARGS__)
#define INFOC(msg, ...) mpf::core::Logger::Info::printlnc((msg)__VA_OPT__(, ) __VA_ARGS__)
#define INFOCN(msg, ...) mpf::core::Logger::Info::printc((msg)__VA_OPT__(, ) __VA_ARGS__)
#define INFOCRLF() mpf::core::Logger::Info::newLine()
#define INFOF() mpf::core::Logger::Info::flush()
#else
#define INFO(msg, ...) MPF_DO_NOTHING
#define INFON(msg, ...) MPF_DO_NOTHING
#define INFOC(msg, ...) MPF_DO_NOTHING
#define INFOCN(msg, ...) MPF_DO_NOTHING
#define INFOCRLF() MPF_DO_NOTHING
#define INFOF() MPF_DO_NOTHING
#endif

#if MPF_LOG_VALUE >= MPF_LOG_VALUE_DEBUG
#define DEBUG(msg, ...) mpf::core::Logger::Debug::println(_LOGGER_TAG, (msg)__VA_OPT__(, ) __VA_ARGS__)
#define DEBUGN(msg, ...) mpf::core::Logger::Debug::print(_LOGGER_TAG, (msg)__VA_OPT__(, ) __VA_ARGS__)
#define DEBUGC(msg, ...) mpf::core::Logger::Debug::printlnc((msg)__VA_OPT__(, ) __VA_ARGS__)
#define DEBUGCN(msg, ...) mpf::core::Logger::Debug::printc((msg)__VA_OPT__(, ) __VA_ARGS__)
#define DEBUGCRLF() mpf::core::Logger::Debug::newLine()
#define DEBUGF() mpf::core::Logger::Debug::flush()
#else
#define DEBUG(msg, ...) MPF_DO_NOTHING
#define DEBUGN(msg, ...) MPF_DO_NOTHING
#define DEBUGC(msg, ...) MPF_DO_NOTHING
#define DEBUGCN(msg, ...) MPF_DO_NOTHING
#define DEBUGCRLF() MPF_DO_NOTHING
#define DEBUGF() MPF_DO_NOTHING
#endif

#if MPF_LOG_VALUE >= MPF_LOG_VALUE_TRACE
#define TRACE(msg, ...) mpf::core::Logger::Trace::println(_LOGGER_TAG, (msg)__VA_OPT__(, ) __VA_ARGS__)
#define TRACEN(msg, ...) mpf::core::Logger::Trace::print(_LOGGER_TAG, (msg)__VA_OPT__(, ) __VA_ARGS__)
#define TRACEC(msg, ...) mpf::core::Logger::Trace::printlnc((msg)__VA_OPT__(, ) __VA_ARGS__)
#define TRACECN(msg, ...) mpf::core::Logger::Trace::printc((msg)__VA_OPT__(, ) __VA_ARGS__)
#define TRACECRLF() mpf::core::Logger::Trace::newLine()
#define TRACEF() mpf::core::Logger::Trace::flush()
#else
#define TRACE(msg, ...) MPF_DO_NOTHING
#define TRACEN(msg, ...) MPF_DO_NOTHING
#define TRACEC(msg, ...) MPF_DO_NOTHING
#define TRACECN(msg, ...) MPF_DO_NOTHING
#define TRACECRLF() MPF_DO_NOTHING
#define TRACEF() MPF_DO_NOTHING
#endif

namespace mpf::core {

    enum class LogLevel : uint8_t {
        None = 0,
        Error = 1,
        Warn = 2,
        Info = 3,
        Debug = 4,
        Trace = 5
    };

    class LogWriter {
        static constexpr std::size_t FormatBufferSize = 1024;

        static inline std::array<char, FormatBufferSize> FormatBuffer{};

        template <LogLevel level, LogLevel activeLevel>
        friend class LogLevelLogger;

        static void writeTag(std::string_view name);

        static void writeTime();

        static void writeLevel(LogLevel level);

        template <LogLevel level>
        static void writePrefix(std::string_view const& name) {
            writeTime();
            writeLevel(level);
            writeTag(name);
        }

        static void println(std::string_view const & printStr);

        template <typename... ArgT>
        static void println(std::format_string<ArgT...> const& formatString, ArgT &&... args) {
            print<ArgT...>(formatString, std::forward<ArgT>(args)...);
            newLine();
        }

        static void print(std::string_view const & printStr);

        template <typename... ArgT>
        static void print(std::format_string<ArgT...> const& formatString, ArgT &&... args) {
            std::format_to_n_result const result =
                std::format_to_n(FormatBuffer.begin(), FormatBuffer.size(), formatString, std::forward<ArgT>(args)...);
            LogWriter::print({FormatBuffer.begin(), result.out});
        }

        static void newLine();

        static void flush();

    public:
        LogWriter() = delete;
    };

    template <LogLevel level, LogLevel activeLevel>
    class LogLevelLogger {
    public:
        static void println(std::string_view const& name, std::string_view const& message) {
            if constexpr (level <= activeLevel) {
                LogWriter::writePrefix<level>(name);
                LogWriter::println(message);
            }
        }

        template <typename... ArgT>
        static void println(std::string_view const& name,
                            std::format_string<ArgT...> const& formatString,
                            ArgT &&... args) {
            if constexpr (level <= activeLevel) {
                LogWriter::writePrefix<level>(name);
                LogWriter::println<ArgT...>(formatString, std::forward<ArgT>(args)...);
            }
        }

        static void print(std::string_view const& name, std::string_view const& message) {
            if constexpr (level <= activeLevel) {
                LogWriter::writePrefix<level>(name);
                LogWriter::print(message);
            }
        }

        template <typename... ArgT>
        static void print(std::string_view const& name,
                          std::format_string<ArgT...> const& formatString,
                          ArgT &&... args) {
            if constexpr (level <= activeLevel) {
                LogWriter::writePrefix<level>(name);
                LogWriter::print<ArgT...>(formatString, std::forward<ArgT>(args)...);
            }
        }

        static void printlnc(std::string_view const & message) {
            if constexpr (level <= activeLevel) {
                LogWriter::println(message);
            }
        }

        template <typename... ArgT>
        static void printlnc(std::format_string<ArgT...> const& formatString, ArgT &&... args) {
            if constexpr (level <= activeLevel) {
                LogWriter::println<ArgT...>(formatString, std::forward<ArgT>(args)...);
            }
        }

        static void printc(std::string_view const & message) {
            if constexpr (level <= activeLevel) {
                LogWriter::print(message);
            }
        }

        template <typename... ArgT>
        static void printc(std::format_string<ArgT...> const& formatString, ArgT &&... args) {
            if constexpr (level <= activeLevel) {
                LogWriter::print<ArgT...>(formatString, std::forward<ArgT>(args)...);
            }
        }

        static void newLine() {
            if constexpr (level <= activeLevel) {
                LogWriter::newLine();
            }
        }

        static void flush() {
            if constexpr (level <= activeLevel) {
                LogWriter::flush();
            }
        }
    };

    class Logger {
        static constexpr auto ActiveLevel = LogLevel::MPF_LOG_LEVEL;

        static inline LogSink const * m_logSink = nullptr;
    public:
        using Error = LogLevelLogger<LogLevel::Error, ActiveLevel>;

        using Warn = LogLevelLogger<LogLevel::Warn, ActiveLevel>;

        using Info = LogLevelLogger<LogLevel::Info, ActiveLevel>;

        using Debug = LogLevelLogger<LogLevel::Debug, ActiveLevel>;

        using Trace = LogLevelLogger<LogLevel::Trace, ActiveLevel>;

        static void setLogSink(LogSink const * logSink);

        static LogSink const * getLogSink();

        Logger() noexcept = delete;

        ~Logger() = delete;
    };

} // namespace mpf::core
