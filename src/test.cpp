#include <iostream>
#include <array>

#include <gsl/span>

using namespace std;

int main(void)
{
	// https://bugs.llvm.org//show_bug.cgi?id=21629
	std::array<int, 10> ar = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	gsl::span<int> s{ar};

	cout << "Hello World" << endl;

	return(0);

}

