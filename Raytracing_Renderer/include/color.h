#include <cstdint>
#include <string>

using namespace std;

struct Color {
	uint8_t r;
	uint8_t g;
	uint8_t b;

	Color();
	Color(uint8_t red, uint8_t green, uint8_t blue);

	string ToString() const;
};