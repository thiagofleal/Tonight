#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../include/tonight.h"
#include "../include/Tonight/exceptions.h"
#include "../include/Tonight/memory.h"
#include "../include/Tonight/array.h"
#include "../include/Tonight/string.h"

INLINE string TONIGHT toString(register pointer __array){
	register size_t size = (strlen(__array) + 1) * sizeof(char);
	return memcpy(Memory.alloc(size), __array, size);
}

static INLINE string TONIGHT __concatString(char dest[], char from[], size_t length){
	return strncat(dest, from, length - strlen(dest) - 1);
}

static string TONIGHT wideToString(wstring s){
    char str[1001];
	snprintf(str, ARRAY_LENGTH(str) - 1, "%ls", s);
	return toString(str);
}

string TONIGHT s_cs(char var){
	char c[] = {var, 0};
	return toString(c);
}

string TONIGHT s_bs(bool var){
	return var ? toString("true") : toString("false");
}

string TONIGHT s_is(int var){
	static char s[15];
	snprintf(s, sizeof s, "%i", var);
	return toString(s);
}

string TONIGHT s_fsf(float var, int _decimal){
	static char s[100];
	snprintf(s, sizeof s, "%.*f", _decimal, var);
	return toString(s);
}

string TONIGHT s_dsf(double var, int _decimal){
	static char s[100];
	snprintf(s, sizeof s, "%.*lf", _decimal, var);
	return toString(s);
}

string TONIGHT s_ds(double var){
	static char s[100];
	snprintf(s, sizeof s, "%.10g", var);
	return toString(s);
}

string TONIGHT s_ps(pointer var){
	static char s[100];
	snprintf(s, sizeof s, "%p", var);
	return toString(s);
}

INLINE string TONIGHT s_fs(float var){
	return s_ds((double)var);
}

INLINE string TONIGHT s_cps(char *p){
	return s_cs(*p);
}

INLINE string TONIGHT s_bps(bool *p){
	return s_bs(*p);
}

INLINE string TONIGHT s_ips(int *p){
	return s_is(*p);
}

INLINE string TONIGHT s_fps(float *p){
	return s_fs(*p);
}

INLINE string TONIGHT s_dps(double *p){
	return s_ds(*p);
}

INLINE string TONIGHT s_fpsf(float *p, int d){
	return s_fsf(*p, d);
}

INLINE string TONIGHT s_dpsf(double *p, int d){
	return s_dsf(*p, d);
}

fixString TONIGHT cs(char var){
	register char *s = s_cs(var);
	static fixString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

fixString TONIGHT bs(bool var){
	register char *s = s_bs(var);
	static fixString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

fixString TONIGHT is(int var){
	register char *s = s_is(var);
	static fixString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

fixString TONIGHT fsf(float var, int _decimal){
	register char *s = s_fsf(var, _decimal);
	static fixString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

fixString TONIGHT dsf(double var, int _decimal){
	register char *s = s_dsf(var, _decimal);
	static fixString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

fixString TONIGHT ds(double var){
	register char *s = s_ds(var);
	static fixString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

fixString TONIGHT fs(float var){
	register char *s = s_fs(var);
	static fixString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

INLINE fixString TONIGHT ps(pointer var){
	register char *s = s_ps(var);
	static fixString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

INLINE fixString TONIGHT cps(char *p){
	return cs(*p);
}

INLINE fixString TONIGHT bps(bool *p){
	return bs(*p);
}

INLINE fixString TONIGHT ips(int *p){
	return is(*p);
}

INLINE fixString TONIGHT fps(float *p){
	return fs(*p);
}

INLINE fixString TONIGHT dps(double *p){
	return ds(*p);
}

INLINE fixString TONIGHT fpsf(float *p, int d){
	return fsf(*p, d);
}

INLINE fixString TONIGHT dpsf(double *p, int d){
	return dsf(*p, d);
}

INLINE fixString TONIGHT pps(pointer *p){
	return ps(*p);
}

longFixString TONIGHT cls(char var){
	register char *s = s_cs(var);
	static longFixString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

longFixString TONIGHT bls(bool var){
	register char *s = s_bs(var);
	static longFixString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

longFixString TONIGHT ils(int var){
	register char *s = s_is(var);
	static longFixString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

longFixString TONIGHT fls(float var){
	register char *s = s_fs(var);
	static longFixString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

longFixString TONIGHT dls(double var){
	register char *s = s_ds(var);
	static longFixString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

longFixString TONIGHT flsf(float var, int d){
	register char *s = s_fsf(var, d);
	static longFixString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

longFixString TONIGHT dlsf(double var, int d){
	register char *s = s_dsf(var, d);
	static longFixString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

/* String abstract class */
static string TONIGHT String_formated(const string frmt, ...){
	static char s[1001];
	va_list v;
	va_start(v, frmt);
	vsprintf(s, frmt, v);
	va_end(v);
	return toString(s);
}

static string TONIGHT String_concat(string wrd_1, ...){
	va_list va;
	static char s[10001];
	static string p;
	*s = 0;
	va_start(va, wrd_1);
	for (p = wrd_1; p; p = va_arg(va, string))
		__concatString(s, p, sizeof s);
	va_end(va);
	return toString(s);
}

static string TONIGHT String_nconcat(size_t size, string wrd_1, ...){
	va_list va;
	char ARRAY s = NULL;
	static string p;
	s = Array.Char(size + 1);
	*s = 0;
	va_start(va, wrd_1);
	for (p = wrd_1; p; p = va_arg(va, string))
		strcat(s, p);
	va_end(va);
	p = toString(s);
	Array.free(s);
	return p;
}

static string TONIGHT String_upper(const string str){
	register string s, aux = toString(str);
	for(s = aux; *s; s++){
		*s = toupper(*s);
	}
	return aux;
}

static string TONIGHT String_lower(const string str){
	register string s, aux = toString(str);
	for(s = aux; *s; s++){
		*s = tolower(*s);
	}
	return aux;
}

static bool TONIGHT String_equal(register string const wrd_1, register string const wrd_2){
	register string s1 = wrd_1, s2 = wrd_2;
	while(*s1 && *s2){
		if(*s1 != *s2){
			if(isupper(*s1))
				if(tolower(*s1) != *s2)
					return false;
			if(islower(*s1))
				if(toupper(*s1) != *s2)
					return false;
		}
		s1++; s2++;
	}
	return *s1 == *s2 ? true : false;
}

static bool TONIGHT String_identic(register string const wrd_1, register string const wrd_2){
	register string s1 = wrd_1, s2 = wrd_2;
	while(*s1 && *s2){
		if(*s1 != *s2) return false;
		s1++; s2++;
	}
	return *s1 == *s2 ? true : false;
}

static string TONIGHT String_sep(register string *stringp, register const string delim){
	register string s;
	register string spanp;
	register int c, sc;
	string tok;

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

static string ARRAY String_split(string src, string lim){
	register int i, ret_len;
	string ARRAY ret = NULL;
	string aux, aux2;
	for(aux2 = aux = toString(src), i = 0; String_sep(&aux, lim); i++);
	Memory.free(aux2);
	ret_len = i;
	ret = Array.String(ret_len);
	aux = src;
	for(aux2 = aux = toString(src), i = 0; i < ret_len; i++)
		ret[i] = toString(String_sep(&aux, lim));
	Memory.free(aux2);
	return ret;
}

static string String_trim(const string _str){
    register string str = _str;
	register string aux = str + strlen(str) - 1;
	while(isspace(*str))
		++str;
	while(isspace(*aux))
		*aux-- = 0;
	return toString(str);
}

static INLINE void String_free(string str){
    Memory.free(str);
}

const struct __String String = {
	.formated = (pointer)String_formated,
	.copy = (pointer)toString,
	.concat = (pointer)String_concat,
	.nconcat = String_nconcat,
	.upper = String_upper,
	.lower = String_lower,
	.length = (pointer)strlen,
	.compare = (pointer)strcmp,
	.equal = String_equal,
	.identic = String_identic,
	.sep = String_sep,
	.split = String_split,
	.trim = String_trim,
	.free = String_free
};

static fixString TONIGHT FixString_concat(string wrd_1, ...){
	va_list va;
	string p;
	static fixString ret;
	*ret.Text = 0;
	va_start(va, wrd_1);
	for (p = wrd_1; p; p = va_arg(va, string))
		__concatString(ret.Text, p, sizeof ret);
	va_end(va);
	return ret;
}

static fixString TONIGHT FixString_formated(const string format, ...){
	va_list v;
	fixString ret;
	va_start(v, format);
	vsnprintf(ret.Text, sizeof ret, format, v);
	va_end(v);
	return ret;
}

static INLINE int TONIGHT FixString_compare(fixString s1, fixString s2){
    return strncmp(getText(s1), getText(s2), sizeof s1);
}

static INLINE bool TONIGHT FixString_equal(fixString s1, fixString s2){
    return String_equal(getText(s1), getText(s2));
}

static INLINE bool TONIGHT FixString_identic(fixString s1, fixString s2){
    return String_identic(getText(s1), getText(s2));
}

const struct __FixString FixString = {
    .concat = FixString_concat,
    .formated = FixString_formated,
    .compare = FixString_compare,
	.equal = FixString_equal,
	.identic = FixString_identic
};

static longFixString TONIGHT LongFixString_concat(string wrd_1, ...){
	va_list va;
	string p;
	static longFixString ret;
	*ret.Text = 0;
	va_start(va, wrd_1);
	for (p = wrd_1; p; p = va_arg(va, string))
		__concatString(ret.Text, p, sizeof ret);
	va_end(va);
	return ret;
}

static longFixString TONIGHT LongFixString_formated(const string format, ...){
	va_list v;
	longFixString ret;
	va_start(v, format);
	vsnprintf(ret.Text, sizeof ret, format, v);
	va_end(v);
	return ret;
}

static INLINE int TONIGHT LongFixString_compare(longFixString s1, longFixString s2){
    return strncmp(getText(s1), getText(s2), sizeof s1);
}

static INLINE bool TONIGHT LongFixString_equal(longFixString s1, longFixString s2){
    return String_equal(getText(s1), getText(s2));
}

static INLINE bool TONIGHT LongFixString_identic(longFixString s1, longFixString s2){
    return String_identic(getText(s1), getText(s2));
}

const struct __LongFixString LongFixString = {
    .concat = LongFixString_concat,
    .formated = LongFixString_formated,
    .compare = LongFixString_compare,
    .equal = LongFixString_equal,
    .identic = LongFixString_identic
};
