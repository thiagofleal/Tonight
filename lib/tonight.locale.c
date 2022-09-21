#include <locale.h>
#include "../include/tonight.h"
#include "../include/Tonight/locale.h"

struct localeCategoryDescriptor {
    int descriptor;
};

static INLINE string TONIGHT Locale_set(localeCategoryDescriptor category, string name){
	return setlocale(category->descriptor, name);
}

static INLINE string TONIGHT Locale_get(localeCategoryDescriptor category){
	return setlocale(category->descriptor, NULL);
}

const struct __Locale Locale = {
    .set = Locale_set,
    .get = Locale_get
};

static struct localeCategoryDescriptor
    lc_All = {LC_ALL},
    lc_Collate = {LC_COLLATE},
    lc_Character = {LC_CTYPE},
    lc_Monetary = {LC_MONETARY},
    lc_Numeric = {LC_NUMERIC},
    lc_Time = {LC_TIME};

const struct __LocaleCategory LocaleCategory = {
    .All = &lc_All,
    .Collate = &lc_Collate,
    .Character = &lc_Character,
    .Monetary = &lc_Monetary,
    .Numeric = &lc_Numeric,
    .Time = &lc_Time
};
