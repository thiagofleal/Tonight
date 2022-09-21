#ifndef ___TONIGHT_COLLECTION___
#   define ___TONIGHT_COLLECTION___

#   ifdef __cplusplus
        extern "C"{
#   endif // __cplusplus

#   ifdef __foreachkey__
#       undef __foreachkey__
#   endif
#   ifdef foreachkey
#       undef foreachkey
#   endif
#   ifdef __foreach__
#       undef __foreach__
#   endif
#   ifdef foreach
#       undef foreach
#   endif

#	define  __foreachkey__(var, collect)    if(initForeachkey(collect))while(foreachkeyIterator(&var))
#	define  foreachkey(_args_)				__foreachkey__(_args_)

#	define  __foreach__(var, collect)   if(initForeach(collect))while(foreachIterator(&var))
#	define  foreach(_args_)             __foreach__(_args_)

	typedef struct{
		void (* currentValue)(pointer, pointer);
		void (* currentKey)(pointer, pointer);
		bool (* next)(pointer);
		void (* reset)(pointer);
	}ICollection;

    extern const TONIGHT ICollection Collection;

    extern INLINE bool TONIGHT NO_CALL initForeachkey(pointer);
    extern bool TONIGHT NO_CALL foreachkeyIterator(pointer);

    extern INLINE bool TONIGHT NO_CALL initForeach(pointer);
    extern bool TONIGHT NO_CALL foreachIterator(pointer);

	extern INLINE ICollection * TONIGHT getICollection(pointer);
	extern INLINE void TONIGHT setICollection(pointer, ICollection*);

#endif //___TONIGHT_COLLECTION___
