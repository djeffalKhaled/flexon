## About:
One tiring aspect about bison and flex is the lack of a direct way to generate at least a starter project and a single-line execution command, this CLI tool makes it easier:

https://github.com/user-attachments/assets/462f9ec6-4871-4b55-bd54-1312dc8a8615

## Installation:
Run this to allow the tool to be used as a command in linux:
```
gcc flexon.c -o flexon
mkdir -p ~/.local/bin
mv mycli ~/.local/bin
export PATH=$PATH:~/.local/bin
```
