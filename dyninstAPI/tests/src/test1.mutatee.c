
/* Test application (Mutatee) */

#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#if defined(sparc_sun_sunos4_1_3) || defined(sparc_sun_solaris2_4)
#include <unistd.h>
#endif

/* XXX Currently, there's a bug in the library that prevents a subroutine call
 * instrumentation point from being recognized if it is the first instruction
 * in a function.  The following variable is used in this program in a number
 * of kludges to get around this.
 */
int kludge;

// control debug printf statements
#define dprintf	if (debugPrint) printf
int debugPrint = 0;

#define TRUE	1
#define FALSE	0

int globalVariable1_1 = 0;
int globalVariable3_1 = 31;
int globalVariable4_1 = 41;
int globalVariable5_1 = 51;
int globalVariable5_2 = 51;

int globalVariable6_1 = 0xdeadbeef;
int globalVariable6_2 = 0xdeadbeef;
int globalVariable6_3 = 0xdeadbeef;
int globalVariable6_4 = 0xdeadbeef;
int globalVariable6_5 = 0xdeadbeef;
int globalVariable6_6 = 0xdeadbeef;

int globalVariable7_1 = 71, globalVariable7_2 = 71,
    globalVariable7_3 = 71, globalVariable7_4 = 71,
    globalVariable7_5 = 71, globalVariable7_6 = 71,
    globalVariable7_7 = 71, globalVariable7_8 = 71,
    globalVariable7_9 = 71, globalVariable7_10 = 71,
    globalVariable7_11 = 71, globalVariable7_12 = 71,
    globalVariable7_13 = 71, globalVariable7_14 = 71,
    globalVariable7_15 = 71, globalVariable7_16 = 71;


int globalVariable8_1 = 1;

int globalVariable10_1 = 0, globalVariable10_2 = 0, 
    globalVariable10_3 = 0, globalVariable10_4 = 0;

int globalVariable11_1 = 0, globalVariable11_2 = 0, 
    globalVariable11_3 = 0, globalVariable11_4 = 0, globalVariable11_5 = 0;

int globalVariable12_1 = 0;

int globalVariable13_1 = 0;

int globalVariable14_1 = 0;
int globalVariable14_2 = 0;

int globalVariable15_1 = 0;
int globalVariable15_2 = 0;
int globalVariable15_3 = 0;

int globalVariable16_1 = 0;
int globalVariable16_2 = 0;
int globalVariable16_3 = 0;
int globalVariable16_4 = 0;


void call1_1()
{
    dprintf("call1() called - setting globalVariable1_1 = 11\n");
    globalVariable1_1 = 11;
}

void call2_1(int arg1, int arg2, char *arg3)
{
    if ((arg1 == 1) && (arg2 == 2) && (!strcmp(arg3, "testString2_1"))) {
	printf("Passed test #2 (three parameter function)\n");
    } else {
	printf("**Failed** test #2 (three parameter function)\n");
	if (arg1 != 1) 
	    printf("    arg1 = %d, should be 1\n", arg1);
	if (arg1 != 2) 
	    printf("    arg2 = %d, should be 2\n", arg2);
	if (strcmp(arg3, "testString2_1")) 
	    printf("    arg3 = %s, should be \"testString2_1\"\n", arg3);
    }
}

void call3_1(int arg1, int arg2)
{
    if ((arg1 == 31) && (arg2 == 32))  {
	printf("Passed test #3 (passing variables to functions)\n");
    } else {
	printf("**Failed** test #3 (passing variables to functions)\n");
	printf("    arg1 = %d, should be 31\n", arg1);
	printf("    arg2 = %d, should be 32\n", arg2);
    }
}

int call9_1(int p1, int p2, int p3, int p4, int p5)
{
    int x; 
    x = (((p1 + p2) + (p3 + p4) + (p5)));
    if (x != (91 + 92 + 93 + 94 + 95 )) {
      printf("**Failed** test case #9 (preserve registers - funcCall)\n");
      if (p1 != 91) printf("    call9_1 parameter 1 is %d not 91\n", p1);
      if (p2 != 92) printf("    call9_1 parameter 2 is %d not 92\n", p2);
      if (p3 != 93) printf("    call9_1 parameter 2 is %d not 93\n", p3);
      if (p4 != 94) printf("    call9_1 parameter 4 is %d not 94\n", p4);
      if (p5 != 95) printf("    call9_1 parameter 5 is %d not 95\n", p5);
      exit(-1);
    }
    dprintf("inside call9_1\n");
    return x;
}

void call10_1()
{
    if (globalVariable10_4 == 0) {
	globalVariable10_4 = 1;	// update marker of call order
	globalVariable10_1 = 1;	// flag that this was called first
    }
}


void call10_2()
{
    if (globalVariable10_4 == 1) {
	globalVariable10_4 = 2;	// update marker of call order
	globalVariable10_2 = 1;	// flag that this was called first
    }
}

void call10_3()
{
    if (globalVariable10_4 == 2) {
	globalVariable10_4 = 3;	// update marker of call order
	globalVariable10_3 = 1;	// flag that this was called first
    }
}

void call11_1()
{ 
    if (globalVariable11_1 == 0) globalVariable11_2 = 1;
}

void call11_2()
{ 
    if (globalVariable11_1 == 1) globalVariable11_3 = 1;
}

void call11_3()
{ 
    if (globalVariable11_1 == 2) globalVariable11_4 = 1;
}

void call11_4()
{ 
    if (globalVariable11_1 == 3) globalVariable11_5 = 1;

    if (globalVariable11_2 && globalVariable11_3 && 
	globalVariable11_4 && globalVariable11_5) {
        printf("Passed test #11 (snippets at entry,exit,call)\n");
    } else {
        printf("**Failed test #11 (snippets at entry,exit,call)\n");
	if (!globalVariable11_2) 
	    printf("    entry snippet not called at the correct time\n");
	if (!globalVariable11_3) 
	    printf("    pre call snippet not called at the correct time\n");
	if (!globalVariable11_4) 
	    printf("    post call snippet not called at the correct time\n");
	if (!globalVariable11_5) 
	    printf("    exit snippet not called at the correct time\n");
    }
}

void call12_1()
{
    globalVariable12_1++;
}

void call13_1(int a1, int a2, int a3, int a4, int a5)
{
    if (a1 == 131) globalVariable13_1 |= 1;
    if (a2 == 132) globalVariable13_1 |= 2;
    if (a3 == 133) globalVariable13_1 |= 4;
    if (a4 == 134) globalVariable13_1 |= 8;
    if (a5 == 135) globalVariable13_1 |= 16;
    dprintf("a1 = %d\n", a1);
    dprintf("a2 = %d\n", a2);
    dprintf("a3 = %d\n", a3);
    dprintf("a4 = %d\n", a4);
    dprintf("a5 = %d\n", a5);
}

void call14_1()
{
    globalVariable14_1 = 1;
}

void call15_1()
{
    globalVariable15_1++;
}

void call15_2()
{
    globalVariable15_2++;
}

void call15_3()
{
    globalVariable15_3++;
}

//
// This is a series of nearly empty functions to attach code to 
//
void func1_1() { dprintf("func1_1 () called\n"); }
void func2_1() { dprintf("func2_1 () called\n"); }
void func3_1() { dprintf("func3_1 () called\n"); }
void func4_1() { dprintf("func4_1 () called\n"); }
void func5_1() { dprintf("func5_1 () called\n"); }
void func6_1() { dprintf("func7_1 () called\n"); }
void func7_1() { dprintf("func7_1 () called\n"); }

void func8_1(int p1, int p2, int p3, int p4, int p5, int p6, int p7,
	     int p8, int p9, int p10)
{
    dprintf("func8_1 (...) called\n");
    if ((p1 == 1) && (p2 == 2) && (p3 == 3) && (p4 == 4) && (p5 == 5) && 
	(p6 == 6) && (p7 == 7) && (p8 == 8) && (p9 == 9) && (p10 == 10))  {
        printf("Passed test #8 (preserve registers - expr)\n");
    } else {
	printf("**Failed** test #8 (preserve registers - expr )\n");
	if (p1 != 1)  printf("    parameter #1 is %d not 1\n", p1);
	if (p2 != 2)  printf("    parameter #2 is %d not 2\n", p2);
	if (p3 != 3)  printf("    parameter #3 is %d not 3\n", p3);
	if (p4 != 4)  printf("    parameter #4 is %d not 4\n", p4);
	if (p5 != 5)  printf("    parameter #5 is %d not 5\n", p5);
	if (p6 != 6)  printf("    parameter #6 is %d not 6\n", p6);
	if (p7 != 7)  printf("    parameter #7 is %d not 7\n", p7);
	if (p8 != 8)  printf("    parameter #8 is %d not 8\n", p8);
	if (p9 != 9)  printf("    parameter #9 is %d not 9\n", p9);
	if (p10 != 10)  printf("    parameter #10 is %d not 10\n", p10);
    }
}

void func9_1(int p1, int p2, int p3, int p4, int p5, int p6, int p7,
	     int p8, int p9, int p10)
{
    dprintf("func9_1 (...) called\n");
    if ((p1 == 1) && (p2 == 2) && (p3 == 3) && (p4 == 4) && (p5 == 5) && 
	(p6 == 6) && (p7 == 7) && (p8 == 8) && (p9 == 9) && (p10 == 10))  {
        printf("Passed test #9 (preserve registers - funcCall)\n");
    } else {
	printf("**Failed** test #9 (preserve registers - funcCall )\n");
	if (p1 != 1)  printf("    parameter #1 is %d not 1\n", p1);
	if (p2 != 2)  printf("    parameter #2 is %d not 2\n", p2);
	if (p3 != 3)  printf("    parameter #3 is %d not 3\n", p3);
	if (p4 != 4)  printf("    parameter #4 is %d not 4\n", p4);
	if (p5 != 5)  printf("    parameter #5 is %d not 5\n", p5);
	if (p6 != 6)  printf("    parameter #6 is %d not 6\n", p6);
	if (p7 != 7)  printf("    parameter #7 is %d not 7\n", p7);
	if (p8 != 8)  printf("    parameter #8 is %d not 8\n", p8);
	if (p9 != 9)  printf("    parameter #9 is %d not 9\n", p9);
	if (p10 != 10)  printf("    parameter #10 is %d not 10\n", p10);
    }
}

void func10_1()
{
    if ((globalVariable10_1 == 1) && (globalVariable10_2 == 1) && 
	(globalVariable10_3 == 1) && (globalVariable10_4 == 3)) {
	printf("Passed test #10 (insert snippet order)\n");
    } else {
	printf("** Failed test #10 (insert snippet order)\n");
	if (!globalVariable10_1) 
	    printf("    call10_1 was not called first\n");
	if (!globalVariable10_2) 
	    printf("    call10_2 was not called second\n");
	if (!globalVariable10_3) 
	    printf("    call10_3 was not called third\n");
    }
}

void func11_2() {
    globalVariable11_1 = 2;
}

void func11_1()
{
    globalVariable11_1 = 1;
    func11_2();
    globalVariable11_1 = 3;
}

void func12_2()
{
}

void func12_1()
{
    func12_2();
    kill(getpid(), SIGSTOP);
    func12_2();
    if (globalVariable12_1 == 1) {
        printf("Passed test #12 (insert/remove and malloc/free)\n");
    } else {
        printf("**Failed test #12 (insert/remove and malloc/free)\n");
    }
}

void func13_1(int p1, int p2, int p3, int p4, int p5)
{
    if ((p1 == 131) && (p2 == 132) && (p3 == 133) && 
	(p4 == 134) && (p5 == 135) && (globalVariable13_1 == 31)) {
	printf("Passed test #13 (paramExpr,nullExpr)\n");
    } else {
	printf("**Failed test #13 (paramExpr,nullExpr)\n");
	if (p1 != 131) printf("  parameter 1 is %d, not 131\n", p1);
	if (p2 != 132) printf("  parameter 2 is %d, not 132\n", p2);
	if (p3 != 133) printf("  parameter 3 is %d, not 133\n", p3);
	if (p4 != 134) printf("  parameter 4 is %d, not 134\n", p4);
	if (p5 != 135) printf("  parameter 5 is %d, not 135\n", p5);
	if (!(globalVariable13_1 & 1)) printf("    passed param a1 wrong\n");
	if (!(globalVariable13_1 & 2)) printf("    passed param a2 wrong\n");
	if (!(globalVariable13_1 & 4)) printf("    passed param a3 wrong\n");
	if (!(globalVariable13_1 & 8)) printf("    passed param a4 wrong\n");
	if (!(globalVariable13_1 & 16)) printf("    passed param a5 wrong\n");
    }
}


void func14_2()
{
    globalVariable14_1 = 2;
}

void func14_3()
{
    globalVariable14_2 = 1;
}

void func14_1()
{
    kludge = 1;	// Here so that the following function call isn't the first
		// instruction

    func14_2();
    func14_3();

    if (globalVariable14_1 == 1 && globalVariable14_2 == 0) {
        printf("Passed test #14 (replace/remove function call)\n");
    } else {
        printf("**Failed test #14 (replace/remove function call)\n");
	if (globalVariable14_1 != 1)
    	    printf("    call to func14_2() was not replaced\n");
	if (globalVariable14_2 != 0)
	    printf("    call to func14_3() was not removed\n");
    }
}


void check15result(char *varname, int value, int expected,
		   char *errstr, int *failed)
{
    if (value != expected) {
	if (!*failed)
	    printf("**failed test #15 (setMutationsActive)\n");
	*failed = TRUE;

	printf("    %s = %d %s\n", varname, value, errstr);
    }		
}


void func15_2()
{
}

void func15_3()
{
    globalVariable15_3 = 100;
}

void func15_4()
{
    kludge = 1;	// Here so that the following function call isn't the first
		// instruction

    func15_3();
}


void func15_1()
{
    int failed = FALSE;

    func15_2();
    check15result("globalVariable15_1", globalVariable15_1, 1,
		  "after first call to instrumented function", &failed);

#if defined(sparc_sun_sunos4_1_3) || defined(sparc_sun_solaris2_4)
    // Test a function that makes a system call (is a special case on Sparc)
    access(".", R_OK);
    check15result("globalVariable15_2", globalVariable15_2, 2,
		  "after first call to instrumented function", &failed);
#endif

    func15_4();
    check15result("globalVariable15_3", globalVariable15_3, 1,
		  "after first call to instrumented function", &failed);

    /***********************************************************/

    kill(getpid(), SIGSTOP);

    func15_2();
    check15result("globalVariable15_1", globalVariable15_1, 1,
		  "after second call to instrumented function", &failed);

#if defined(sparc_sun_sunos4_1_3) || defined(sparc_sun_solaris2_4)
    access(".", R_OK);
    check15result("globalVariable15_2", globalVariable15_2, 2,
		  "after second call to instrumented function", &failed);
#endif

    func15_4();
    check15result("globalVariable15_3", globalVariable15_3, 100,
		  "after second call to instrumented function", &failed);

    /***********************************************************/

    kill(getpid(), SIGSTOP);

    func15_2();
    check15result("globalVariable15_1", globalVariable15_1, 2,
		  "after third call to instrumented function", &failed);

#if defined(sparc_sun_sunos4_1_3) || defined(sparc_sun_solaris2_4)
    access(".", R_OK);
    check15result("globalVariable15_2", globalVariable15_2, 4,
		  "after third call to instrumented function", &failed);
#endif

    func15_4();
    check15result("globalVariable15_3", globalVariable15_3, 101,
		  "after third call to instrumented function", &failed);

    if (!failed) {
        printf("Passed test #15 (setMutationsActive)\n");
    }
}


void func16_2() { dprintf("func16_2 () called\n"); }
void func16_3() { dprintf("func16_3 () called\n"); }

void func16_1()
{
    int failed = 0;

    func16_2();
    if (globalVariable16_1 != 1 || globalVariable16_2 != 0) {
        printf("**Failed test #16 (if-else)\n");
	if (globalVariable16_1 != 1)
	    printf("    True clause of first if should have been executed but was not.\n");
	if (globalVariable16_2 != 0)
	    printf("    False clause of first if should not have been executed but was.\n");
	failed = 1;
    }

    func16_3();
    if (globalVariable16_3 != 0 || globalVariable16_4 != 1) {
        printf("**Failed test #16 (if-else)\n");
	if (globalVariable16_3 != 1)
	    printf("    True clause of second if should not have been executed but was.\n");
	if (globalVariable16_4 != 0)
	    printf("    False clause of second if should have been executed but was not.\n");
	failed = 1;
    }

    if (!failed)
    	printf("Passed test #16 (if-else)\n");
}


void fail7Print(int tCase, int fCase, char *op)
{
    if (tCase != 72) 
	printf(" operator %s was not true when it should be\n", op); 
    if (fCase != 71) 
	printf(" operator %s was not false when it should be\n", op); 
}

void main(int argc, char *argv[])
{
    if (argc == 2 && !strcmp(argv[1], "-verbose")) {
	debugPrint = 1;
    }

    // Test #1
    dprintf("Value of globalVariable1_1 is %d.\n", globalVariable1_1);
    func1_1();
    dprintf("Value of globalVariable1_1 is now %d.\n", globalVariable1_1);

    if (globalVariable1_1 == 11)
        printf("\nPassed test #1 (zero arg function call)\n");
    else
        printf("\n**Failed** test #1 (zero arg function call)\n");

    // Test #2
    func2_1();

    // Test #3 
    func3_1();

    // Test #4
    func4_1();
    if (globalVariable4_1 == 41) {
	printf("**Failed** test #4 (sequence)\n");
	printf("    none of the items were executed\n");
    } else if (globalVariable4_1 == 42) {
	printf("**Failed** test #4 (sequence)\n");
	printf("    first item was the last (or only) one to execute\n");
    } else if (globalVariable4_1 == 43) {
        printf("Passed test #4 (sequence)\n");
    }

    // test #5
    func5_1();
    if ((globalVariable5_1 == 51) && (globalVariable5_2 == 53)) {
        printf("Passed test #5 (if w.o. else)\n");
    } else {
	printf("**Failed** test #5 (if w.o. else)\n");
	if (globalVariable5_1 != 51) {
	    printf("    condition executed for false\n");
	}
	if (globalVariable5_2 != 53) {
	    printf("    condition not executed for true\n");
	}
    }

    func6_1();
    if ((globalVariable6_1 == 60+2) && (globalVariable6_2 == 64-1) &&
	(globalVariable6_3 == 66/3) && (globalVariable6_4 == 67/3) &&
	(globalVariable6_5 == 6 * 5) && (globalVariable6_6 == 3)) {
	printf("Passed test #6 (arithmetic operators)\n");
    } else {
	printf("**Failed** test #6 (arithmetic operators)\n");
	if (globalVariable6_1 != 60+2) 
	    printf("    addition error 60+2 got %d\n", globalVariable6_1);
	if (globalVariable6_2 != 64-1) 
	    printf("    subtraction error 64-1 got %d\n", globalVariable6_2);
	if (globalVariable6_3 != 66/3)
	    printf("    division error 66/3 got %d\n", globalVariable6_3);
	if (globalVariable6_4 != 67/3)
	    printf("    division error 67/3 got %d\n", globalVariable6_4);
	if (globalVariable6_5 != 6 * 5)
	    printf("    mult error 6*5 got %d\n", globalVariable6_5);
	if (globalVariable6_6 != 3)
	    printf("    mod error 10,3 got %d\n", globalVariable6_6);
    }

    func7_1();
    if ((globalVariable7_1 == 72) && (globalVariable7_2 == 71) &&
	(globalVariable7_3 == 72) && (globalVariable7_4 == 71) &&
	(globalVariable7_5 == 72) && (globalVariable7_6 == 71) &&
	(globalVariable7_7 == 72) && (globalVariable7_8 == 71) &&
	(globalVariable7_9 == 72) && (globalVariable7_10 == 71) &&
	(globalVariable7_11 == 72) && (globalVariable7_12 == 71) &&
	(globalVariable7_13 == 72) && (globalVariable7_14 == 71) &&
	(globalVariable7_15 == 72) && (globalVariable7_16 == 71)) { 
	printf("Passed test #7 (relational operators)\n");
    } else {
	printf("**Failed** test #7 (relational operators)\n");
	fail7Print(globalVariable7_1, globalVariable7_2, "BPatch_lt");
	fail7Print(globalVariable7_3, globalVariable7_4, "BPatch_eq");
	fail7Print(globalVariable7_5, globalVariable7_6, "BPatch_gt");
	fail7Print(globalVariable7_7, globalVariable7_8, "BPatch_le");
	fail7Print(globalVariable7_9, globalVariable7_10, "BPatch_ne");
	fail7Print(globalVariable7_11, globalVariable7_12, "BPatch_ge");
	fail7Print(globalVariable7_13, globalVariable7_14, "BPatch_and");
	fail7Print(globalVariable7_15, globalVariable7_16, "BPatch_or");
    }

    func8_1(1,2,3,4,5,6,7,8,9,10);

    func9_1(1,2,3,4,5,6,7,8,9,10);

    func10_1();

    func11_1();

    func12_1();

    func13_1(131,132,133,134,135);

    func14_1();

    func15_1();

    func16_1();

    exit(0);
}
