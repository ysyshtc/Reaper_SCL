inline bool turn_left(const line &l, const point &p) {
	return turn_left(l.s, l.t, p);
}

vector<line> half_plane_intersect(const vector<line> &h) {
	int fore = 0, rear = -1;
	vector<line> ret;
	for (int i = 0; i < (int)h.size(); ++i) {
		while (fore < rear && !turn_left(h[i], line_intersect(ret[rear - 1], ret[rear])))
			--rear;
		while (fore < rear && !turn_left(h[i], line_intersect(ret[fore], ret[fore + 1])))
			++fore;
		++rear;
		ret.push_back(h[i]);
	}
	while (rear - fore > 1 && !turn_left(ret[fore], line_intersect(ret[rear - 1], ret[rear])))
		--rear;
	while (rear - fore > 1 && !turn_left(ret[rear], line_intersect(ret[fore], ret[fore + 1])))
		++fore;
	if (rear - fore < 2)
		return vector<line>();
	return ret;
}

