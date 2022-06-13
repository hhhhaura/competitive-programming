#include <cassert>
#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int N, Q;
  std::cin >> N >> Q;
  std::vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    std::cin >> A[i];
    assert(A[i] >= 0 && A[i] < N);
  }

  // Nodes in the persistent segment tree are dynamically allocated.
  // For a node z:
  //  - tree[z]: the number of integers lying in the subtree of z
  //  - left[z]: the left child of z
  //  - right[z]: the right child of z
  /*std::vector<int> tree, left, right;

  // Create a new node. If z != -1, the new node is identical to node z.
  auto NewNode = [&](int z = -1) {
    tree.push_back(0);
    left.push_back(-1);
    right.push_back(-1);
    if (z != -1) {
      tree.back() = tree[z];
      left.back() = left[z];
      right.back() = right[z];
    }
    return tree.size() - 1;
  };

  auto Build = [&]() {
    auto dfs = [&](auto dfs, int l, int r) -> int {
      int node = NewNode();
      if (r - l > 1) {
        int m = (l + r) >> 1;
        left[node] = dfs(dfs, l, m);
        right[node] = dfs(dfs, m, r);
      }
      return node;
    };

    return dfs(dfs, 0, N);
  };

  auto Update = [&](int z, int p) {
    auto dfs = [&](auto dfs, int l, int r, int z) -> int {
      int node = NewNode(z);
      if (r - l == 1) {
        tree[node]++;
      } else {
        int m = (l + r) >> 1;
        if (p < m) {
          left[node] = dfs(dfs, l, m, left[z]);
        } else {
          right[node] = dfs(dfs, m, r, right[z]);
        }
        tree[node] = tree[left[node]] + tree[right[node]];
      }
      return node;
    };

    return dfs(dfs, 0, N, z);
  };

  // Returns the number of integers in [ql, qr) in the segment tree rooted at z.
  auto Query = [&](int z, int ql, int qr) {
    auto dfs = [&](auto dfs, int l, int r, int z) -> int {
      if (l >= qr || ql >= r) {
        return 0;
      }
      if (l >= ql && r <= qr) {
        return tree[z];
      }
      int m = (l + r) >> 1;
      return dfs(dfs, l, m, left[z]) + dfs(dfs, m, r, right[z]);
    };

    return dfs(dfs, 0, N, z);
  };

  // roots[i] is the root of the segment tree corresponding to A[0], A[1], ...,
  // A[i - 1].
  std::vector<int> roots(N + 1);
  
  roots[0] = Build();
  for (int i = 0; i < N; ++i) {
    roots[i + 1] = Update(roots[i], A[i]);
  }
	*/
  while (Q--) {
    int L, R, X, Y;
    std::cin >> L >> R >> X >> Y;
    int cnt = 0;
	for(int i = L; i < R; i ++) {
		if(A[i] < Y && A[i] >= X) cnt++;
	}
	std::cout << cnt << "\n";
	//std::cout << Query(roots[R], X, Y) - Query(roots[L], X, Y) << "\n";
  }
  return 0;
}
