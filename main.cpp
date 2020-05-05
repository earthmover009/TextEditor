#include<FL/Fl.h>
#include<FL/Fl_Window.h>
#include "EditorWindow.h"




int main(int argc, char** argv)
{
    Fl_Window* window = new EditorWindow(800, 600, "Text Editor");

    window->show(1, argv);

    //if (argc > 1) load_file(argv[1], -1);

    return Fl::run();
}
