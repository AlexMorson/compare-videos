#include "app.h"

#include <opencv2/opencv.hpp>

#include <string>

App::App(const std::string &file1, const std::string &file2) :
        m_win{"Compare Videos"},
        m_video1{file1},
        m_video2{file2} {

    // Create a window and hide the status bar
    cv::namedWindow(m_win, cv::WINDOW_GUI_NORMAL);
    cv::setMouseCallback(m_win, on_mouse_event, this);
}

App::~App() {
    cv::destroyAllWindows();
}

void App::on_mouse_event(int event, int x, int y, int flags, void *userdata) {
    App *app = (App *) userdata;
    if (event == cv::EVENT_LBUTTONDOWN)
        app->on_mouse_click(x, y);
}

void App::on_mouse_click(int x, int y) {
    if (x < m_video1.width()) {
        m_selected1 = true;
        m_selected2 = not m_selected2;
    } else {
        m_selected1 = not m_selected1;
        m_selected2 = true;
    }
}

void App::run() {
    bool paused = true;
    cv::Mat cat;

    bool running = true;
    while (running) {
        switch (cv::waitKey(16)) {
            case ' ':
                paused = not paused;
                break;
            case 'q':
                running = false;
                break;
            case 'a':
                if (m_selected1) m_video1.step_backward();
                if (m_selected2) m_video2.step_backward();
                break;
            case 'd':
                if (m_selected1) m_video1.step_forward();
                if (m_selected2) m_video2.step_forward();
                break;
            case 's':
                if (m_selected1) m_video1.set_mark();
                if (m_selected2) m_video2.set_mark();
                break;
        }

        if (not paused) {
            if (m_selected1) m_video1.step_forward();
            if (m_selected2) m_video2.step_forward();
        }

        cv::hconcat(m_video1.frame(), m_video2.frame(), cat);

        // Display which video(s) are selected
        constexpr int radius = 2;
        cv::Point tl, br;
        if (m_selected1 and not m_selected2) {
            tl = {radius, radius};
            br = {m_video1.width() - radius, m_video1.height() - radius};
        } else if (m_selected2 and not m_selected1) {
            tl = {m_video1.width() + radius, radius};
            br = {m_video1.width() + m_video2.width() - radius, m_video2.height() - radius};
        } else {
            tl = {radius, radius};
            br = {m_video1.width() + m_video2.width() - radius, m_video2.height() - radius};
        }
        cv::rectangle(cat, tl, br, {0, 255, 255}, 2 * radius);

        cv::imshow(m_win, cat);
    }

}