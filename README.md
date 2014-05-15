bomberman
=========

Authors
-------
![Alt text](./avatars/delemo_b.png "Optional title")


Compilation
-----------
#####Basic :
~~~bash
$ make 
~~~


#####Debug or not debug :
~~~bash
$ make DEBUG=1
$ make DEBUG=0
~~~
Currently, by default DEBUG equals 0.


#####Optimisations :
~~~bash
$ make OPTI=3
~~~
This will compile with -03 (the default value).
Note: if DEBUG is enable, OPTI is ignored in order to let you debug the program correctly.
