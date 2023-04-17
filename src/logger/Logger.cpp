#include "Logger.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace MuVi {
    std::shared_ptr<spdlog::logger> Logger::s_AudioWorkerLogger;
    std::shared_ptr<spdlog::logger> Logger::s_FftWorkerLogger;
    std::shared_ptr<spdlog::logger> Logger::s_RendererWorkerLogger;

    void Logger::Init() {
        spdlog::set_pattern("%^[%T] %n: %v%$");

        s_AudioWorkerLogger = spdlog::stdout_color_mt("AudioWorker");
        s_AudioWorkerLogger->set_level(spdlog::level::trace);

        s_FftWorkerLogger = spdlog::stdout_color_mt("FftWorker");
        s_FftWorkerLogger->set_level(spdlog::level::trace);

        s_RendererWorkerLogger = spdlog::stdout_color_mt("RendererWorker");
        s_RendererWorkerLogger->set_level(spdlog::level::trace);
    }
}