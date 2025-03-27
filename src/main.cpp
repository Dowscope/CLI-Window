#include <curses.h>
#include <vector>
#include <cstdlib>
#include "dowwindow.h"


std::vector<dowwindow*> windows;

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

void commandList(dowwindow* win) {
    win->writeText(1, 3, "Switch to window [#] | [q]uit", true);
}

bool checkWindowStatus(int index){
    return windows[index]->isSelectable();
}

int main() {
    init_ncurses();

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x); 

    windows.push_back( new dowwindow(max_y-5, max_x/2, 0, 0, "CLI Window 1!", true) );
    windows.push_back( new dowwindow(max_y-5, max_x/2+1, 0, max_x/2, "CLI Window 2!", true) );
    windows.push_back( new dowwindow(5, max_x, max_y-5, 0, "Commands Available", false) );

    commandList(windows[2]);

    int active_win = 0;
    windows[active_win]->setActive(true);

    // Main loop to wait for the 'q' key
    bool running = true;
    while (running) {
        // Do something if you want while waiting for 'q'
        // For example, print something based on other keypresses
        int ch = wgetch(windows[active_win]->getWindow());

        if (ch == KEY_DOWN || ch == KEY_UP || ch == KEY_LEFT || ch == KEY_RIGHT) {
            windows[active_win]->writeText( 2, 1, "Arrow key pressed!" );
        } else if (ch == 'q') {
            running = false;
        } else if (ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch == '9') {
            char keyStr[2] = { static_cast<char>(ch), '\0' };
            int screenIndex = atoi(keyStr) - 1;
            if (screenIndex < windows.size() && windows[screenIndex]->isSelectable()) {
                active_win = screenIndex;
            }

        } else {
            char buffer[20];
            sprintf(buffer, "Key pressed: %d", ch);
            windows[active_win]->writeText( 2, 1, buffer );
        }

        // Refresh all windows
        for (auto win : windows) {
            win->setActive(windows[active_win] == win);
        }
    }
    

    endwin();
    return 0;
}