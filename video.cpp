#include "video.h"

#include <opencv2/opencv.hpp>

Video::Video(const std::string &file) :
        m_file{file},
        m_cap{file},
        m_width{int(m_cap.get(cv::CAP_PROP_FRAME_WIDTH))},
        m_height{int(m_cap.get(cv::CAP_PROP_FRAME_HEIGHT))} {
    read();
}

void Video::step_forward() {
    if (not m_has_frame) return;

    ++m_pos;
    read();
}

void Video::step_backward() {
    if (m_pos == 0) return;

    --m_pos;
    m_cap.set(cv::CAP_PROP_POS_FRAMES, m_pos - 1);
    read();
}

void Video::set_mark() {
    m_mark = m_pos;
}

cv::Mat Video::frame() const {
    cv::Mat output = m_frame.clone();
    int frame_offset = m_pos - m_mark;
    cv::putText(output, m_file, {5, 20}, cv::FONT_HERSHEY_SIMPLEX, 0.5, {255, 255, 255}, 1);
    cv::putText(output, std::to_string(frame_offset), {5, 50}, cv::FONT_HERSHEY_SIMPLEX, 1, {255, 255, 255}, 2);
    return output;
}

bool Video::has_frame() const {
    return m_has_frame;
}

int Video::width() const {
    return m_width;
}

int Video::height() const {
    return m_height;
}

void Video::read() {
    m_cap.read(m_frame);
    m_has_frame = not m_frame.empty();
    if (not m_has_frame)
        m_frame = cv::Mat::zeros(m_height, m_width, CV_8UC3);
}