int n, A;
vector<int> ans, e[1001];
void dfs(int i) {
	while (!e[i].empty()) {
		int j = e[i].back();
		e[i].pop_back();
		dfs(j);
	}
	ans.push_back(i);
}
int main() {
	dfs(A);
	reverse(ans.begin(), ans.end());
}

