#include <stdlib.h>

#include "../include/Tonight/tonight.h"

typedef struct __struct_exception{
	EXCEPTION exception;
	string message;
}_Exception, *Exception;

/* Exceptions */
static EXCEPTION_DEFINE ___GenericException = {"Generic exception throwed", NULL};
EXCEPTION TONIGHT GenericException = &___GenericException;

Define_Exception(AssertException $as "Assert fail" $extends GenericException);
Define_Exception(ErrnoException $as "Errno error" $extends GenericException);
Define_Exception(MemoryAllocException $as "Memory allocate error" $extends GenericException);
Define_Exception(ArrayIndexBoundException $as "Invalid array index" $extends GenericException);
Define_Exception(FileOpenException $as "File open error" $extends GenericException);
Define_Exception(InputException $as "Input error" $extends GenericException);
Define_Exception(ConvertException $as "Convert error" $extends GenericException);
Define_Exception(NotImplementException $as "Not implemented method error" $extends GenericException);
Define_Exception(ArgumentException $as "Argument error" $extends GenericException);
Define_Exception(IllegalAccessException $as "Null argument error" $extends GenericException);
Define_Exception(NullArgumentException $as "Null argument error" $extends ArgumentException);
Define_Exception(ApplicationException $as "Application error" $extends ArgumentException);

/* try - catch - throw */

enum ctrl{
	CTRL_CONTINUE,
	CTRL_FINALLY,
	CTRL_CATCH,
	CTRL_BREAK,
	CTRL_TRY
};

typedef struct{
	pointer jump;
	int ctrl;
	bool inside_try;
	bool exec_try;
	bool thrown;
	bool final;
}strContext, *Context;

typedef struct{
	Context context;
	pointer next;
}Stack_node, *Stack;

static strContext begin = {
	NULL, CTRL_CONTINUE, false, false, false, false
};

static struct{
	Stack stack;
	Context current;
	Exception value;
}except = {NULL, &begin, NULL};

static Context createContext(void){
	Context ctxt = calloc(1, sizeof(strContext));
	if(!ctxt) exit(EXIT_FAILURE);
	ctxt->jump = malloc(sizeof(jmp_buf));
	if(!ctxt->jump) exit(EXIT_FAILURE);
	return ctxt;
}

static void deleteContext(Context ctxt){
	if(ctxt){
		if(ctxt->jump) free(ctxt->jump);
		free(ctxt);
	}
}

static void push_context(Context value){
	Stack node = malloc(sizeof(Stack_node));
	if(!node) exit(EXIT_FAILURE);
	node->context = value;
	node->next = except.stack;
	except.stack = node;
}

static Context pop_context(void){
	Stack node = except.stack;
	if(node){
		Context ctx = node->context;
		except.stack = node->next;
		free(node);
		return ctx;
	}
	return NULL;
}

Exception TONIGHT getException(void){
	return except.value;
}

pointer TONIGHT __create_try_context(void){
	Context ctxTry = createContext();
	ctxTry->inside_try = true;
	ctxTry->ctrl = CTRL_TRY;
	ctxTry->exec_try = false;
	ctxTry->final = false;
	push_context(except.current);
	except.current = ctxTry;
	return ctxTry->jump;
}

INLINE void TONIGHT __restaure_try_context(void){
	deleteContext(except.current);
	except.current = pop_context();
}

bool TONIGHT __try_context(void){
	switch(except.current->ctrl){
		case CTRL_TRY:
			except.current->ctrl = CTRL_BREAK;
			except.current->exec_try = true;
			return true;
		case CTRL_BREAK:
			__restaure_try_context();
		case CTRL_CONTINUE:
			return false;
		case CTRL_CATCH:
			except.current->ctrl = CTRL_BREAK;
			return true;
		case CTRL_FINALLY:
			except.current->ctrl = CTRL_CONTINUE;
			except.current->final = true;
			return true;
	}
	return false;
}

bool TONIGHT __function_try(void){
	if(except.current->exec_try){
		except.current->exec_try = false;
		return true;
	}
	return false;
}

bool TONIGHT __function_catch(EXCEPTION _exception){
	if(except.current->thrown){
		EXCEPTION *_e = &except.value->exception;
		while(_e){
			if(*_e == _exception){
				__restaure_try_context();
				except.current->ctrl = CTRL_FINALLY;
				except.current->thrown = false;
				return true;
			}
			_e = (*_e)->_super;
		}
	}
	return false;
}

bool TONIGHT __function_finally(void){
	if(except.current->final){
		except.current->final = false;
		return true;
	}
	return false;
}

void TONIGHT Throw(EXCEPTION __exc, string message){
	if(except.current->inside_try){
		static _Exception exc;
		exc.exception = __exc;
		exc.message = message;
		except.current->thrown = true;
		except.value = &exc;
		except.current->ctrl = CTRL_CATCH;
		longjmp(except.current->jump, 1);
	}
}

INLINE string TONIGHT Error(Exception exc){
	return exc->exception->error_name;
}

INLINE string TONIGHT Message(Exception exc){
	return exc->message;
}

INLINE EXCEPTION TONIGHT ExceptionType(Exception exc){
	return exc->exception;
}
