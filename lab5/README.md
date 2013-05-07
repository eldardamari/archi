#task0 - notes

- These routines have traditionally been used by programs to save the name
of a working directory for the purpose of returning to it.  A much faster
and less error-prone method of accomplishing this is to open the current
directory (`.') and use the fchdir(2) function to return.

- execve ,read man 3
