/**
 * Author: Wzięte z tonowak
 * Description: Stwierdzanie istnienia i wyznaczanie ujemnego cyklu w grafie skierowanym
 *  (cykl może być gdziekolwiek, nie tylko osiągalny z jakiegoś źródła).
 *  \texttt{graph[v]} = lista par $(u, w)$ krawędzi $v \to u$ o wadze $w$.
 *  \texttt{cycle} spełnia \texttt{cycle[i]->cycle[(i+1)\%sz(cycle)]}.
 *  Żeby wyznaczyć krawędzie na cyklu, wystarczy wybierać najtańszą krawędź między wierzchołkami.
 *  Odległości mogą dojść do $-n^2 \max|w|$, więc zwykle $I$ = \texttt{ll}.
 * Time: O(nm)
 */
#pragma once

template<class I>
pair<bool, vi> negative_cycle(vector<vector<pair<int, I>>> graph) {
	int n = sz(graph);
	vector<I> dist(n);
	vi from(n, -1);
	int v_on_cycle = -1;
	rep(iter, 0, n) {
		v_on_cycle = -1;
		rep(v, 0, n)
			for(auto [u, w] : graph[v])
				if(dist[u] > dist[v] + w) {
					dist[u] = dist[v] + w;
					from[u] = v;
					v_on_cycle = u;
				}
	}
	if(v_on_cycle == -1)
		return {false, {}};
	rep(iter, 0, n)
		v_on_cycle = from[v_on_cycle];
	vi cycle = {v_on_cycle};
	for(int v = from[v_on_cycle]; v != v_on_cycle; v = from[v])
		cycle.emplace_back(v);
	reverse(all(cycle));
	return {true, cycle};
}
