# ICPC Team Notebook

이 저장소는 ICPC (International Collegiate Programming Contest) 참가를 위한 알고리즘 팀노트(Team Reference Document)입니다.  
[KACTL](https://github.com/kth-competitive-programming/kactl)을 기반으로 커스텀 및 관리되고 있습니다.

- **생성된 팀노트 PDF**: [`kactl.pdf`](./kactl.pdf)
- **알고리즘 소스코드**: [`content/`](./content/)

---

## 👥 Team Information


- **소속 (University)**: Konkuk University
- **팀명 (Team)**: GreenSiro
- **팀원 (Members)**: Kwanho Nam, Yubi Bae, Jeongmin Lee

---

## 📑 목차 및 구조

팀노트는 대회 규정에 따라 **최대 25페이지(+ 표지 1페이지)** 이내로 구성됩니다.  
코드 및 자료는 [`content/`](./content/) 디렉터리 내 분야별로 관리됩니다.

- `content/contest/`: C++ 템플릿, `.vimrc`, 컴파일 플래그 및 환경 설정
- `content/data-structures/`: 자료구조 (세그먼트 트리, Fenwick, Treap 등)
- `content/numerical/`: 수치해석 및 다항식 (FFT, 행렬, 심슨 공식 등)
- `content/number-theory/`: 정수론 (모듈러 역원, 밀러-라빈, 에라토스테네스 등)
- `content/combinatorial/`: 조합론 및 카운팅
- `content/graph/`: 그래프 알고리즘 (네트워크 플로우, 매칭, 2-SAT 등)
- `content/geometry/`: 기하 알고리즘 (볼록 껍질, 선분 교차, 원 등)
- `content/strings/`: 문자열 (KMP, 아호-코라식, Manacher, 접미사 배열 등)
- `content/various/`: 기타 유용한 알고리즘 및 테크닉

---

## 🛠️ 빌드 방법 (Build)

KACTL은 LaTeX를 이용해 2열/3열의 고밀도 PDF를 빌드합니다. (Linux / WSL 환경 권장)

### 1. 필수 패키지 설치 (Ubuntu/Debian 기준)

```bash
sudo apt-get update
sudo apt-get install -y texlive-latex-base texlive-latex-extra texlive-fonts-recommended texlive-fonts-extra texlive-publishers python3
```

### 2. PDF 생성

```bash
make kactl       # 전체 빌드 (kactl.pdf 생성)
make fast        # 빠른 빌드 (캐시 활용)
make clean       # 빌드 산출물 정리
```

> **제외된 알고리즘 확인**:  
> `make showexcluded` 명령어로 현재 PDF에 미포함된(주석 처리된) 알고리즘 목록을 확인할 수 있습니다.

---

## ✏️ 팀노트 커스터마이징 가이드

### 1. 팀 정보 및 표지 변경
[`content/kactl.tex`](./content/kactl.tex) 파일에서 팀 정보를 수정할 수 있습니다.
```latex
\university{학교명 약칭}{학교 전체 영문명}{로고파일명}
\team{팀 이름}{팀원 1, 팀원 2, 팀원 3}
\contest{대회명 (예: The 2026 ICPC Asia Regional)}{날짜}
```
- 컬러 문법 강조를 원할 경우 `\enablecolors` 주석을 해제합니다.

### 2. 알고리즘 추가 및 제거
각 챕터 디렉터리의 `chapter.tex` 파일(예: `content/graph/chapter.tex`)에서 알고리즘을 포함하거나 제외할 수 있습니다.
```latex
\kactlimport{Dinic.h}         % 포함
% \kactlimport{EdmondsKarp.h} % 제외 (주석 처리)
```
- 지면 정렬 및 줄맞춤을 위해 `\columnbreak`, `\newpage`, `\hardcolumnbreak` 명령어를 활용할 수 있습니다.

### 3. 코드 작성 규칙 (Coding Style)
- **가로 길이 제한**: 한 줄 최대 **63자** (초과 시 PDF에서 줄바꿈이 발생합니다).
- **들여쓰기**: 탭(Tab) 사용 (PDF 출력 시 2칸 공백으로 변환).
- **헤더 주석**: 각 소스코드 상단에 메타데이터를 유지합니다.
  ```cpp
  /**
   * Author: 작성자
   * Date: 2026-00-00
   * License: CC0
   * Source: 출처 / 문제 링크
   * Description: 알고리즘 설명 및 주의사항
   * Time: O(...)
   * Status: stress-tested / tested on Baekjoon 12345
   */
  ```

### 4. 해시 검증 기능 (MD5 Hash)
- PDF로 생성된 각 알고리즘 우측 상단에는 공백과 주석을 무시하고 계산된 **6자리 MD5 해시값**이 출력됩니다.
- 대회 현장에서 코드를 타이핑한 뒤 오타가 없는지 빠르게 검증할 수 있습니다:
  ```bash
  ./content/contest/hash.sh < my_code.cpp
  ```
  (Vim 설정인 `.vimrc`를 사용하면 `:Hash` 명령어로 에디터 내에서 바로 확인 가능합니다.)

---

## 🧪 테스트 (Testing)

- `stress-tests/`: 랜덤 생성 입력을 이용해 naive 알고리즘과 정답을 대조하는 스트레스 테스트
- 테스트 실행:
  ```bash
  make test
  ```

---

## 📜 License & Credits

- 본 팀노트는 [KTH KACTL](https://github.com/kth-competitive-programming/kactl)을 기반으로 합니다.
- KACTL 원본 코드의 라이선스(주로 CC0)를 준수하며, 새로 추가하는 알고리즘 역시 출처 및 라이선스를 명시합니다.
