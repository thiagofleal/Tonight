#ifndef TONIGHT_FILE_H
#	define	TONIGHT_FILE_H

#   include "stream.h"

#	ifdef __cplusplus
		extern "C"{
#	endif

    typedef struct FileMode *FileMode;

    extern const struct __File{
		file (* open)(string, FileMode);
		void (* close)(file);
		void (* rewind)(file);
		bool (* end)(file);
		file (* stdInput)(void);
		file (* stdOutput)(void);
		file (* stdError)(void);
		struct Mode{
			FileMode read;
			FileMode write;
			FileMode append;
		}Mode;
    }File;

#	ifdef __cplusplus
		}
#	endif

#endif
