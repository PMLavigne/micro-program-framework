/**
 * Logging.cpp
 */

#include "mpf/core/Logging.h"

#include <cstdio>

#include "mpf/util/StringUtil.h"

using std::string_view;
using mpf::util::StringUtil;

namespace mpf::core {

    static constexpr string_view NewLine{"\r\n"};
    static constexpr string_view Space{" "};
    static constexpr string_view TagSeparator{" | "};
    static constexpr string_view ErrorTag{"[E]"};
    static constexpr string_view WarnTag{"[W]"};
    static constexpr string_view InfoTag{"[I]"};
    static constexpr string_view DebugTag{"[D]"};
    static constexpr string_view TraceTag{"[T]"};

    void LogWriter::writeTag(std::string_view const name) {
        if (Logger::getLogSink() != nullptr) {
            Logger::getLogSink()->write(name);
            Logger::getLogSink()->write(TagSeparator);
        }
    }

    void LogWriter::writeTime() {
        if (Logger::getLogSink() != nullptr) {
            Logger::getLogSink()->writeTimeStamp();
            Logger::getLogSink()->write(Space);
        }
    }

    void LogWriter::writeLevel(LogLevel const level) {
        auto const* logSink = Logger::getLogSink();
        if (logSink == nullptr) {
            return;
        }

        switch (level) {
            using enum LogLevel;
        case Error: {
            logSink->write(ErrorTag);
        } break;

        case Warn: {
            logSink->write(WarnTag);
        } break;

        case Info: {
            logSink->write(InfoTag);
        } break;

        case Debug: {
            logSink->write(DebugTag);
        } break;

        case Trace: {
            logSink->write(TraceTag);
        } break;

        default:
            break;
        }

        logSink->write(Space);
    }

    void LogWriter::println(std::string_view const& printStr) {
        print(printStr);
        newLine();
    }

    void LogWriter::print(std::string_view const & printStr) {
        if (Logger::getLogSink() != nullptr) {
            Logger::getLogSink()->write(printStr);
        }
    }

    void LogWriter::newLine() {
        if (Logger::getLogSink() != nullptr) {
            Logger::getLogSink()->write(NewLine);
        }
    }

    void LogWriter::flush() {
        if (Logger::getLogSink() != nullptr) {
            Logger::getLogSink()->flush();
        }
    }

    void Logger::setLogSink(LogSink const* logSink) {
        m_logSink = logSink;
    }

    LogSink const* Logger::getLogSink() {
        return m_logSink;
    }
} // namespace mpf::core
