#ifndef TONIGHT_READER_H
#	define	TONIGHT_READER_H

#   include "stream.h"

#	ifdef __cplusplus
		extern "C"{
#	endif

    struct IReader {
        int (* nextChar)(void);
        int (* nextInt)(void);
        float (* nextFloat)(void);
        double (* nextDouble)(void);
        pointer (* next)(void);
        pointer (* nextLine)(void);
    };

    interface(IReader);

    struct Reader {
        pointer stream;
    };

    Class(Reader $extends Object $implements IReader);

#	ifdef __cplusplus
		}
#	endif

#endif
