# Module 1: Shell Scripts

## Preliminaries
The shell is the main way we interact with a computer on the command line: one
popular shell is the "bourne-again shell" (a pun on the original Bourne shell).
Others include the c-shell (csh and tcsh), the z-shell (zsh), the friendly
interactive shell (fish), and many more.

Back in the day (1970) one interacted with a computer through a shell and only a
shell: the name was picked to imply something that wraps around the computer
operating system and separates it from the outside world. Nowadays most people
use graphical user interfaces, but for various reasons shells are still the
preferred environment for clusters and other machines that are accessed over a
network.

One can work interactively with a shell, but a much more powerful way to use a
shell is to write a script, i.e., a set of commands the shell will execute in
sequence. Like a normal programming language these can include variables, loops,
functions, etc.

All shell scripts should start with
```bash
#!/bin/bash
set -eou pipefail
```
This does two things:
1. Tells the shell (the one we launch the shell script from) that we should use
   bash. If we wanted something else, like python, we would use a different
   command, like `#!/usr/bin/env python`.
2. Shell scripts are difficult to debug. The second line sets up the script to
   fail immediately for most errors, like failing commands or undefined
   variables.

Some things shell scripting is useful for:
* Suppose the program you are running outputs a drag coefficient every 100 time
  steps in a giant logfile. How can you collect all of the times and drag
  coefficients without manually going through the file?
* What's an effective way to set up a program to run over a wide range of
  parameters in a loop? I will give an example here of running the same program
  with 40 different configurations by using simple for-loops and `seq` here.

## 0. Work interactively and break the shell
Like some programming languages (php, perl) shell variables start with a `$`
character (in fact, those languages acquired this feature from shell scripts!).
Try running these three commands:
```
echo PATH
echo $PATH
echo '$PATH'
echo "$PATH"
```
What happens?

Now, to break the current login session, try
```
PATH=""
echo "$PATH"
ls
```
What happens? Everything should be totally broken at this point - you can log
out and back in again to get a new shell with a not-broken `$PATH`.

## 1. hello-world.sh
### Goal
Print "hello, world" to the screen.
### Commands
* echo, or printf

## 2. loop.sh
### Goal
print
    car car car car boat car boat car plane

each on new lines, to the screen.
### Commands
* echo, or printf
* for-loops

## 3. loop-capitalize.sh
### Goal
Same as loop, but capitalize the words without hard-coding the capitalizations.
### Commands
* echo, or printf
* for-loops
* pipes
* tr

## 4. loop-unique.sh
### Goal
Same as loop, but capitalize the words without hard-coding the capitalizations.
### Commands
* echo, or printf
* for-loops
* pipes
* sort
### Hints
`sort` has a flag which deletes duplicates. Alternatively, which other program
can do that in this context?

## 5. split-sonnets.sh
### Goal
Write each of Shakespeare's sonnets into a separate file for later reading.
### Commands
* mkdir
* seq
* for-loops
* pipes (`|`) and output redirection (`>`)
* tail
### Hints
* This script requires a regular expression for grep: we want to match the first
  occurance of a string. To do this, use "^X" where X is the string which should
  start the line.
* Each sonnet is exactly fourteen lines long. Check out the `-a` option for
  grep.

## 6. love-sonnets.sh
### Goal
Copy all of the sonnets containing the word love (there should be 98 of them)
into a new folder named love-sonnets.
### Commands
* mkdir
* for-loops
* grep
* subshells: i.e., executing a shell within a shell via `$(X)` in which `X` is a
  shell program
* basename
### Hints
* Check out the `R` and `l` options for `grep`.
* Not all computers have basename installed
* Check your work with `wc` and `ls`.

## 7. zero-sonnets.sh
### Goal
Copy all of the sonnets whose number ends in a zero into a new folder named
zero-sonnets.
### Commands
* mkdir
* find
* not so much a command, but we can use globs to detect things with `find`.
### Hints
* You will either need to use `cd` or get crafty with `basename` here.
* `find` is a very powerful program: use the `-exec` flag, rather than a
  for-loop, for this one.

  Try something like
```
find ./sonnets -exec bash -c 'FILENAME={}; ....'
```
  to start a shell every time `find` does its thing. The `FILENAME={}` defines a new variable named `FILENAME` and sets it equal to whatever `find` found.

  Single quotes and double quotes do different things in shell scripting! try
```
echo '$PATH'
echo "$PATH"
```
  What changes?

## 8. no-love-sonnets.sh
### Goal
Copy all of the sonnets which do not the word love into a new folder named
no-love-sonnets. There should be 56 of them.

Here, we need to handle failure in a careful way: the `set -eou pipefail` will
cause a script to immediately stop if there is any error - that includes `grep`
failing to find a match. In this case, we want to handle the 'failure'
ourselves. The best way to do this is to turn off the error checking with `set
+e` and then turn it on again with `set -e` once we are done.
### Commands
* mkdir
* for-loops
* grep
### Hints
* In shell scripting, and also in C, a return code of `0` indicates success and
  a return code of anything else indicates an issue. The special variable `$?`
  always stores the value of the last return code.
* Check out the `-q` option for `grep`.
* The 'do-nothing statement' in bash is `:`.

## 9. no-love-sonnets-2.sh
### Goal
Copy all of the sonnets which do not the word love into a new folder named
no-love-sonnets in a different way: the `-L` flag with grep.
### Commands
* mkdir
* for-loops
* grep
* xargs. This is like `find -exec`, but for a preexisting pipeline. Typically we
  use `xargs -I{}` to make it act like `find`.
### Hints

## 10. rot13
### Goal
Write a helper script which can decode the solutions (which are rotated 13
characters) as part of a pipeline. You can use this script to decode the
solutions.
### Commands
* tr
* chmod (you will need it to run the script)
* pipes

## Wrapping things up: moving files back and forth
To conclude this module, use `tar` and `scp` to move files from the VCL machine
to your own.
