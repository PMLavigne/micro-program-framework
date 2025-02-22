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

#define LOGGER(tag) static constexpr std::string_view _LOGGER_TAG { #tag }

#define MPF_DO_NOTHING ((void)0)

#define MPF_LOG(level, msg, ...) if constexpr (mpf::core::Logger::level ## Enabled) \
    mpf::core::Logger::level::println(_LOGGER_TAG, (msg)__VA_OPT__(, ) __VA_ARGS__); \
    else MPF_DO_NOTHING

#define MPF_LOGN(level, msg, ...) if constexpr (mpf::core::Logger::level ## Enabled) \
    mpf::core::Logger::level::print(_LOGGER_TAG, (msg)__VA_OPT__(, ) __VA_ARGS__); \
    else MPF_DO_NOTHING

#define MPF_LOGC(level, msg, ...) if constexpr (mpf::core::Logger::level ## Enabled) \
    mpf::core::Logger::level::printlnc((msg)__VA_OPT__(, ) __VA_ARGS__); \
    else MPF_DO_NOTHING

#define MPF_LOGCN(level, msg, ...) if constexpr (mpf::core::Logger::level ## Enabled) \
    mpf::core::Logger::level::printc((msg)__VA_OPT__(, ) __VA_ARGS__); \
    else MPF_DO_NOTHING

#define MPF_LOGCRLF(level) if constexpr (mpf::core::Logger::level ## Enabled) \
    mpf::core::Logger::level::newLine(); \
    else MPF_DO_NOTHING

#define MPF_LOGF(level) if constexpr (mpf::core::Logger::level ## Enabled) \
    mpf::core::Logger::level::flush(); \
    else MPF_DO_NOTHING

#define ERROR(msg, ...) MPF_LOG(Error, msg __VA_OPT__(, ) __VA_ARGS__)
#define ERRORN(msg, ...) MPF_LOGN(Error, msg __VA_OPT__(, ) __VA_ARGS__)
#define ERRORC(msg, ...) MPF_LOGC(Error, msg __VA_OPT__(, ) __VA_ARGS__)
#define ERRORCN(msg, ...) MPF_LOGCN(Error, msg __VA_OPT__(, ) __VA_ARGS__)
#define ERRORCRLF() MPF_LOGCRLF(Error)
#define ERRORF() MPF_LOGF(Error)

#define WARN(msg, ...) MPF_LOG(Warn, msg __VA_OPT__(, ) __VA_ARGS__)
#define WARNN(msg, ...) MPF_LOGN(Warn, msg __VA_OPT__(, ) __VA_ARGS__)
#define WARNC(msg, ...) MPF_LOGC(Warn, msg __VA_OPT__(, ) __VA_ARGS__)
#define WARNCN(msg, ...) MPF_LOGCN(Warn, msg __VA_OPT__(, ) __VA_ARGS__)
#define WARNCRLF() MPF_LOGCRLF(Warn)
#define WARNF() MPF_LOGF(Warn)

#define INFO(msg, ...) MPF_LOG(Info, msg __VA_OPT__(, ) __VA_ARGS__)
#define INFON(msg, ...) MPF_LOGN(Info, msg __VA_OPT__(, ) __VA_ARGS__)
#define INFOC(msg, ...) MPF_LOGC(Info, msg __VA_OPT__(, ) __VA_ARGS__)
#define INFOCN(msg, ...) MPF_LOGCN(Info, msg __VA_OPT__(, ) __VA_ARGS__)
#define INFOCRLF() MPF_LOGCRLF(Info)
#define INFOF() MPF_LOGF(Info)

#define DEBUG(msg, ...) MPF_LOG(Debug, msg __VA_OPT__(, ) __VA_ARGS__)
#define DEBUGN(msg, ...) MPF_LOGN(Debug, msg __VA_OPT__(, ) __VA_ARGS__)
#define DEBUGC(msg, ...) MPF_LOGC(Debug, msg __VA_OPT__(, ) __VA_ARGS__)
#define DEBUGCN(msg, ...) MPF_LOGCN(Debug, msg __VA_OPT__(, ) __VA_ARGS__)
#define DEBUGCRLF() MPF_LOGCRLF(Debug)
#define DEBUGF() MPF_LOGF(Debug)

#define TRACE(msg, ...) MPF_LOG(Trace, msg __VA_OPT__(, ) __VA_ARGS__)
#define TRACEN(msg, ...) MPF_LOGN(Trace, msg __VA_OPT__(, ) __VA_ARGS__)
#define TRACEC(msg, ...) MPF_LOGC(Trace, msg __VA_OPT__(, ) __VA_ARGS__)
#define TRACECN(msg, ...) MPF_LOGCN(Trace, msg __VA_OPT__(, ) __VA_ARGS__)
#define TRACECRLF() MPF_LOGCRLF(Trace)
#define TRACEF() MPF_LOGF(Trace)



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

        static void println(std::string_view const& printStr);

        template <typename... ArgT>
        static void println(std::format_string<ArgT...> const& formatString, ArgT&&... args) {
            print<ArgT...>(formatString, std::forward<ArgT>(args)...);
            newLine();
        }

        static void print(std::string_view const& printStr);

        template <typename... ArgT>
        static void print(std::format_string<ArgT...> const& formatString, ArgT&&... args) {
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
                            ArgT&&... args) {
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
                          ArgT&&... args) {
            if constexpr (level <= activeLevel) {
                LogWriter::writePrefix<level>(name);
                LogWriter::print<ArgT...>(formatString, std::forward<ArgT>(args)...);
            }
        }

        static void printlnc(std::string_view const& message) {
            if constexpr (level <= activeLevel) {
                LogWriter::println(message);
            }
        }

        template <typename... ArgT>
        static void printlnc(std::format_string<ArgT...> const& formatString, ArgT&&... args) {
            if constexpr (level <= activeLevel) {
                LogWriter::println<ArgT...>(formatString, std::forward<ArgT>(args)...);
            }
        }

        static void printc(std::string_view const& message) {
            if constexpr (level <= activeLevel) {
                LogWriter::print(message);
            }
        }

        template <typename... ArgT>
        static void printc(std::format_string<ArgT...> const& formatString, ArgT&&... args) {
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
    public:
        static constexpr auto ActiveLevel = static_cast<LogLevel>(MPF_LOG_VALUE);

        static constexpr bool ErrorEnabled = ActiveLevel >= LogLevel::Error;

        static constexpr bool WarnEnabled = ActiveLevel >= LogLevel::Warn;

        static constexpr bool InfoEnabled = ActiveLevel >= LogLevel::Info;

        static constexpr bool DebugEnabled = ActiveLevel >= LogLevel::Debug;

        static constexpr bool TraceEnabled = ActiveLevel >= LogLevel::Trace;

        using Error = LogLevelLogger<LogLevel::Error, ActiveLevel>;

        using Warn = LogLevelLogger<LogLevel::Warn, ActiveLevel>;

        using Info = LogLevelLogger<LogLevel::Info, ActiveLevel>;

        using Debug = LogLevelLogger<LogLevel::Debug, ActiveLevel>;

        using Trace = LogLevelLogger<LogLevel::Trace, ActiveLevel>;

        static void setLogSink(LogSink const* logSink);

        static LogSink const* getLogSink();

        Logger() noexcept = delete;

        ~Logger() = delete;

    private:
        static inline LogSink const* m_logSink = nullptr;
    };

} // namespace mpf::core
