# C-Garbage Collector

A simple Garbage Collector in C ...


The function `gc_get_ptr_list()` avoids a global variable...

The function `gc_alloc_ptr_list` avoids to alloc the pointer with the desired size + `sizeof(void *)`, explanation:

Let's say I want to allocate a char * for 5 characters (word "test\0")
```
|
+-+-+-+-+-+
|T|E|S|T|█|
+-+-+-+-+-+
|
```
Well, in reality I'm going to allocate `5 + sizeof (void *)`, to get that:
```
                 Memory allocated for user
                 |
                 |
                |↓
+-+-+-+-+-+-+-+-+-+-+-+-+-+
| | | | | | | | |T|E|S|T|█|
+-+-+-+-+-+-+-+-+-+-+-+-+-+
 ↑              |
 |
 |
 Next pointer address

```
The first 8 bytes will be used to store the next allocated address I assign with the same function -> linked list!

With the particularity of having the attributes `__attribute__ ((destructor))` causes the function to be called automatically after execution enters `main()`. All stored pointers in the list are `free` at the end of the program.





Graphically explanation:
```



                    Memory allocated in addition by the GC to store the address of the next allocation
                    |            Allocated memory requested by the user
                    |            |
             +-------------+ +-------+
             |             | |       |
            +-+-+-+-+-+-+-+-+-+-+-+-+-+
    42      |0|0|0|0|0|0|0|0|T|E|S|T|█|
            +-+-+-+-+-+-+-+-+-+-+-+-+-+
            ↑                ↑
            |                Address given to the user (42 + 8)
            |
            |       Memory allocated in addition by the GC to store the address of the next allocation
            |       |           Allocated memory requested by the user
            |       |           |
            |+-------------+ +-----+
            ||             | |     |
            +-+-+-+-+-+-+-+-+-+-+-+-+
    113     |4|2|0|0|0|0|0|0|O|U|I|█|
            +-+-+-+-+-+-+-+-+-+-+-+-+
            ↑                ↑
            |                Address given to the user (113 + 8)
            |
            |       Memory allocated in addition by the GC to store the address of the next allocation
            |       |                 Allocated memory requested by the user
            |       |                 |
            |+-------------+ +---------------+
            ||             | |               |
            +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    189     |1|1|3|0|0|0|0|0|T|O|T|O|T|A|T|A|█|
            +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
                             ↑
                             Address given to the user (189 + 8)
```
## Sources:

[gcc-attibutes]: https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#Common-Function-Attributes
[garbage-collector]: https://en.wikipedia.org/wiki/Garbage_collection_(computer_science)

* **[GCC Attibutes][gcc-attibutes]**
* **[Garbage Collector][garbage-collector]**
