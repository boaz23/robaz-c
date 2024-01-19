int powi(int b, unsigned int e) {
	int res = 1;
	while (e > 0) {
		if ((e & 1) != 0) {
			res *= b;
		}

		b *= b;
		e >>= 1;
	}

	return res;
}
