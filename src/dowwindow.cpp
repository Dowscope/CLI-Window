#include "dowwindow.h"

using namespace std;

dowwindow::dowwindow(int height, int width, int start_y, int start_x, const char* title, bool selectable)
    : _selectable(selectable), _h(height), _w(width), _y(start_y), _x(start_x), _name(title)
{
    _win = newwin(height, width, start_y, start_x);
    _draw_window_border();
    wrefresh(_win);
}

dowwindow::~dowwindow()
{
    delwin(_win);
}

void dowwindow::setActive(bool active)
{
    if (!_selectable) { return; }

    isActive = active;
    _highlight_active_window();
}

void dowwindow::writeText(int y, int x, const char *text, bool centered)
{
    if (centered) {
        x = (getmaxx(_win) - strlen(text)) / 2;
    }
    mvwprintw(_win, y, x, text);
    wrefresh(_win);
}

void dowwindow::_draw_window_border()
{
    int width = getmaxx(_win); // Get the window width
    int title_start = (width - strlen(_name) - 4) / 2;

    // Draw top border manually to include _name
    mvwaddch(_win, 0, 0, ACS_ULCORNER); // Top-left corner
    mvwhline(_win, 0, 1, ACS_HLINE, title_start - 1); // Left of _name
    mvwprintw(_win, 0, title_start, "[ %s ]", _name); // _name in center
    mvwhline(_win, 0, title_start + strlen(_name) + 4, ACS_HLINE, width - title_start - strlen(_name) - 2);
    mvwaddch(_win, 0, width - 1, ACS_URCORNER); // Top-right corner

    // Draw side and bottom borders without overriding the top
    for (int y = 1; y < getmaxy(_win) - 1; y++) {
        mvwaddch(_win, y, 0, ACS_VLINE);
        mvwaddch(_win, y, width - 1, ACS_VLINE);
    }

    mvwaddch(_win, getmaxy(_win) - 1, 0, ACS_LLCORNER); // Bottom-left
    mvwhline(_win, getmaxy(_win) - 1, 1, ACS_HLINE, width - 2); // Bottom border
    mvwaddch(_win, getmaxy(_win) - 1, width - 1, ACS_LRCORNER); // Bottom-right
    wrefresh(_win);
}

void dowwindow::_highlight_active_window()
{
    if (isActive) {
        wattron(_win, COLOR_PAIR(2)); // Use the highlight color
    } else {
        wattron(_win, COLOR_PAIR(1)); // Use the normal color
    }

    _draw_window_border();
    wattroff(_win, COLOR_PAIR(1)); // Reset colors
    wattroff(_win, COLOR_PAIR(2));

    wrefresh(_win);
}
