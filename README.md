# lab exercises 2
cs513 software systems; term 1, 2024-26  

## instructions to run

it is recommended to use the following script to run the C programs:
```bash
#!/bin/bash

args=""
for i in $(seq 2 $#)
do
        argi=${!i}
        args="$args $argi"
done
exe="run-$(date +%s).o"
if gcc $1 -o $exe
then
        ./$exe $args
        rm $exe
fi
```
save the script as runc.sh and use `chmod u+x runc.sh` to allow it to function properly. additionally, you can add the line `alias runc='<path-to-runc.sh>'` to the `~/.bashrc` file to use the script from any directory. don't forget to use a fresh terminal instance after editing `~/.bashrc`!

to run any C program, use
`runc <filename.c> <additional-args-here>`

## other remarks

- no one will probably ever read this anyway :)
  
thank you

