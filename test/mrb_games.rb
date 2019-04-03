##
## Games Test
##

assert("Games#hello") do
  t = Games.new "hello"
  assert_equal("hello", t.hello)
end

assert("Games#bye") do
  t = Games.new "hello"
  assert_equal("hello bye", t.bye)
end

assert("Games.hi") do
  assert_equal("hi!!", Games.hi)
end
