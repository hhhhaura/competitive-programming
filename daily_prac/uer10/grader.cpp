#include "distance.h"
#include <cstdio>
#include <string>
#include <cmath>
namespace {
	static const double eps = 1e-6;
	static int cnt, n, k, limit;
	static std::vector < std::vector < int > > pos;
	static void gg(std::string res) {
		printf("WA %s\n", res.c_str());
		exit(0);
	}
	static double calc(std::vector < double > x, std::vector < double > y) {
		double ans = 0;
		for (int i = 0; i < k; i++) ans += (x[i] - y[i]) * (x[i] - y[i]);
		return sqrt(ans);
	}
	static double calc(std::vector < int > x, std::vector < int > y) {
		double ans = 0;
		for (int i = 0; i < k; i++) ans += 1ll * (x[i] - y[i]) * (x[i] - y[i]);
		return sqrt(ans);
	}
	static std::string itoa(int x) {
		char buf[100];
		sprintf(buf, "%d", x);
		return (std::string)buf;
	}
}
int query(int x, int y) {
	if (++cnt > limit) gg("too much query");
	if (x < 0 || x >= n || y < 0 || y >= n) gg("query out of bounds");
	int ans = 0;
	for (int i = 0; i < k; i++) ans += (pos[x][i] - pos[y][i]) * (pos[x][i] - pos[y][i]);
	return ans;
}
int main() {
	int ignore;
	ignore = scanf("%d%d%d", &n, &k, &limit);
	pos.resize(n);
	for (int i = 0; i < n; i++) {
		pos[i].resize(k);
		for (auto &x : pos[i]) ignore = scanf("%d", &x);
	}
	std::vector < std::vector < double > > ans = solve(n, k, limit);
	if ((int)ans.size() != n) gg("output is not n*k");
	for (auto i : ans) if ((int)i.size() != k) gg("output is not n*k");
	double sum = 0;
	for (int i = 0; i < k; i++) {
		int _min = pos[0][i], _max = pos[0][i];
		for (int j = 1; j < n; j++) _min = std::min(_min, pos[j][i]);
		for (int j = 1; j < n; j++) _max = std::max(_max, pos[j][i]);
		sum += (_max - _min) * (_max - _min);
	}
	sum = sqrt(sum);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < i; j++) {
			double out = calc(ans[i], ans[j]);
			double need = calc(pos[i], pos[j]);
			if (!(fabs(out - need) / std::max(1., sum) <= eps)) {
				std::string res = "distance of " + itoa(j) + " and " + itoa(i) + " is wrong";
				gg(res);
			}
		}
	printf("OK\nquery count: %d\n", cnt);
}