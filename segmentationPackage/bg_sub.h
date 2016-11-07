#ifndef BG_SUB_H
#define BG_SUB_H

#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <iostream>
#include <sstream>

class bg_sub
{
public:
    std::string video_path;
    bg_sub(std::string);
    void processVideo();
};

#endif // BG_SUB_H
