#ifndef TONIGHT_CONVERSOR_H
#	define	TONIGHT_CONVERSOR_H

#	ifdef __cplusplus
		extern "C"{
#	endif

    extern const struct __Conversor{
		char (* toChar)(string);
		byte (* toByte)(string);
		bool (* toBool)(string);
		int (* toInt)(string);
		float (* toFloat)(string);
		double (* toDouble)(string);
		string (* fromChar)(char);
		string (* fromByte)(byte);
		string (* fromBool)(bool);
		string (* fromInt)(int);
		string (* fromFloat)(float);
		string (* fromDouble)(double);
	}Conversor;

#	ifdef __cplusplus
		}
#	endif

#endif
