Challenge: Given a string of various parentheses, write a function to determine whether the parens are balanced properly.  
Interlocking parens are not allowed, so you can't just count the number of each.  
Bonus points if you do it with parser combinators.

"()" => True
"(())" => True
"()()" => True
"[()]" => True
"<{[()]}>" => True 
"(" => False
"[(])" => False
")(" => False
"()[[]](<><[()]>)" => True

```
psq95@psq-kde ~/d/parenbal> cmake -B _build
-- The C compiler identification is GNU 10.2.0
-- The CXX compiler identification is GNU 10.2.0
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /home/psq95/dev/parenbal/_build
psq95@psq-kde ~/d/parenbal> cmake --build _build/
gmake[1]: Entering directory '/home/psq95/dev/parenbal/_build'
gmake[2]: Entering directory '/home/psq95/dev/parenbal/_build'
Scanning dependencies of target parenbal
gmake[2]: Leaving directory '/home/psq95/dev/parenbal/_build'
gmake[2]: Entering directory '/home/psq95/dev/parenbal/_build'
[ 33%] Building C object CMakeFiles/parenbal.dir/src/parenbal.c.o
[ 66%] Building C object CMakeFiles/parenbal.dir/src/main.c.o
[100%] Linking C executable parenbal
gmake[2]: Leaving directory '/home/psq95/dev/parenbal/_build'
[100%] Built target parenbal
gmake[1]: Leaving directory '/home/psq95/dev/parenbal/_build'
psq95@psq-kde ~/d/parenbal> _build/parenbal
(0,0) PASS : 
(0,0) PASS : ()
(0,0) PASS : (())
(0,0) PASS : ()()
(0,0) PASS : [()]
(0,0) PASS : <{[()]}>
(1,1) PASS : (
(2,2) PASS : [(])
(1,1) PASS : )(
(0,0) PASS : ()[[]](<><[()]>)
psq95@psq-kde ~/d/parenbal> 
```

