#include <stdarg.h>
#include "../include/tonight.h"
#include "../include/Tonight/writer.h"

static inline void write_text(pointer stream, string txt, string add){
    struct{
        string arg1;
        string arg2;
    }args = {
        txt, add
    };
    Stream.print(stream, "%s%s", &args);
}

static void Writer_text(string txt){
    pointer stream = $$(this $as Writer).stream;
    write_text(stream, txt, "");
}

static void Writer_textln(string txt){
    pointer stream = $$(this $as Writer).stream;
    write_text(stream, txt, "\n");
}

static void write_print(pointer stream, string txt, va_list list, string add){
    string current = txt;
    do{
        write_text(stream, current, add);
    }while((current = va_arg(list, string)));
}

static void Writer_print(string txt, va_list list){
    pointer stream = $$(this $as Writer).stream;
    write_print(stream, txt, list, "");
}

static void Writer_println(string txt, va_list list){
    pointer stream = $$(this $as Writer).stream;
    write_print(stream, txt, list, "");
    write_text(stream, "", "\n");
}

static void Writer_printargln(string txt, va_list list){
    pointer stream = $$(this $as Writer).stream;
    write_print(stream, txt, list, "\n");
}

static void Writer_newLine(void){
    pointer stream = $$(this $as Writer).stream;
    write_text(stream, "", "\n");
}

static void Writer_addLines(int qtd){
    pointer stream = $$(this $as Writer).stream;
    while(qtd--) write_text(stream, "", "\n");
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

static void IWriter_text(string txt){
    Method(Writer){
        getInterface(Writer).text(txt);
    }
}

static void IWriter_textln(string txt){
    Method(Writer){
        getInterface(Writer).textln(txt);
    }
}

static void IWriter_print(string txt, ...){
    va_list list;
    va_start(list, txt);
    Method(Writer){
        getInterface(Writer).print(txt, list);
    }
    va_end(list);
}

static void IWriter_println(string txt, ...){
    va_list list;
    va_start(list, txt);
    Method(Writer){
        getInterface(Writer).println(txt, list);
    }
    va_end(list);
}

static void IWriter_printargln(string txt, ...){
    va_list list;
    va_start(list, txt);
    Method(Writer){
        getInterface(Writer).printargln(txt, list);
    }
    va_end(list);
}

static void IWriter_newLine(void){
    Method(Writer){
        getInterface(Writer).newLine();
    }
}

static void IWriter_addLines(int qtd){
    Method(Writer){
        getInterface(Writer).addLines(qtd);
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
