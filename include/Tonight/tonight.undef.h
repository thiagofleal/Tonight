/*
*	This file is part of the Tonight library
*	
*	File: tonight.undef.h
*	This file prepares the framework macros.
*	
*	Copyright (C)  2018  Thiago Fernandes Leal.
*	Permission is granted to copy, distribute and/or modify this document
*	under the terms of the GNU Free Documentation License, Version 1.3
*	or any later version published by the Free Software Foundation;
*	with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
*	A copy of the license is included in the section entitled "GNU
*	Free Documentation License".
*/

#ifndef TONIGHT_UNDEFINITIONS
#	define TONIGHT_UNDEFINITIONS

#	ifndef TONIGHT_LIBRARY
#		error "Include the Tonight library with #include<Tonight/tonight.h>"
#	endif

#	ifdef TONIGHT
#		undef TONIGHT
#	endif
#	ifdef NO_CALL
#		undef NO_CALL
#	endif

#	ifdef key_right
#		undef key_right
#	endif
#	ifdef key_left
#		undef key_left
#	endif
#	ifdef key_up
#		undef key_up
#	endif
#	ifdef key_down
#		undef key_down
#	endif
#	ifdef key_ESC
#		undef key_ESC
#	endif
#	ifdef key_ENTER
#		undef key_ENTER
#	endif
#	ifdef key_SPACE
#		undef key_SPACE
#	endif
#	ifdef key_BS
#		undef key_BS
#	endif

#	ifdef $Empty
#		undef $Empty
#	endif
#	ifdef $end
#		undef $end
#	endif

#	ifdef ARRAY
#		undef ARRAY
#	endif
#	ifdef MATRIX
#		undef MATRIX
#	endif
#	ifdef getText
#		undef getText
#	endif

#	ifdef $throws
#		undef $throws
#	endif
#	ifdef Try
#		undef Try
#	endif
#	ifdef Catch
#		undef Catch
#	endif
#	ifdef Finally
#		undef Finally
#	endif
#	ifdef Define_Exception
#		undef Define_Exception
#	endif

#	ifndef __cplusplus
#		ifdef and
#			undef and
#		endif
#		ifdef or
#			undef or
#		endif
#		ifdef try
#			undef try
#		endif
#		ifdef catch
#			undef catch
#		endif
#		ifdef finally
#			undef finally
#		endif
#		ifdef throw
#			undef throw
#		endif
#		ifdef using
#			undef using
#		endif
#	endif

#	ifdef INLINE
#		undef INLINE
#	endif

#	ifdef NORMAL
#		undef NORMAL
#	endif
#	ifdef ARRAY_LENGTH
#		undef ARRAY_LENGTH
#	endif

#	ifdef SELECT
#		undef SELECT
#	endif

#	ifdef DOWN_10
#		undef DOWN_10
#	endif
#	ifdef DOWN_20
#		undef DOWN_20
#	endif
#	ifdef DOWN_30
#		undef DOWN_30
#	endif
#	ifdef DOWN_40
#		undef DOWN_40
#	endif
#	ifdef DOWN_50
#		undef DOWN_50
#	endif

#	ifdef COUNT
#		undef COUNT
#	endif
#	ifdef New_Array
#		undef New_Array
#	endif

#	ifdef OptionalArgs
#		undef OptionalArgs
#	endif

#	ifdef __using__
#		undef __using__
#	endif
#	ifdef Using
#		undef Using
#	endif

#	ifdef __forindex__
#		undef __forindex__
#	endif
#	ifdef forindex
#		undef forindex
#	endif

#	ifdef __foreach__
#		undef __foreach__
#	endif
#	ifdef foreach
#		undef foreach
#	endif

#	ifdef $in
#		undef $in
#	endif
#	ifdef $as
#		undef $as
#	endif
#	ifdef $with
#		undef $with
#	endif
#	ifdef $where
#		undef $where
#	endif
#	ifdef $from
#		undef $from
#	endif

#	ifdef $c
#		undef $c
#	endif
#	ifdef $b
#		undef $b
#	endif
#	ifdef $i
#		undef $i
#	endif
#	ifdef $f
#		undef $f
#	endif
#	ifdef $d
#		undef $d
#	endif
#	ifdef $s
#		undef $s
#	endif
#	ifdef $o
#		undef $o
#	endif
#	ifdef $ff
#		undef $ff
#	endif
#	ifdef $df
#		undef $df
#	endif
#	ifdef $F
#		undef $F
#	endif

#	ifdef $cp
#		undef $cp
#	endif
#	ifdef $bp
#		undef $bp
#	endif
#	ifdef $ip
#		undef $ip
#	endif
#	ifdef $fp
#		undef $fp
#	endif
#	ifdef $dp
#		undef $dp
#	endif
#	ifdef $sp
#		undef $sp
#	endif
#	ifdef $fpf
#		undef $fpf
#	endif
#	ifdef $dpf
#		undef $dpf
#	endif

#	ifdef $lc
#		undef $lc
#	endif
#	ifdef $lb
#		undef $lb
#	endif
#	ifdef $li
#		undef $li
#	endif
#	ifdef $lf
#		undef $lf
#	endif
#	ifdef $ld
#		undef $ld
#	endif
#	ifdef $ls
#		undef $ls
#	endif
#	ifdef $lo
#		undef $lo
#	endif
#	ifdef $lff
#		undef $lff
#	endif
#	ifdef $ldf
#		undef $ldf
#	endif
#	ifdef $lF
#		undef $lF
#	endif

#	ifdef Writer
#		undef Writer
#	endif
#	ifdef Scanner
#		undef Scanner
#	endif
#	ifdef Random
#		undef Random
#	endif
#	ifdef Timer
#		undef Timer
#	endif
#	ifdef Painter
#		undef Painter
#	endif
#	ifdef Object
#		undef Object
#	endif
#	ifdef Char
#		undef Char
#	endif
#	ifdef Byte
#		undef Byte
#	endif
#	ifdef Bool
#		undef Bool
#	endif
#	ifdef Int
#		undef Int
#	endif
#	ifdef Float
#		undef Float
#	endif
#	ifdef Double
#		undef Double
#	endif
#	ifdef String
#		undef String
#	endif
#	ifdef Pointer
#		undef Pointer
#	endif

#	ifndef __cplusplus
#		ifdef true
#			undef true
#		endif
#		ifdef false
#			undef false
#		endif
#	endif

#	ifdef __DefineCast__
#		undef __DefineCast__
#	endif
#	ifdef DefineCast
#		undef DefineCast
#	endif

#	ifdef __CONDITION__
#		undef __DefineCast__
#	endif
#	ifdef __Condition__
#		undef __Condition__
#	endif
#	ifdef Where
#		undef Where
#	endif
#	ifdef DefineCast
#		undef DeclareCondition
#	endif

#	ifdef __Define_Class__
#		undef __Define_Class__
#	endif
#	ifdef __class__
#		undef __class__
#	endif
#	ifdef class
#		undef class
#	endif
#	ifdef Define_Class
#		undef Define_Class
#	endif

#	ifdef interface
#		undef interface
#	endif
#	ifdef __select__
#		undef __select__
#	endif
#	ifdef $
#		undef $
#	endif

#	ifdef private
#		undef private
#	endif
#	ifdef protected
#		undef protected
#	endif
#	ifdef public
#		undef public
#	endif

#	ifdef $extends
#		undef $extends
#	endif
#	ifdef $implements
#		undef $implements
#	endif

#	ifdef CLASS
#		undef CLASS
#	endif
#	ifdef this
#		undef this
#	endif
#	ifdef constructArg
#		undef constructArg
#	endif
#	ifdef setInterface
#		undef setInterface
#	endif
#	ifdef getInterface
#		undef getInterface
#	endif
#	ifdef callInterface
#		undef callInterface
#	endif

#	ifdef Constructor
#		undef Constructor
#	endif
#	ifdef Destructor
#		undef Destructor
#	endif

#	ifdef super
#		undef super
#	endif
#	ifdef super_construct
#		undef super_construct
#	endif
#	ifdef super_delete
#		undef super_delete
#	endif
#	ifdef super_getInterface
#		undef super_getInterface
#	endif
#	ifdef super_setInterface
#		undef super_setInterface
#	endif
#	ifdef super_cast
#		undef super_cast
#	endif

#endif
