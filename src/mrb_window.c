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

static mrb_value mrb_games_window(mrb_state *mrb, mrb_value self)
{
  return mrb_nil_value();
}

static mrb_value mrb_games_view(mrb_state *mrb, mrb_value self)
{
  GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return mrb_nil_value();

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return mrb_nil_value();
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.6, 0.8, 0.8, 1.0);
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        glColor4f(1.0, 0.0, 0.0, 1.0);

        glBegin(GL_TRIANGLES);
        glVertex2f(   0,  0.5);
        glVertex2f(-0.5, -0.5);
        glVertex2f( 0.5, -0.5);
        glEnd();

        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

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
  mrb_define_class_method(mrb, window, "windowconf", mrb_games_window, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, window, "test", mrb_games_window, MRB_ARGS_NONE());
  mrb_define_method(mrb, window, "tests", bar_method, MRB_ARGS_NONE());
  DONE;
}

void mrb_window_init_final(mrb_state *mrb)
{
}
