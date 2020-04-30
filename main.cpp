#include<FL/Fl.h>
#include<FL/Fl_Window.h>
#include<FL/Fl_Text_Buffer.H>

int            changed = 0;
char           filename[256] = "";
Fl_Text_Buffer* textbuf;

int main()
{
    Fl_Window window(200, 200, "Window title");

    window.show();
    return Fl::run();
}