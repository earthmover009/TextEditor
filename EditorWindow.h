#pragma once

#include<FL/Fl.h>
#include<FL/Fl_Window.h>
#include<FL/Fl_Double_Window.H>
#include<FL/Fl_Input.H>
#include<FL/Fl_Button.H>
#include<FL/Fl_Return_Button.H>
#include<FL/Fl_Text_Editor.H>
#include<string>


namespace Globals
{
	extern int				changed;
	extern std::string		filename;
	extern Fl_Text_Buffer* textbuf;
}


class EditorWindow : public Fl_Double_Window
{

public:
	EditorWindow( int width, int height, const char* title );

	~EditorWindow();

	Fl_Window* replace_dlg;
	Fl_Input* replace_find;
	Fl_Input* replace_with;
	Fl_Button* replace_all;
	Fl_Return_Button* replace_next;
	Fl_Button* replace_cancel;

	Fl_Text_Editor* editor;
	std::string search;

};

