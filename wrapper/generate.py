#!/usr/bin/python2.7

data=open("template.cpp").read()

d_header_template="""
alias C_Custom!WIDGET_NAME!=void*;

extern(C){
    C_Custom!WIDGET_NAME! Custom!WIDGET_NAME!_Create(int x, int y, int w, int h, const char* label = null);
    void Custom!WIDGET_NAME!_SetHandle(C_Custom!WIDGET_NAME! w, HandleProc h);
    void Custom!WIDGET_NAME!_SetDraw(C_Custom!WIDGET_NAME! w, DrawProc d);
    void Custom!WIDGET_NAME!_RealDraw(C_Custom!WIDGET_NAME! w);
    int  Custom!WIDGET_NAME!_RealHandle(C_Custom!WIDGET_NAME! w, int evt);
}
"""

lines=data.split("\n")

body_position=lines.index("//BODY")

widgets=[
	"Window",
	"Double_Window",
	"Button",
	"Group",
	"Input",
	"Pack",
	"Scroll",
	"Box",
	"Value_Input",
	"Value_Output",
	"Progress",
	"Text_Display",
	"Text_Editor",
	"Choice",
	"Check_Button",
	"Light_Button",
]

head="\n".join(lines[0:body_position])
body="\n".join(lines[body_position:])

cpp_out=""
d_out="""
alias HandleProc = extern (C) int function(void* w, int evt);
alias DrawProc = extern (C) void function(void* w);
"""

for w in widgets:
	cpp_out+=body.replace("!WIDGET_NAME!",w)
	d_out+=d_header_template.replace("!WIDGET_NAME!",w)

open("libcustomwidgets.cxx","w").write(cpp_out)
open("../source/customwidget_bindings.d","w").write(d_out)
