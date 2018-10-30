#include <ncurses.h>

#include <string>
#include <unistd.h>
#include <cstdint>

#include "game.h"

WINDOW* wnd;

struct {
  vec2i pos;
  char disp_char;
} player;

int init() {
  wnd = initscr();
  cbreak();
  noecho();
  clear();
  refresh();

  // enable function keys
  keypad(wnd, true);

  // disable input blocking
  nodelay(wnd, true);

  // hide cursor
  curs_set(0);

  if(!has_colors()) {
    endwin();
    printf("ERROR: Terminal does not support color.\n");
    exit(1);
  }


  attron(A_BOLD);
  box(wnd, 0, 0);
  attroff(A_BOLD);

  return 0;
}


void run() {

  player.disp_char = '❤';
  player.pos = {10, 5};
  int in_char;
  bool exit_requested = false;

  while(1) {
    in_char = wgetch(wnd);
    mvaddch(player.pos.y, player.pos.x, ' ');

    switch(in_char) {
      case 'q':
        exit_requested = true;
        break;
      case KEY_UP:
      case 'w':
        player.pos.y -= 1;
        break;
      case KEY_DOWN:
      case 's':
        player.pos.y += 1;
        break;
      case KEY_LEFT:
      case 'a':
        player.pos.x -= 1;
        break;
      case KEY_RIGHT:
      case 'd':
        player.pos.x += 1;
        break;
      default:
        break;
    }

    mvaddch(player.pos.y, player.pos.x, player.disp_char);
    refresh();

    if(exit_requested) break;
  }
}


void close() {
  endwin();
}