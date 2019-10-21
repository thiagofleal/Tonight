#include <stdlib.h>
#include "../include/tonight.h"
#include "../include/Tonight/exceptions.h"
#include "../include/Tonight/string.h"
#include "../include/Tonight/conversor.h"

static INLINE string TONIGHT byte_toString(byte b){
	return s_is((int)b);
}

static char TONIGHT char_fromString(string s){
	char ret = *s;
	if(* ++ s){
        fixString fs = FixString.formated("Impossible to convert \"%s\" to character", s);
        throw(ConvertException, getText(fs));
	}
	return ret;
}

static byte TONIGHT $throws byte_fromString(string s){
	string a;
	byte b = (byte)strtol(s, &a, 0);
	if(*a){
        fixString fs = FixString.formated("Impossible to convert \"%s\" to byte", s);
        throw(ConvertException, getText(fs));
	}
	return b;
}

static bool TONIGHT $throws bool_fromString(string s){
	if(String.equal(s, "true"))
		return true;
	if(String.equal(s, "false"))
		return false;
	if(true){
        fixString fs = FixString.formated("Impossible to convert \"%s\" to boolean", s);
        throw(ConvertException, getText(fs));
	}
	return false;
}

static int TONIGHT $throws int_fromString(string s){
	int i;
	string a;
	i = (int)strtol(s, &a, 0);
	if(*a){
        fixString fs = FixString.formated("Impossible to convert \"%s\" to integer", s);
        throw(ConvertException, getText(fs));
	}
	return i;
}

static float TONIGHT $throws float_fromString(string s){
	float f;
	string a;
	f = strtof(s, &a);
	if(*a){
        fixString fs = FixString.formated("Impossible to convert \"%s\" to floating point", s);
        throw(ConvertException, getText(fs));
	}
	return f;
}

static double TONIGHT $throws double_fromString(string s){
	double d;
	string a;
	d = strtod(s, &a);
	if(*a){
        fixString fs = FixString.formated("Impossible to convert \"%s\" to floating point", s);
        throw(ConvertException, getText(fs));
	}
	return d;
}

const struct __Conversor Conversor = {
    .toChar = char_fromString,
    .toByte = byte_fromString,
    .toBool = bool_fromString,
    .toInt = int_fromString,
    .toFloat = float_fromString,
    .toDouble = double_fromString,
    .fromChar = s_cs,
    .fromByte = byte_toString,
    .fromBool = s_bs,
    .fromInt = s_is,
    .fromFloat = s_fs,
    .fromDouble = s_ds
};
