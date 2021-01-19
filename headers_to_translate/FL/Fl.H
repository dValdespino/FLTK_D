#include <FL/ .H>

#  ifndef Fl_Object
#    define Fl_Object Fl_Widget
#  endif

#  ifdef check
#    undef check
#  endif

#  ifdef BSD
#    undef BSD
#  endif

#define uchar unsigned char

class Fl_Widget;
class Fl_Window;
class Fl_Image;
struct Fl_Label;
class Fl_Screen_Driver;
class Fl_System_Driver;

extern const char* fl_local_alt;
extern const char* fl_local_ctrl;
extern const char* fl_local_meta;
extern const char* fl_local_shift;


typedef void (Fl_Label_Draw_F)(const Fl_Label* label, int x, int y, int w, int h, Fl_Align align);


typedef void (Fl_Label_Measure_F)(const Fl_Label* label, int &width, int &height);


typedef void (Fl_Box_Draw_F)(int x, int y, int w, int h, Fl_Color color);


typedef void (*Fl_Timeout_Handler)(void* data);


typedef void (*Fl_Awake_Handler)(void* data);


typedef void (*Fl_Idle_Handler)(void* data);


typedef void (*Fl_Old_Idle_Handler)();


typedef void (*Fl_FD_Handler)(FL_SOCKET fd, void* data);


typedef int (*Fl_Event_Handler)(int event);


typedef int (*Fl_System_Handler)(void* event, void* data);


typedef void (*Fl_Abort_Handler)(const char* format, ...);


typedef void (*Fl_Atclose_Handler)(Fl_Window* window, void* data);


typedef int (*Fl_Args_Handler)(int argc, char** argv, int &i);

/** Signature of event_dispatch functions passed as parameters.
    \see Fl::event_dispatch(Fl_Event_Dispatch) */
typedef int (*Fl_Event_Dispatch)(int event, Fl_Window* w);


typedef void (*Fl_Clipboard_Notify_Handler)(int source, void* data);




/**
  The Fl is the FLTK global (static) class containing
  state information and global methods for the current application.
*/
class Fl {
  Fl() {}; // no constructor!

public:

  static Fl_Screen_Driver* screen_driver();
  static Fl_System_Driver* system_driver();
  static void reset_marked_text(); // resets marked text
  static void insertion_point_location(int x, int y, int height); // sets window coordinates & height of insertion point

public: // run time information about compile time configuration


  static bool cfg_gfx_xlib;   ///< X11 Xlib rendering available, usually on Linux systems
  static bool cfg_gfx_quartz; ///< Quartz rendering available, usually on OS X systems
  static bool cfg_gfx_gdi;    ///< GDI rendering available, usually on Windows systems
  static bool cfg_gfx_opengl; ///< OpenGL rendering available, available on many platforms
  static bool cfg_gfx_cairo;  ///< Cairo rendering available, available on many platforms
  static bool cfg_gfx_directx;///< DirectX rendering available, usually on Windows systems



  static bool cfg_prn_ps;     ///< PostScript rendering available, usually on Linux systems
  static bool cfg_prn_quartz; ///< Quartz rendering available, usually on OS X systems
  static bool cfg_prn_gdi;    ///< GDI rendering available, usually on Windows systems



  static bool cfg_win_x11;    ///< X11 window management available, usually on Linux systems
  static bool cfg_win_cocoa;  ///< Cocoa window management available, usually on OS X systems
  static bool cfg_win_win32;  ///< Windows window management available, on low level Windows



  static bool cfg_sys_posix;  ///< Posix system available, usually on Linux and OS X systems, but also Cygwin
  static bool cfg_sys_win32;  ///< Windows system available, on Windows


public: // should be private!

  static int e_number;
  static int e_x;
  static int e_y;
  static int e_x_root;
  static int e_y_root;
  static int e_dx;
  static int e_dy;
  static int e_state;
  static int e_clicks;
  static int e_is_click;
  static int e_keysym;
  static char* e_text;
  static int e_length;
  static void* e_clipboard_data;
  static const char* e_clipboard_type;
  static Fl_Event_Dispatch e_dispatch;
  static Fl_Widget* belowmouse_;
  static Fl_Widget* pushed_;
  static Fl_Widget* focus_;
  static int damage_;
  static Fl_Widget* selection_owner_;
  static Fl_Window* modal_;
  static Fl_Window* grab_;
  static int compose_state; // used for dead keys (Windows) or marked text (MacOS)
  static void call_screen_init(); // recompute screen number and dimensions

  static void damage(int d) {damage_ = d;}

public:
  typedef enum {
    OPTION_ARROW_FOCUS = 0,
    OPTION_VISIBLE_FOCUS,
    OPTION_DND_TEXT,
    OPTION_SHOW_TOOLTIPS,
    OPTION_FNFC_USES_GTK,
    OPTION_PRINTER_USES_GTK,
    OPTION_SHOW_SCALING,
    OPTION_LAST
  } Fl_Option;

private:
  static unsigned char options_[OPTION_LAST];
  static unsigned char options_read_;
  static int program_should_quit_; // non-zero means the program was asked to cleanly terminate

public:
  static bool option(Fl_Option opt);
  static void option(Fl_Option opt, bool val);
  static void (*idle)();

  static Fl_Awake_Handler* awake_ring_;
  static void** awake_data_;
  static int awake_ring_size_;
  static int awake_ring_head_;
  static int awake_ring_tail_;
  static const char* scheme_;
  static Fl_Image* scheme_bg_;

  static int e_original_keysym; // late addition
  static int scrollbar_size_;
  static int menu_linespacing_; // STR #2927

  static int add_awake_handler_(Fl_Awake_Handler, void*);
  static int get_awake_handler_(Fl_Awake_Handler &, void* &);

  // API version number
  static double version();
  static int api_version();

  // ABI version number
  static int abi_version();

  static inline int abi_check(const int val = FL_ABI_VERSION) {
    return val == abi_version();
  }

  // argument parsers:
  static int arg(int argc, char** argv, int &i);
  static int args(int argc, char** argv, int &i, Fl_Args_Handler cb = 0);
  static void args(int argc, char** argv);

  static const char* const help;

  // things called by initialization:
  static void display(const char*);
  static int visual(int);

  static void own_colormap();
  static void get_system_colors();
  static void foreground(uchar, uchar, uchar);
  static void background(uchar, uchar, uchar);
  static void background2(uchar, uchar, uchar);

  // schemes:
  static int scheme(const char* name);

  static const char* scheme() {return scheme_;}

  static int is_scheme(const char* name) {
    return (scheme_ && name && !strcmp(name, scheme_));
  }
  static int reload_scheme(); // platform dependent
  static int scrollbar_size();
  static void scrollbar_size(int W);
  static int menu_linespacing();
  static void menu_linespacing(int H);

  // execution:
  static int wait();
  static double wait(double time);
  static int check();
  static int ready();
  static int run();
  static int program_should_quit() {return program_should_quit_;}
  static void program_should_quit(int should_i) { program_should_quit_ = should_i; }

  static Fl_Widget* readqueue();

  static void add_timeout(double t, Fl_Timeout_Handler, void* = 0); // platform dependent
  static void repeat_timeout(double t, Fl_Timeout_Handler, void* = 0); // platform dependent
  static int  has_timeout(Fl_Timeout_Handler, void* = 0);
  static void remove_timeout(Fl_Timeout_Handler, void* = 0);
  static void add_check(Fl_Timeout_Handler, void* = 0);
  static int  has_check(Fl_Timeout_Handler, void* = 0);
  static void remove_check(Fl_Timeout_Handler, void* = 0);
  // private
  static void run_checks();
  static void add_fd(int fd, int when, Fl_FD_Handler cb, void* = 0); // platform dependent
  static void add_fd(int fd, Fl_FD_Handler cb, void* = 0); // platform dependent

  static void remove_fd(int, int when); // platform dependent

  static void remove_fd(int); // platform dependent

  static void add_idle(Fl_Idle_Handler cb, void* data = 0);
  static int  has_idle(Fl_Idle_Handler cb, void* data = 0);
  static void remove_idle(Fl_Idle_Handler cb, void* data = 0);

  static int damage() {return damage_;}
  static void redraw();
  static void flush();

  static void (*warning)(const char*, ...);
  static void (*error)(const char*, ...);
  static void (*fatal)(const char*, ...);
  static Fl_Window* first_window();
  static void first_window(Fl_Window*);
  static Fl_Window* next_window(const Fl_Window*);

  static Fl_Window* modal() {return modal_;}
  static Fl_Window* grab() {return grab_;}

  static void grab(Fl_Window*); // platform dependent
  static int event()            {return e_number;}
  static int event_x()  {return e_x;}
  static int event_y()  {return e_y;}
  static int event_x_root()     {return e_x_root;}
  static int event_y_root()     {return e_y_root;}
  static int event_dx() {return e_dx;}
  static int event_dy() {return e_dy;}
  static void get_mouse(int &, int &);
  static int event_clicks()     {return e_clicks;}
  static void event_clicks(int i) {e_clicks = i;}
  static int event_is_click()   {return e_is_click;}
  static void event_is_click(int i) {e_is_click = i;}
  static int event_button()     {return e_keysym - FL_Button;}

  static int event_state()      {return e_state;}

  static int event_state(int mask) {return e_state & mask;}
  static int event_key()        {return e_keysym;}
  static int event_original_key() {return e_original_keysym;}

  static int event_key(int key);
  static int get_key(int key); // platform dependent
  static const char* event_text() {return e_text;}
  static int event_length() {return e_length;}
  static void* event_clipboard() { return e_clipboard_data; }
  static const char* event_clipboard_type() {return e_clipboard_type; }

  static int compose(int &del);
  static void compose_reset();
  static int event_inside(int, int, int, int);
  static int event_inside(const Fl_Widget*);
  static int test_shortcut(Fl_Shortcut);

  static void enable_im();
  static void disable_im();

  // event destinations:
  static int handle(int, Fl_Window*);
  static int handle_(int, Fl_Window*);
  /**  Gets the widget that is below the mouse.
       \see  belowmouse(Fl_Widget*) */
  static Fl_Widget* belowmouse() {return belowmouse_;}
  static void belowmouse(Fl_Widget*);
  /** Gets the widget that is being pushed.
      \see void pushed(Fl_Widget*) */
  static Fl_Widget* pushed()    {return pushed_;}
  static void pushed(Fl_Widget*);

  static Fl_Widget* focus()     {return focus_;}
  static void focus(Fl_Widget*);
  static void add_handler(Fl_Event_Handler h);
  static void remove_handler(Fl_Event_Handler h);
  static void add_system_handler(Fl_System_Handler h, void* data);
  static void remove_system_handler(Fl_System_Handler h);
  static void event_dispatch(Fl_Event_Dispatch d);
  static Fl_Event_Dispatch event_dispatch();


  static void copy(const char* stuff, int len, int destination = 0, const char* type = Fl::clipboard_plain_text); // platform dependent

  static void paste(Fl_Widget &receiver, int source, const char* type = Fl::clipboard_plain_text);

  static void add_clipboard_notify(Fl_Clipboard_Notify_Handler h, void* data = 0);
  static void remove_clipboard_notify(Fl_Clipboard_Notify_Handler h);
  static int clipboard_contains(const char* type);
  static char const* const clipboard_plain_text;
  static char const* const clipboard_image;
  static int dnd(); // platform dependent

  static Fl_Widget* selection_owner() {return selection_owner_;}
  static void selection_owner(Fl_Widget*);
  static void selection(Fl_Widget &owner, const char*, int len);
  static void paste(Fl_Widget &receiver);

  static int x(); // via screen driver
  static int y(); // via screen driver
  static int w(); // via screen driver
  static int h(); // via screen driver

  // multi-head support:
  static int screen_count(); // via screen driver
  static void screen_xywh(int &X, int &Y, int &W, int &H); // via screen driver
  static void screen_xywh(int &X, int &Y, int &W, int &H, int mx, int my); // via screen driver
  static void screen_xywh(int &X, int &Y, int &W, int &H, int n); // via screen driver
  static void screen_xywh(int &X, int &Y, int &W, int &H, int mx, int my, int mw, int mh); // via screen driver
  static int screen_num(int x, int y); // via screen driver
  static int screen_num(int x, int y, int w, int h); // via screen driver
  static void screen_dpi(float &h, float &v, int n = 0); // via screen driver
  static void screen_work_area(int &X, int &Y, int &W, int &H, int mx, int my); // via screen driver
  static void screen_work_area(int &X, int &Y, int &W, int &H, int n); // via screen driver
  static void screen_work_area(int &X, int &Y, int &W, int &H); // via screen driver
  static float screen_scale(int n); // via screen driver
  static void screen_scale(int n, float factor); // via screen driver
  static int screen_scaling_supported();
  static void keyboard_screen_scaling(int value);

  // color map:
  static void   set_color(Fl_Color, uchar, uchar, uchar);
  static void   set_color(Fl_Color i, unsigned c); // platform dependent
  static unsigned get_color(Fl_Color i);
  static void   get_color(Fl_Color i, uchar &red, uchar &green, uchar &blue);
  static void   free_color(Fl_Color i, int overlay = 0); // platform dependent

  static const char* get_font(Fl_Font);
  static const char* get_font_name(Fl_Font, int* attributes = 0);
  static int get_font_sizes(Fl_Font, int* &sizep);
  static void set_font(Fl_Font, const char*);
  static void set_font(Fl_Font, Fl_Font);

  static Fl_Font set_fonts(const char* = 0); // platform dependent
  // labeltypes:
  static void set_labeltype(Fl_Labeltype, Fl_Label_Draw_F*, Fl_Label_Measure_F*);

  // boxtypes:
  static Fl_Box_Draw_F* get_boxtype(Fl_Boxtype);
  static void set_boxtype(Fl_Boxtype, Fl_Box_Draw_F*, uchar, uchar, uchar, uchar);
  static void set_boxtype(Fl_Boxtype, Fl_Boxtype from);
  static int box_dx(Fl_Boxtype);
  static int box_dy(Fl_Boxtype);
  static int box_dw(Fl_Boxtype);
  static int box_dh(Fl_Boxtype);

  static int draw_box_active();
  static Fl_Color box_color(Fl_Color);
  static void set_box_color(Fl_Color);

  static void set_abort(Fl_Abort_Handler f) {fatal = f;}
  static void (*atclose)(Fl_Window*, void*);
  static void default_atclose(Fl_Window*, void*);
  static void set_atclose(Fl_Atclose_Handler f) {atclose = f;}
  static int event_shift() {return e_state & FL_SHIFT;}

  static int event_ctrl() {return e_state & FL_CTRL;}

  static int event_command() {return e_state & FL_COMMAND;}

  static int event_alt() {return e_state & FL_ALT;}
  static int event_buttons() {return e_state & 0x7f000000;}
  static int event_button1() {return e_state & FL_BUTTON1;}
  static int event_button2() {return e_state & FL_BUTTON2;}
  static int event_button3() {return e_state & FL_BUTTON3;}
  static void set_idle(Fl_Old_Idle_Handler cb) {idle = cb;}

  static void grab(Fl_Window &win) {grab(&win);}
  static void release() {grab(0);}

  static void visible_focus(int v) { option(OPTION_VISIBLE_FOCUS, (v != 0)); }
  static int  visible_focus() { return option(OPTION_VISIBLE_FOCUS); }

  static void dnd_text_ops(int v) { option(OPTION_DND_TEXT, (v != 0)); }
  static int  dnd_text_ops() { return option(OPTION_DND_TEXT); }
  static int lock();
  static void unlock();
  static void awake(void* message = 0);

  static int awake(Fl_Awake_Handler cb, void* message = 0);
  /**
    The thread_message() method returns the last message
    that was sent from a child by the awake() method.

    See also: \ref advanced_multithreading
  */
  static void* thread_message(); // platform dependent


  static void delete_widget(Fl_Widget* w);
  static void do_widget_deletion();
  static void watch_widget_pointer(Fl_Widget* &w);
  static void release_widget_pointer(Fl_Widget* &w);
  static void clear_widget_pointer(Fl_Widget const* w);


  /**  sets whether GL windows should be drawn at high resolution on Apple
   computers with retina displays
   \version 1.3.4
   */
  static void use_high_res_GL(int val) { use_high_res_GL_ = val; }
  /**  returns whether GL windows should be drawn at high resolution on Apple
   computers with retina displays.
   Default is no.
   \version 1.3.4
   */
  static int use_high_res_GL() { return use_high_res_GL_; }

  /**  sets whether OpenGL uses textures to draw all text.
   By default, FLTK draws OpenGL text using textures, if the necessary
   hardware support is available. Call \p Fl::draw_GL_text_with_textures(0)
   once in your program before the first call to gl_font() to have FLTK
   draw instead OpenGL text using a legacy, platform-dependent procedure.
   It's recommended not to deactivate textures under the MacOS platform
   because the MacOS legacy procedure is extremely rudimentary.
   \param val use 0 to prevent FLTK from drawing GL text with textures
   \see gl_texture_pile_height(int max)
   \version 1.4.0
   */
  static void draw_GL_text_with_textures(int val) { draw_GL_text_with_textures_ = val; }

  /**  returns whether whether OpenGL uses textures to draw all text.
   Default is yes.
   \see draw_GL_text_with_textures(int val)
   \version 1.4.0
   */
  static int draw_GL_text_with_textures() { return draw_GL_text_with_textures_; }
};