module fltk_d_utils;

import fltk_d;
import std.string;

alias FL_CALLBACK_LONG=void function(void* w_ptr, long arg);
alias FL_CALLBACK_VOIDP=void function(void* w_ptr, void* arg);

char* cString(string str){
	return cast(char*)toStringz(str);
}

string dString(char* str){
	return cast(string)fromStringz(str);
}

struct FLTK_CALLBACK_INFO{
	FL_CALLBACK_VOIDP cb;
	void* arg;
	void* widget_ptr;
}

extern(C++)
void HANDLE_FLTK_CALLBACK_VOIDP(Widget w, void* param){
	auto cb_info=cast(FLTK_CALLBACK_INFO*)param;
	cb_info.cb(cb_info.widget_ptr, cb_info.arg);
}

extern(C++)
void HANDLE_FLTK_CALLBACK_LONG(Widget w, void* param){
	auto cb_info=cast(FLTK_CALLBACK_INFO*)param;
	cb_info.cb(cb_info.widget_ptr, cb_info.arg);
}

void SetCallbackVoidP(Widget w, FL_CALLBACK_VOIDP cb, void* param=null){
	auto info=new FLTK_CALLBACK_INFO();
	info.cb=cb;
	info.arg=param;
	info.widget_ptr=Widget.swigGetCPtr(w);

	w.callback(new SWIGTYPE_p_f_p_Fl_Widget_p_void__void(&HANDLE_FLTK_CALLBACK_VOIDP, true),cast(void*)info);
}

void SetCallbackLong(Widget w, FL_CALLBACK_LONG cb, long param=0){
	auto info=new FLTK_CALLBACK_INFO();
	info.cb=cast(FL_CALLBACK_VOIDP)cb;
	info.arg=cast(void*)param;
	info.widget_ptr=Widget.swigGetCPtr(w);

	w.callback(new SWIGTYPE_p_f_p_Fl_Widget_p_void__void(&HANDLE_FLTK_CALLBACK_LONG, true), cast(void*)info);
}

template Wrap(T)
{
    T Wrap(void* raw)
    {
        return new T(cast(void*) raw, false);
    }
}

void CenterWidget(Widget widget, Widget parent = null)
{
    if (parent is null)
    {
        widget.position(Fl.w / 2 - widget.w / 2, Fl.h / 2 - widget.h / 2);
    }
    else
    {
        widget.position(parent.x + parent.w / 2 - widget.w / 2, parent.y + parent.h / 2
                - widget.h / 2);
    }
}