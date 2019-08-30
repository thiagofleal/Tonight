/* Tonight */

    /* Std */

        /* Console */
        struct Input Tonight_Std_Console_Input = {
            .ReadChar = __Scanner_nextChar,
            .ReadInt = __Scanner_nextInt,
            .ReadFloat = __Scanner_nextFloat,
            .ReadDouble = __Scanner_nextDouble,
            .Read = __Scanner_next,
            .ReadLine = __Scanner_nextLine,
            .ClearInputBuffer = __Scanner_clear,
            .IgnoreString = __Scanner_ignore,
            .IgnoreChar = __Scanner_ignoreChar
        };

        struct Output Tonight_Std_Console_Output = {
            .WriteText = __Screen_text,
            .WriteTextln = __Screen_textln,
            .Write = __Screen_print,
            .Writeln = __Screen_println,
            .Writeargln = __Screen_printargln,
            .newLine = __Screen_nl,
            .newMultipleLines = __Screen_nls,
            .ClearOutputBuffer = __Screen_clear
        };

        struct IO Tonight_Std_Console = {
            .Input = &Tonight_Std_Console_Input,
            .Output = &Tonight_Std_Console_Output
        };

        /* File */
        struct Input Tonight_Std_File_Input = {
            .ReadChar = __Scanner_file_nextChar,
            .ReadInt = __Scanner_file_nextInt,
            .ReadFloat = __Scanner_file_nextFloat,
            .ReadDouble = __Scanner_file_nextDouble,
            .Read = __Scanner_file_next,
            .ReadLine = __Scanner_file_nextLine,
            .ClearInputBuffer = __Scanner_file_clear,
            .IgnoreString = __Scanner_file_ignore,
            .IgnoreChar = __Scanner_file_ignoreChar
        };

        struct Output Tonight_Std_File_Output = {
            .WriteText = __Recorder_text,
            .WriteTextln = __Recorder_textln,
            .Write = __Recorder_print,
            .Writeln = __Recorder_println,
            .Writeargln = __Recorder_printargln,
            .newLine = __Recorder_nl,
            .newMultipleLines = __Recorder_nls,
            .ClearOutputBuffer = __Recorder_clear
        };

        struct IO Tonight_Std_File = {
            .Input = &Tonight_Std_File_Input,
            .Output = &Tonight_Std_File_Output
        };

        /* String */
        struct Input Tonight_Std_String_Input = {
            .ReadChar = __Scanner_string_nextChar,
            .ReadInt = __Scanner_string_nextInt,
            .ReadFloat = __Scanner_string_nextFloat,
            .ReadDouble = __Scanner_string_nextDouble,
            .Read = __Scanner_string_next,
            .ReadLine = __Scanner_string_nextLine,
            .ClearInputBuffer = __Scanner_string_clear,
            .IgnoreString = __Scanner_string_ignore,
            .IgnoreChar = __Scanner_string_ignoreChar
        };

        struct Output Tonight_Std_String_Output = {
            .WriteText = __String_text,
            .WriteTextln = __String_textln,
            .Write = __String_print,
            .Writeln = __String_println,
            .Writeargln = __String_printargln,
            .newLine = __Default_void_function,
            .newMultipleLines = __Default_void_function,
            .ClearOutputBuffer = __Default_void_function
        };

        struct IO Tonight_Std_String = {
            .Input = &Tonight_Std_String_Input,
            .Output = &Tonight_Std_String_Output
        };

        /* Object */
        struct Input Tonight_Std_Object_Input = {
            .ReadChar = __Scanner_object_nextChar,
            .ReadInt = __Scanner_object_nextInt,
            .ReadFloat = __Scanner_object_nextFloat,
            .ReadDouble = __Scanner_object_nextDouble,
            .Read = __Scanner_object_next,
            .ReadLine = __Scanner_object_nextLine,
            .ClearInputBuffer = __Scanner_object_clear,
            .IgnoreString = __Scanner_object_ignore,
            .IgnoreChar = __Scanner_object_ignoreChar
        };

        struct Output Tonight_Std_Object_Output = {
            .WriteText = __Object_text,
            .WriteTextln = __Object_textln,
            .Write = __Object_print,
            .Writeln = __Object_println,
            .Writeargln = __Object_printargln,
            .newLine = __Object_nl,
            .newMultipleLines = __Object_nls,
            .ClearOutputBuffer = __Object_clear
        };

        struct IO Tonight_Std_Object = {
            .Input = &Tonight_Std_Object_Input,
            .Output = &Tonight_Std_Object_Output
        };

        /* Error */
        struct Input Tonight_Std_Error_Input = {
            .ReadChar = __Scanner_Error_nextChar,
            .ReadInt = __Scanner_Error_nextInt,
            .ReadFloat = __Scanner_Error_nextFloat,
            .ReadDouble = __Scanner_Error_nextDouble,
            .Read = __Scanner_Error_next,
            .ReadLine = __Scanner_Error_nextLine,
            .ClearInputBuffer = __Default_void_function,
            .IgnoreString = __Default_void_function,
            .IgnoreChar = __Default_void_function,
        };

        struct Output Tonight_Std_Error_Output = {
            .WriteText = __Error_text,
            .WriteTextln = __Error_textln,
            .Write = __Error_print,
            .Writeln = __Error_println,
            .Writeargln = __Error_printargln,
            .newLine = __Error_nl,
            .newMultipleLines = __Error_nls,
            .ClearOutputBuffer = __Error_clear
        };

        struct IO Tonight_Std_Error = {
            .Input = &Tonight_Std_Error_Input,
            .Output = &Tonight_Std_Error_Output
        };

    struct IO_set Tonight_Std = {
        .Console = &Tonight_Std_Console,
        .File = &Tonight_Std_File,
        .String = &Tonight_Std_String,
        .Object = &Tonight_Std_Object,
        .Error = &Tonight_Std_Error,
    };

    /* Wide */
        /* Console */
        struct Input Tonight_Wide_Console_Input = {
            .ReadChar = __Scanner_Wide_nextChar,
            .ReadInt = __Scanner_Wide_nextInt,
            .ReadFloat = __Scanner_Wide_nextFloat,
            .ReadDouble = __Scanner_Wide_nextDouble,
            .Read = __Scanner_Wide_next,
            .ReadLine = __Scanner_Wide_nextLine,
            .ClearInputBuffer = __Scanner_Wide_clear,
            .IgnoreString = __Scanner_Wide_ignore,
            .IgnoreChar = __Scanner_Wide_ignoreChar
        };

        struct Output Tonight_Wide_Console_Output = {
            .WriteText = __Screen_Wide_text,
            .WriteTextln = __Screen_Wide_textln,
            .Write = __Screen_Wide_print,
            .Writeln = __Screen_Wide_println,
            .Writeargln = __Screen_Wide_printargln,
            .newLine = __Screen_Wide_nl,
            .newMultipleLines = __Screen_Wide_nls,
            .ClearOutputBuffer = __Screen_Wide_clear
        };

        struct IO Tonight_Wide_Console = {
            .Input = &Tonight_Wide_Console_Input,
            .Output = &Tonight_Wide_Console_Output
        };

        /* File */
        struct Input Tonight_Wide_File_Input = {
            .ReadChar = __Scanner_Wide_file_nextChar,
            .ReadInt = __Scanner_Wide_file_nextInt,
            .ReadFloat = __Scanner_Wide_file_nextFloat,
            .ReadDouble = __Scanner_Wide_file_nextDouble,
            .Read = __Scanner_Wide_file_next,
            .ReadLine = __Scanner_Wide_file_nextLine,
            .ClearInputBuffer = __Scanner_Wide_file_clear,
            .IgnoreString = __Scanner_Wide_file_ignore,
            .IgnoreChar = __Scanner_Wide_file_ignoreChar
        };

        struct Output Tonight_Wide_File_Output = {
            .WriteText = __Recorder_Wide_text,
            .WriteTextln = __Recorder_Wide_textln,
            .Write = __Recorder_Wide_print,
            .Writeln = __Recorder_Wide_println,
            .Writeargln = __Recorder_Wide_printargln,
            .newLine = __Recorder_Wide_nl,
            .newMultipleLines = __Recorder_Wide_nls,
            .ClearOutputBuffer = __Recorder_Wide_clear
        };

        struct IO Tonight_Wide_File = {
            .Input = &Tonight_Wide_File_Input,
            .Output = &Tonight_Wide_File_Output
        };

        /* String */
        struct Input Tonight_Wide_String_Input = {
            .ReadChar = __Scanner_Wide_string_nextChar,
            .ReadInt = __Scanner_Wide_string_nextInt,
            .ReadFloat = __Scanner_Wide_string_nextFloat,
            .ReadDouble = __Scanner_Wide_string_nextDouble,
            .Read = __Scanner_Wide_string_next,
            .ReadLine = __Scanner_Wide_string_nextLine,
            .ClearInputBuffer = __Scanner_Wide_string_clear,
            .IgnoreString = __Scanner_Wide_string_ignore,
            .IgnoreChar = __Scanner_Wide_string_ignoreChar
        };

        struct Output Tonight_Wide_String_Output = {
            .WriteText = __String_Wide_text,
            .WriteTextln = __String_Wide_textln,
            .Write = __String_Wide_print,
            .Writeln = __String_Wide_println,
            .Writeargln = __String_Wide_printargln,
            .newLine = __Default_void_function,
            .newMultipleLines = __Default_void_function,
            .ClearOutputBuffer = __Default_void_function
        };

        struct IO Tonight_Wide_String = {
            .Input = &Tonight_Wide_String_Input,
            .Output = &Tonight_Wide_String_Output
        };

        /* Error */
        struct Input Tonight_Wide_Error_Input = {
            .ReadChar = __Scanner_Wide_Error_nextChar,
            .ReadInt = __Scanner_Wide_Error_nextInt,
            .ReadFloat = __Scanner_Wide_Error_nextFloat,
            .ReadDouble = __Scanner_Wide_Error_nextDouble,
            .Read = __Scanner_Wide_Error_next,
            .ReadLine = __Scanner_Wide_Error_nextLine,
            .ClearInputBuffer = __Default_void_function,
            .IgnoreString = __Default_void_function,
            .IgnoreChar = __Default_void_function,
        };

        struct Output Tonight_Wide_Error_Output = {
            .WriteText = __Error_Wide_text,
            .WriteTextln = __Error_Wide_textln,
            .Write = __Error_Wide_print,
            .Writeln = __Error_Wide_println,
            .Writeargln = __Error_Wide_printargln,
            .newLine = __Error_Wide_nl,
            .newMultipleLines = __Error_Wide_nls,
            .ClearOutputBuffer = __Error_Wide_clear
        };

        struct IO Tonight_Wide_Error = {
            .Input = &Tonight_Wide_Error_Input,
            .Output = &Tonight_Wide_Error_Output
        };

    struct IO_set Tonight_Wide = {
		.Console = &Tonight_Wide_Console,
		.File = &Tonight_Wide_File,
		.String = &Tonight_Wide_String,
		.Error = &Tonight_Wide_Error
	};

	/* Random */
	struct RandomicMaker Tonight_Random_Simple = {
        .MakeRandomicChar = __Random_simple_nextChar,
        .MakeRandomicInt = __Random_simple_nextInt,
        .MakeRandomicFloat = __Random_simple_nextFloat,
        .MakeRandomicDouble = __Random_simple_nextDouble
    };

    struct RandomicMaker Tonight_Random_Limit = {
        .MakeRandomicChar = __Random_end_nextChar,
        .MakeRandomicInt = __Random_end_nextInt,
        .MakeRandomicFloat = __Random_end_nextFloat,
        .MakeRandomicDouble = __Random_end_nextDouble
    };

    struct RandomicMaker Tonight_Random_Range = {
        .MakeRandomicChar = __Random_begin_end_nextChar,
        .MakeRandomicInt = __Random_begin_end_nextInt,
        .MakeRandomicFloat = __Random_begin_end_nextFloat,
        .MakeRandomicDouble = __Random_begin_end_nextDouble
    };

	struct __Random_set Tonight_Random = {
        .Simple = &Tonight_Random_Simple,
        .Limit = &Tonight_Random_Limit,
        .Range = &Tonight_Random_Range
    };

    /* Timer */
    struct TimerCreate Tonight_Timer_Now = {
        .GetTime = __time,
        .TimeHours = __Time_hours,
        .TimeMinutes = __Time_minutes,
        .TimeSeconds = __Time_seconds,
        .TimeMonth = __Time_month,
        .TimeDay_month = __Time_day_month,
        .TimeDay_week = __Time_day_week,
        .TimeDay_year = __Time_day_year,
        .TimeYear = __Time_year
    };

    struct __Timer_set Tonight_Timer = {
        .Now = &Tonight_Timer_Now
    };

    /* Color */
    struct ColorCreate Tonight_Color_Console = {
        .textColor = __Colors_text,
        .backgroundColor = __Colors_background,
        .bothColors = __Colors_textbackground
    };

    struct __Color_set Tonight_Color = {
	    .Console = &Tonight_Color_Console
	};

	/* Conversor */
	struct __Conversor_set Tonight_Conversor = {
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
		.fromDouble = s_ds,
		.fromTime = string_fromDate
	};

	/* Locale */
	struct __Locale_set Tonight_Locale = {
		.getCategory = __getCategory,
		.setCategory = __setCategory,
		.getName = __getName,
		.setName = __setName,
		.set = __locale,
		.get = __getlocale,

		.Category = {
			.All = LC_ALL,
			.Collate = LC_COLLATE,
			.Type = LC_CTYPE,
			.Monetary = LC_MONETARY,
			.Numeric = LC_NUMERIC,
			.Time = LC_TIME
		}
	};

	/* Util */
	struct __Util_set Tonight_Util = {
	    .DefaultFunctionPointer = __Default_void_function,
        .assert = __assert,
        .checkErrno = __checkErrno,
        .password = __Scanner_Password,
        .clearScreen = __clearScreen,
        .getKey = getKey,
        .getKeyEcho = getKeyEcho,
        .pressKey = pressKey,
        .sleep = __sleep,
        .position = cursor_position,
	};

	/* Encode */
	struct __Encode_set Tonight_Encode = {
		.enableSTD = __enableASCII,
		.enableUTF8 = __enableUTF8,
	};

	/* Callback */
	struct __Callback_set Tonight_Callback = {
        .setMalloc = Callback_setMalloc,
        .setCalloc = Callback_setCalloc,
        .setRealloc = Callback_setRealloc,
        .setFree = Callback_setFree
    };

    /* Shared */
    struct __Shared_set Tonight_Shared = {
		.close = __Shared_close,
		.open = __Shared_open,
		.get = __Shared_get
	};

const TONIGHT struct Resources namespace_Tonight = {
	.Std = &Tonight_Std,
	.Wide = &Tonight_Wide,
	.Random = &Tonight_Random,
    .Timer = &Tonight_Timer,
	.Color = &Tonight_Color,
	.Conversor = &Tonight_Conversor,
	.Locale = &Tonight_Locale,
    .Util = &Tonight_Util,
	.Encode = &Tonight_Encode,
	.Callback = &Tonight_Callback,
	.Shared = &Tonight_Shared
};

const TONIGHT struct Resources *Tonight = &namespace_Tonight;

/* New */
const TONIGHT struct __New New = {
	.Scanner = __new_Scanner,
	.Writer = __new_Writer,
	.Random = __new_Random,
	.Timer = __new_Timer,
	.Painter = __new_Painter,
	.Object = (pointer)newInstance,

	.Char = __new_char,
	.Byte = __new_byte,
	.Bool = __new_bool,
	.Int = __new_int,
	.Float = __new_float,
	.Double = __new_double,
	.String = __new_String,
	.Pointer = __new_pointer
};

/* Array */
const struct __Array Array = {
	.length = Array_length,
	.size = Array_size,
	.access = Array_access,
	.free = Array_free,
	.setStringMethod = Array_setStringMethod,
	.toString = Array_toString,
	.convert = Array_convert,
	.where = Array_where,
	.contains = Array_contains,
	.sort = Array_sort,
    .forEach = Array_forEach,

	.Char = __new_array_char,
	.Byte = __new_array_byte,
	.Bool = __new_array_bool,
	.Int = __new_array_int,
	.Float = __new_array_float,
	.Double = __new_array_double,
	.String = __new_array_String,
	.Object = __new_array_Object,
	.Pointer = __new_array_pointer,
	.Generic = __new_array_generic
};

const struct ___Array_Interface___ ___Array___ = {
	.select = Array_select
};

/* Memory */
const struct __Memory Memory = {
	.alloc = __new_memory,
	.realloc = __realloc_memory,
	.size = __memory_size,
	.copy = __memory_copy,
	.free = __memory_free
};

/* String */
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
	.free = (pointer)__memory_free,
	.toString = (pointer)toString,
	.toWide = stringToWide
};

const struct ___String_Interface___ ___String___ = {
	.select = String_select
};

const struct __String WideString = {
	.formated = (pointer)WString_formated,
	.copy = (pointer)toWide,
	.concatenate = (pointer)WString_concatenate,
	.upper = (pointer)WString_upper,
	.lower = (pointer)WString_lower,
	.length = (pointer)wcslen,
	.compare = (pointer)wcscmp,
	.sep = (pointer)WString_sep,
	.split = (pointer)WString_split,
	.trim = (pointer)WString_trim,
	.free = (pointer)__memory_free,
	.toString = wideToString,
	.toWide = (pointer)toWide
};

const struct ___String_Interface___ ___WideString___ = {
	.select = WString_select
};

/* File */
const struct __File File = {
	.open = __new_File,
	.close = File_close,
	.end = File_end,
	.rewind = File_rewind,
	.stdInput = File_stdInput,
	.stdOutput = File_stdOutput,
	.stdError = File_stdError,
	.Mode.read = {"r"},
	.Mode.write = {"w"},
	.Mode.append = {"a"}
};

const struct ___File_Interface___ ___File___ = {
	.select = File_select
};

/* Key */
const struct __Key Key = {
	.Right = key_right,
	.Left = key_left,
	.Up = key_up,
	.Down = key_down,
	.Escape = key_ESC,
	.Enter = key_ENTER,
	.Space = key_SPACE,
	.BackSpace = key_BS
};

/* Exit */
const struct __Exit Exit = {
	.Success = EXIT_SUCCESS,
	.Failure = EXIT_FAILURE,
	.With = exit,
	.WithSuccess = Exit_WithSuccess,
	.WithFail = Exit_WithFail
};

/* Collection */
const ICollection Collection = {
	.length = Collection_lenght,
	.size = Collection_size,
	.access = Collection_access,
	.index = Collection_index
};
