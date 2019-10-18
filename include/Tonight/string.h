#ifndef TONIGHT_STRING_H
#	define	TONIGHT_STRING_H

#	ifdef __cplusplus
		extern "C"{
#	endif

#	define	$c(arg)	getText(cs(arg))
#	define	$b(arg)	getText(bs(arg))
#	define	$i(arg)	getText(is(arg))
#	define	$f(arg)	getText(fs(arg))
#	define	$d(arg)	getText(ds(arg))
#	define	$p(arg)	getText(ps(arg))
#	define	$s(arg)	getText(arg)
#	define	$o(arg)	getText($(arg $as Object).toRetString())
#	define	$ff(arg, n)	getText(fsf(arg, n))
#	define	$df(arg, n)	getText(dsf(arg, n))

#	define	$cp(arg)		getText(cps(arg))
#	define	$bp(arg)		getText(bps(arg))
#	define	$ip(arg)		getText(ips(arg))
#	define	$fp(arg)		getText(fps(arg))
#	define	$dp(arg)		getText(dps(arg))
#	define	$pp(arg)		getText(pps(arg))
#	define	$sp(arg)		getText((*arg))
#	define	$fpf(arg, n)	getText(fpsf(arg, n))
#	define	$dpf(arg, n)	getText(dpsf(arg, n))

#	define	$lc(arg)	getText(cls(arg))
#	define	$lb(arg)	getText(bls(arg))
#	define	$li(arg)	getText(ils(arg))
#	define	$lf(arg)	getText(fls(arg))
#	define	$ld(arg)	getText(dls(arg))
#	define	$ls(arg)	getText(arg)
#	define	$lo(arg)	getText($(arg $as Object).toLongRetString())
#	define	$lff(arg, n)	getText(flsf(arg, n))
#	define	$ldf(arg, n)	getText(dlsf(arg, n))

	extern const struct __String{
		void (* free)(string);
		string (* formated)(const string, ...);
		string (* copy)(const string);
		string (* concat)(string, ...);
		string (* nconcat)(size_t, string, ...);
		string (* upper)(const string);
		string (* lower)(const string);
		string (* trim)(const string);
		string (* sep)(string*, const string);
		string* (* split)(const string, const string);
		size_t (* length)(const string);
		int (* compare)(const string, const string);
		bool (* equal)(register string const, register string const);
		bool (* identic)(register string const, register string const);
	}String;

	extern const struct __FixString{
		fixString (* concat)(string, ...);
        fixString (* formated)(const string, ...);
		int (* compare)(fixString, fixString);
		bool (* equal)(fixString, fixString);
		bool (* identic)(fixString, fixString);
	}FixString;

	extern const struct __LongFixString{
		longFixString (* concat)(string, ...);
        longFixString (* formated)(const string, ...);
		int (* compare)(longFixString, longFixString);
		bool (* equal)(longFixString, longFixString);
		bool (* identic)(longFixString, longFixString);
	}LongFixString;

    extern string TONIGHT toString(pointer);
    extern string TONIGHT s_cs(char);
    extern string TONIGHT s_bs(bool);
    extern string TONIGHT s_is(int);
    extern string TONIGHT s_fs(float);
    extern string TONIGHT s_ds(double);
    extern string TONIGHT s_fsf(float, int);
    extern string TONIGHT s_dsf(double, int);
    extern string TONIGHT s_ps(pointer);

    extern INLINE string TONIGHT s_cps(char*);
    extern INLINE string TONIGHT s_bps(bool*);
    extern INLINE string TONIGHT s_ips(int*);
    extern INLINE string TONIGHT s_fps(float*);
    extern INLINE string TONIGHT s_dps(double*);
    extern INLINE string TONIGHT s_fpsf(float*, int);
    extern INLINE string TONIGHT s_dpsf(double*, int);
    extern INLINE string TONIGHT s_pps(pointer*);

    extern fixString TONIGHT cs(char);
    extern fixString TONIGHT bs(bool);
    extern fixString TONIGHT is(int);
    extern fixString TONIGHT fs(float);
    extern fixString TONIGHT ds(double);
    extern fixString TONIGHT fsf(float, int);
    extern fixString TONIGHT dsf(double, int);
    extern fixString TONIGHT ps(pointer);

    extern INLINE fixString TONIGHT cps(char*);
    extern INLINE fixString TONIGHT bps(bool*);
    extern INLINE fixString TONIGHT ips(int*);
    extern INLINE fixString TONIGHT fps(float*);
    extern INLINE fixString TONIGHT dps(double*);
    extern INLINE fixString TONIGHT fpsf(float*, int);
    extern INLINE fixString TONIGHT dpsf(double*, int);
    extern INLINE fixString TONIGHT pps(pointer*);

    extern longFixString TONIGHT cls(char);
    extern longFixString TONIGHT bls(bool);
    extern longFixString TONIGHT ils(int);
    extern longFixString TONIGHT fls(float);
    extern longFixString TONIGHT dls(double);
    extern longFixString TONIGHT flsf(float, int);
    extern longFixString TONIGHT dlsf(double, int);

	#ifdef __cplusplus
		}
	#endif // __cplusplus
#endif
