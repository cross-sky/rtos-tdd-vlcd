
#include <stdio.h>
#include <stdarg.h>
#include "CppUTest/TestHarness.h"

extern "C"
{
#include "atom.h"
#include "except.h"
}

Except_T expect;

TEST_GROUP(Atom)
{
void setup()
{

}

void teardown()
{

}
};

TEST(Atom, compareSrcAndDst)
{
	char *src = "hello world.";
	const char *dst;
	dst = Atom_string(src);
	STRCMP_EQUAL(dst, src);
}
