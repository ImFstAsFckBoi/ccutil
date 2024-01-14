#pragma once


namespace cc {

/*
 * ANSI Escape sequences
 * 
 * https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
 * https://www.climagic.org/mirrors/VT100_Escape_Codes.html
 * 
 */

#define cleareol	"\33[K"		// Clear line from cursor right
#define clearbol	"\33[1K"	// Clear line from cursor left
#define clearline	"\33[2K"	// Clear entire line
#define cleareos	"\33[J"		// Clear screen from cursor down
#define clearbos	"\33[1J"	// Clear screen from cursor up
#define clearscreen	"\33[2J"	// Clear entire screen 


enum ARROWS_VALUE
{
	UP    = 65,
	DOWN  = 66,
	RIGHT = 67,
	LEFT  = 68
};

/* 
 * ASCII Codes
 * 
 * https://www.ascii-code.com/
 * 
 */

#define EOF EOT

enum ASCII_CTRL_CODES
{
	NUL	= 000,	// Null char
	SOH	= 001,	// Start of Heading
	STX	= 002,	// Start of Text
	ETX	= 003,	// End of Text
	EOT	= 004,	// End of Transmission
	ENQ	= 005,	// Enquiry
	ACK	= 006,	// Acknowledgment
	BEL	= 007,	// Bell
	BS	= 010,	// Back Space
	HT	= 011,	// Horizontal Tab
	LF	= 012,	// Line Feed
	VT	= 013,	// Vertical Tab
	FF	= 014,	// Form Feed
	CR	= 015,	// Carriage Return
	SO	= 016,	// Shift Out / X-On
	SI	= 017,	// Shift In / X-Off
	DLE	= 020,	// Data Line Escape
	DC1	= 021,	// Device Control 1 (oft. XON)
	DC2	= 022,	// Device Control 2
	DC3	= 023,	// Device Control 3 (oft. XOFF)
	DC4	= 024,	// Device Control 4
	NAK	= 025,	// Negative Acknowledgement
	SYN	= 026,	// Synchronous Idle
	ETB	= 027,	// End of Transmit Block
	CAN	= 030,	// Cancel
	EM	= 031,	// End of Medium
	SUB	= 032,	// Substitute
	ESC	= 033,	// Escape
	FS	= 034,	// File Separator
	GS	= 035,	// Group Separator
	RS	= 036,	// Record Separator
	US	= 037 	// Unit Separator
};


}
