#include <tonight.h>
#include <Tonight/exceptions.h>
#include <Tonight/string.h>
#include <Tonight/application.h>
#include <Tonight/console.h>
#include <Tonight/writer.h>
#include <Tonight/reader.h>

int Main(string ARRAY args)
{
    object w = NULL;
    object r = NULL;

    using(w $as new(Writer, Console.getStream()) $with delete)
    {
        using(r $as new(Reader, Console.getStream()) $with delete)
        {
            try
            {
                double n1, n2, average;

                $(w $as Writer)->text("Input the first value: ");
                n1 = $(r $as Reader)->nextDouble();
                $(w $as Writer)->text("Input the second value: ");
                n2 = $(r $as Reader)->nextDouble();

                average = (n1 + n2) / 2.0;

                $(w $as Writer)->println("The average between ", $d(n1), " and ", $d(n2), " is ", $d(average), $end);
                Console.getKey();
            }
            catch(InputException)
            {
                string s = $(r $as Reader)->nextLine();
                $(w $as Writer)->println("Impossible to read a double from \"", s, "\"", $end);
                String.free(s);
                return Main(args);
            }
            catch(GenericException)
            {
                $(w $as Writer)->printargln(CurrentException.error(), CurrentException.message(), $end);
                Console.getKey();
            }
        }
    }

    return ExitValue.Success;
}
