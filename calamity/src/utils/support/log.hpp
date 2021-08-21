#pragma once

#include "zcommon.hpp"

namespace Calamity::Log
{
    enum class Level { Trace, Debug, Info, Warn, Error, Critical };

    class Sink
    {
      public:
        virtual ~Sink() = default;

        virtual void log(Level level, const std::string& msg) = 0;
    };

    class StdoutSink final : public Sink
    {
        explicit StdoutSink();
        ~StdoutSink();

        void log(Level level, const std::string& msg) override;

        std::mutex m_lock;
    };

    class Logger
    {
    };
}  // namespace Calamity::Log
