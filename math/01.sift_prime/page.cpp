vector<int> sift(int n) {
	vector<bool> visited(n + 1, false);
	vector<int> ret;
	for (int i = 2; i < n; ++i)
		visited[i] = false;
	for (int i = 2; i < n; ++i)
		if (!visited[i]) {
			ret.push_back(i);
			if (n / i < i)
				continue;
			for (int j = i * i; j < n; j += i)
				visited[j] = true;
		}
	return ret;
}

