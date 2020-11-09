# Kapish

Kapish is a minimal but realistic killer application interactive UNIX shell.

## Getting Started

The zip file include:
* doublylinkedlist.c
  **the container program of history command information**
* doublylinkedlist.h
* .kapishrc
  **includes some testing commands**
* kapish.c
  **the shell program**
* Makefile
* README.md

## Running the tests


The demo: 
```
? make
? ./kapish
```

### Break down into end to end tests
Some testing command example

```
setenv A b
test built-in command setenv, should add one environment variable A, pass the value b to A.
```

```
unsetenv A 
test built-in command unsetenv, should delete the environment variable A.
```

```
cd
test built-in command cd when argument is ommitted, should change dir to the HOME directory
```
```
cd ../kapish
test built-in command cd, shoud change to the directory follow the argument.
```
```
ls -a 
test library command ls with option all files, should list all file include hidden ones in current directory.
```
```
history 
test built-in command history, should standard print out the list of history commands from the very beginning to recent one. 
```
```
!l
test built-in command history, should find the rencent command match string "l" and excute the commond. 
```
```
akldjfao;iekhqpoilegj[oaig!dawerioqwjoirqkjw[oeirqw[oerjq[oiero[qweri[oqpiwer[oqweriqjweoirjqweirjqweoijfqeruitjh10934=910-erqweoiruqp9i423jr1349ru31oi4jrpi1o34j5oi134jr1oi34j5134i51345134r9123951=-39451025ui3o4tj2oi34i5109u4t193j4t[314opi51034u9t24utoi3u415051[04i5r1o3utr
akldjfao;iekhqpoilegj[oaig!dawerioqwjoirqkjw[oeirqw[oerjq[oiero[qweri[oqpiwer[oqweriqjweoirjqweirjqweoijfqeruitjh10934=910-erqweoiruqp9i423jr1349ru31oi4jrpi1o34j5oi134jr1oi34j5134i51345134r9123951=-39451025ui3o4tj2oi34i5109u4t193j4t[314opi51034u9t24utoi3u415051[04i5r1o3utr
akldjfao;iekhqpoilegj[oaig!dawerioqwjoirqkjw[oeirqw[oerjq[oiero[qweri[oqpiwer[oqweriqjweoirjqweirjqweoijfqeruitjh10934=910-erqweoiruqp9i423jr1349ru31oi4jrpi1o34j5oi134jr1oi34j5134i51345134r9123951=-39451025ui3o4tj2oi34i5109u4t193j4t[314opi51034u9t24utoi3u415051[04i5r1o3utr
akldjfao;iekhqpoilegj[oaig!dawerioqwjoirqkjw[oeirqw[oerjq[oiero[qweri[oqpiwer[oqweriqjweoirjqweirjqweoijfqeruitjh10934=910-erqweoiruqp9i423jr1349ru31oi4jrpi1o34j5oi134jr1oi34j5134i51345134r9123951=-39451025ui3o4tj2oi34i5109u4t193j4t[314opi51034u9t24utoi3u415051[04i5r1o3utr
akldjfao;iekhqpoilegj[oaig!dawerioqwjoirqkjw[oeirqw[oerjq[oiero[qweri[oqpiwer[oqweriqjweoirjqweirjqweoijfqeruitjh10934=910

test uncommand name string which acced 512, should just standard print the line without crash kapish.
```
```
exit
test built-in command exit, should terminate kapish succesfully.
```

## Author

* **Yue Lyu** - V00902738



## Acknowledgments

* Googled several liabrary function in C
*  *Get inspired by* - [Stephen Brennan](https://brennan.io/2015/01/16/write-a-shell-in-c/)


