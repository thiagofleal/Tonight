#ifndef TONIGHT_FILE_H
#	define	TONIGHT_FILE_H

#   include "stream.h"

#	ifdef __cplusplus
		extern "C"{
#	endif

    typedef struct FileModeDescriptor *FileModeDescriptor;

    extern const struct __File{
		file (* open)(string, FileModeDescriptor);
		void (* close)(file);
		void (* rewind)(file);
		bool (* end)(file);
		file (* stdInput)(void);
		file (* stdOutput)(void);
		file (* stdError)(void);
    }File;

    extern const struct __FileMode{
        FileModeDescriptor read;
        FileModeDescriptor write;
        FileModeDescriptor append;
    }FileMode;

#	ifdef __cplusplus
		}
#	endif

#endif
