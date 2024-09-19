#!/bin/bash
# ========================================================================================
# Name:       Priyansh Agrahari
# Reg. No.:   MT2024120
# Date:       19 September 2024

# 13. Write two programs: first program is waiting to catch SIGSTOP signal,
# the second program will send the signal (using kill system call). Find out whether the 
# first program is able to catch the signal or not.
# ========================================================================================

echo "starting 13_try_to_catch.c...";
gcc 13_try_to_catch.c -o 13_try.o;
./13_try.o &
pid=$!

echo "starting and sending pid to 13_send_stop.c...";
gcc 13_send_stop.c -o 13_send.o;
./13_send.o $pid;

echo "checking status of $pid:";
cat /proc/$pid/status | head -n 6;

echo "killing $pid...";
kill -9 $pid;

echo "deleting executables...";
rm 13_try.o 13_send.o;

<<sample
$ sh 13_check.sh
starting 13_try_to_catch.c...
starting and sending pid to 13_send_stop.c...
[189579 P1] waiting for SIGSTOP...
[189591 P2] received pid: 189579
[189591 P2] SIGSTOP sent to 189579, exiting...
checking status of 189579:
Name:   13_try.o
Umask:  0022
State:  T (stopped)
Tgid:   189579
Ngid:   0
Pid:    189579
killing 189579...
deleting executables...

sample