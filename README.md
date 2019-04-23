# mruby-games   [![Build Status](https://travis-ci.org/yuuki/mruby-games.svg?branch=master)](https://travis-ci.org/yuuki/mruby-games)
Games class
## install by mrbgems
- add conf.gem line to `build_config.rb`

```ruby
MRuby::Build.new do |conf|

    # ... (snip) ...

    conf.gem :github => 'yuuki/mruby-games'
end
```
## example
```ruby
p Games.hi
#=> "hi!!"
t = Games.new "hello"
p t.hello
#=> "hello"
p t.bye
#=> "hello bye"
```

## License
under the MIT License:
- see LICENSE file


## Testしてほしいところ。

開発環境: Ubuntu
glfwとglをインストールしてください。
rakeしたら、
```
./mruby/bin/mirb
```
でirbが起動するのでできるので
```
Omega.view
```

をすると画面が出ます。ここでポリゴンショックが起こります
