#include <boost/program_options.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

#include "AudioLoopbackWorker.h"
#include "FftWorker.h"
#include "Logger.h"
#include "MuviConfig.h"
#include "RendererWorker.h"

namespace po = boost::program_options;

int main(int argc, char** argv) {
    Muvi::renderer_config_t config;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "print usage message")
        ("debug", "Enable additional logs")
        ("color,c",
         po::value<int>(&config.colormap)->default_value(DEFAULT_COLORMAP),
         "Color map to use. Range 0-21. See OpenCV 4.7.0-dev documentation "
         "https://docs.opencv.org/4.x/d3/d50/group__imgproc__colormap.html")
        ("width,w", po::value<int>(&config.width)->default_value(DEFAULT_WIDTH),
         "Width of the window")
        ("height,h",
         po::value<int>(&config.height)->default_value(DEFAULT_HEIGHT),
         "Height of the window");

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(desc).run(), vm);
    po::notify(vm);

    MuVi::Logger::Init(vm.count("debug"));

    if (config.colormap < cv::COLORMAP_AUTUMN ||
        config.colormap > cv::COLORMAP_DEEPGREEN) {
        MUVI_ERROR("Invalid colormap value. Falling to default: {}",
                   DEFAULT_COLORMAP);
    }

    Muvi::AudioLoopbackWorker audioLoopbackWorker;
    audioLoopbackWorker.Spawn();

    Muvi::FftWorker fftWorker(audioLoopbackWorker);
    fftWorker.Spawn();

    Muvi::RendererWorker rendererWorker(fftWorker, config);
    rendererWorker.Spawn();

    audioLoopbackWorker.Join();
    fftWorker.Join();
    rendererWorker.Join();

    return 0;
}