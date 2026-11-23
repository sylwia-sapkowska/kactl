mt19937_64 rng(random_device{}());
ll rd(ll l, ll r) {
	return uniform_int_distribution<ll>(l, r)(rng);
}