#include "EditorWindow.h"
#include<FL/Fl_Sys_Menu_Bar.H>
#include<FL/Fl_Text_Buffer.H>
#include"CallbackUtils.h"


int	Globals::changed = 0;
std::string Globals::filename = "";
Fl_Text_Buffer* Globals::textbuf = new Fl_Text_Buffer;

void initialization(EditorWindow* window);

EditorWindow::EditorWindow(int width, int height, const char* title)
	: Fl_Double_Window(width, height, title)
{

    Fl_Menu_Item menuitems[] = {
      { "&File",              0, 0, 0, FL_SUBMENU },
        { "&New File",        0, (Fl_Callback*)new_cb },
        { "&Open File...",    FL_CTRL + 'o', (Fl_Callback*)open_cb },
        { "&Insert File...",  FL_CTRL + 'i', (Fl_Callback*)insert_cb, 0, FL_MENU_DIVIDER },
        { "&Save File",       FL_CTRL + 's', (Fl_Callback*)save_cb },
        { "Save File &As...", FL_CTRL + FL_SHIFT + 's', (Fl_Callback*)saveas_cb, 0, FL_MENU_DIVIDER },
        { "New &View", FL_ALT + 'v', (Fl_Callback*)view_cb, 0 },
        { "&Close View", FL_CTRL + 'w', (Fl_Callback*)close_cb, 0, FL_MENU_DIVIDER },
        { "E&xit", FL_CTRL + 'q', (Fl_Callback*)quit_cb, 0 },
        { 0 },

      { "&Edit", 0, 0, 0, FL_SUBMENU },
        { "&Undo",       FL_CTRL + 'z', (Fl_Callback*)undo_cb, 0, FL_MENU_DIVIDER },
        { "Cu&t",        FL_CTRL + 'x', (Fl_Callback*)cut_cb, this },
        { "&Copy",       FL_CTRL + 'c', (Fl_Callback*)copy_cb, this },
        { "&Paste",      FL_CTRL + 'v', (Fl_Callback*)paste_cb, this },
        { "&Delete",     0, (Fl_Callback*)delete_cb, this },
        { 0 },

      { "&Search", 0, 0, 0, FL_SUBMENU },
        { "&Find...",       FL_CTRL + 'f', (Fl_Callback*)find_cb, this },
        { "F&ind Again",    FL_CTRL + 'g', (Fl_Callback*)find2_cb, this },
        { "&Replace...",    FL_CTRL + 'r', (Fl_Callback*)replace_cb, this },
        { "Re&place Again", FL_CTRL + 't', (Fl_Callback*)replace2_cb, this },
        { 0 },

      { 0 }
    };
    
    Fl_Menu_Bar* m = new Fl_Menu_Bar(0, 0, 800, 30);
    m->copy(menuitems);

    editor  = new Fl_Text_Editor(0, 30, 800, 570);
    editor->buffer(Globals::textbuf );
    editor->textfont(FL_COURIER);

    Globals::textbuf->add_modify_callback(changed_cb, this);
    Globals::textbuf->call_modify_callbacks();

    initialization(this);
    
}

void initialization(EditorWindow* window)
{
    window->replace_dlg = new Fl_Window(300, 105, "Replace");
    window->replace_find = new Fl_Input(70, 10, 200, 25, "Find:");
    window->replace_with = new Fl_Input(70, 40, 200, 25, "Replace:");
    window->replace_all = new Fl_Button(10, 70, 90, 25, "Replace All");
    window->replace_next = new Fl_Return_Button(105, 70, 120, 25, "Replace Next");
    window->replace_cancel = new Fl_Button(230, 70, 60, 25, "Cancel");
}

EditorWindow::~EditorWindow()
{
	//TODO
}