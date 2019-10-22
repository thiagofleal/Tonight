#ifndef TONIGHT_LOCALE_H
#	define	TONIGHT_LOCALE_H

#	ifdef __cplusplus
		extern "C"{
#	endif

    typedef struct localeCategoryDescriptor *localeCategoryDescriptor;

    extern const struct __Locale{
        string (* set)(localeCategoryDescriptor, string);
        string (* get)(localeCategoryDescriptor);
    }Locale;

    extern const struct __LocaleCategory{
        localeCategoryDescriptor All;
        localeCategoryDescriptor Collate;
        localeCategoryDescriptor Character;
        localeCategoryDescriptor Monetary;
        localeCategoryDescriptor Numeric;
        localeCategoryDescriptor Time;
    }LocaleCategory;

#	ifdef __cplusplus
		}
#	endif

#endif
