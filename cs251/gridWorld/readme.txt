The driver can read in all arguments except for the rand one it gives an error while comparing and i dont know why. Also if an invalid command is entered after the menu is displayed it displays an ivalid input error but the menu does not display again.

As for gw.c all function work as intended in the required run time except for a few cases involoving district 0,0. when a person is killed from this district an extra 0 is printed at the end of its members list as well as the id of the person kill being printed at the begining. this error seems to only occur for this district which is confusing. A similar error happens when using the create function on district 0,0.
it increase the population of both the district and the world but gives the person an id of 0.

gcc -c gw.c
gcc main.c gw.o -o gwsim
