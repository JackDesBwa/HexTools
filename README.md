Hexadecimal console utilities
=============================

Build
-----

There are one-file code without any special library needed. Thus it can
simply be build with default make rules. For example, to build "livehex"
just execute "make livehex".

livehex
-------

Livehex prints the bytes incomming from its standard input to their
hexadecimal notation on its standard output. It is similar to "od -t x1"
except that the data are not buffered.

This allows to analyse a stream which has low throughput without having
to wait for a complete 16 bytes emission.

For example, 
    dd if=/dev/urandom of=/dev/stdout count=20 bs=1 2>/dev/null | ./livehex
produces this kind of output
    0000000: 7C C9 7D 59 F9 AE F4 FB  8C 49 75 7B 69 EE CC F7 
    0000010: D4 DA 32 F3

bin2hex
-------

Bin2hex performs similar operation than livehex, but the output format
is different. It prints hexadecimal values separated by spaces without
any other presentation characters, except that each read batch is
separated by a new line character. This can be useful in interactive
programs.
