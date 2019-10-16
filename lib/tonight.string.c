#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../include/tonight.h"
#include "../include/Tonight/exceptions.h"
#include "../include/Tonight/memory.h"
#include "../include/Tonight/array.h"
#include "../include/Tonight/string.h"

bool TONIGHT equal(register string const wrd_1, register string const wrd_2){
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

static INLINE string TONIGHT __concatString(char dest[], char from[], size_t length){
	return strncat(dest, from, length - strlen(dest) - 1);
}

retString TONIGHT retConcat(string wrd_1, ...){
	va_list va;
	string p;
	static retString ret;
	*ret.Text = 0;
	va_start(va, wrd_1);
	for (p = wrd_1; p; p = va_arg(va, string))
		__concatString(ret.Text, p, sizeof ret);
	va_end(va);
	return ret;
}

string TONIGHT concat(string wrd_1, ...){
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

string TONIGHT nconcat(size_t size, string wrd_1, ...){
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

INLINE string TONIGHT toString(register pointer __array){
	register size_t size = (strlen(__array) + 1) * sizeof(char);
	return memcpy(Memory.alloc(size), __array, size);
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

retString TONIGHT cs(char var){
	register char *s = s_cs(var);
	static retString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

retString TONIGHT bs(bool var){
	register char *s = s_bs(var);
	static retString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

retString TONIGHT is(int var){
	register char *s = s_is(var);
	static retString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

retString TONIGHT fsf(float var, int _decimal){
	register char *s = s_fsf(var, _decimal);
	static retString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

retString TONIGHT dsf(double var, int _decimal){
	register char *s = s_dsf(var, _decimal);
	static retString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

retString TONIGHT ds(double var){
	register char *s = s_ds(var);
	static retString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

retString TONIGHT fs(float var){
	register char *s = s_fs(var);
	static retString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

INLINE retString TONIGHT ps(pointer var){
	register char *s = s_ps(var);
	static retString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

longRetString TONIGHT longRetConcat(string wrd_1, ...){
	va_list va;
	string p;
	static longRetString ret;
	*ret.Text = 0;
	va_start(va, wrd_1);
	for (p = wrd_1; p; p = va_arg(va, string))
		__concatString(ret.Text, p, sizeof ret);
	va_end(va);
	return ret;
}

INLINE retString TONIGHT cps(char *p){
	return cs(*p);
}

INLINE retString TONIGHT bps(bool *p){
	return bs(*p);
}

INLINE retString TONIGHT ips(int *p){
	return is(*p);
}

INLINE retString TONIGHT fps(float *p){
	return fs(*p);
}

INLINE retString TONIGHT dps(double *p){
	return ds(*p);
}

INLINE retString TONIGHT fpsf(float *p, int d){
	return fsf(*p, d);
}

INLINE retString TONIGHT dpsf(double *p, int d){
	return dsf(*p, d);
}

INLINE retString TONIGHT pps(pointer *p){
	return ps(*p);
}

longRetString TONIGHT cls(char var){
	register char *s = s_cs(var);
	static longRetString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.Callback.free(s);
	return ret;
}

longRetString TONIGHT bls(bool var){
	register char *s = s_bs(var);
	static longRetString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

longRetString TONIGHT ils(int var){
	register char *s = s_is(var);
	static longRetString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

longRetString TONIGHT fls(float var){
	register char *s = s_fs(var);
	static longRetString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

longRetString TONIGHT dls(double var){
	register char *s = s_ds(var);
	static longRetString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

longRetString TONIGHT flsf(float var, int d){
	register char *s = s_fsf(var, d);
	static longRetString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

longRetString TONIGHT dlsf(double var, int d){
	register char *s = s_dsf(var, d);
	static longRetString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

retString TONIGHT formated(const string format, ...){
	va_list v;
	retString ret;
	va_start(v, format);
	vsnprintf(ret.Text, sizeof ret, format, v);
	va_end(v);
	return ret;
}

longRetString TONIGHT longFormated(const string format, ...){
	va_list v;
	longRetString ret;
	va_start(v, format);
	vsnprintf(ret.Text, sizeof ret, format, v);
	va_end(v);
	return ret;
}

static string TONIGHT String_formated(const string frmt, ...){
	static char s[1001];
	va_list v;
	va_start(v, frmt);
	vsprintf(s, frmt, v);
	va_end(v);
	return toString(s);
}

static INLINE string TONIGHT String_concatenate(string str1, string str2){
	return concat(str1, str2, $end);
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

static INLINE string TONIGHT byte_toString(byte b){
	return s_is((int)b);
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
	.concatenate = (pointer)String_concatenate,
	.upper = (pointer)String_upper,
	.lower = (pointer)String_lower,
	.length = (pointer)strlen,
	.compare = (pointer)strcmp,
	.sep = (pointer)String_sep,
	.split = (pointer)String_split,
	.trim = (pointer)String_trim,
	.free = (pointer)String_free,
	.toString = (pointer)toString,
	//.toWide = stringToWide
};
