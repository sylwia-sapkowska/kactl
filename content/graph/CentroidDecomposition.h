/**
 * Author: Wzięte z tonowak
 * Description: Template do Centroid Decomposition.
 *  Nie używamy \texttt{podsz}, \texttt{odwi}, ani \texttt{odwi\_cnt}.
 *  Konstruktor przyjmuje liczbę wierzchołków i drzewo (spójne).
 *  Jeśli chcemy mieć rozbudowane krawędzie, to zmienić tam, gdzie zaznaczone.
 *  Mamy tablicę odwiedzonych z refreshem w O(1) (używać bez skrępowania).
 *  \texttt{visit(v)} oznacza v jako odwiedzony.
 *  \texttt{is\_vis(v)} zwraca, czy v jest odwiedzony.
 *  \texttt{refresh()} zamienia niezablokowane wierzchołki na nieodwiedzone.
 *  W \texttt{decomp} mamy standardowe wykonanie CD na poziomie spójnej.
 *  Tablica \texttt{par} mówi, kto jest naszym ojcem w drzewie CD, \texttt{root} to korzeń drzewa CD.
 * Time: O(n \log n)
 */
#pragma once

struct CentroDecomp {
	const vector<vi> &graph; // tu
	vi par, podsz, odwi;
	int odwi_cnt = 1;
	const int INF = int(1e9);
	int root;
	void refresh() { ++odwi_cnt; }
	void visit(int v) { odwi[v] = max(odwi[v], odwi_cnt); }
	bool is_vis(int v) { return odwi[v] >= odwi_cnt; }
	void dfs_podsz(int v) {
		visit(v);
		podsz[v] = 1;
		for (int u : graph[v]) // tu
			if (!is_vis(u)) {
				dfs_podsz(u);
				podsz[v] += podsz[u];
			}
	}
	int centro(int v) {
		refresh();
		dfs_podsz(v);
		int sz = podsz[v] / 2;
		refresh();
		while (true) {
			visit(v);
			for (int u : graph[v]) // tu
				if (!is_vis(u) && podsz[u] > sz) {
					v = u;
					break;
				}
			if (is_vis(v))
				return v;
		}
	}
	void decomp(int v) {
		refresh();
		// Tu kod. Centroid to v, ktory jest juz dozywotnio odwiedzony.
		// Koniec kodu.
		refresh();
		for (int u : graph[v]) // tu
			if (!is_vis(u)) {
				u = centro(u);
				par[u] = v;
				odwi[u] = INF;
				// Opcjonalnie tutaj przekazujemy info synowi w drzewie CD.
				decomp(u);
			}
	}
	CentroDecomp(int n, const vector<vi> &grph) // tu
		: graph(grph), par(n, -1), podsz(n), odwi(n) {
		root = centro(0);
		odwi[root] = INF;
		decomp(root);
	}
};
