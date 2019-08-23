class Games
  def bye
    self.hello + " bye"
  end
end

class Gameloop
  # ゲームを起動を担うクラス
  # ここで、Window, Context, Vulkan, Monitor, Keybordを呼び出す
  # 上記のクラスを使って、ゲームを作っていく。
  def self.main_loop
    #windowの初期化
    #windowをメインループさせる。
    Window.view
  end
end

class Window
  def self.init()
    puts ("initialize!")
  end
end

class Context
end

class Vulkan
end

class Monitor
end

class Input
end
