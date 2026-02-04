#include <cstdint>
#include <string>

using namespace std;

struct Color {
	int r;
	int g;
	int b;

	Color();
	Color(int red, int green, int blue);

	string ToString() const;
};