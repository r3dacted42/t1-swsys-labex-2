#!/bin/bash
# ========================================================================================
# Name:       Priyansh Agrahari
# Reg. No.:   MT2024120
# Date:       20 September 2024

# 19. Create a FIFO file by
#     a. mknod command
#     b. mkfifo command <---
#     c. use strace command to find out, which command (mknod or mkfifo) is better.
#     c. mknod system call
#     d. mkfifo library function
# ========================================================================================

if mkfifo 19b.fifo
then
    echo "open ./19b.fifo in read mode to get the message";
    echo "hello there, this was written to the fifo pipe!" > 19b.fifo
fi

<<sample
Sample Execution:

$ sh 19b_mknod_pipe.sh 
open the pipe in read mode to get the message

--on another terminal instance:
$ cat 19b.fifo
hello there, this was written to the fifo pipe!

$ ll
...
prw-r--r-- 1 r3dacted42 r3dacted42     0 Sep 20 16:36 19b.fifo|
...

sample