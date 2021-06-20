#ifndef VIDEO_H
#define VIDEO_H

#include <opencv2/opencv.hpp>

#include <string>

class Video {
public:
    Video(const std::string &file);

    void step_forward();

    void step_backward();

    void set_mark();

    cv::Mat frame() const;

    bool has_frame() const;

    int width() const;

    int height() const;

private:
    std::string m_file;
    cv::VideoCapture m_cap;
    int m_pos{0};
    int m_mark{0};
    int m_width, m_height;
    cv::Mat m_frame;
    bool m_has_frame{false};

    void read();
};

#endif
