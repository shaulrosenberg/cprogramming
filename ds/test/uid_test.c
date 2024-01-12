#include <stdio.h>

#include "uid.h"
#include "tests.h"

static void TestUid();

int main()
{
	TestUid();

	PASS;
	return 0;
}

static void TestUid()
{
	ilrd_uid_ty uid1;
	ilrd_uid_ty uid2;

	uid1 = UIDCreate();
	uid2 = UIDCreate();

	TEST("UIDIsSame", UIDIsSame(uid1, uid2), 0);
	TEST("UIDIsSame", UIDIsSame(uid1, uid1), 1);
	TEST("UIDIsSame", UIDIsSame(uid2, uid2), 1);
}