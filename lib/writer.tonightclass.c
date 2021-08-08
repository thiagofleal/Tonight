#include <stdarg.h>
#include "../include/tonight.h"
#include "../include/Tonight/string.h"
#include "../include/Tonight/writer.h"

typedef struct{
    pointer first;
    pointer list;
}print_args;

static inline void write_text(pointer stream, ...){
    va_list list;
    va_start(list, stream);
    Stream.print(stream, "%s%s", list);
    va_end(list);
}

static void Writer_text(pointer txt){
    pointer stream = $$(this $as Writer).stream;
    write_text(stream, txt, "");
}

static void Writer_textln(pointer txt){
    pointer stream = $$(this $as Writer).stream;
    write_text(stream, txt, "\n");
}

static void write_print(pointer stream, pointer first, va_list list, string endline, string endcmd){
    fixString frmt = FixString.empty;
    va_list p;
    va_copy(p, list);
    while(va_arg(list, pointer)){
        frmt = FixString.append(frmt, "%s");
        frmt = FixString.append(frmt, endline);
    }
    frmt = FixString.append(frmt, endcmd);
    write_text(stream, first, endline);
    Stream.print(stream, (const string)getText(frmt), p);
    va_end(p);
}

static void Writer_print(pointer pArgs){
    print_args *args = pArgs;
    pointer stream = $$(this $as Writer).stream;
    write_print(stream, args->first, args->list, "", "");
}

static void Writer_println(pointer pArgs){
    print_args *args = pArgs;
    pointer stream = $$(this $as Writer).stream;
    write_print(stream, args->first, args->list, "", "\n");
}

static void Writer_printargln(pointer pArgs){
    print_args *args = pArgs;
    pointer stream = $$(this $as Writer).stream;
    write_print(stream, args->first, args->list, "\n", "");
}

static void Writer_newLine(void){
    pointer stream = $$(this $as Writer).stream;
    write_text(stream, "\n");
}

static void Writer_addLines(int qtd){
    pointer stream = $$(this $as Writer).stream;
    while(qtd--) write_text(stream, "\n");
}

static IWriter Writer_vtble = {
    .text = Writer_text,
    .textln = Writer_textln,
    .print = (pointer)Writer_print,
    .println = (pointer)Writer_println,
    .printargln = (pointer)Writer_printargln,
    .newLine = Writer_newLine,
    .addLines = Writer_addLines
};

static void Writer_constructor(va_list args){
    construct(superOf(Writer));
    $$(this $as Writer).stream = va_arg(args, pointer);
    setInterface(Writer, Writer_vtble);
}

static void Writer_destructor(void){
    destruct(superOf(Writer));
}

static void IWriter_text(pointer txt){
    Method(Writer){
        getInterface(Writer)->text(txt);
    }
}

static void IWriter_textln(pointer txt){
    Method(Writer){
        getInterface(Writer)->textln(txt);
    }
}

static void IWriter_print(pointer txt, ...){
    Method(Writer){
        va_list list;
        print_args args = {
            .first = txt,
            .list = list
        };
        va_start(list, txt);
        getInterface(Writer)->print(&args);
        va_end(list);
    }
}

static void IWriter_println(pointer txt, ...){
    Method(Writer){
        va_list list;
        print_args args = {
            .first = txt,
            .list = list
        };
        va_start(list, txt);
        getInterface(Writer)->println(&args);
        va_end(list);
    }
}

static void IWriter_printargln(pointer txt, ...){
    Method(Writer){
        va_list list;
        print_args args = {
            .first = txt,
            .list = list
        };
        va_start(list, txt);
        getInterface(Writer)->printargln(&args);
        va_end(list);
    }
}

static void IWriter_newLine(void){
    Method(Writer){
        getInterface(Writer)->newLine();
    }
}

static void IWriter_addLines(int qtd){
    Method(Writer){
        getInterface(Writer)->addLines(qtd);
    }
}

static IWriter iWriter = {
    .text = IWriter_text,
    .textln = IWriter_textln,
    .print = IWriter_print,
    .println = IWriter_println,
    .printargln = IWriter_printargln,
    .newLine = IWriter_newLine,
    .addLines = IWriter_addLines
};

Constructor(Writer, Writer_constructor);
Destructor(Writer, Writer_destructor);

Define_Class(Writer $extends Object $implements IWriter $as iWriter);
