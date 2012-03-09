#include "events.h"
#include "snake.h"
#include "fruits.h"

int check_fruit_collision(GAME* game, int cury, int curx) {
  return fruit_is_on(&game->fruits, cury, curx) != NULL;
}
 
int check_fruit_collision_handler(GAME* game, int cury, int curx) {
  kill_fruit(&game->fruits, cury, curx);
  grow_fruit(game);
  game->snake.grow++;
  game->highscore++;
  glog("fruit collision");
  return 1;
}

int check_border_collision(GAME* game, int cury, int curx) {
  int y,x;
  getmaxyx(stdscr, y, x);
  y--;
  x--;
  return cury <= 0 || curx <= 0 || cury >= y || curx >= x;
}

int check_extended_border_collision(GAME* game, int cury, int curx) {
  int y,x, range, rangex1, rangex2, rangey1, rangey2;
  getmaxyx(stdscr, y, x);
  range = x / 2;
  rangex1 = range * 0.9;
  rangex2 = range * 1.1;

  range = y / 2;
  rangey1 = range * 0.9;
  rangey2 = range * 1.1;
  return check_border_collision(game, cury, curx)
    && !(curx >= rangex1 && curx <= rangex2 || cury >= rangey1 && cury <= rangey2);
}

int check_border_collision_handler(GAME* game, int cury, int curx) {
  glog("border collision %i %i", cury, curx);
  return 0;
}

int check_self_collision(GAME* game, int cury, int curx) {
  int back = 0;
  WINDOW* on;
  glog("SNAKE PART ON %i %i", cury, curx);
  back = ! ((on = snake_part_is_on(&game->snake, cury, curx)) == NULL || on == game->snake.parts[game->snake.length - 1]);
  glog("returning %i", back);
  return back;
}

int check_self_collision_handler(GAME* game, int cury, int curx) {
  glog("self collision");
  return 0;
}