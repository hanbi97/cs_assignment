# ComputerGraphics (Fall / 2019)

### Rocket Project
![이미지 11](https://user-images.githubusercontent.com/36736904/82207250-7a7c1700-9944-11ea-90ea-fd55fdc73725.png)
<br/>

#### 구현내용
1.대기<br/>
밤에 로켓을 발사하는 걸 테마로 잡고 달, 로켓, 땅, 밤 하늘이 나타나게 했습니다.
<br/>

2.발사 <br/>
Q 버튼을 짧게 누르면 낙하산을 펼치지 않고 땅에 떨어지고 길게 누르면 로켓이 내려올 때 낙하산을 펼치며 땅에 떨어지게 했습니다.
<br/>

3.자유낙하<br/>
포물선을 그리며 운동하게 했습니다.
<br/>

4.낙하산<br/>
일정 에너지 이상(40)이 되면 낙하산이 펼쳐집니다. 아무리 Q를 오래 눌러도 화면 밖을 탈출하는 걸 막기 위해 최대 에너지를 45로 제한 했습니다.
<br/>

5.착륙<br/>
로켓이 땅에 박힙니다.

#### 조작방법
발사 : Q
<br/>

낙하산: 일정 시간 이상 Q를 눌러서 에너지가 충전 되면 알아서 펴집니다
<br/>

카메라 조종: 마우스와 키보드 방향키로 시점 조절 가능, 로켓이 이동 시 에너지에 따라 카메라 위치가 바뀝니다
<br/>


#### 주요코드에 대한 설명, 소스코드 내에서 위치
* tutorial04.cpp
<br/>

하늘 색 설정한 코드: 102번째 줄 glClearColor(0.0f, 0.0f ,81.0f / 255.0f, 0.0f);
<br/>

도형들 정점 선언한 배열 :123번째 줄~367번째 줄
<br/>

땅과 달이 있는 행렬 선언: 382번째 줄
<br/>

로켓이 있는 행렬 선언: 420번째 줄
<br/>

로켓이 포물선 운동하는 코드: 34번째 줄, 384번째 줄<br/>
glm::mat4 getRotationMatrix(glm::vec3 direction)
rotationMatrix는 eulerAngleXYZ()함수를 이용해 구현
로켓의 방향벡터와 에너지를 합해서 로켓이 얼마나 날아갈지 계산했고, 낙하산이 펴지는지 안 펴지는지에 따라 낙하속도 조절을 했습니다.
Head[1](로켓의 머리가 향하는 방향)의 값이 0 이하면 땅에 닿은 것 이므로 로켓의 움직임을 중단했습니다.
<br/>

원을 만드는 코드:  654번째 줄<br/>
GLfloat *makeCircleVertexData(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides);
<br/>

원뿔을 만드는 코드: 682번째 줄<br/>
GLfloat *makeConeVertexData(GLfloat x, GLfloat y, GLfloat z, GLfloat height, GLfloat radius, GLint numberOfSides);
<br/>

원기둥을 만드는 코드: 709번째 줄<br/>
GLfloat *makeCylinderVertexData(GLfloat x, GLfloat y, GLfloat z, GLfloat height, GLfloat radius, GLint numberOfSides);
<br/>

* controls.cpp
<br/>

Q를 눌렀을 때 에너지가 충전되는걸 구현한 코드: 115번째 줄
<br/>

Q를 눌렀다 떼면 충전된 에너지 양에 따라 낙하산을 펼지 말지 결정하는 코드: 120번째 줄
<br/>

로켓을 발사하고 로켓이 이동한 거리에 따라 시점을 이동시켜준 코드: 136~156번째 줄<br/>
- 낙하산이 펴질 정도로 에너지가 큰 로켓을 쏘아올리는 중일 때:<br/> 
verticalAngle = 0.8f;
position = vec3(41, 13, 170);
(위를 볼 수 있도록 조절해줌)
- 낙하산이 펴질 정도로 에너지가 큰 로켓을 쏘는 행동이 끝났을 때:<br/>
verticalAngle = 0.2f;
position = vec3(80, 3, 200); 
(처음 y 좌표로 돌아오고 x만 이동한 걸 보여줌)
- 낙하산이 안 펴지는 에너지가 작은 로켓을 쏠 때: <br/>
verticalAngle = 0.2f;
position = vec3(38, 3, 200);
(화면 안에서 모든 행동이 일어나기 때문에 시점을 변환할 필요가 없음)
