/* Tonight */
const TONIGHT struct Resources Tonight = {
	.Std ={
		.Console = {
			.Input = {
				.ReadChar = __Scanner_nextChar,
				.ReadInt = __Scanner_nextInt,
				.ReadFloat = __Scanner_nextFloat,
				.ReadDouble = __Scanner_nextDouble,
				.Read = __Scanner_next,
				.ReadLine = __Scanner_nextLine,
				.ClearInputBuffer = __Scanner_clear,
				.IgnoreString = __Scanner_ignore,
				.IgnoreChar = __Scanner_ignoreChar
			},
			.Output = {
				.WriteText = __Screen_text,
				.WriteTextln = __Screen_textln,
				.Write = __Screen_print,
				.Writeln = __Screen_println,
				.Writeargln = __Screen_printargln,
				.newLine = __Screen_nl,
				.newMultipleLines = __Screen_nls,
				.ClearOutputBuffer = __Screen_clear
			}
		},
		.File = {
			.Input = {
				.ReadChar = __Scanner_file_nextChar,
				.ReadInt = __Scanner_file_nextInt,
				.ReadFloat = __Scanner_file_nextFloat,
				.ReadDouble = __Scanner_file_nextDouble,
				.Read = __Scanner_file_next,
				.ReadLine = __Scanner_file_nextLine,
				.ClearInputBuffer = __Scanner_file_clear,
				.IgnoreString = __Scanner_file_ignore,
				.IgnoreChar = __Scanner_file_ignoreChar
			},
			.Output = {
				.WriteText = __Recorder_text,
				.WriteTextln = __Recorder_textln,
				.Write = __Recorder_print,
				.Writeln = __Recorder_println,
				.Writeargln = __Recorder_printargln,
				.newLine = __Recorder_nl,
				.newMultipleLines = __Recorder_nls,
				.ClearOutputBuffer = __Recorder_clear
			}
		},
		.String = {
			.Input = {
				.ReadChar = __Scanner_string_nextChar,
				.ReadInt = __Scanner_string_nextInt,
				.ReadFloat = __Scanner_string_nextFloat,
				.ReadDouble = __Scanner_string_nextDouble,
				.Read = __Scanner_string_next,
				.ReadLine = __Scanner_string_nextLine,
				.ClearInputBuffer = __Scanner_string_clear,
				.IgnoreString = __Scanner_string_ignore,
				.IgnoreChar = __Scanner_string_ignoreChar
			},
			.Output = {
				.WriteText = __String_text,
				.WriteTextln = __String_textln,
				.Write = __String_print,
				.Writeln = __String_println,
				.Writeargln = __String_printargln,
				.newLine = __Default_void_function,
				.newMultipleLines = __Default_void_function,
				.ClearOutputBuffer = __Default_void_function
			}
		},
		.Object = {
			.Input = {
				.ReadChar = __Scanner_object_nextChar,
				.ReadInt = __Scanner_object_nextInt,
				.ReadFloat = __Scanner_object_nextFloat,
				.ReadDouble = __Scanner_object_nextDouble,
				.Read = __Scanner_object_next,
				.ReadLine = __Scanner_object_nextLine,
				.ClearInputBuffer = __Scanner_object_clear,
				.IgnoreString = __Scanner_object_ignore,
				.IgnoreChar = __Scanner_object_ignoreChar
			},
			.Output = {
				.WriteText = __Object_text,
				.WriteTextln = __Object_textln,
				.Write = __Object_print,
				.Writeln = __Object_println,
				.Writeargln = __Object_printargln,
				.newLine = __Object_nl,
				.newMultipleLines = __Object_nls,
				.ClearOutputBuffer = __Object_clear
			}
		},
		.Error = {
			.Input = {
				.ReadChar = __Scanner_Error_nextChar,
				.ReadInt = __Scanner_Error_nextInt,
				.ReadFloat = __Scanner_Error_nextFloat,
				.ReadDouble = __Scanner_Error_nextDouble,
				.Read = __Scanner_Error_next,
				.ReadLine = __Scanner_Error_nextLine,
				.ClearInputBuffer = __Default_void_function,
				.IgnoreString = __Default_void_function,
				.IgnoreChar = __Default_void_function,
			},
			
			.Output = {
				.WriteText = __Error_text,
				.WriteTextln = __Error_textln,
				.Write = __Error_print,
				.Writeln = __Error_println,
				.Writeargln = __Error_printargln,
				.newLine = __Error_nl,
				.newMultipleLines = __Error_nls,
				.ClearOutputBuffer = __Error_clear
			},
		},
		.Random = {
			.Simple = {
				.MakeRandomicChar = __Random_simple_nextChar,
				.MakeRandomicInt = __Random_simple_nextInt,
				.MakeRandomicFloat = __Random_simple_nextFloat,
				.MakeRandomicDouble = __Random_simple_nextDouble
			},
			.Limit = {
				.MakeRandomicChar = __Random_end_nextChar,
				.MakeRandomicInt = __Random_end_nextInt,
				.MakeRandomicFloat = __Random_end_nextFloat,
				.MakeRandomicDouble = __Random_end_nextDouble
			},
			.Range = {
				.MakeRandomicChar = __Random_begin_end_nextChar,
				.MakeRandomicInt = __Random_begin_end_nextInt,
				.MakeRandomicFloat = __Random_begin_end_nextFloat,
				.MakeRandomicDouble = __Random_begin_end_nextDouble
			}
		},
		.TimeNow = {
			.GetTime = __time,
			.TimeHours = __Time_hours,
			.TimeMinutes = __Time_minutes,
			.TimeSeconds = __Time_seconds,
			.TimeMonth = __Time_month,
			.TimeDay_month = __Time_day_month,
			.TimeDay_week = __Time_day_week,
			.TimeDay_year = __Time_day_year,
			.TimeYear = __Time_year
		}
	},
	.Wide ={
		.Console = {
			.Input = {
				.ReadChar = __Scanner_Wide_nextChar,
				.ReadInt = __Scanner_Wide_nextInt,
				.ReadFloat = __Scanner_Wide_nextFloat,
				.ReadDouble = __Scanner_Wide_nextDouble,
				.Read = __Scanner_Wide_next,
				.ReadLine = __Scanner_Wide_nextLine,
				.ClearInputBuffer = __Scanner_Wide_clear,
				.IgnoreString = __Scanner_Wide_ignore,
				.IgnoreChar = __Scanner_Wide_ignoreChar
			},
			.Output = {
				.WriteText = __Screen_Wide_text,
				.WriteTextln = __Screen_Wide_textln,
				.Write = __Screen_Wide_print,
				.Writeln = __Screen_Wide_println,
				.Writeargln = __Screen_Wide_printargln,
				.newLine = __Screen_Wide_nl,
				.newMultipleLines = __Screen_Wide_nls,
				.ClearOutputBuffer = __Screen_Wide_clear
			}
		},
		.File = {
			.Input = {
				.ReadChar = __Scanner_Wide_file_nextChar,
				.ReadInt = __Scanner_Wide_file_nextInt,
				.ReadFloat = __Scanner_Wide_file_nextFloat,
				.ReadDouble = __Scanner_Wide_file_nextDouble,
				.Read = __Scanner_Wide_file_next,
				.ReadLine = __Scanner_Wide_file_nextLine,
				.ClearInputBuffer = __Scanner_Wide_file_clear,
				.IgnoreString = __Scanner_Wide_file_ignore,
				.IgnoreChar = __Scanner_Wide_file_ignoreChar
			},
			.Output = {
				.WriteText = __Recorder_Wide_text,
				.WriteTextln = __Recorder_Wide_textln,
				.Write = __Recorder_Wide_print,
				.Writeln = __Recorder_Wide_println,
				.Writeargln = __Recorder_Wide_printargln,
				.newLine = __Recorder_Wide_nl,
				.newMultipleLines = __Recorder_Wide_nls,
				.ClearOutputBuffer = __Recorder_Wide_clear
			}
		},
		.String = {
			.Input = {
				.ReadChar = __Scanner_Wide_string_nextChar,
				.ReadInt = __Scanner_Wide_string_nextInt,
				.ReadFloat = __Scanner_Wide_string_nextFloat,
				.ReadDouble = __Scanner_Wide_string_nextDouble,
				.Read = __Scanner_Wide_string_next,
				.ReadLine = __Scanner_Wide_string_nextLine,
				.ClearInputBuffer = __Scanner_Wide_string_clear,
				.IgnoreString = __Scanner_Wide_string_ignore,
				.IgnoreChar = __Scanner_Wide_string_ignoreChar
			},
			.Output = {
				.WriteText = __String_Wide_text,
				.WriteTextln = __String_Wide_textln,
				.Write = __String_Wide_print,
				.Writeln = __String_Wide_println,
				.Writeargln = __String_Wide_printargln,
				.newLine = __Default_void_function,
				.newMultipleLines = __Default_void_function,
				.ClearOutputBuffer = __Default_void_function
			}
		},
		.Error = {
			.Input = {
				.ReadChar = __Scanner_Wide_Error_nextChar,
				.ReadInt = __Scanner_Wide_Error_nextInt,
				.ReadFloat = __Scanner_Wide_Error_nextFloat,
				.ReadDouble = __Scanner_Wide_Error_nextDouble,
				.Read = __Scanner_Wide_Error_next,
				.ReadLine = __Scanner_Wide_Error_nextLine,
				.ClearInputBuffer = __Default_void_function,
				.IgnoreString = __Default_void_function,
				.IgnoreChar = __Default_void_function,
			},
			
			.Output = {
				.WriteText = __Error_Wide_text,
				.WriteTextln = __Error_Wide_textln,
				.Write = __Error_Wide_print,
				.Writeln = __Error_Wide_println,
				.Writeargln = __Error_Wide_printargln,
				.newLine = __Error_Wide_nl,
				.newMultipleLines = __Error_Wide_nls,
				.ClearOutputBuffer = __Error_Wide_clear
			},
		},
	},
	.Resources = {
		.Color = {
			.textColor = __Colors_text,
			.backgroundColor = __Colors_background,
			.bothColors = __Colors_textbackground
		}
	},
	
	.Convert = {
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
	},
	
	.Locale = {
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
	},
	
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
	.initRandom = __initRandom,
	.enableASCII = __enableASCII,
	.enableUTF8 = __enableUTF8,
	
	.Mode = {
		.Default = TonightModeDefault,
		.Loop = TonightModeLoop
	},
	
	.Callback = {
		.setMalloc = Callback_setMalloc,
		.setCalloc = Callback_setCalloc,
		.setRealloc = Callback_setRealloc,
		.setFree = Callback_setFree
	},
	
	.Shared = {
		.close = __Shared_close,
		.open = __Shared_open,
		.get = __Shared_get
	}
};

/* New */
const TONIGHT struct __New New = {
	.Scanner = __new_Scanner,
	.Writer = __new_Writer,
	.Random = __new_Random,
	.Timer = __new_Timer,
	.Painter = __new_Painter,
	.Object = new,
	
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
	.toString = Array_toString,
	.convert = Array_convert,
	
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

/* Memory */
const struct __Memory Memory = {
	.alloc = __new_memory,
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
	.free = (pointer)__memory_free
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
	.free = (pointer)__memory_free
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
	.access = Collection_access
};
