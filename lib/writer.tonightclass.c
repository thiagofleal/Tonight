#include <stdarg.h>
#include "../include/tonight.h"
#include "../include/Tonight/string.h"
#include "../include/Tonight/writer.h"

static inline void write_text(pointer stream, pointer txt){
    struct{
        string arg1;
    }args = {
        txt
    };
    Stream.print(stream, "%s", &args);
}

static inline void write_textln(pointer stream, pointer txt){
    struct{
        string arg1;
    }args = {
        txt
    };
    Stream.print(stream, "%s\n", &args);
}

static void Writer_text(pointer txt){
    pointer stream = $$(this $as Writer).stream;
    write_text(stream, txt);
}

static void Writer_textln(pointer txt){
    pointer stream = $$(this $as Writer).stream;
    write_textln(stream, txt);
}

extern int printf(const string, ...);

static void write_print(pointer stream, va_list list, string endline, string endcmd){
    register int count = 0;
    fixString frmt = FixString.empty;
    pointer p = list;
    while(va_arg(list, pointer)) ++count;
    while(count--){
        frmt = FixString.append(frmt, "%s");
        frmt = FixString.append(frmt, endline);
    }
    frmt = FixString.append(frmt, endcmd);
    Stream.print(stream, (const string)getText(frmt), p);
}

static void Writer_print(va_list list){
    pointer stream = $$(this $as Writer).stream;
    write_print(stream, list, "", "");
}

static void Writer_println(va_list list){
    pointer stream = $$(this $as Writer).stream;
    write_print(stream, list, "", "\n");
}

static void Writer_printargln(va_list list){
    pointer stream = $$(this $as Writer).stream;
    write_print(stream, list, "\n", "");
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

static void Writer_constructor(pointer args){
    $va_set(args, {
        pointer stream;
    });
    construct(superOf(Writer));
    $$(this $as Writer).stream = $va_get.stream;
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
        getInterface(Writer)->print(&txt);
    }
}

static void IWriter_println(pointer txt, ...){
    Method(Writer){
        getInterface(Writer)->println(&txt);
    }
}

static void IWriter_printargln(pointer txt, ...){
    Method(Writer){
        getInterface(Writer)->printargln(&txt);
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
