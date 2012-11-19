struct State {
	static State *memory;
	State *go[MAXC], *link;
	int len;
	void init(int init_len = 0) {
		len = init_len; link = NULL;
		memset(go, NULL, sizeof go);
	}
	State* next_state(State* start, int token) {
		State *it = this, *next = memory++;
		next->init(it->len + 1);
		while (it != NULL && it->go[token] == NULL) {
			it->go[token] = next;
			it = it->link;
		}
		if (it == NULL) {
			next->link = start;
			return next;
		}
		State *old = it->go[token];
		if (old->len == it->len + 1)
			next->link = old;
		else {
			State *split = memory++;
			memcpy(split, old, sizeof(State));
			split->len = it->len + 1;
			old->link = next->link = split;
			while (it != NULL && it->go[token] == old) {
				it->go[token] = split;
				it = it->link;
			}
		}
		return next;
	}
};
void* pool = malloc(MAX_MEM * sizeof(State));// free(pool);
State* State::memory = (State*)pool;

pair<State*, State*> make_automaton(char* const s) {
	State *start = State::memory;
	State *last = State::memory++;
	start->init(0);
	int length = strlen(s);
	for (int i = 0; i < length; ++i)
		last = last->next_state(start, s[i] - 'a');
	return make_pair(start, last);
}

