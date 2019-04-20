#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
//
const int N = 400000;
int n, m, r;
int stp[N];
int state[N], head, tail;

void decode(int st, int &rst, int *pl1, int *pl2, int &np) {
	np = st & 1;
	rst = (st >>= 1) & 3;
	pl2[1] = (st >>= 2) & 15;
	pl2[0] = (st >>= 4) & 15;
	pl1[1] = (st >>= 4) & 15;
	pl1[0] = (st >>= 4) & 15;
}
int encode(int rst, int*pl1, int *pl2, int np) {
	return (pl1[0]<<15) + (pl1[1]<<11) + (pl2[0]<<7) + (pl2[1]<<3) + (rst<<1) + np;
}
void init() {
	
	scanf("%d%d%d",&n, &m, &r);
	
	head = 0;
	tail = 1;
	memset(stp,-1,sizeof(stp));
	if (r) r = n; else r = 1;
}
void work() {

	int now, next, rest=m, player[2][2]={1,1,1,1}, np=0;
	state[1] = encode(m, player[0], player[1], np);
	stp[state[1]] = 0;
	bool tag = false;
	
	int i, j, k;
	while (head < tail) {
		now = state[++head];
		decode(now, rest, player[0], player[1], np);
	//	printf("(%d %d) (%d %d) %d %d\n", player[0][0], player[0][1], player[1][0], player[1][1], rest, np);
	//	printf("%d ",head);
		for (i = 0; i <= 1; i++)
		if (player[np][i]) {
			if (rest && (!player[np][!i])) {
				k=player[np][i];
				for (j = 1; j < k; j++) {
					player[np][i] = j;
					player[np][!i] = k-j;
					next = encode(rest-1, player[0], player[1], !np);
					if (stp[next] < 0) {
						state[++tail] = next;
						stp[next] = stp[now] + 1;
					}
					else if (stp[next] < stp[now]) {
						tag = true;
						break;
					}
				}
				player[np][i] = k;
				player[np][!i] = 0;
			}
			for (j = 0; j <= 1; j++) if (player[!np][j]){
				k = player[!np][j];
				player[!np][j] += player[np][i];
				if (player[!np][j] >= n) player[!np][j] %= r;
				next = encode(rest, player[0], player[1], !np);
				if (stp[next] < 0) {
					state[++tail] = next;
					stp[next] = stp[now] + 1;
				}
				else if (stp[next] < stp[now]) {
					tag = true;
					break;
				}
				player[!np][j] = k;
			}
		}
	//	printf("%d\n",tail);
	}
	
	if (tag) printf("Infinite\n");
	else printf("%s\n%d\n", (state[tail] & 1) ? "First" : "Second", stp[state[tail]]);
	/*for (i = 0; i <= tail; i++) {
		decode(state[i], rest, player[0], player[1], np);
		printf("%d: (%d %d) (%d %d) %d %d\n", i, player[0][0], player[0][1], player[1][0], player[1][1], rest, np);
	}*/
}
//
int main() {
	init();
	work();
	return 0;
}
