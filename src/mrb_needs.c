#include "mruby.h"
#include "mruby/data.h"
#include "mruby/array.h"
#include "mrb_games.h"
#include <GLFW/glfw3.h>

#define DONE mrb_gc_arena_restore(mrb, 0);

typedef struct {
  char *str;
  int len;
  GLFWwindow *window;
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
  data->window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
  DATA_PTR(self) = data;
  printf("%i\n", data->window);

  return self;
}

static mrb_value bar_method(mrb_state* mrb, mrb_value self){
  mrb_games_data *h = DATA_PTR(self);
  printf("%i\n", h->window);
  return mrb_nil_value();
}

void mrb_needs_init(mrb_state *mrb) {
  struct RClass *games;
  games = mrb_define_class(mrb, "Game_Needs", mrb->object_class);
  mrb_define_method(mrb, games, "initialize", mrb_object_init, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, games, "tests", bar_method, MRB_ARGS_NONE());
  DONE;
}
