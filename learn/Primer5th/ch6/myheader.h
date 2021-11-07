
#ifndef __MYHEADER_H
#define __MYHEADER_H

#include <stdio.h>

#define debug_msg(e) fprintf(stderr, "Debug: %s\n  in function %s at line %d\n  compiled on %s at %s\n%s\n\n", \
                             __FILE__,                                                                                      \
                             __func__, __LINE__,                                                                            \
                             __DATE__, __TIME__,                                                                            \
                             e)

#endif