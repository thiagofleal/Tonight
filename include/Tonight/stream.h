#ifndef TONIGHT_STREAM_H
#	define	TONIGHT_STREAM_H

#	ifdef __cplusplus
		extern "C"{
#	endif

    typedef struct IStream{
        int (* scan)(pointer, const string, pointer);
        int (* print)(pointer, const string, pointer);
    }IStream;

    $_add(Stream, {
        int (* scan)(const string, pointer);
        int (* print)(const string, pointer);
    });

    extern const IStream Stream;
    extern INLINE IStream* getIStream(pointer);

#	ifdef __cplusplus
		}
#	endif

#endif
