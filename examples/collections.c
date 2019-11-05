#include <tonight.h>
#include <Tonight/application.h>
#include <Tonight/exceptions.h>
#include <Tonight/console.h>
#include <Tonight/string.h>
#include <Tonight/memory.h>
#include <Tonight/writer.h>
#include <Tonight/array.h>
#include <Tonight/list.h>
#include <Tonight/map.h>

int Main(string ARRAY args)
{
    object w = $Empty(object);

    using(w $as new(Writer, Console.getStream()) $with delete)
    {
        string s = String.empty;
        int ARRAY intArr = $Empty(int ARRAY);
        object intList = $Empty(object);
        object map = $Empty(object);

        /* Get the application arguments */
        foreach(s $in args)
        {
            $(w $as Writer).println("Argument: ", s, $end);
        }

        /* Array */
        using(intArr $as Array.Int(10) $with Array.free)
        {
            int i = $Empty(int);

            foreachkey(i $in intArr)
            {
                intArr[i] = i;
            }

            /* Get string from array */
            using(s $as Array.toString(intArr, ", ", ips) $with String.free)
            {
                $(w $as Writer).println("Array: [", s, "]", $end);
            }
        }

        /* List */
        using(intList $as new(List) $with delete)
        {
            int i;

            for(i = 0; i < 10; i++)
            {
                $(intList $as List).add(InstanceOf.Int(i));
            }

            $(intList $as List).setFreeCallBack(Memory.free);
            $(intList $as List).setStringMethod(ips);

            /* Get string from list */
            using(s $as $(intList $as List).toString(", ") $with String.free)
            {
                $(w $as Writer).println("List: [", s, "]", $end);
            }
        }

        /* Map */
        using(map $as new(Map) $with delete)
        {
            $(map $as Map).setFreeCallBack(Memory.free);

            $(map $as Map).set("first", InstanceOf.Double(1.2));
            $(map $as Map).set("second", InstanceOf.Double(3.4));
            $(map $as Map).set("third", InstanceOf.Double(5.6));
            $(map $as Map).set("fourth", InstanceOf.Double(7.89));

            foreachkey(s $in map)
            {
                $(w $as Writer).println("key: ", s, " => value: ", $dp($(map $as Map).get(s)), $end);
            }
        }
    }

    Console.getKey();
    return ExitValue.Success;
}
