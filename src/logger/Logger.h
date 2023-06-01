#pragma once

#include <memory>

#include "spdlog/spdlog.h"

namespace MuVi {
    class Logger {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetAudioWorkerLogger() { return s_AudioWorkerLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetFftWorkerLogger() { return s_FftWorkerLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetRendererWorkerLogger() { return s_RendererWorkerLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_AudioWorkerLogger;
        static std::shared_ptr<spdlog::logger> s_FftWorkerLogger;
        static std::shared_ptr<spdlog::logger> s_RendererWorkerLogger;
    };
}

#define MUVI_AUDIO_TRACE(...)       ::MuVi::Logger::GetAudioWorkerLogger()->trace(__VA_ARGS__)
#define MUVI_AUDIO_INFO(...)        ::MuVi::Logger::GetAudioWorkerLogger()->info(__VA_ARGS__)
#define MUVI_AUDIO_WARN(...)        ::MuVi::Logger::GetAudioWorkerLogger()->warn(__VA_ARGS__)
#define MUVI_AUDIO_ERROR(...)       ::MuVi::Logger::GetAudioWorkerLogger()->error(__VA_ARGS__)
#define MUVI_AUDIO_CRITICAL(...)    ::MuVi::Logger::GetAudioWorkerLogger()->critical(__VA_ARGS__)

#define MUVI_FFT_TRACE(...)         ::MuVi::Logger::GetFftWorkerLogger()->trace(__VA_ARGS__)
#define MUVI_FFT_INFO(...)          ::MuVi::Logger::GetFftWorkerLogger()->info(__VA_ARGS__)
#define MUVI_FFT_WARN(...)          ::MuVi::Logger::GetFftWorkerLogger()->warn(__VA_ARGS__)
#define MUVI_FFT_ERROR(...)         ::MuVi::Logger::GetFftWorkerLogger()->error(__VA_ARGS__)
#define MUVI_FFT_CRITICAL(...)      ::MuVi::Logger::GetFftWorkerLogger()->critical(__VA_ARGS__)

#define MUVI_RENDERER_TRACE(...)    ::MuVi::Logger::GetRendererWorkerLogger()->trace(__VA_ARGS__)
#define MUVI_RENDERER_INFO(...)     ::MuVi::Logger::GetRendererWorkerLogger()->info(__VA_ARGS__)
#define MUVI_RENDERER_WARN(...)     ::MuVi::Logger::GetRendererWorkerLogger()->warn(__VA_ARGS__)
#define MUVI_RENDERER_ERROR(...)    ::MuVi::Logger::GetRendererWorkerLogger()->error(__VA_ARGS__)
#define MUVI_RENDERER_CRITICAL(...) ::MuVi::Logger::GetRendererWorkerLogger()->critical(__VA_ARGS__)
