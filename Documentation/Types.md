# Tonight's types

Following a description about the data types defined by the Tonight library

## Data types

The types that realy stores data (and not references data) are descripted below.

> ### bool

This type is used to store boolean values (**true** or **false**). If the language used is C++, the **bool** type is native, but, if is it C, the type is defined as a unsigned char.

```C
typedef unsigned char bool;
```

The values that can be used by the **bool** type are defined as 0 and 1.

```C
#define true 0x1
#define false 0x0
```

> #### **bool** use exemples

```C
bool boolean_value_1 = true;
bool boolean_value_2 = false;

if(boolean_value_1){
  /* code */
}
```

> ### retString

This type is used to return string values from functions without dinamic memory allocation. It is defined as a structure whith a **char** array of 101 positions, and than it's suports until 100 characters in the string (one character is used as the string terminator - '\0'). For larger strings use the *long_retString* type.

```C
typedef struct{
  char Text[101];
}retString;
```

> #### retString use exemple

```C
retString retString_test(void){
  retString ret;
  Writer write = new Writer(Tonight.std.string.output);
  write.text(getText(ret), "This is a test...");
  return ret;
}
```

> ### long_retString

This type is like the *retString* type but stores until 1000 characters. For more information, see *retString*.

```C
typedef struct{
  char Text[1001];
}long_retString;
```

> #### long_retString use exemple

```C
long_retString long_retString_test(string str){
  retString ret;
  Writer write = new Writer(Tonight.std.string.output);
  write.print(getText(ret), "This is a test: ", str, $end);
  return ret;
}
```

> ### EXCEPTION_DEFINE

This type is used to store a definition of an exception. This type isn't used by the library user, but an *EXCEPTION_DEFINE* instance is created by the *Define_Exception* macro.

```C
struct str_EXCEPTION{
  const string error_name;
  EXCEPTION *_super;
};
```

> ### _Exception

This type is internal used to store exceptions throwed in the application.

```C
typedef struct __struct_exception{
  EXCEPTION exception;
  string message;
}_Exception, *Exception;
```

> ### **struct** str_Class

This type is internal used to store a class definition. A ***struct** str_Class* instance stores the size of the class instance, the class' constructor and the class' destructor.

```C
typedef struct str_Class{
  const size_t size;
  void (* ctor)(Intern_Object *, __builtin_va_list *);
  void (* dtor)(Intern_Object *);
}*Class_Name;
```

> ### Intern_Object

This type is internal used to store a class instance object in the memory heap. An *Intern_Object* instance must stores a pointer to the class instance and a pointer to the class.

```C
struct str_Intern_Object{
  pointer obj;
  Class_Name class_pointer;
};
```

## Pointer types

The pointer types are showed below.

> ### string

This data type stores a pointer to string of characters. It is defined as a **char** pointer

```C
typedef char* string;
```

* **Note:** It's important to free the *string* after its use, except when it is allocated statically (with double quotes).

> #### string use exemples

```C
string hello = "Hello";
string world = "World";
string helloWorld = concat(hello, ", ", world, "!", $end);
/* code */
Memory.free(helloWorld);
```

> ### pointer

This data type stores a generic memory pointer. It is defined as a **void** pointer.

```C
typedef void* pointer;
```

> #### pointer use exemples

```C
int i;
pointer p = &i;
pointer mem = Memory.alloc(sizeof(int));
```

> ### file

This data type stores a pointer to a file buffer. It is used to handle files. It's defined as a *FILE* pointer;

```C
typedef void* file;
```

> #### file use examples

```C
file file = File.open("file_name.ext", "w");
Writer write = new Writer(Tonight.std.file.output);
write.textln(file, "This is a test...");
```

> ### object

This data type stores an object intanced from a class. It is used to handle objects. It's defined as a pointer to an structure *Intern_Object*. To instance an *object**, use ***new** object(Class)* and to free, use ***delete**(object)*.

```C
typedef struct str_Intern_Object *object;
```

> #### object use example

```C
object obj = new Object(Test);
/* code */
delete(obj);
```

> ### EXCEPTION

This data type is used to store an exception type. It is defined as a pointer to an structure *Exception_Define*. An *EXCEPTION* instance must be used in a header file, but, in a code file, the use of *Define_Exception* replaces the *EXCEPTION* by an implicity instance declaration.

```C
typedef struct str_EXCEPTION EXCEPTION_DEFINE, *EXCEPTION;
```

> #### EXCEPTION use examples

```C
EXCEPTION ExampleException;

Define_Exception(TestException, "This is a test", GenericException);//Creates an EXCEPTION named "TestException"
```

> ### Exception

This data type stores an exception pointer. It is defined as an *_Exception* pointer.

```C
typedef struct __struct_exception{
  EXCEPTION exception;
  string message;
}_Exception, *Exception;
```

> #### Exception use example

```C
try{
/* Code */
}
catch(GenericException){
  Exception e = getException();
  /* Code */
}
```

### Class_Name

This data type stores a class pointer. A *Class_Name* instance isn't explicity declared, but it's created by ***class*** macro. It is defined as a pointer to an structure ***struct** str_Class*.

```C
typedef struct str_Class{
  const size_t size;
  void (* ctor)(Intern_Object *, __builtin_va_list *);
  void (* dtor)(Intern_Object *);
}*Class_Name;
```

A *Class_Name* instance is used only by ***new** object* function to construct an object.

## Function pointer types

> ### P_void

A pointer to a **void**-returns function, with or without parameters. The main use for this data type is for callback.

```C
typedef void (*P_void)	(OptionalArgs);
```

> #### P_void use example

```C
void func(P_void callback){
  /* code */
}

void func_callback(/* arguments list */){
  /* code */
}

/* inside a function */
func(func_callback);
```

> ### P_char

A pointer to a **char**-returns function, with or without parameters. The main use for this data type is for callback.

```C
typedef char (*P_char)	(OptionalArgs);
```

> #### P_char use example

```C
void func(P_char callback){
  /* code */
}

char func_callback(/* arguments list */){
  /* code */
}

/* inside a function */
func(func_callback);
```

> ### P_bool

A pointer to a **bool**-returns function, with or without parameters. The main use for this data type is for callback.

```C
typedef bool (*P_bool)	(OptionalArgs);
```

> #### P_bool use example

```C
void func(P_bool callback){
  /* code */
}

bool func_callback(/* arguments list */){
  /* code */
}

/* inside a function */
func(func_callback);
```

> ### P_int

A pointer to a **int**-returns function, with or without parameters. The main use for this data type is for callback.

```C
typedef int (*P_int)	(OptionalArgs);
```

> #### P_int use example

```C
void func(P_int callback){
  /* code */
}

int func_callback(/* arguments list */){
  /* code */
}

/* inside a function */
func(func_callback);
```

> ### P_float

A pointer to a **float**-returns function, with or without parameters. The main use for this data type is for callback.

```C
typedef float (*P_float)	(OptionalArgs);
```

> #### P_float use example

```C
void func(P_float callback){
  /* code */
}

float func_callback(/* arguments list */){
  /* code */
}

/* inside a function */
func(func_callback);
```

> ### P_double

A pointer to a **double**-returns function, with or without parameters. The main use for this data type is for callback.

```C
typedef char (*P_double)	(OptionalArgs);
```

> #### P_double use example

```C
void func(P_double callback){
  /* code */
}

double func_callback(/* arguments list */){
  /* code */
}

/* inside a function */
func(func_callback);
```

> ### P_string

A pointer to a *string*-returns function, with or without parameters. The main use for this data type is for callback.

```C
typedef string (*P_string)	(OptionalArgs);
```

> #### P_string use example

```C
void func(P_string callback){
  /* code */
}

string func_callback(/* arguments list */){
  /* code */
}

/* inside a function */
func(func_callback);
```

> ### P_pointer

A pointer to a *pointer*-returns function, with or without parameters. The main use for this data type is for callback.

```C
typedef pointer (*P_pointer)	(OptionalArgs);
```

> #### P_pointer use example

```C
void func(P_pointer callback){
  /* code */
}

pointer func_callback(/* arguments list */){
  /* code */
}

/* inside a function */
func(func_callback);
```

> ### P_object

A pointer to a *object*-returns function, with or without parameters. The main use for this data type is for callback.

```C
typedef object (*P_object)	(OptionalArgs);
```

> #### P_object use example

```C
void func(P_object callback){
  /* code */
}

object func_callback(/* arguments list */){
  /* code */
}

/* inside a function */
func(func_callback);
```

> ### P_retString

A pointer to a *retString*-returns function, with or without parameters. The main use for this data type is for callback.

```C
typedef retString (*P_retString)	(OptionalArgs);
```

> #### P_retString use example

```C
void func(P_retString callback){
  /* code */
}

retString func_callback(/* arguments list */){
  /* code */
}

/* inside a function */
func(func_callback);
```

> ### P_long_retString

A pointer to a *long_retString*-returns function, with or without parameters. The main use for this data type is for callback.

```C
typedef long_retString (*P_long_retString)	(OptionalArgs);
```

> #### P_long_retString use example

```C
void func(P_long_retString callback){
  /* code */
}

long_retString func_callback(/* arguments list */){
  /* code */
}

/* inside a function */
func(func_callback);
```
