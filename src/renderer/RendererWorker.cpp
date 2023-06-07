#include "RendererWorker.h"

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "Logger.h"
#include "RendererGraph.h"

namespace Muvi {

    void RendererWorker::Run() {
        RendererGraph graph(m_config);
        fft_buff_t buff;

        while (IsRunning()) {
            memset(&buff, 0x00, sizeof(fft_buff_t));
            while (Consume(buff)) {
                MUVI_RENDERER_TRACE("RECEIVED BUFFER");
                graph.Render(buff);
            }
            graph.HandleUI();
        }
    }
}  // namespace Muvi
