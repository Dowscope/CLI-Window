/**************************************************************
 * Add this to the top of your main.cpp file for initialization:
    void init_ncurses() {
        initscr(); 
        refresh();
        noecho();
        curs_set(0);
        keypad(stdscr, TRUE);

        start_color();

        // Define color pairs (Foreground, Background)
        init_pair(1, COLOR_WHITE, COLOR_BLACK); // Normal border
        init_pair(2, COLOR_YELLOW, COLOR_BLACK); // Highlighted border
    }
*/

#ifndef __DOWWINDOW
#define __DOWWINDOW

#include <curses.h>
#include <cstring>

///////////////////////////////////////////////////////////
/// @brief dowwindow
///
class dowwindow
{
public:
    bool isActive = false;

    dowwindow(int height, int width, int start_y, int start_x, const char* title, bool selectable = false);
    virtual ~dowwindow();

    // Methods
    void setActive(bool active);
    void writeText(int y, int x, const char* text, bool centered = false);

    WINDOW* getWindow() { return _win; }
    bool isSelectable() { return _selectable; }
private:
    // Members
    WINDOW* _win;
    const char* _name;
    int _h;
    int _w;
    int _y;
    int _x;
    bool _selectable = false;

    // Methods
    void _draw_window_border();
    void _highlight_active_window();
};

#endif  // __DOWWINDOW_H
