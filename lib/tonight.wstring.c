#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include "../include/tonight.h"
#include "../include/Tonight/exceptions.h"
#include "../include/Tonight/memory.h"
#include "../include/Tonight/array.h"
#include "../include/Tonight/wstring.h"

INLINE wstring TONIGHT toWideString(register pointer __array){
	register size_t size = (wcslen(__array) + 1) * sizeof(wchar_t);
	return memcpy(Memory.alloc(size), __array, size);
}

static INLINE wstring TONIGHT __concatWideString(wchar_t dest[], wchar_t from[], size_t length){
	return wcsncat(dest, from, length - wcslen(dest) - 1);
}

static wstring TONIGHT stringToWide(string s){
    wchar_t str[1001];
	snwprintf(str, ARRAY_LENGTH(str) - 1, L"%hs", s);
	return toWideString(str);
}

wstring TONIGHT w_cs(wchar_t var){
	wchar_t c[] = {(wchar_t)var, 0};
	return toWideString(c);
}

wstring TONIGHT w_bs(bool var){
	return var ? toWideString(L"true") : toWideString(L"false");
}

wstring TONIGHT w_is(int var){
	static wchar_t s[15];
	snwprintf(s, sizeof s, L"%i", var);
	return toWideString(s);
}

wstring TONIGHT w_fsf(float var, int _decimal){
	static wchar_t s[100];
	snwprintf(s, sizeof s, L"%.*f", _decimal, var);
	return toWideString(s);
}

wstring TONIGHT w_dsf(double var, int _decimal){
	static wchar_t s[100];
	snwprintf(s, sizeof s, L"%.*lf", _decimal, var);
	return toWideString(s);
}

wstring TONIGHT w_ds(double var){
	static wchar_t s[100];
	snwprintf(s, sizeof s, L"%.10g", var);
	return toWideString(s);
}

wstring TONIGHT w_ps(pointer var){
	static wchar_t s[100];
	snwprintf(s, sizeof s, L"%p", var);
	return toWideString(s);
}

INLINE wstring TONIGHT w_fs(float var){
	return w_ds((double)var);
}

INLINE wstring TONIGHT w_cps(wchar_t *p){
	return w_cs(*p);
}

INLINE wstring TONIGHT w_bps(bool *p){
	return w_bs(*p);
}

INLINE wstring TONIGHT w_ips(int *p){
	return w_is(*p);
}

INLINE wstring TONIGHT w_fps(float *p){
	return w_fs(*p);
}

INLINE wstring TONIGHT w_dps(double *p){
	return w_ds(*p);
}

INLINE wstring TONIGHT w_fpsf(float *p, int d){
	return w_fsf(*p, d);
}

INLINE wstring TONIGHT w_dpsf(double *p, int d){
	return w_dsf(*p, d);
}

fixWideString TONIGHT wcs(wchar_t var){
	register wstring s = w_cs(var);
	static fixWideString ret;
	wcsncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

fixWideString TONIGHT wbs(bool var){
	register wstring s = w_bs(var);
	static fixWideString ret;
	wcsncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

fixWideString TONIGHT wis(int var){
	register wstring s = w_is(var);
	static fixWideString ret;
	wcsncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

fixWideString TONIGHT wfsf(float var, int _decimal){
	register wstring s = w_fsf(var, _decimal);
	static fixWideString ret;
	wcsncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

fixWideString TONIGHT wdsf(double var, int _decimal){
	register wstring s = w_dsf(var, _decimal);
	static fixWideString ret;
	wcsncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

fixWideString TONIGHT wds(double var){
	register wstring s = w_ds(var);
	static fixWideString ret;
	wcsncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

fixWideString TONIGHT wfs(float var){
	register wstring s = w_fs(var);
	static fixWideString ret;
	wcsncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

INLINE fixWideString TONIGHT wps(pointer var){
	register wstring s = w_ps(var);
	static fixWideString ret;
	wcsncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

INLINE fixWideString TONIGHT wcps(wchar_t *p){
	return wcs(*p);
}

INLINE fixWideString TONIGHT wbps(bool *p){
	return wbs(*p);
}

INLINE fixWideString TONIGHT wips(int *p){
	return wis(*p);
}

INLINE fixWideString TONIGHT wfps(float *p){
	return wfs(*p);
}

INLINE fixWideString TONIGHT wdps(double *p){
	return wds(*p);
}

INLINE fixWideString TONIGHT wfpsf(float *p, int d){
	return wfsf(*p, d);
}

INLINE fixWideString TONIGHT wdpsf(double *p, int d){
	return wdsf(*p, d);
}

INLINE fixWideString TONIGHT wpps(pointer *p){
	return wps(*p);
}

longFixWideString TONIGHT wcls(wchar_t var){
	register wstring s = w_cs(var);
	static longFixWideString ret;
	wcsncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

longFixWideString TONIGHT wbls(bool var){
	register wstring s = w_bs(var);
	static longFixWideString ret;
	wcsncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

longFixWideString TONIGHT wils(int var){
	register wstring s = w_is(var);
	static longFixWideString ret;
	wcsncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

longFixWideString TONIGHT wfls(float var){
	register wstring s = w_fs(var);
	static longFixWideString ret;
	wcsncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

longFixWideString TONIGHT wdls(double var){
	register wstring s = w_ds(var);
	static longFixWideString ret;
	wcsncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

longFixWideString TONIGHT wflsf(float var, int d){
	register wstring s = w_fsf(var, d);
	static longFixWideString ret;
	wcsncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

longFixWideString TONIGHT wdlsf(double var, int d){
	register wstring s = w_dsf(var, d);
	static longFixWideString ret;
	wcsncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

/* WideString abstract class */
static wstring TONIGHT WideString_formated(const wstring frmt, ...){
	static wchar_t s[1001];
	va_list v;
	va_start(v, frmt);
	vswprintf(s, frmt, v);
	va_end(v);
	return toWideString(s);
}

static wstring TONIGHT WideString_concat(wstring wrd_1, ...){
	va_list va;
	static wchar_t s[10001];
	static wstring p;
	*s = 0;
	va_start(va, wrd_1);
	for (p = wrd_1; p; p = va_arg(va, wstring))
		__concatWideString(s, p, sizeof s);
	va_end(va);
	return toWideString(s);
}

static wstring TONIGHT WideString_nconcat(size_t size, wstring wrd_1, ...){
	va_list va;
	wchar_t ARRAY s = NULL;
	static wstring p;
	s = Array.WideChar(size + 1);
	*s = 0;
	va_start(va, wrd_1);
	for (p = wrd_1; p; p = va_arg(va, wstring))
		wcscat(s, p);
	va_end(va);
	p = toWideString(s);
	Array.free(s);
	return p;
}

static wstring TONIGHT WideString_upper(const wstring str){
	register wstring s, aux = toWideString(str);
	for(s = aux; *s; s++){
		*s = towupper(*s);
	}
	return aux;
}

static wstring TONIGHT WideString_lower(const wstring str){
	register wstring s, aux = toWideString(str);
	for(s = aux; *s; s++){
		*s = towlower(*s);
	}
	return aux;
}

static bool TONIGHT WideString_equal(register wstring const wrd_1, register wstring const wrd_2){
	register wstring s1 = wrd_1, s2 = wrd_2;
	while(*s1 && *s2){
		if(*s1 != *s2){
			if(iswupper(*s1))
				if(towlower(*s1) != *s2)
					return false;
			if(iswlower(*s1))
				if(towupper(*s1) != *s2)
					return false;
		}
		s1++; s2++;
	}
	return *s1 == *s2 ? true : false;
}

static bool TONIGHT WideString_identic(register wstring const wrd_1, register wstring const wrd_2){
	register wstring s1 = wrd_1, s2 = wrd_2;
	while(*s1 && *s2){
		if(*s1 != *s2) return false;
		s1++; s2++;
	}
	return *s1 == *s2 ? true : false;
}

static wstring TONIGHT WideString_sep(register wstring *stringp, register const wstring delim){
	register wstring s;
	register wstring spanp;
	register int c, sc;
	wstring tok;

	if (!(s = *stringp))
		return NULL;
	for (tok = s;;) {
		c = *s++;
		spanp = delim;
		do {
			if ((sc = *spanp++) == c){
				if (!c)
					s = NULL;
				else
					s[-1] = 0;
				*stringp = s;
				return tok;
			}
		} while (sc != 0);
	}
}

static wstring ARRAY WideString_split(wstring src, wstring lim){
	register int i, ret_len;
	wstring ARRAY ret = NULL;
	wstring aux, aux2;
	for(aux2 = aux = toWideString(src), i = 0; WideString_sep(&aux, lim); i++);
	Memory.free(aux2);
	ret_len = i;
	ret = Array.WideString(ret_len);
	aux = src;
	for(aux2 = aux = toWideString(src), i = 0; i < ret_len; i++)
		ret[i] = toWideString(WideString_sep(&aux, lim));
	Memory.free(aux2);
	return ret;
}

static wstring WideString_trim(const wstring _str){
    register wstring str = _str;
	register wstring aux = str + wcslen(str) - 1;
	while(iswspace(*str))
		++str;
	while(iswspace(*aux))
		*aux-- = 0;
	return toWideString(str);
}

static INLINE void WideString_free(wstring str){
    Memory.free(str);
}

const struct __WideString WideString = {
	.formated = (pointer)WideString_formated,
	.copy = (pointer)toWideString,
	.concat = (pointer)WideString_concat,
	.nconcat = WideString_nconcat,
	.upper = WideString_upper,
	.lower = WideString_lower,
	.length = (pointer)wcslen,
	.compare = (pointer)wcscmp,
	.equal = WideString_equal,
	.identic = WideString_identic,
	.sep = WideString_sep,
	.split = WideString_split,
	.trim = WideString_trim,
	.free = WideString_free,
	.fromString = stringToWide,
	.empty = L""
};

static fixWideString TONIGHT FixWideString_concat(wstring wrd_1, ...){
	va_list va;
	wstring p;
	static fixWideString ret;
	*ret.Text = 0;
	va_start(va, wrd_1);
	for (p = wrd_1; p; p = va_arg(va, wstring))
		__concatWideString(ret.Text, p, sizeof ret);
	va_end(va);
	return ret;
}

static fixWideString TONIGHT FixWideString_formated(const wstring format, ...){
	va_list v;
	fixWideString ret;
	va_start(v, format);
	vsnwprintf(ret.Text, sizeof ret, format, v);
	va_end(v);
	return ret;
}

static INLINE fixWideString TONIGHT FixWideString_append(fixWideString fix, wstring add){
    wcsncat(getText(fix), add, sizeof fix - wcslen(getText(fix)));
    return fix;
}

static INLINE int TONIGHT FixWideString_compare(fixWideString s1, fixWideString s2){
    return wcsncmp(getText(s1), getText(s2), sizeof s1);
}

static INLINE bool TONIGHT FixWideString_equal(fixWideString s1, fixWideString s2){
    return WideString_equal(getText(s1), getText(s2));
}

static INLINE bool TONIGHT FixWideString_identic(fixWideString s1, fixWideString s2){
    return WideString_identic(getText(s1), getText(s2));
}

const struct __FixWideString FixWideString = {
    .concat = FixWideString_concat,
    .formated = FixWideString_formated,
    .append = FixWideString_append,
    .compare = FixWideString_compare,
	.equal = FixWideString_equal,
	.identic = FixWideString_identic,
	.empty = {L""}
};

static longFixWideString TONIGHT LongFixWideString_concat(wstring wrd_1, ...){
	va_list va;
	wstring p;
	static longFixWideString ret;
	*ret.Text = 0;
	va_start(va, wrd_1);
	for (p = wrd_1; p; p = va_arg(va, wstring))
		__concatWideString(ret.Text, p, sizeof ret);
	va_end(va);
	return ret;
}

static longFixWideString TONIGHT LongFixWideString_formated(const wstring format, ...){
	va_list v;
	longFixWideString ret;
	va_start(v, format);
	vsnwprintf(ret.Text, sizeof ret, format, v);
	va_end(v);
	return ret;
}

static INLINE longFixWideString TONIGHT LongFixWideString_append(longFixWideString fix, wstring add){
    wcsncat(getText(fix), add, sizeof fix - wcslen(getText(fix)));
    return fix;
}

static INLINE int TONIGHT LongFixWideString_compare(longFixWideString s1, longFixWideString s2){
    return wcsncmp(getText(s1), getText(s2), sizeof s1);
}

static INLINE bool TONIGHT LongFixWideString_equal(longFixWideString s1, longFixWideString s2){
    return WideString_equal(getText(s1), getText(s2));
}

static INLINE bool TONIGHT LongFixWideString_identic(longFixWideString s1, longFixWideString s2){
    return WideString_identic(getText(s1), getText(s2));
}

const struct __LongFixWideString LongFixWideString = {
    .concat = LongFixWideString_concat,
    .formated = LongFixWideString_formated,
    .append = LongFixWideString_append,
    .compare = LongFixWideString_compare,
    .equal = LongFixWideString_equal,
    .identic = LongFixWideString_identic,
	.empty = {L""}
};

static INLINE void WideString_select_free(void){
    WideString_free(getCurrentObject());
}

static INLINE wstring WideString_select_copy(void){
    return toWideString(getCurrentObject());
}

static INLINE wstring WideString_select_upper(void){
    return WideString_upper(getCurrentObject());
}

static INLINE wstring WideString_select_lower(void){
    return WideString_lower(getCurrentObject());
}

static INLINE wstring WideString_select_trim(void){
    return WideString_trim(getCurrentObject());
}

static INLINE wstring* WideString_select_split(const wstring lim){
    return WideString_split(getCurrentObject(), lim);
}

static INLINE size_t WideString_select_length(void){
    return wcslen(getCurrentObject());
}

$_interface(WideString, {
    .free = WideString_select_free,
    .copy = WideString_select_copy,
    .upper = WideString_select_upper,
    .lower = WideString_select_lower,
    .trim = WideString_select_trim,
    .split = WideString_select_split,
    .length = WideString_select_length
});
