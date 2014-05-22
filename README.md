bomberman
=========

(Relativement) Important
------------------------
Les tabulations c'est nulle !

Heureusement, avec sublime text:
> 1. ctrl+shift+p
> 2. lancez 'install package'
> 3. installez 'editorconfig'.

Le fichier '.editorconfig' à la racine du dépot prendra effet et les tabulations seront desormais remplacées par 4 espaces.


Authors
-------
![Alt text](./avatars/delemo_b.png "delemo_b")
![Alt text](./avatars/sauval_d.jpeg "sauval_d")
![Alt text](./avatars/svirch_n.png "svirch_n")
![Alt text](./avatars/defrei_r.png "defrei_r")
![Alt text](./avatars/parejo_p.png "parejo_p")

Compilation
-----------
#####Basic :
~~~bash
$ make 
~~~

#####Maybe you prefer clang ?
~~~bash
$ make CXX=clang++
~~~
Warning: it's possible you could not compile the project with clang-3.0. Please, use clang-3.5 instead.

#####Debug or not debug :
~~~bash
$ make DEBUG=1
$ make DEBUG=0
~~~
Currently, by default DEBUG equals 1.

#####Optimisations :
~~~bash
$ make OPTI=3
~~~
This will compile with -03 (the default value).
Note: if DEBUG is enable, OPTI is ignored in order to let you debug the program correctly.

Sound Manager
-------------
#####Format :
Musique d'ambiance : .mp3<br/>
Fx : .wav

#####Dependency :
libsdl-mixer1.2-dev
