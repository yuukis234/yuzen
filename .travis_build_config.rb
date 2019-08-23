MRuby::Build.new do |conf|
  toolchain :gcc
  conf.gembox 'default'
  conf.gem File.expand_path(File.dirname(__FILE__))
  conf.enable_test

  conf.linker do |linker|
    linker.libraries = ["glfw3", "GL", "m", "dl",
                        "Xinerama", "Xrandr", "Xi",
                        "Xcursor", "X11", "Xxf86vm", "pthread", "SDL2"]
  end

  if ENV['DEBUG'] == 'true'
    conf.enable_debug
    conf.cc.defines = %w(MRB_ENABLE_DEBUG_HOOK)
    conf.gem core: 'mruby-bin-debugger'
  end
end
