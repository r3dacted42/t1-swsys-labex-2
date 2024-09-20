#!/bin/bash
# ========================================================================================
# Name:       Priyansh Agrahari
# Reg. No.:   MT2024120
# Date:       20 September 2024

# 19. Create a FIFO file by
#     a. mknod command <---
#     b. mkfifo command
#     c. use strace command to find out, which command (mknod or mkfifo) is better.
#     c. mknod system call
#     d. mkfifo library function
# ========================================================================================

if mknod 19a.fifo p
then
    echo "open ./19a.fifo in read mode to get the message";
    echo "hello there, this was written to the fifo pipe!" > 19a.fifo
fi

<<sample
Sample Execution:

$ sh 19a_mknod_pipe.sh 
open the pipe in read mode to get the message

--on another terminal instance:
$ cat 19a.fifo
hello there, this was written to the fifo pipe!

$ ll
...
prw-r--r-- 1 r3dacted42 r3dacted42     0 Sep 20 16:33 19a.fifo|
...

sample