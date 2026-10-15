# 추가 알고리즘 사용 안내

새 헤더 41개는 `content/contest/template.cpp`의 표준 라이브러리와 `ll` 별칭을 전제로 합니다. 라이선스는 CC0입니다.
모든 구간은 양끝을 포함하는 `[l, r]`입니다. 빈 구간은 `l > r`로 표현합니다.
인덱스는 짧고 직접 구현하기 쉬운 방식을 선택합니다. 새 배열·그래프 코드는 0-based, 기존 Fenwick·SegmentTree·PST는 1-based입니다.
범용화나 복잡한 최적화보다 대회 중 옮겨 적고 수정하기 쉬운 구현을 우선합니다.

## 자료구조·DP

| 헤더 | API / 조건 |
|---|---|
| LazySegmentTree | 초기값 0. `update(l,r,x)` 덧셈, `update(l,r,x,true)` 대입, `query(l,r)` 합 |
| SparseTable | 정적 최솟값. `query(l,r)`는 비어 있지 않은 구간 |
| UnionFindRollback | `snapshot()` 이후 변경을 `rollback(t)`으로 복구. 경로 압축 없음 |
| LiChaoTree | `LiChaoTree(lo,hi)` 정수 도메인 양끝 포함. `add(m,b)`, `query(x)` 최솟값. 결과 `__int128` |
| DivideAndConquerDP | 상태는 prefix 길이. `cur[j]=min(prev[k]+cost(k,j-1))`, `k<j`. 비용 구간 `[k,j-1]`, 최적 k의 단조성 필요 |
| KnuthDP | 구간 합병 DP. `opt[l][r-1] <= opt[l][r] <= opt[l+1][r]` 조건 필요 |
| SubsetDP | `subsetSum(a)` 부분집합 합, `subsetSum(a,true)` 역변환. 길이 2의 거듭제곱 |

## 그래프·트리·유량

| 헤더 | API / 조건 |
|---|---|
| SCC | `addEdge`, `build`. 컴포넌트 번호는 축약 DAG 위상 순서 |
| 2sat | `TwoSAT(n)`. 리터럴 `2*i`는 참, `2*i+1`은 부정. `either(a,b)`, `force(a)`, `solve()`, 결과 `value` |
| BiconnectedComponents | `LowLink(n)`, `build()`. 단절점 `cut`, 단절선 ID `bridges`. 다중 간선 지원 |
| TopoSort | `topoSort(g)`. 사이클이면 빈 벡터. 빈 그래프도 빈 벡터 |
| EulerWalk | `EulerWalk(n,directed)`, `walk(start)`. 무방향 간선은 한 번만 추가. 실패 시 빈 벡터 |
| LCA | 연결된 비어 있지 않은 트리. `lca`, `dist`, `kth`, `ancestor`. 루트 위 조상은 -1. 서브트리 `[tin,tout]` |
| HLD | `path(u,v,callback,edge=false)`. 콜백에 `[l,r]` 전달. 서브트리 `[pos[u],pos[u]+sz[u]-1]`. 입력 g의 순서를 바꿔 가장 큰 자식을 `g[u][0]`에 배치. 부모 간선은 유지. 교환법칙 성립 연산용. 간선 값은 자식 정점에 저장 |
| CompressTree | `virtualTree(vertices,lca)`. 필요한 LCA 자동 추가. `(부모,자식)`은 원래 정점 ID. 간선 길이는 `dist` |
| CentroidDecomposition | `calcSize` → `findCentroid` → `build`의 재귀형. `parent`는 센트로이드 트리 부모, 루트 -1. 원본 트리는 객체보다 오래 유지. 일자 트리의 DFS 스택 깊이는 O(N) |
| Dinic | 비음수 용량, `s != t`. `maxflow(s,t)`는 추가 유량 반환 |
| MinCostMaxFlow | 초기 음수 비용 사이클 금지. 그래프당 `flow(s,t,limit)` 한 번. `(유량,비용)` 반환 |
| HopcroftKarp | 좌·우 정점 ID 별도. `maxMatching()` 후 `minCover()` 호출 |
| Hungarian | 행 수 <= 열 수, 유한 비용. `(최소비용,행별 열 번호)` 반환 |

SCC·LowLink·Dinic·매칭은 재귀 DFS를 사용합니다. 큰 입력에서 스택 크기를 확인하세요.

## 문자열·정수론·수치

| 헤더 | API / 조건 |
|---|---|
| KMP, Zfunc | `kmp(text,pat)`, `prefixFunction`, `zFunction`. 빈 패턴은 모든 경계에 매칭. `z[0]=0` |
| Manacher | `(odd,even)` 반경. 홀수 `[i-r+1,i+r-1]`, 짝수 `[i-r,i+r-1]` |
| AhoCorasick | 소문자 a-z, 비어 있지 않은 패턴. 모두 `add` 후 `build` 한 번. `countMatches`는 중복 패턴도 셈 |
| SuffixArray | `sa`, `rank`, `lcp`. 직전 접미사와 LCP. O(N log² N) |
| Hashing | `StringHash(s).get(l,r)`. 같은 base끼리 비교. 이중 모듈러도 충돌 가능 |
| Modular | `NT::power`, `inverse`, `extGcd`, `crt`. 양의 mod. 역원 불가 -1. CRT 불가 `(0,-1)`, lcm 초과 `(0,0)` |
| Sieve | `primes`, 최소 소인수 `spf`, `phi`, `mu` |
| Factor | `Factor64::prime`, `factor(n)`. uint64 범위. factor는 n>=1. 확률적 실행시간 |
| Binomial | 소수 mod, 전처리 N < mod. `choose(n,r)`. Lucas는 N=mod-1 필요하므로 큰 소수에는 비현실적 |
| NumberTheoreticTransform | `NTT::convolution`. mod 998244353, 입력 정규화. 결과 길이 <= 2²³ |
| FastFourierTransform | `FFT::convolution`. 정수 합성곱. 길이·계수 크기에 따라 실수 오차 가능 |
| SolveLinear | 확장 행렬과 변수 수 전달. -1 불가능 / 0 유일 / 1 무한해. 자유변수 0. EPS는 규모에 맞춤 |
| XorBasis | unsigned 64-bit. `insert`, `contains`, `maxXor` |
| LinearRecurrence | c[0]은 직전 항 계수. k>=1, 초기 항 k개, 값 정규화. O(k² log n) |

Catalan·포함배제·Burnside·목걸이 공식은 `combinatorial/identities.tex`에 있습니다.
`ll` 누적합·비용·곱이 범위를 넘지 않는지 확인하세요.

## 기하

| 헤더 | API / 조건 |
|---|---|
| Point | 정수 좌표 절댓값 <= 10⁹. 외적·내적·제곱거리 `__int128` |
| SegmentIntersection | 끝점 접촉·겹침·점 선분 포함 |
| ConvexHull | CCW, 중복 끝점 없음. 일직선 내부 점 제거 |
| HullDiameter | strict CCW 볼록 껍질의 거리 제곱. O(N) |
| InsidePolygon | 단순 다각형. 바깥 -1 / 경계 0 / 내부 1 |
| CircleIntersection | 실수 좌표 `DPoint`. 교점 개수, 동일 원 -1. EPS는 규모에 맞춤 |

## 검증

저장소 루트에서 새 묶음의 검증을 실행합니다.

```bash
g++ -std=c++17 -O2 -Wall -Wextra stress-tests/integration/CoreAlgorithms.cpp -o core-tests
./core-tests
```

고정 시드의 랜덤 입력으로 배열·완전탐색·느린 DP 등과 대조합니다.
최대 유량은 모든 컷, 매칭·할당은 모든 작은 배정, SCC는 도달성, 단절점·단절선은 삭제 후 연결요소와 비교합니다.
문자열은 직접 연산, NTT·FFT는 이중 반복문 합성곱, 정수론은 작은 수 완전탐색 및 큰 인수 재곱으로 검사합니다.
LCA·HLD는 부모 경로, 센트로이드는 분할 균형, 가상 트리는 조상·부모 관계를 확인합니다.
기하는 모든 점 쌍의 지름 및 교차·포함·원 교점 경계 사례를 검사합니다.

이 검증은 기존 KACTL 테스트 전체 통과를 뜻하지 않습니다.
최종 PDF의 페이지 수와 인쇄 가독성은 LaTeX 빌드 후 별도로 확인해야 합니다.
