//HEAD
#include <Fl/Fl.H>
#include <stdio.h>

//BODY
#include <Fl/Fl_!WIDGET_NAME!.H>
class Custom!WIDGET_NAME!: public Fl_!WIDGET_NAME! {
public:
	Custom!WIDGET_NAME!(int x, int y, int w, int h, const char* label = 0);

	int (*_handle)(Custom!WIDGET_NAME!*, int) = nullptr;
	void (*_draw)(Custom!WIDGET_NAME!*) = nullptr;

	void real_draw();
	int real_handle(int evt);

	void draw();
	int handle(int evt);
};

Custom!WIDGET_NAME!::Custom!WIDGET_NAME!(int x, int y, int w, int h, const char* label): Fl_!WIDGET_NAME!(x, y, w, h, label) {
}

void Custom!WIDGET_NAME!::draw() {
	if (_draw != NULL)
		return _draw(this);

	// return Fl_Widget::draw();
	return Fl_!WIDGET_NAME!::draw();
}

int Custom!WIDGET_NAME!::handle(int evt) {
	if (_handle != NULL)
		return _handle(this, evt);

	return Fl_!WIDGET_NAME!::handle(evt);
}

void Custom!WIDGET_NAME!::real_draw() {
	Fl_!WIDGET_NAME!::draw();
}

int Custom!WIDGET_NAME!::real_handle(int evt) {
	return Fl_!WIDGET_NAME!::handle(evt);
}

extern "C" Custom!WIDGET_NAME!* Custom!WIDGET_NAME!_Create(int x, int y, int w, int h, const char* label = 0) {
	return new Custom!WIDGET_NAME!(x, y, w, h, label);
}

extern "C" void Custom!WIDGET_NAME!_SetHandle(Custom!WIDGET_NAME!* b, int (*handler)(Custom!WIDGET_NAME!* b, int evt)) {
	b->_handle = handler;
}

extern "C" void Custom!WIDGET_NAME!_SetDraw(Custom!WIDGET_NAME!* b, void (*draw)(Custom!WIDGET_NAME!* b)) {
	b->_draw = draw;
}

extern "C" void Custom!WIDGET_NAME!_RealDraw(Custom!WIDGET_NAME!* b) {
	b->real_draw();
}

extern "C" int Custom!WIDGET_NAME!_RealHandle(Custom!WIDGET_NAME!* b, int evt) {
	return b->real_handle(evt);
}