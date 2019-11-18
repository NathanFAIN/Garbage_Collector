# C-Garbage Collector

Un simple Garbage Collector en C...



La fonction `gc_get_ptr_list()` permet d'éviter une variable globale..

La fonction `gc_alloc_ptr_list` permet de malloc un pointeur à la taille désiré (avec un petit bonus), explication:

Imaginons que je souhaite  alloc un char * pour 5 caractères (mot "test\0")
```
|
+-+-+-+-+-+
|T|E|S|T|█|
+-+-+-+-+-+
|
```
Et bien, en réalité je vais alloc `5 + sizeof(void *)`, pour avoir cela:
```
                 Variable alloué pour l'utilisateur
                 |
                 |
                |↓
+-+-+-+-+-+-+-+-+-+-+-+-+-+
| | | | | | | | |T|E|S|T|█|
+-+-+-+-+-+-+-+-+-+-+-+-+-+
 ↑              |
 |
 |
 Adresse du prochain pointeur
```
Les 8 premiers octets me servirons à stocker la prochaine adresse que j'alloc avec la même fonction -> liste chainée!

Puis, comme on peut le deviner la fonction `gc_destroy_ptr_list()` pour deruire tout les pointeurs stocké dans la "liste chainé".. Avec la particularité d'avoir l'attribut `__attribute__ ((destructor))` qui permet d'appeler la fonction de façon automatique lors de la fermeture du programme (exit ou return), plutot partique pour un GC automatique!
```




```
Explication imagée:
```



                    Mémoire alloué en plus par le GC pour stocker l'adresse de la prochaine allocation
                    |            Mémoire alloué demandé par l'utilisateur
                    |            |
             +-------------+ +-------+
             |             | |       |
            +-+-+-+-+-+-+-+-+-+-+-+-+-+
    42      |0|0|0|0|0|0|0|0|T|E|S|T|█|
            +-+-+-+-+-+-+-+-+-+-+-+-+-+
            ↑                ↑
            |                Adresse donné à l'utilisateur (42 + 8)
            |
            |       Mémoire alloué en plus par le GC pour stocker l'adresse de la prochaine allocation
            |       |           Mémoire alloué demandé par l'utilisateur
            |       |           |
            |+-------------+ +-----+
            ||             | |     |
            +-+-+-+-+-+-+-+-+-+-+-+-+
    113     |4|2|0|0|0|0|0|0|O|U|I|█|
            +-+-+-+-+-+-+-+-+-+-+-+-+
            ↑                ↑
            |                Adresse donné à l'utilisateur (113 + 8)
            |
            |       Mémoire alloué en plus par le GC pour stocker l'adresse de la prochaine allocation
            |       |                 Mémoire alloué demandé par l'utilisateur
            |       |                 |
            |+-------------+ +---------------+
            ||             | |               |
            +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    189     |1|1|3|0|0|0|0|0|T|O|T|O|T|A|T|A|█|
            +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
                             ↑
                             Adresse donné à l'utilisateur (189 + 8)
```
## Sources:

[gcc-attibutes]: https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#Common-Function-Attributes
[gcc-garbage-collector]: https://en.wikipedia.org/wiki/Garbage_collection_(computer_science)

* **[GCC Attibutes][gcc-attibutes]**
* **[GCC Garbage Collector][gcc-garbage-collector]**
