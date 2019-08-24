/*
** mrb_games.c - Games class
**
** Copyright (c) yuuki 2019
**
** See Copyright Notice in LICENSE
*/

#include "mruby.h"
#include "mruby/data.h"
#include "mruby/variable.h"
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

static mrb_value mrb_games_init(mrb_state *mrb, mrb_value self)
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

  mrb_get_args(mrb, "s", &str, &len);
  data = (mrb_games_data *)mrb_malloc(mrb, sizeof(mrb_games_data));
  data->str = str;
  data->len = len;
  DATA_PTR(self) = data;

  return self;
}


static mrb_value mrb_games_view(mrb_state *mrb, mrb_value self)
{
  GLFWwindow* window;

    /* Initialize the library */
    /* ここでゲーム自体を初期化します。ここでイニシャライズできなければnilを返します。*/
    if (!glfwInit())
        return mrb_nil_value();

    /* Create a windowed mode window and its OpenGL context */
    /* ここで画面を設定します。*/
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return mrb_nil_value();
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    /* ここでメインロジックをループさせます。*/
    /* TODO:このループをループクラスとして作る*/
    while (!glfwWindowShouldClose(window))
    {
        /*背景の色を変更する*/
        glClearColor(0.6, 0.8, 1.0, 1.0);
        /* Render here */
        /*バッファを初期化するカラー情報を設定*/
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        /* windowを入れ替える。 */
        glfwSwapBuffers(window);

        /*図形の色を変えます。*/
        glColor4f(1.0, 0.0, 0.0, 1.0);

        /*glBeginで図形を初期化*/
        glBegin(GL_TRIANGLES);
        /*glVertex2fで頂点を指定*/
        glVertex2f(   0,  0.5);
        glVertex2f(-0.5, -0.5);
        glVertex2f( 0.5, -0.5);
        glEnd();

        /* windowをbuffewから交換シアmス*/
        glfwSwapBuffers(window);
        /* Poll for and process events */
        /* マウスの操作などのイベントを取り出し、それを記録します。*/
        glfwPollEvents();
    }

    /* ここでゲーム自体を終了させます。*/
    glfwTerminate();
    return mrb_nil_value();
}

mrb_value bar_method(mrb_state* mrb, mrb_value self){
  puts("Executing example command!");
  return mrb_attr_get(mrb, self, mrb_intern_str(mrb, mrb_str_new_lit(mrb, "data" )));
}

void mrb_window_init(mrb_state *mrb)
{
  struct RClass *window;
  window = mrb_define_class(mrb, "Window", mrb->object_class);
  mrb_define_method(mrb, window, "initialize", mrb_games_init, MRB_ARGS_REQ(2));
  mrb_define_class_method(mrb, window, "view", mrb_games_view, MRB_ARGS_NONE());
  mrb_define_method(mrb, window, "tests", bar_method, MRB_ARGS_NONE());
  DONE;
}

void mrb_window_init_final(mrb_state *mrb)
{
}
