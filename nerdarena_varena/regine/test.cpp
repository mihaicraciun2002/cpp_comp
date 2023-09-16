#include <iostream>
#include <fstream>
 
using namespace std;
ifstream fin("regine.in");
ofstream fout("regine.out");
 
const int N_MAX = 14;
const int NIL = -1;
char queen[N_MAX + 1];
bool prin[N_MAX * 2 - 1]{}, sec[N_MAX * 2 - 1]{};//diagonala principala si secundara e libera
int nxt[N_MAX + 1];

int deadends;
 
void backtracking(int pos, int n, int nxt[], char queen[], int &cnt) {
	if(pos == n){
		++cnt;
		if(cnt < 4){
			for(int i = 0; i < n; ++i)
				fout << (int) queen[i] << ' ';
			fout.put('\n');
		}
		return;
	}
 
	int l = nxt[0], ant = 0;
    bool ok = 0;
	while(l != NIL){
		if(!prin[pos - l + n - 1] && !sec[pos + l]){
			queen[pos] = l;
            ok = 1;
			nxt[ant] = nxt[l];
			prin[pos - l + n - 1] = true;
			sec[pos + l] = true;
			backtracking(pos + 1, n, nxt, queen, cnt);
			nxt[ant] = l;
			prin[pos - l + n - 1] = false;
			sec[pos + l] = false;
		}
		ant = l;
		l = nxt[l];
	}
    if(ok == 0)  {
        deadends++;
    }
}
 
int main() {
	int n, cnt = 0;
	fin >> n;
 
	for(int i = 0; i <= n; ++i)
		nxt[i] = i + 1;
	nxt[n] = NIL;
 
	backtracking(0, n, nxt, queen, cnt);
 
	fout << cnt << '\n';
    cerr << deadends;
 
	fin.close();
	fout.close();
	return 0;
}