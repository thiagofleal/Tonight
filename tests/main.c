#include "../include/tonight.h"
#include "../include/Tonight/exceptions.h"
#include "../include/Tonight/collection.h"
#include "../include/Tonight/application.h"
#include "../include/Tonight/test.h"
#include "../include/Tonight/stream.h"
#include "../include/Tonight/writer.h"
#include "../include/Tonight/console.h"
#include "../include/Tonight/string.h"

extern void testMemory(void);

int Main(string ARRAY args) {
    object writer;
    int ret;

    using (writer $as new(Writer, Console.getStream()) $with delete) {
        TestResult result;
        TestResultItem item;

        Test.start();

        testMemory();

        result = Test.finalize();
        ret = result.count.failed || result.count.except ? ExitValue.Failure : ExitValue.Success;

        $(writer $as Writer)->println($i(result.count.tests), " tests:", $end);
        $(writer $as Writer)->println($i(result.count.success), " tests success (", $d(result.statistic.success * 100.0), "%)", $end);
        $(writer $as Writer)->println($i(result.count.failed), " tests failed (", $d(result.statistic.failed * 100.0), "%)", $end);
        $(writer $as Writer)->println($i(result.count.except), " exceptions (", $d(result.statistic.except * 100.0), "%)", $end);

        foreach (item $in result.results) {
            if (!item.success) {
                $(writer $as Writer)->newLine();
                $(writer $as Writer)->println(" -> ", ExceptionManager.message(item.except), $end);
            }
        }
    }
    return ret;
}
