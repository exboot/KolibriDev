/*
This is adapded thunk for console.obj sys library
.h is equal to svn:\programs\develop\libraries\console\console_en.txt 

Adapted for tcc by Siemargl, 2016
Adapted for dynamic API by Magomed Kostoev, 2020 (just copied this, actually =P)
*/
#ifndef __dylibc__kos__console_h__
#define __dylibc__kos__console_h__

#define cdecl   __attribute__ ((cdecl))
#define stdcall __attribute__ ((stdcall))

/*
console.obj exports the following functions
*/
extern void stdcall (*con_init)(unsigned int wnd_width, unsigned int wnd_height,
	unsigned int scr_width, unsigned int scr_height, const char* title);
/* 	Console initialization. Must be called only once.
wnd_width, wnd_height - width and height (in units of characters) of the visible 
region; 
scr_width, scr_height - width and height (in units of characters) of console;
Any of these four parameters can be set to -1 (=0xFFFFFFFF)
to use the library's default values;
title - console window's caption. */

extern void stdcall (*con_exit)(int bCloseWindow);
/* 	You should call this funstion at the end of the program.
If bCloseWindow is zero, the string "[Finished]" will be added to the caption of 
the window and the console window will remain on the screen until the user
closes it. */

extern void stdcall (*con_set_title)(const char* title);
/* 	Set new window caption. */

extern void stdcall (*con_write_asciiz)(const char* str);
/*	Display ASCIIZ-string to the console at the current position, shifting
the current position. */

extern void stdcall (*con_write_string)(const char* str, unsigned int length);
/* 	Similar to con_write_asciiz, but length of the string must be given as a 
separate parameter */

extern int cdecl (*con_printf)(const char* format, ...);
/* 	Standard "printf" function from ANSI C. */

extern unsigned int stdcall (*con_get_flags)(void);
/*	Get output flags. */

extern unsigned int stdcall (*con_set_flags)(unsigned int new_flags);
/*	Set output flags. This function returns previous values. */

/* Flags (bitmask): */
/* text color */
#define CON_COLOR_BLUE		0x01
#define CON_COLOR_GREEN	0x02
#define CON_COLOR_RED		0x04
#define CON_COLOR_BRIGHT	0x08
/* background color */
#define CON_BGR_BLUE		0x10
#define CON_BGR_GREEN		0x20
#define CON_BGR_RED		0x40
#define CON_BGR_BRIGHT		0x80
/* output controls */
#define CON_IGNORE_SPECIALS	0x100
/* if this flag is cleared, function interprets special characters:
10 ('\n') - next line
13 ('\r') - carriage return
8 ('\b') - backspace
9 ('\t') - tab
27 ('\033' = '\x1B') - the beginning of Esc-sequences;
otherwise, these characters will be displayed like ordinary characters. */
/* Supported Esc-sequences:
	Esc[<number1>;<number2>;<number3>m - choice of character attributes:
		You can specify one, two or three codes in any order;
		0 = normal mode (white on black)
		1 = bright selection
		5 = bright background
		7 = inverse mode (black on white)
		30 = black characters
		31 = red characters
		32 = green characters
		33 = brown characters
		34 = blue characters
		35 = purple characters
		36 = turqoise characters
		37 = white characters
		40 = black background
		41 = red background
		42 = green background
		43 = brown background
		44 = blue background
		45 = purple background
		46 = turqoise background
		47 = white background
	The following sequences appeared in version 5 of library:
	Esc[2J - clear screen, move cursor to upper left corner
	Esc[<number1>;<number2>H = Esc[<number1>;<number2>f -
		move cursor to <number1>,<number2>
	Esc[<number>A - move cursor to <number> lines up
	Esc[<number>B - move cursor to <number> lines down
	Esc[<number>C - move cursor to <number> positions right
	Esc[<number>D - move cursor to <number> positions left
*/
/* signal "console closed"; appeared in version 6;
	ignored by con_set_flags */
#define CON_WINDOW_CLOSED 0x200
/* The default value for flags = 7. (grey text on black background) */

extern int stdcall (*con_get_font_height)(void);
/*	Get the height of the font. */

extern int stdcall (*con_get_cursor_height)(void);
/*	Get the height of the cursor. */

extern int stdcall (*con_set_cursor_height)(int new_height);
/* 	Set the height of the cursor. This function returns previous value.
An attempt to set the value out of the correct interval (from 0 to 
font_height-1) is ignored.
Cursor with zero height isn't displayed.
Default value: - 15% from  font height. */

extern int stdcall (*con_getch)(void);
/*	Get one character from the keyboard. 

For normal characters function returns ASCII-code. For extended 
characters (eg, Fx, and arrows), first function call returns 0
and second call returns the extended code (similar to the DOS-function 
input). Starting from version 7, after closing the console window,
this function returns 0. */

extern unsigned short stdcall (*con_getch2)(void);
/*	Reads a character from the keyboard. Low byte contains the ASCII-code 
(0 for extended characters), high byte - advanced code (like in BIOS 
input functions). Starting from version 7, after closing the console
window, this function returns 0. */

extern int stdcall (*con_kbhit)(void);
/*	Returns 1 if a key was pressed, 0 otherwise. To read pressed keys use
con_getch and con_getch2. Starting from version 6, after closing 
the console window, this function returns 1. */

extern char* stdcall (*con_gets)(char* str, int n);
/*	Reads a string from the keyboard. Reading is interrupted when got
"new line" character, or after reading the (n-1) characters (depending on 
what comes first). In the first case the newline is also recorded in the
str. The acquired line is complemented by a null character.
Starting from version 6, the function returns a pointer to the entered
line if reading was successful, and NULL if the console window was closed. */

typedef int (stdcall * con_gets2_callback)(int keycode, char** pstr, int* pn, 
	int* ppos);

extern char* stdcall (*con_gets2)(con_gets2_callback callback, char* str, int n);
/*	Con_gets completely analogous, except that when the user
press unrecognized key, it calls the specified callback-procedure
(which may, for example, handle up / down for history and tab to enter
autocompletion). You should pass to the procedure: key code and three pointers 
- to the string, to the maximum length and to the current position. 
function may change the contents of string and may change the string 
itself (for example, to reallocate memory for increase the limit), 
maximum length, and position of the line - pointers are passed for it.
Return value: 0 = line wasn't changed 1 = line changed, you should
remove old string and display new, 2 = line changed, it is necessary 
to display it; 3 = immediately exit the function.
Starting from version 6, the function returns a pointer to the entered
line with the successful reading, and NULL if the console window was closed. */

extern void stdcall (*con_cls)();
/*	Clear screen and set cursor at upper left corner. */


extern void stdcall (*con_get_cursor_pos)(int* px, int* py);
/*	Wrote current (x) coordinate of cursor to *px, and (y) to *py. */

extern void stdcall (*con_set_cursor_pos)(int x, int y);
/*	Set the cursor position to the specified coordinates. If any of the
parameters beyond the relevant range (from 0 to 1 scr_width-
for x, from 0 to 1 for scr_height-y, scr_width scr_height and were asked if
call con_init), then the corresponding coordinate of the cursor does not change.
*/

#endif
