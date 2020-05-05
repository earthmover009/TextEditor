#include"CallbackUtils.h"
#include"EditorWindow.h"
#include <FL/Fl_File_Chooser.H>

int loading = 0;
std::string title = "";

int check_save(void);

void load_file(char* newfile, int ipos);

void save_file(std::string newfile);

void set_title(Fl_Window* w);

void cut_cb(Fl_Widget*, void* v)
{
	EditorWindow* e = (EditorWindow*)v;
	Fl_Text_Editor::kf_cut(0, e->editor);
}

void copy_cb(Fl_Widget*, void* v)
{
	EditorWindow* e = (EditorWindow*)v;
	Fl_Text_Editor::kf_copy(0, e->editor);
}

void paste_cb(Fl_Widget*, void* v)
{
	EditorWindow* e = (EditorWindow*)v;
	Fl_Text_Editor::kf_paste(0, e->editor);
}

void delete_cb(Fl_Widget*, void* v)
{
	Globals::textbuf->remove_selection();
}

void find2_cb(Fl_Widget* w, void* v)
{
	EditorWindow* e = (EditorWindow*)v;
	if (e->search[0] == '\0') {
		// Search string is blank; get a new one...
		find_cb(w, v);
		return;
	}

	int pos = e->editor->insert_position();
	int found = Globals::textbuf->search_forward(0, e->search.c_str(), &pos);
	if (found) {
		// Found a match; select and update the position...
		Globals::textbuf->select(pos, pos + strlen(e->search.c_str()));
		e->editor->insert_position(pos + strlen(e->search.c_str()));
		e->editor->show_insert_position();
	}
	else fl_alert("No occurrences of \'%s\' found!", e->search);
}

void replace_cb(Fl_Widget*, void* v)
{
	EditorWindow* e = (EditorWindow*)v;
	e->replace_dlg->show();
}

void replace2_cb(Fl_Widget*, void* v)
{
	EditorWindow* e = (EditorWindow*)v;
	const char* find = e->replace_find->value();
	const char* replace = e->replace_with->value();

	if (find[0] == '\0') {
		// Search string is blank; get a new one...
		e->replace_dlg->show();
		return;
	}

	e->replace_dlg->hide();

	int pos = e->editor->insert_position();
	int found = Globals::textbuf->search_forward(pos, find, &pos);

	if (found) {
		// Found a match; update the position and replace text...
		Globals::textbuf->select(pos, pos + strlen(find));
		Globals::textbuf->remove_selection();
		Globals::textbuf->insert(pos, replace);
		Globals::textbuf->select(pos, pos + strlen(replace));
		e->editor->insert_position(pos + strlen(replace));
		e->editor->show_insert_position();
	}
	else fl_alert("No occurrences of \'%s\' found!", find);
}

void replall_cb(Fl_Widget*, void* v)
{
	EditorWindow* e = (EditorWindow*)v;
	const char* find = e->replace_find->value();
	const char* replace = e->replace_with->value();

	find = e->replace_find->value();
	if (find[0] == '\0') {
		// Search string is blank; get a new one...
		e->replace_dlg->show();
		return;
	}

	e->replace_dlg->hide();

	e->editor->insert_position(0);
	int times = 0;

	// Loop through the whole string
	for (int found = 1; found;) {
		int pos = e->editor->insert_position();
		found = Globals::textbuf->search_forward(pos, find, &pos);

		if (found) {
			// Found a match; update the position and replace text...
			Globals::textbuf->select(pos, pos + strlen(find));
			Globals::textbuf->remove_selection();
			Globals::textbuf->insert(pos, replace);
			e->editor->insert_position(pos + strlen(replace));
			e->editor->show_insert_position();
			times++;
		}
	}
}

void find_cb(Fl_Widget * w, void* v)
{
	EditorWindow* e = (EditorWindow*)v;
	const char* val;

	val = fl_input("Search String:", e->search.c_str());
	if (val != NULL) {
		// User entered a string - go find it!
		e->search = val;
		find2_cb(w, v);
	}
}

void replcan_cb(Fl_Widget*, void* v)
{
	EditorWindow* e = (EditorWindow*)v;
	e->replace_dlg->hide();
}

void changed_cb(int, int nInserted, int nDeleted, int, const char*, void* v)
{
	if ((nInserted || nDeleted) && !loading) Globals::changed = 1;
	EditorWindow* w = (EditorWindow*)v;
	set_title(w);
	if (loading)
	{
		w->editor->show_insert_position();
	}
}

void new_cb(Fl_Widget*, void*)
{
	if (!check_save()) return;

	Globals::filename = "";
	Globals::textbuf->select(0, Globals::textbuf->length());
	Globals::textbuf->remove_selection();
	Globals::changed = 0;
	Globals::textbuf->call_modify_callbacks();
}

void open_cb(Fl_Widget*, void*)
{
	if (!check_save()) return;

	char* newfile = fl_file_chooser("Open File?", "*", Globals::filename.c_str());
	if (newfile != NULL) load_file(newfile, -1);
}

void insert_cb()
{
}

void save_cb()
{
}

void saveas_cb()
{
}

void view_cb()
{
}

void close_cb()
{
}

void quit_cb(Fl_Widget*, void*)
{
	if (Globals::changed && !check_save())
		return;

	exit(0);
}

void undo_cb()
{
}

int check_save(void) {
	if (!Globals::changed) return 1;

	int r = fl_choice("The current file has not been saved.\n"
		"Would you like to save it now?",
		"Cancel", "Save", "Discard");

	if (r == 1) {
		save_cb(); // Save the file...
		return !Globals::changed;
	}

	return (r == 2) ? 1 : 0;
}

void load_file(char* newfile, int ipos) {
	loading = 1;
	int insert = (ipos != -1);
	Globals::changed = insert;
	if (!insert) Globals::filename = "";
	int r;
	if (!insert) r = Globals::textbuf->loadfile(newfile);
	else r = Globals::textbuf->insertfile(newfile, ipos);
	if (r)
		fl_alert("Error reading from file \'%s\'\n", newfile);
	else
		if (!insert) Globals::filename = newfile;
	loading = 0;
	Globals::textbuf->call_modify_callbacks();
}

void save_file(std::string newfile) {
	if (Globals::textbuf->savefile(newfile.c_str()))
		fl_alert("Error writing to file \'%s\'\n", newfile);
	else
		Globals::filename = newfile;
	Globals::changed = 0;
	Globals::textbuf->call_modify_callbacks();
}

void set_title(Fl_Window* w) {
	if (Globals::filename.empty()) title = "Untitled";
	else {
		std::string::size_type slash;
		slash = Globals::filename.rfind('/');
#ifdef WIN32
		if (slash == std::string::npos) slash = Globals::filename.rfind('\\');
#endif
		if (slash != std::string::npos)
		{
			std::string str = Globals::filename.substr(slash);
			title = &str[0];
		}
		else title = Globals::filename.c_str();
	}

	if (Globals::changed) title += " (modified)";

	w->label(title.c_str());
}