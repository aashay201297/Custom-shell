README
_______________________________________________________
_______________________________________________________

FEATURES SUPPORTED
-------------------------------------------------------
The shell supports cd,pwd,echo and other built in commands.
Errors are handled properly using perror.
Echo command is not the same as in the bash shell.
Pipes and redirection can be used as in BASH.


HOW TO COMPILE
-------------------------------------------------------

to compile run the command:-   make

HOW TO RUN
-------------------------------------------------------
run the command:- ./main
FILES
-------------------------------------------------------
executeCD.c:- the function to execute cd command
executeCMD.c:- the function to execute built in commands other than pwd,cd,echo
executeECHO.c:- the function to execute echo command
executePWD.c:- the function to execute pwd command
parse.c:- the function to parse the given string of commands properly
pinfo.c:- th efunction to execute pinfo command (bonus)
print.c:- the function to print the initials in shell
main.c:- the main loop

