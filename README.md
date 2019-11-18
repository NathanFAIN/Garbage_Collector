# C-Knowledge

A simple garbage collector in C...

La premiere fonction `gc_get_ptr_list()` est juste là pour éviter un variable globale..
La fonction `gc_alloc_ptr_list` permet de malloc un pointeur à la taille désiré (avec un petit bonus), je m'explique:
Imaginons tu veux alloc un char * pour 5 caractères (mot "test\0")
```
+-+-+-+-+-+
|T|E|S|T|█|
+-+-+-+-+-+
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
Les 4 premiers octets me servirons pour stocker la prochaine adresse que j'alloc avec la meme fonction -> liste chainée!
Sauf que du coup j'utilise un seul malloc pour alouer deux choses, je ne sais pas si c'est malin..

Puis comme tu peux le deviner la fonction `gc_destroy_ptr_list()` pour deruire tout les pointeurs stocké dans la "liste chainé".. Avec la particularité d'avoir l'attribut `__attribute__ ((destructor))` qui permet d'appeler la fonction de facon automatique lors de la fermeture du programme (exit ou return), plutot partique pour un GC full auto!

Le "tricks" `*(void **)ptr` permet de prendre les `sizeof(void *)` premiers octets de la à l'adresse de `ptr`. Si on traduit en francais -> "on prend la valeur à l'index 0 du tableau de `void *` de ptr"












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
