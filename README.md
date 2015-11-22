Hexadecimal console utilities
=============================

Build
-----

There are one-file code without any special library needed. Thus it can
simply be built with default make rules. For example, to build "livehex"
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

With the command

    echo -ne "\x1\x23\x45\x67\x89\xab\xcd\xef" | ./bin2hex

output is

     01 23 45 67 89 AB CD EF


hex2bin
-------

Hex2bin transforms standard input hexadecimal values to binary values.
The hex values can be formatted in various formats such as AA, aa, 0xAA,
0Xaa, 0xAa, etc. and must be separated by spaces. A non-hexadecimal
character stops evaluation of the line.

With the command

    echo "1 23 0x45 0X67 89 ab CD          eF" | ./hex2bin | od -t x1

output is

    0000000 01 23 45 67 89 ab cd ef
    0000010


schex
-----

Schex is a utility specially designed to be used with socat. It is like
a bin2hex from fd 3 to stderr and a hex2bin from stdin to stdout.

For example, the following command opens a tcp server on port 1234 with
socat. Incoming binary data are translated to hexadecimal and typing
hexadecial send answer back translated into binary.

    socat tcp-listen:1234,reuseaddr exec:./schex,fdin=3
