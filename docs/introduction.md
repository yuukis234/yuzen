#Introduction

プログラマーがゲームロジックを再現しやすく、よりよいゲーム作成ができるようにするフレームワーク
表現しやすい環境を整える。

#使うオブジェクト集

##Gameloop
###intorduction
ゲームのメインループを制御するクラス。
このループ内でWindow, Context, Vulkan, Monitor, Inputを使った制御を行う。


##Window
###introduction
表示するWindowを制御するクラス。
必要な表示をこの場で行う。

##Context
###introduction
全体の制御を行うクラス。

##Vulkan
###introduction
３D制御を行うクラス

##Monitor
###introduction
表示を制御するクラス

##Input
###introduction
入力制御をしてくれるクラス
