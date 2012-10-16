#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

void get_inverse(int inv[], int mod) {
	inv[1] = 1;
	for (int i = 2; i < mod; ++i)
		inv[i] = (mod - mod / i * inv[mod % i] % mod) % mod;
}

const int MAXN = 111111;
int inv[MAXN];

int main() {
	get_inverse(inv, 100003);
	cout << (11 * inv[11]) % 100003 << endl;
}
