#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>

#include "Logger.h"
#include "RendererWorker.h"
#include "RendererGraph.h"

namespace Muvi {


    void RendererWorker::Run() {
        RendererGraph graph;
        fft_buff_t buff;

        while(IsRunning()) {
            memset(&buff, 0x00,sizeof(fft_buff_t));
            while(1){//Consume(buff)) {
                MUVI_RENDERER_TRACE("RECEIVED BUFFER");
                graph.Render(buff);
            }
            waitForProduct();
        }
    }
} // Muvi
