#include "minishell.h"

int	main()
{
	prompt();
	return (0);
}

/*
Imagine that your computer is a big toy box, and each toy is a program. The toys need some 
information to work properly, like instructions on how to play with them or some special settings. 
These pieces of information are called environment variables.

When you start a program (take a toy out of the box), it gets a list of these environment variables 
so it knows how to work correctly. This list of variables is called envp. It's like a small note that 
comes with the toy, telling you how to play with it or set it up.

In your minishell program, envp is a list of these notes that you can use to make your program work 
correctly and do things like remember where other programs are or how to set up special features.
*/