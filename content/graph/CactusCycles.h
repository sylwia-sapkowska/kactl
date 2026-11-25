/**
 * Author: Wzięte z tonowak
 * Description: Wyznaczanie cykli w grafie. Zakłada, że jest nieskierowany graf bez pętelek i multikrawędzi,
 *  każda krawędź leży na co najwyżej jednym cyklu prostym (silniejsze założenie, niż o wierzchołkach).
 *  \texttt{cactus\_cycles(graph)} zwraca taką listę cykli, że istnieje krawędź między $i$-tym,
 *  a $(i+1) \bmod \texttt{sz(cycle)}$-tym wierzchołkiem.
 * Time: O(n + m)
 */
#pragma once

vector<vi> cactus_cycles(const vector<vi>& graph) {
	vi state(sz(graph), 0), stack;
	vector<vi> ret;
	function<void (int, int)> dfs = [&](int v, int p) {
		if(state[v] == 2) {
			ret.emplace_back(stack.rbegin(), find(stack.rbegin(), stack.rend(), v) + 1);
			return;
		}
		stack.emplace_back(v);
		state[v] = 2;
		for(int u : graph[v])
			if(u != p and state[u] != 1)
				dfs(u, v);
		state[v] = 1;
		stack.pop_back();
	};
	rep(i, 0, sz(graph))
		if (!state[i])
			dfs(i, -1);
	return ret;
}
