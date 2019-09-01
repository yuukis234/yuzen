#include "mruby.h"
#include "mruby/data.h"
#include "mruby/array.h"
#include "mrb_games.h"
#include <GLFW/glfw3.h>

#define DONE mrb_gc_arena_restore(mrb, 0);

typedef struct {
  char *str;
  int len;
} mrb_games_data;

static const struct mrb_data_type mrb_games_data_type = {
  "mrb_games_data", mrb_free,
};

static mrb_value mrb_object_init (mrb_state *mrb, mrb_value self)
{
  mrb_games_data *data;
  char *str;
  int len;

  data = (mrb_games_data *)DATA_PTR(self);
  if (data) {
    mrb_free(mrb, data);
  }
  DATA_TYPE(self) = &mrb_games_data_type;
  DATA_PTR(self) = NULL;

  mrb_get_args(mrb, "z", &str, &len);
  printf("%s\n", str);
  data = (mrb_games_data *)mrb_malloc(mrb, sizeof(mrb_games_data));
  data->str = str;
  data->len = len;
  DATA_PTR(self) = data;

  return self;
}

static mrb_value puts_str(mrb_state *mrb, mrb_value self)
{
  mrb_games_data *data = DATA_PTR(self);
  printf("%s\n", data->str);
  return mrb_nil_value();
}

static mrb_value create_object(mrb_state *mrb, mrb_value self)
{
  char *str;
  mrb_value test3 = mrb_ary_new(mrb);
  mrb_int lens = 1;
  mrb_get_args(mrb, "z|A", &str,  &test3);
  printf("%i\n", mrb_ary_ref(mrb, test3, lens));
  printf("%s\n", str);
  return mrb_nil_value();
}

static mrb_value create_triangle(mrb_state *mrb, mrb_value self) {
  /*背景の色を変更する*/
  glClearColor(0.6, 0.8, 1.0, 1.0);
  /* Render here */
  /*バッファを初期化するカラー情報を設定*/
  glClear(GL_COLOR_BUFFER_BIT);

  /*図形の色を変えます。*/
  glColor4f(1.0, 0.0, 0.0, 1.0);

  /*glBeginで図形を初期化*/
  glBegin(GL_TRIANGLES);
  /*glVertex2fで頂点を指定*/
  glVertex2f(   0,  0.5);
  glVertex2f(-0.5, -0.5);
  glVertex2f( 0.5, -0.5);
  glEnd();

  return mrb_nil_value();
}

void mrb_objects_init(mrb_state *mrb) {
  struct RClass *games;
  games = mrb_define_class(mrb, "Game_Object", mrb->object_class);
  mrb_define_method(mrb, games, "initialize", mrb_object_init, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, games, "puts_str", puts_str, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, games, "create_object", create_object, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, games, "create_triangle", create_triangle, MRB_ARGS_NONE());
  DONE;
}


void mrb_mruby_object_gem_final(mrb_state *mrb)
{
}
