#ifndef TONIGHT_WRITER_H
#	define	TONIGHT_WRITER_H

#   include "stream.h"

    struct IWriter{
        void (* text)(pointer);
        void (* textln)(pointer);
        void (* print)(pointer, ...);
        void (* println)(pointer, ...);
        void (* printargln)(pointer, ...);
        void (* newLine)(void);
        void (* addLines)(int);
    };

    interface(IWriter);

    struct Writer{
        pointer stream;
    };

    Class(Writer $extends Object $implements IWriter);

#endif
