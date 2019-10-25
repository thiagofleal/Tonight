#ifndef TONIGHT_WRITER_H
#	define	TONIGHT_WRITER_H

#   include "stream.h"

    struct IWriter{
        void (* text)(string);
        void (* textln)(string);
        void (* print)(string, ...);
        void (* println)(string, ...);
        void (* printargln)(string, ...);
        void (* newLine)(void);
        void (* addLines)(int);
    };

    interface(IWriter);

    struct Writer{
        pointer stream;
    };

    Class(Writer $extends Object $implements IWriter);

#endif
