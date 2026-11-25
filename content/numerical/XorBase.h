/**
 * Author: Wzięte z tonowak
 * Description: Dla zbioru $S$ wyznacza minimalny zbiór $B$ taki, że każdy element $S$
 *  można zapisać jako xor jakiegoś podzbioru $B$. Zwrócona baza jest zredukowana
 *  (najwyższy bit każdego elementu bazy nie występuje w pozostałych).
 *  Elementy muszą być z $[0, 2^{bits})$.
 * Time: O(n \cdot bits + bits^2)
 */
#pragma once

int highest_bit(int ai) {
	return ai == 0 ? 0 : __lg(ai) + 1;
}
constexpr int bits = 30;
vi xor_base(vi elems) {
	vector<vi> at_bit(bits + 1);
	for(int ai : elems)
		at_bit[highest_bit(ai)].emplace_back(ai);
	for(int b = bits; b >= 1; --b)
		while(sz(at_bit[b]) > 1) {
			int ai = at_bit[b].back();
			at_bit[b].pop_back();
			ai ^= at_bit[b].back();
			at_bit[highest_bit(ai)].emplace_back(ai);
		}
	at_bit.erase(at_bit.begin());
	rep(b0, 0, bits - 1)
		for(int a0 : at_bit[b0])
			rep(b1, b0 + 1, bits)
				for(int &a1 : at_bit[b1])
					if((a1 >> b0) & 1)
						a1 ^= a0;
	vi ret;
	for(auto &v : at_bit) {
		assert(sz(v) <= 1);
		for(int ai : v)
			ret.emplace_back(ai);
	}
	return ret;
}
