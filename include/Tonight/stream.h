#ifndef TONIGHT_STREAM_H
#	define	TONIGHT_STREAM_H

#	ifdef __cplusplus
		extern "C"{
#	endif

    typedef struct IStream{
        int (* scan)(pointer, const string, pointer);
        int (* print)(pointer, const string, pointer);
        int (* wscan)(pointer, const wstring, pointer);
        int (* wprint)(pointer, const wstring, pointer);
    }IStream;

    extern const IStream Stream;
    extern INLINE IStream* getIStream(pointer);

#	ifdef __cplusplus
		}
#	endif

#endif
