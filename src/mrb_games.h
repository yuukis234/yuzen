/*
** mrb_games.h - Games class
**
** See Copyright Notice in LICENSE
*/

#ifndef MRB_GAMES_H
#define MRB_GAMES_H
#include <GLFW/glfw3.h>

void mrb_mruby_games2_gem_init(mrb_state *mrb);
void mrb_window_init(mrb_state *mrb);
void mrb_objects_init(mrb_state *mrb);
void mrb_needs_init(mrb_state *mrb);
void mrb_key_bord_init(mrb_state *mrb);

#endif
