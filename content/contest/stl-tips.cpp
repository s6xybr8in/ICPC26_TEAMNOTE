/**
 * Author: Green Siro
 * Description: Integer hashing and floating-point output.
 */

// Requires data-structures/CustomHash.h.
void hashExample(int expected_size) {
	unordered_set<ll, CustomHash> s;
	s.max_load_factor(0.7f);
	s.reserve(expected_size);
	s.insert(42);
	bool found = s.count(42) != 0; // C++17
	(void)found;
	unordered_map<ll, int, CustomHash> freq;
	freq.max_load_factor(0.7f);
	freq.reserve(expected_size);
	++freq[42];
}

void precisionExample() {
	// << fixed << setprecision(n): n digits after decimal.
	cout << fixed << setprecision(3) << 1.2 << '\n';
	// Output: 1.200 (rounded, not truncated).
	// Formatting persists for subsequent output.
	cout << defaultfloat << setprecision(6);
	// Without fixed, precision counts significant digits.
	// Formatting does not improve calculation accuracy.
}
