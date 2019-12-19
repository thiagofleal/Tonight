#ifndef TONIGHT_WIDESTRING_H
#	define	TONIGHT_WIDESTRING_H

#	ifdef __cplusplus
		extern "C"{
#	endif

#	define	$wc(arg)	getText(wcs(arg))
#	define	$wb(arg)	getText(wbs(arg))
#	define	$wi(arg)	getText(wis(arg))
#	define	$wf(arg)	getText(wfs(arg))
#	define	$wd(arg)	getText(wds(arg))
#	define	$wp(arg)	getText(wps(arg))
#	define	$ws(arg)	getText(warg)
#	define	$wo(arg)	getText($(arg $as Object).toFixWideString())
#	define	$wff(arg, n)	getText(wfsf(arg, n))
#	define	$wdf(arg, n)	getText(wdsf(arg, n))

#	define	$wcp(arg)		getText(wcps(arg))
#	define	$wbp(arg)		getText(wbps(arg))
#	define	$wip(arg)		getText(wips(arg))
#	define	$wfp(arg)		getText(wfps(arg))
#	define	$wdp(arg)		getText(wdps(arg))
#	define	$wpp(arg)		getText(wpps(arg))
#	define	$wsp(arg)		getText((*arg))
#	define	$wfpf(arg, n)	getText(wfpsf(arg, n))
#	define	$wdpf(arg, n)	getText(wdpsf(arg, n))

#	define	$wlc(arg)	getText(wcls(arg))
#	define	$wlb(arg)	getText(wbls(arg))
#	define	$wli(arg)	getText(wils(arg))
#	define	$wlf(arg)	getText(wfls(arg))
#	define	$wld(arg)	getText(wdls(arg))
#	define	$wls(arg)	getText(arg)
#	define	$wlo(arg)	getText($(arg $as Object).toLongFixWideString())
#	define	$wlff(arg, n)	getText(wflsf(arg, n))
#	define	$wldf(arg, n)	getText(wdlsf(arg, n))

	extern const struct __WideString{
		void (* free)(wstring);
		wstring (* formated)(const wstring, ...);
		wstring (* copy)(const wstring);
		wstring (* concat)(wstring, ...);
		wstring (* nconcat)(size_t, wstring, ...);
		wstring (* upper)(const wstring);
		wstring (* lower)(const wstring);
		wstring (* trim)(const wstring);
		wstring* (* split)(const wstring, const wstring);
		wstring (* replace)(const wstring, const wstring, const wstring);
		size_t (* length)(const wstring);
		int (* compare)(const wstring, const wstring);
		bool (* equal)(const wstring, const wstring);
		bool (* identic)(const wstring, const wstring);
		wstring (* fromString)(string);
		wstring empty;
	}WideString;

	extern const struct __FixWideString{
		fixWideString (* concat)(wstring, ...);
        fixWideString (* formated)(const wstring, ...);
		fixWideString (* append)(fixWideString, wstring);
		int (* compare)(fixWideString, fixWideString);
		bool (* equal)(fixWideString, fixWideString);
		bool (* identic)(fixWideString, fixWideString);
		fixWideString empty;
	}FixWideString;

	extern const struct __LongFixWideString{
		longFixWideString (* concat)(wstring, ...);
        longFixWideString (* formated)(const wstring, ...);
		longFixWideString (* append)(longFixWideString, wstring);
		int (* compare)(longFixWideString, longFixWideString);
		bool (* equal)(longFixWideString, longFixWideString);
		bool (* identic)(longFixWideString, longFixWideString);
		longFixWideString empty;
	}LongFixWideString;

	$_add(WideString, {
		void (* free)(void);
		wstring (* copy)(void);
		wstring (* upper)(void);
		wstring (* lower)(void);
		wstring (* trim)(void);
		wstring* (* split)(const wstring);
		wstring (* replace)(const wstring, const wstring);
		size_t (* length)(void);
    });

    extern wstring TONIGHT toWideString(pointer);
    extern wstring TONIGHT w_cs(wchar_t);
    extern wstring TONIGHT w_bs(bool);
    extern wstring TONIGHT w_is(int);
    extern wstring TONIGHT w_fs(float);
    extern wstring TONIGHT w_ds(double);
    extern wstring TONIGHT w_fsf(float, int);
    extern wstring TONIGHT w_dsf(double, int);
    extern wstring TONIGHT w_ps(pointer);

    extern INLINE wstring TONIGHT w_cps(wchar_t*);
    extern INLINE wstring TONIGHT w_bps(bool*);
    extern INLINE wstring TONIGHT w_ips(int*);
    extern INLINE wstring TONIGHT w_fps(float*);
    extern INLINE wstring TONIGHT w_dps(double*);
    extern INLINE wstring TONIGHT w_fpsf(float*, int);
    extern INLINE wstring TONIGHT w_dpsf(double*, int);
    extern INLINE wstring TONIGHT w_pps(pointer*);

    extern fixWideString TONIGHT wcs(wchar_t);
    extern fixWideString TONIGHT wbs(bool);
    extern fixWideString TONIGHT wis(int);
    extern fixWideString TONIGHT wfs(float);
    extern fixWideString TONIGHT wds(double);
    extern fixWideString TONIGHT wfsf(float, int);
    extern fixWideString TONIGHT wdsf(double, int);
    extern fixWideString TONIGHT wps(pointer);

    extern INLINE fixWideString TONIGHT wcps(wchar_t*);
    extern INLINE fixWideString TONIGHT wbps(bool*);
    extern INLINE fixWideString TONIGHT wips(int*);
    extern INLINE fixWideString TONIGHT wfps(float*);
    extern INLINE fixWideString TONIGHT wdps(double*);
    extern INLINE fixWideString TONIGHT wfpsf(float*, int);
    extern INLINE fixWideString TONIGHT wdpsf(double*, int);
    extern INLINE fixWideString TONIGHT wpps(pointer*);

    extern longFixWideString TONIGHT wcls(wchar_t);
    extern longFixWideString TONIGHT wbls(bool);
    extern longFixWideString TONIGHT wils(int);
    extern longFixWideString TONIGHT wfls(float);
    extern longFixWideString TONIGHT wdls(double);
    extern longFixWideString TONIGHT wflsf(float, int);
    extern longFixWideString TONIGHT wdlsf(double, int);

	#ifdef __cplusplus
		}
	#endif // __cplusplus
#endif
