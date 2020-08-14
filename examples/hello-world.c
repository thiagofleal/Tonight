#include <tonight.h>
#include <Tonight/application.h>
#include <Tonight/console.h>
#include <Tonight/writer.h>

int Main(string ARRAY args)
{
    object w = $Empty(object);

    using(w $as new(Writer, Console.getStream()) $with delete)
    {
        $(w $as Writer)->textln("Hello World!");
    }

    Console.getKey();
    return ExitValue.Success;
}
