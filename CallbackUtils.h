#pragma once
#include <FL/fl_ask.H>

void new_cb(Fl_Widget*, void*);

void open_cb(Fl_Widget*, void*);

void insert_cb();

void save_cb();

void saveas_cb();

void view_cb();

void close_cb();

void quit_cb(Fl_Widget*, void*);

void undo_cb();

void cut_cb(Fl_Widget*, void* v);

void copy_cb(Fl_Widget*, void* v);

void paste_cb(Fl_Widget*, void* v);

void delete_cb(Fl_Widget*, void* v);

void find_cb(Fl_Widget* w, void* v);

void find2_cb(Fl_Widget* w, void* v);

void replace_cb(Fl_Widget*, void* v);

void replace2_cb(Fl_Widget*, void* v);

void replall_cb(Fl_Widget*, void* v);

void replcan_cb(Fl_Widget*, void* v);

void changed_cb(int, int nInserted, int nDeleted, int, const char*, void* v);