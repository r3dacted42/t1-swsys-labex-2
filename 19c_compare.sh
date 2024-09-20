#!/bin/bash
# ========================================================================================
# Name:       Priyansh Agrahari
# Reg. No.:   MT2024120
# Date:       20 September 2024

# 19. Create a FIFO file by
#     a. mknod command
#     b. mkfifo command
#     c. use strace command to find out, which command (mknod or mkfifo) is better. <---
#     c. mknod system call
#     d. mkfifo library function
# ========================================================================================

t=$(date +%s)
name1="$(echo $t)_mknod.fifo"
name2="$(echo $t)_mkfifo.fifo"

echo "mknod uses mknodat:";
strace mknod $name1 p 2>&1 | tail -n 5;
echo;
echo "mkfifo also uses mknodat:";
strace mkfifo $name2 2>&1 | tail -n 5;
echo;
echo "hence, mknod is better";

rm $name1 $name2;

<<sample
Sample Execution:

$ sh 19c_compare.sh 
mknod uses mknodat:
mknodat(AT_FDCWD, "1726831135_mknod.fifo", S_IFIFO|0666) = 0
close(1)                                = 0
close(2)                                = 0
exit_group(0)                           = ?
+++ exited with 0 +++

mkfifo also uses mknodat:
mknodat(AT_FDCWD, "1726831135_mkfifo.fifo", S_IFIFO|0666) = 0
close(1)                                = 0
close(2)                                = 0
exit_group(0)                           = ?
+++ exited with 0 +++

hence, mknod is better

sample