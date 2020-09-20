


## Score: 70/90 (77.78%)


### ✓ - [0/0] - Output from `make`

- **Points**: 0 / 0


```
clang++  -std=c++1y -stdlib=libc++ -O0 -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -MMD -MP -g -c -Wno-delete-non-virtual-dtor circle.cpp -o .objs/circle.o
clang++  -std=c++1y -stdlib=libc++ -O0 -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -MMD -MP -g -c -Wno-delete-non-virtual-dtor flower.cpp -o .objs/flower.o
clang++  -std=c++1y -stdlib=libc++ -O0 -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -MMD -MP -g -c -Wno-delete-non-virtual-dtor line.cpp -o .objs/line.o
clang++  -std=c++1y -stdlib=libc++ -O0 -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -MMD -MP -g -c -Wno-delete-non-virtual-dtor rectangle.cpp -o .objs/rectangle.o
clang++  -std=c++1y -stdlib=libc++ -O0 -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -MMD -MP -g -c -Wno-delete-non-virtual-dtor shape.cpp -o .objs/shape.o
clang++  -std=c++1y -stdlib=libc++ -O0 -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -MMD -MP -g -c -Wno-delete-non-virtual-dtor triangle.cpp -o .objs/triangle.o
clang++  -std=c++1y -stdlib=libc++ -O0 -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -MMD -MP -g -c -Wno-delete-non-virtual-dtor truck.cpp -o .objs/truck.o
clang++  -std=c++1y -stdlib=libc++ -O0 -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -MMD -MP -g -c -Wno-delete-non-virtual-dtor vector2.cpp -o .objs/vector2.o
clang++  -std=c++1y -stdlib=libc++ -O0 -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -MMD -MP -g -c -Wno-delete-non-virtual-dtor cs225/HSLAPixel.cpp -o .objs/cs225/HSLAPixel.o
clang++  -std=c++1y -stdlib=libc++ -O0 -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -MMD -MP -g -c -Wno-delete-non-virtual-dtor cs225/PNG.cpp -o .objs/cs225/PNG.o
clang++  -std=c++1y -stdlib=libc++ -O0 -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -MMD -MP -g -c -Wno-delete-non-virtual-dtor cs225/lodepng/lodepng.cpp -o .objs/cs225/lodepng/lodepng.o
clang++  -std=c++1y -stdlib=libc++ -O0 -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -MMD -MP -g -c -Wno-delete-non-virtual-dtor tests/tests.cpp -o .objs/tests/tests.o
clang++  -std=c++1y -stdlib=libc++ -O0 -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -MMD -MP -g -c -Wno-delete-non-virtual-dtor cs225/catch/catchmain.cpp -o .objs/cs225/catch/catchmain.o
clang++ .objs/circle.o .objs/flower.o .objs/line.o .objs/rectangle.o .objs/shape.o .objs/triangle.o .objs/truck.o .objs/vector2.o .objs/cs225/HSLAPixel.o .objs/cs225/PNG.o .objs/cs225/lodepng/lodepng.o .objs/tests/tests.o .objs/cs225/catch/catchmain.o  -std=c++1y -stdlib=libc++ -lc++abi -o test

```


### ✓ - [10/10] - test_virtual_perim

- **Points**: 10 / 10





### ✓ - [10/10] - test_virtual_area

- **Points**: 10 / 10





### ✓ - [20/20] - test_destructor

- **Points**: 20 / 20

```
==72== Memcheck, a memory error detector
==72== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==72== Using Valgrind-3.14.0 and LibVEX; rerun with -h for copyright info
==72== Command: ./test -r xml "test_destructor"
==72== 
==72== 
==72== HEAP SUMMARY:
==72==     in use at exit: 0 bytes in 0 blocks
==72==   total heap usage: 1,667 allocs, 1,667 frees, 216,576 bytes allocated
==72== 
==72== All heap blocks were freed -- no leaks are possible
==72== 
==72== For counts of detected and suppressed errors, rerun with: -v
==72== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

```



### ✓ - [20/20] - test_constructor

- **Points**: 20 / 20





### ✓ - [10/10] - test_pure_virtual

- **Points**: 10 / 10

```
==75== Memcheck, a memory error detector
==75== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==75== Using Valgrind-3.14.0 and LibVEX; rerun with -h for copyright info
==75== Command: ./test -r xml "test_pure_virtual"
==75== 
==75== 
==75== HEAP SUMMARY:
==75==     in use at exit: 0 bytes in 0 blocks
==75==   total heap usage: 1,728 allocs, 1,728 frees, 1,757,183 bytes allocated
==75== 
==75== All heap blocks were freed -- no leaks are possible
==75== 
==75== For counts of detected and suppressed errors, rerun with: -v
==75== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

```



### ✗ - [0/20] - test_slicing

- **Points**: 0 / 20

```
==77== Memcheck, a memory error detector
==77== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==77== Using Valgrind-3.14.0 and LibVEX; rerun with -h for copyright info
==77== Command: ./test -r xml "test_slicing"
==77== 
==77== 
==77== HEAP SUMMARY:
==77==     in use at exit: 264 bytes in 7 blocks
==77==   total heap usage: 1,794 allocs, 1,787 frees, 1,759,556 bytes allocated
==77== 
==77== 64 bytes in 1 blocks are definitely lost in loss record 5 of 7
==77==    at 0x4C29EA3: malloc (vg_replace_malloc.c:309)
==77==    by 0x40475CB: operator new(unsigned long) (in /usr/local/lib/libc++abi.so.1.0)
==77==    by 0x407A35: Flower::Flower(Vector2 const&) (flower.cpp:36)
==77==    by 0x42BD87: ____C_A_T_C_H____T_E_S_T____10() (tests.cpp:134)
==77==    by 0x460CC2: Catch::TestInvokerAsFunction::invoke() const (catch.hpp:10892)
==77==    by 0x451416: Catch::TestCase::invoke() const (catch.hpp:10793)
==77==    by 0x45134C: Catch::RunContext::invokeActiveTestCase() (catch.hpp:9658)
==77==    by 0x44D8A6: Catch::RunContext::runCurrentTest(std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >&, std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >&) (catch.hpp:9622)
==77==    by 0x44BE7E: Catch::RunContext::runTest(Catch::TestCase const&) (catch.hpp:9408)
==77==    by 0x455216: Catch::(anonymous namespace)::runTests(std::__1::shared_ptr<Catch::Config> const&) (catch.hpp:9948)
==77==    by 0x453EB2: Catch::Session::runInternal() (catch.hpp:10149)
==77==    by 0x453B7A: Catch::Session::run() (catch.hpp:10106)
==77== 
==77== 64 bytes in 1 blocks are definitely lost in loss record 6 of 7
==77==    at 0x4C29EA3: malloc (vg_replace_malloc.c:309)
==77==    by 0x40475CB: operator new(unsigned long) (in /usr/local/lib/libc++abi.so.1.0)
==77==    by 0x407A94: Flower::Flower(Vector2 const&) (flower.cpp:38)
==77==    by 0x42BD87: ____C_A_T_C_H____T_E_S_T____10() (tests.cpp:134)
==77==    by 0x460CC2: Catch::TestInvokerAsFunction::invoke() const (catch.hpp:10892)
==77==    by 0x451416: Catch::TestCase::invoke() const (catch.hpp:10793)
==77==    by 0x45134C: Catch::RunContext::invokeActiveTestCase() (catch.hpp:9658)
==77==    by 0x44D8A6: Catch::RunContext::runCurrentTest(std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >&, std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >&) (catch.hpp:9622)
==77==    by 0x44BE7E: Catch::RunContext::runTest(Catch::TestCase const&) (catch.hpp:9408)
==77==    by 0x455216: Catch::(anonymous namespace)::runTests(std::__1::shared_ptr<Catch::Config> const&) (catch.hpp:9948)
==77==    by 0x453EB2: Catch::Session::runInternal() (catch.hpp:10149)
==77==    by 0x453B7A: Catch::Session::run() (catch.hpp:10106)
==77== 
==77== 136 (64 direct, 72 indirect) bytes in 1 blocks are definitely lost in loss record 7 of 7
==77==    at 0x4C29EA3: malloc (vg_replace_malloc.c:309)
==77==    by 0x40475CB: operator new(unsigned long) (in /usr/local/lib/libc++abi.so.1.0)
==77==    by 0x407BB9: Flower::Flower(Vector2 const&) (flower.cpp:43)
==77==    by 0x42BD87: ____C_A_T_C_H____T_E_S_T____10() (tests.cpp:134)
==77==    by 0x460CC2: Catch::TestInvokerAsFunction::invoke() const (catch.hpp:10892)
==77==    by 0x451416: Catch::TestCase::invoke() const (catch.hpp:10793)
==77==    by 0x45134C: Catch::RunContext::invokeActiveTestCase() (catch.hpp:9658)
==77==    by 0x44D8A6: Catch::RunContext::runCurrentTest(std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >&, std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >&) (catch.hpp:9622)
==77==    by 0x44BE7E: Catch::RunContext::runTest(Catch::TestCase const&) (catch.hpp:9408)
==77==    by 0x455216: Catch::(anonymous namespace)::runTests(std::__1::shared_ptr<Catch::Config> const&) (catch.hpp:9948)
==77==    by 0x453EB2: Catch::Session::runInternal() (catch.hpp:10149)
==77==    by 0x453B7A: Catch::Session::run() (catch.hpp:10106)
==77== 
==77== LEAK SUMMARY:
==77==    definitely lost: 192 bytes in 3 blocks
==77==    indirectly lost: 72 bytes in 4 blocks
==77==      possibly lost: 0 bytes in 0 blocks
==77==    still reachable: 0 bytes in 0 blocks
==77==         suppressed: 0 bytes in 0 blocks
==77== 
==77== For counts of detected and suppressed errors, rerun with: -v
==77== ERROR SUMMARY: 3 errors from 3 contexts (suppressed: 0 from 0)

```



---

This report was generated for **yueqij2** using **28abbc5c99dc6a489f32b9f085b7a6cbe4c3e073** (from **September 19th 2020, 10:15:41 pm**)
