입력을 어떻게 하는지 안나와 있어서 실행하면 input.txt에 맞게 바로 output.txt가 생성되게 구현했습니다. <br>
1.변수 입력: 엔터 기준으로 txt파일 문자열 구분해서 각 변수에 알맞게 집어넣었음 <br>
2.switch문을 이용해서 원하는 함수에 들어가게 함 <br>
3. <br>
- fifo<br>
queue이용 <br>
- opt: <br>
pair.first: 들어온 데이터 pair.second: 얼마나 쓰이고 교체되는지 횟수 저장 <br>
pair 이용해서 들어올 문자가 얼마나 쓰일지 횟수를 미리 저장했고 알고리즘을 실행하면서 그 횟수를 1씩 빼줌 <br>
- lru <br>
pair.first: 들어온 데이터 pair.second: 얼마나 안쓰였는지 count한거  <br>
지금까지 얼마나 안쓰였는지 count 하고  pair이용해서 저장, 가장 count 큰 게 가장 오래 안쓰인거라 교체해줌 <br>
