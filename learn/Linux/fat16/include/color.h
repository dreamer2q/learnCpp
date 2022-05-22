#ifndef __COLOR_H
#define __COLOR_H

#define COLOR(color, msg) "\033[" #color "m" msg "\033[0m"
#define RED(msg) COLOR(31, msg)
#define GREEN(msg) COLOR(32, msg)
#define YELLO(msg) COLOR(33, msg)
#define BLUE(msg) COLOR(34, msg)

#endif
