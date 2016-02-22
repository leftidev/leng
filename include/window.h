#ifndef WINDOW_H
#define WINDOW_H

namespace leng {

class Window {
public:
    Window(const char* title, int width, int height);
    ~Window();
    
    void create();
};

}  // namespace leng

#endif // WINDOW_H
