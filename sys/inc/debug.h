#ifndef _DEBUG_H
#define _DEBUG_H

#include <stdio.h>
#include <clock.h>
#include <shell_colors.h>

#ifndef DEBUG_CONFIG_TIMESTAMPS
#define DEBUG_CONFIG_TIMESTAMPS	1
#endif

#ifdef DEBUG
#define _dbg(fmt, args...)	printf(fmt, ## args)
#else
#define _dbg(fmt, args...)	do{}while(0)
#endif

#if DEBUG_CONFIG_TIMESTAMPS
#define dbg(fmt, args...)	{						\
					up_time_t time = get_up_time();		\
					_dbg("[%02d:%02d:%02d.%03d] debug: " fmt, time.hours, time.minutes, time.seconds, time.ms, ## args);		\
				}

#else
#define dbg(fmt, args...)	_dbg(fmt, ## args)
#endif

#define dbgf(fmt, args...)	dbg("%s: " fmt, __FUNCTION__, ## args)

#define TODO_COLOR		COLORFB(BLUE, REGULAR, YELLOW)
#define TODO_COLOR_CLEAR	COLOR_CLEAR
#define TODO(fmt, args...)	dbg( TODO_COLOR "** TODO at [%s:%d]" TODO_COLOR_CLEAR "\n", __FILE__, __LINE__);	\
				dbg( TODO_COLOR "** " fmt TODO_COLOR_CLEAR "\n", ## args)

#define STR(name)	#name
#define PRINT_FIELD(n, f)	dbg("%s.%s	: %d\n", STR(n), STR(f), n.b.f)

typedef volatile unsigned int io;

#define PRINT_REG_FIELD(_pre, _reg, _field)	{\
							io * ptr = (io *) &_pre##_reg->_field; \
							dbg("0x%08x : %-20s = 0x%08x\n", ptr, STR(_reg)"."STR(_field), *ptr); \
						}

#define PRINT_REG(_pre, _reg)			{\
							io * ptr = (io *) ( _pre##_reg ); \
							dbg("0x%08x : %-20s = 0x%08x\n", ptr, STR(_reg),  *ptr); \
						}

#define PRINT_SIZE(t)		dbg("sizeof(%s) = %d\n", STR( t ), sizeof( t ) )

#endif //_DEBUG_H
