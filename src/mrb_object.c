#include "mruby.h"
#include "mruby/data.h"
#include "mrb_games.h"

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

static mrb_value create_object(mrb_state *mrb, mrb_value self)
{
  mrb_games_data *data = DATA_PTR(self);
  printf("%s\n", data->str);
  return mrb_nil_value();
}


void mrb_objects_init(mrb_state *mrb) {
  struct RClass *games;
  games = mrb_define_class(mrb, "Game_Object", mrb->object_class);
  mrb_define_method(mrb, games, "initialize", mrb_object_init, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, games, "create_object", create_object, MRB_ARGS_NONE());
  DONE;
}


void mrb_mruby_object_gem_final(mrb_state *mrb)
{
}
