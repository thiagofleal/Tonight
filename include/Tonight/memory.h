#ifndef ___TONIGHT_MEMORY___
#   define ___TONIGHT_MEMORY___

#   ifdef __cplusplus
        extern "C"{
#   endif // __cplusplus

    extern const struct __Memory{
        void	(* free)(pointer);
        pointer	(* alloc)(size_t);
        pointer	(* realloc)(pointer, size_t);
        size_t	(* size)(pointer);
        pointer	(* copy)(pointer);

        struct Callback{
            void (* setMalloc)(pointer(*)(size_t));
            void (* setCalloc)(pointer(*)(size_t, size_t));
            void (* setRealloc)(pointer(*)(pointer, size_t));
            void (* setFree)(void(*)(pointer));
            pointer (* malloc)(size_t);
            pointer (* calloc)(size_t, size_t);
            pointer (* realloc)(pointer, size_t);
            void (* free)(pointer);
        }Callback;
    }Memory;

    #ifdef __cplusplus
        }
    #endif // __cplusplus

#endif //___TONIGHT_MEMORY___
