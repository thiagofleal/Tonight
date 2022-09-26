#include "../include/tonight.h"
#include "../include/Tonight/exceptions.h"
#include "../include/Tonight/test.h"
#include "../include/Tonight/writer.h"
#include "../include/Tonight/console.h"
#include "../include/Tonight/string.h"

extern void testMemory(void);

void Main(string ARRAY args) {
    object writer;

    using (writer $as new(Writer, Console.getStream()) $with delete) {
        TestResult result;
        TestResultItem item;

        Test.start(TestEcho.DEBUG);

        testMemory();

        result = Test.finalize();

        $(writer $as Writer)->println($i(result.count.tests), " tests realized:", $end);
        $(writer $as Writer)->println("- ", $i(result.count.success), " tests success (", $d(result.statistic.success * 100.0), "%)", $end);
        $(writer $as Writer)->println("- ", $i(result.count.failed), " tests failed (", $d(result.statistic.failed * 100.0), "%)", $end);
        $(writer $as Writer)->println("- ", $i(result.count.except), " exceptions (", $d(result.statistic.except * 100.0), "%)", $end);
    }
}
