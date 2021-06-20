#ifndef APP_H
#define APP_H

#include "video.h"

#include <string>

class App {
public:
    App(const std::string &file1, const std::string &file2);

    ~App();

    void run();

private:
    std::string m_win;

    Video m_video1;
    Video m_video2;

    bool m_selected1 = true;
    bool m_selected2 = true;

    static void on_mouse_event(int event, int x, int y, int flags, void *userdata);

    void on_mouse_click(int x, int y);
};


#endif
