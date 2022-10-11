#include <bits/stdc++.h>
#include "testlib.h"
int main(int argc, char *argv[])
{
	registerValidation(argc, argv);
	std::string s = inf.readLine("[a-z]{1, 100000}", "s");
	size_t n = s.size();
	for (size_t i = 0; i != n; ++i) {
		inf.readInt(1, 1e9);
		if (i == n - 1)
		{
			inf.readEoln();
		} else {
			inf.readSpace();
		}
	}
	inf.readEof();
}