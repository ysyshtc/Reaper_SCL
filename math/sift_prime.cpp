#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

const int MAXN = 111111;
bool visited[MAXN];

vector<int> sift(int n) {
	vector<int> ret;
	for (int i = 2; i < n; ++i)
		visited[i] = false;
	for (int i = 2; i < n; ++i)
		if (!visited[i]) {
			ret.push_back(i);
			for (int j = i + i; j < n; j += i)
				visited[j] = true;
		}
	return ret;
}

int main() {
	vector<int> prim = sift(100);
	for (int i = 0; i < (int)prim.size(); ++i)
		cout << prim[i] << endl;
}
