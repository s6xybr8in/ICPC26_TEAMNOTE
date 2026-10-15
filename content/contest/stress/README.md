# Windows용 스트레스 테스트

Windows의 Python과 g++를 사용합니다. 보고 치기 쉽도록 파일명과 설정을 상단에 모았습니다.

## 실행

stress.py, random_input.py, naive.py(또는 naive.cpp), target_file.cpp를 같은 폴더에 두고 실행합니다.

```powershell
python stress.py
```

저장소 예제는 아래처럼 실행합니다.

```powershell
cd content\contest\stress
python ..\stress.py
```

## 바꿀 곳

```python
GEN = "random_input.py"
NAIVE = "naive.py"  # C++이면 "naive.cpp"
TARGET = "target_file.cpp"
START, TESTS, TIME = 1, 1000, 2
```

- START: 시작 seed, TESTS: 반복 횟수, TIME: 프로그램별 제한 시간(초)
- C++은 시작할 때 `g++ -std=c++17 -O2`로 .exe를 만들고 실행합니다.
- 생성기는 첫 번째 인자로 받은 seed로 입력을 만들어 stdout에 출력합니다. 예제처럼 `random.Random(int(sys.argv[1]))`을 사용하세요.
- naive와 target은 같은 stdin을 읽고 정답만 stdout에 출력합니다. 디버그 메시지는 stderr로 출력하세요.
- 비교는 공백·줄바꿈을 무시하는 토큰 비교입니다. 실수 허용 오차나 여러 정답을 인정하려면 비교 부분을 수정하세요.

## 반례 확인

현재 폴더에 매번 다음 파일을 덮어씁니다. 실패하면 즉시 멈춥니다.

| 파일 | 내용 |
|---|---|
| input.txt | 생성한 입력 |
| naive.out | naive 출력 |
| target.out | target 출력 |
| seed.txt | 현재 seed |

시간 초과·비정상 종료는 seed와 함께 표시합니다. stderr는 터미널에 바로 출력합니다.
재현하려면 START를 실패 seed로, TESTS를 1로 바꿉니다.

예제는 1-based 닫힌 구간 [l,r]의 합입니다.
설치 상태는 `python --version`, `g++ --version`으로 확인하세요.
