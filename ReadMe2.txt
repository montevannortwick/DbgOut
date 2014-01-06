This program displays a debug window that can display info from another program that calls DbgOut(FormattedString);  similar to TRACE().
Built with VS2008 and Unicode not set:  Configuration Properties, General, Character Set:  (Not Set)
To have your program display formatted strings in the DbgOut window:
DbgOut("Now is the time %d\n",variable);
