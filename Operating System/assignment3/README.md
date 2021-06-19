main 함수의 인자로 int argc, char* argv[]를 전달해서 텍스트 파일을 받을수 있게 했다.
입력 인자가 총 5개이므로 5개를 입력 안하면 에러가 나게 했다.
description의 interface 순서대로 txt파일의 값을 벡터에 넣었기 때문에 입력순서가 틀리면 오류가 날 수 있다.

resource-request algorithm을 통해 먼저 request 값이 올바른지 확인했고
그 다음 safety algorithm을 통해 safe sequence가 존재하는지 검사했다.
