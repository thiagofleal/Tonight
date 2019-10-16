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
#	define	$F(format, args...)	getText(formated(format, args))

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
#	define	$lF(format, args...)	getText(longFormated(format, args))

	extern const struct __String{
		void (* free)(string);
		string (* formated)(const string, ...);
		string (* copy)(string);
		string (* concatenate)(string, string);
		string (* upper)(const string);
		string (* lower)(const string);
		string (* trim)(const string);
		string (* sep)(string*, const string);
		string* (* split)(const string, const string);
		size_t (* length)(const string);
		int (* compare)(const string, const string);
		string (* toString)(const string);
		wstring (* toWide)(const string);
	}String;

    extern bool TONIGHT equal(register string const, register string const);
    extern string TONIGHT toString(pointer);
    extern string TONIGHT concat(string, ...);
    extern string TONIGHT nconcat(size_t, string, ...);
    extern retString TONIGHT retConcat(string, ...);
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

    extern retString TONIGHT retConcat(string, ...);
    extern retString TONIGHT cs(char);
    extern retString TONIGHT bs(bool);
    extern retString TONIGHT is(int);
    extern retString TONIGHT fs(float);
    extern retString TONIGHT ds(double);
    extern retString TONIGHT fsf(float, int);
    extern retString TONIGHT dsf(double, int);
    extern retString TONIGHT ps(pointer);
    extern retString TONIGHT formated(const string, ...);

    extern INLINE retString TONIGHT cps(char*);
    extern INLINE retString TONIGHT bps(bool*);
    extern INLINE retString TONIGHT ips(int*);
    extern INLINE retString TONIGHT fps(float*);
    extern INLINE retString TONIGHT dps(double*);
    extern INLINE retString TONIGHT fpsf(float*, int);
    extern INLINE retString TONIGHT dpsf(double*, int);
    extern INLINE retString TONIGHT pps(pointer*);

    extern longRetString TONIGHT longRetConcat(string, ...);
    extern longRetString TONIGHT cls(char);
    extern longRetString TONIGHT bls(bool);
    extern longRetString TONIGHT ils(int);
    extern longRetString TONIGHT fls(float);
    extern longRetString TONIGHT dls(double);
    extern longRetString TONIGHT flsf(float, int);
    extern longRetString TONIGHT dlsf(double, int);
    extern longRetString TONIGHT longFormated(const string, ...);

	#ifdef __cplusplus
		}
	#endif // __cplusplus
#endif
