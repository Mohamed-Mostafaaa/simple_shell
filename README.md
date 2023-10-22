# Implementation of sh in C programming language

# <a href="url"><img src="https://images.assetsdelivery.com/compings_v2/dmstudio/dmstudio1606/dmstudio160600030.jpg" align="middle" width="100" height="100"></a> simple_shell

<a href="https://alxafrica.com"><img src="https://lh3.googleusercontent.com/oVJxT1yn7vwaEM8t9A5MGL6emG0j-_uqHa5H8ikWLvl6Ka-nVmUJZblqWDqPiY-S6itPLnZNgcc8rviK8AVT65l_a3zHiyctwy8=s0" align="right" width="200" height="200" alt="Alx School" border="0"></a>

## Overview
simple_shell is a project on the UNIX Shell. The UNIX Shell is a command-line interpreter or shell that provides a command-line user interface for Unix-like operating systems. The shell is both an interactive command language and a scripting language and is used by the operating system to control the execution of the system using shell scripts.…

## Content
* [Installation](#Installation)
* [Compilation](#Compilation)
* [Testing](#Testing)
* [General Requirements](#General-Requirements)
* [Target output](#Target-output)
* [Tasks](#Tasks)
* [List of allowed functions](##list-of-allowed-functions--syscalls)
https://github.com/Mohamed-Mostafaaa/simple_shell/blob/main/README.md#list-of-allowed-functions--syscalls
## Installation
```
git clone https://github.com/patrickdeyoreo/simple_shell.git
cd simple_shell
gcc *.c -o hsh
```
## Compilation
```
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh 
```
## Testing
- Interactive mode:
```
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
$
```
## General Requirements
* Allowed editors: vi, vim, emacs
* All your files will be compiled on Ubuntu 14.04 LTS
* Your C programs and functions will be compiled with gcc 4.8.4 using the flags -Wall -Werror -Wextra and -pedantic
* All your files should end with a new line
* A README.md file, at the root of the folder of the project is mandatory
* Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl
* No more than 5 functions per file
* All your header files should be included guarded
* Use system calls only when you need to

## Target output
* Unless specified otherwise, your program must have the same output as sh (/bin/sh) and the same error output.
* The only difference is when you print an error, the name of the program must be equivalent to your argv[0]

- Example of error with sh:
```
$ echo "qwerty" | /bin/sh
/bin/sh: 1: qwerty: not found
$ echo "qwerty" | /bin/../bin/sh
/bin/../bin/sh: 1: qwerty: not found
$
```
- Same error with your program hsh:
```
$ echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found
$ echo "qwerty" | ./././hsh
./././hsh: 1: qwerty: not found
$
```

## Tasks
### Mandatory:
1. README, man, AUTHORS
- Write a README
- Write a man for your shell.
- You should have an AUTHORS file at the root of your repository, listing all individuals having contributed content to the repository.

2. Simple shell 0.1
- Write a UNIX command line interpreter.
- Your Shell should:
Display a prompt and wait for the user to type a command. A command line always ends with a new line.
The prompt is displayed again each time a command has been executed.
The command lines are simple, with no semicolons, pipes, redirections, or other advanced features.
The command lines are made only of one word. No arguments will be passed to programs.
Print an error message and display the prompt again if an executable cannot be found.
Handle errors.
You have to handle the “end of file” condition (Ctrl+D)
- You don’t have to:
use the PATH
implement built-ins
handle special characters: ", ', `, \, *, &, #
be able to move the cursor
handle commands with arguments

3. Simple shell 0.2
- Handle command lines with arguments

4. Simple shell 0.3
- Handle the PATH

5. Simple shell 0.4
- Implement the exit built-in, that exits the shell
- Usage: exit
- You don’t have to handle any argument to the built-in exit

6. Simple shell 1.0
- Implement the env built-in, that prints the current environment

7. Write a blog post "What happens when you type ls -l in the shell"

### Advanced
1. Test suite 
- Contribute to a test suite for your shell

2. Simple shell 0.2.1
- Write your strtok function

3. Simple shell 0.4.1
- handle arguments for the built-in exit

4. Simple shell 0.4.2
- Handle Ctrl+C: your shell should not quit when the user inputs ^C

5. setenv, unsetenv
- Implement the setenv and unsetenv builtin commands

6. cd
- Implement the builtin command cd

7. ;
- Handle the commands separator ;

8. alias 
- Implement the alias builtin command

19. Comments
- Handle comments (#)

10. help 
- Implement the help built-in

11. File as an input 
- Your shell should take a file as a command line argument

## List of allowed functions / syscalls
| Functions | Reference |
| --------- | --------- |
| `access` | [man 2 access](https://linux.die.net/man/2/access) |
| `chdir` | [man 2 chdir](https://linux.die.net/man/2/chdir) |
| `close` | [man 2 close](https://linux.die.net/man/2/close) |
| `closedir` | [man 3 closedir](https://linux.die.net/man/3/closedir) |
| `execve` | [man 2 execve](https://linux.die.net/man/2/execve) |
| `exit` | [man 3 exit](https://linux.die.net/man/3/exit) |
| `_exit` | [man 2 \_exit](https://linux.die.net/man/2/_exit) |
| `fflush` | [man 3 fflush](https://linux.die.net/man/3/fflush) |
| `fork` | [man 2 fork](https://linux.die.net/man/2/fork) |
| `free` | [man 3 free](https://linux.die.net/man/3/free) |
| `getcwd` | [man 3 getcwd](https://linux.die.net/man/3/getcwd) |
| `getline` | [man 3 getline](https://linux.die.net/man/3/getline) |
| `isatty` | [man 3 isatty](https://linux.die.net/man/3/isatty) |
| `kill` | [man 2 kill](https://linux.die.net/man/2/kill) |
| `malloc` | [man 3 malloc](https://linux.die.net/man/3/malloc) |
| `open` | [man 2 open](https://linux.die.net/man/2/open) |
| `opendir` | [man 3 opendir](https://linux.die.net/man/3/opendir) |
| `perror` | [man 3 perror](https://linux.die.net/man/3/perror) |
| `read` | [man 2 read](https://linux.die.net/man/2/read) |
| `readdir` | [man 3 readdir](https://linux.die.net/man/3/readdir) |
| `signal` | [man 2 signal](https://linux.die.net/man/2/signal) |
| `stat` | [(\_\_xstat) man 2 stat](https://linux.die.net/man/2/stat) |
| `lstat` | [(\_\_lxstat) man 2 lstat](https://linux.die.net/man/2/lstat) |
| `fstat` | [(\_\_fxstat) man 2 fstat](https://linux.die.net/man/2/fstat) |
| `strtok` | [man 3 strtok](https://linux.die.net/man/3/strtok) |
| `wait` | [man 2 wait](https://linux.die.net/man/2/wait) |
| `waitpid` | [man 2 waitpid](https://linux.die.net/man/2/waitpid) |
| `wait3` | [man 2 wait3](https://linux.die.net/man/2/wait3) |
| `wait4` | [man 2 wait4](https://linux.die.net/man/2/wait4) |
| `write` | [man 2 write](https://linux.die.net/man/2/write) |
