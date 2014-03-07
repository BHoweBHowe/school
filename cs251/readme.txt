I'm not sure if the sset_free function works as intended but everything else should work.

compile with
$gcc -c sset.c
$gcc toy.c sset.o -o toy
