/*
* 2023-05-04
* 
* NXN 정사각 보드,
* 사과의 위치가 주어지고,
* 보드의 상화자우 끝엔 벽이 있다.
* 
* 뱀은 벽 또는 자기자신의 몸과 부딪히면 게임이 끝남
* 
* 게임 시작시 뱀은 맨위 맨좌측에 위치, 길이는 1, 오른쪽을 향함
* 매 초마다 이동,
* 머리를 다음칸에 위치시킨 후, 다음 칸에 사과가 있다면 사과는 없어지고 꼬리는 움직이지 않음
* 사과가 없다면 몸길이를 줄여서 칸을 비워줌(몸길이 변화x)
* 
* 사과위치, 뱀의 이동경로가 주어질 때 게임이 몇 초에 끝나는지
* 
* 입력)
* 1. 보드의 크기 N (2<=N<=100)
* 2. 사과의 개수 K(0 <= K <= 100)
* (보드 크기보다 클 수 있나..?)
* 
* 3. K개의 줄에는 각각 사과의 위치가 주어짐
* 행, 열,
* 사과의 위치는 모두 다름, 1행 1열에는 사과가 없음
* 4. 뱀의 방향 변환 횟수 L(1<=L<=100)
* 5. L개의 줄에 변환 정보, X, C(X초가 끝난 후 C로 방향을 90도 회전(L또는 D)
*	X <= 10,000 이하의 자연수, X가 증가하는 순으로 주어짐
* 
* 출력)
* 첫째 줄에 게임이 몇 초에 끝나는지 출력
* 
* 
* ---000
* 00|0*0
* 00|*00
* 00*000
* 00|--0
* 
* ---------0
* 0****00||0
* 0000000-|0
* 0000000000
* 0000000000
* 0000000000
* 0000000000
* 0000000000
* 0000000000
* 0000000000
* 
* 아니 문제 이해를 잘 못하겟는디
* 애초에 시작할때 맨왼쪽맨위칸에서 1초를 쓰는건지
* 꺾을때 2초씩쓰는건가?
* 벽이 다 있는건가 그럼
* 그럼 1행은 모두 벽이겠네?
* 사과 위치도 다 달라지나..?
* 아니 문제가 왤케 불친절해
* 
* 000000
* 0----0
* 0000|0
* 0000|0
* 0000|0
* 000000 이러면 7아냐?
* 
* 만약 1초가 시작이라면 + 방향전환에도 1초를 쓴다면
* 000000
* 0--|00
* 000|00
* 000|00
* 000|00 이러면 8아닌가
* 000000 
* 
* // 벽이 없다면
* ---000
* 00|000
* 00|000
* 00|000
* 00|000
* 00|000 이럼 9긴 하네
* 
* ----000
* 000|00
* 000|00
* 000|00
* 000|00
* 000|00 8까지 벽 전블럭까지 가는거고, 9 시작할 때 닿이네
* 
* 결론
* 벽은 내부적으로는 없다.
* 방향을 트는 시간이 1초이진 않는것같다.
* 방향을 트는 시간은 따로 없고, 시작 블록에서 1초를 잡진 않는 것 같다.
* 
* 약간 문제를 잘 읽어보면 답이 있는 것 같기도하다
* 
*/

#include <iostream>
#include <vector>
using namespace std;

enum {
	// 시계방향으로
	UP, RIGHT, DOWN, LEFT
};
struct Position
{
	int y = 0;
	int x= 0;
};

class Snake
{
public:
	int snakeLen = 1;
	Position headPosition;
	Position tailPosition;
	vector<Position> chargePosition;
	int goingDirection = RIGHT;

	void go()
	{

	}
};

int main()
{
	int N = 0;
	int K = 0;

	cin >> N;
	if (N < 2 || N > 100)
		return -1;

	int** board = new int* [N];
	for (int i = 0; i < N; i++)
		board[i] = new int[N];

	// 초기화(시켜야 되나?) 애초에 필요가 있나?
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			board[i][j] = 0;
		}
	}

	cin >> K;
	if (K < 0 || K > 100)
		return -1;

	Position* apples = new Position[K];
	for (int i = 0; i < K; i++)
	{
		cin >> apples[i].y >> apples[i].x;
	}

	int L;
	if (L < 1 || L > 100)
		return -1;

	vector<int, char> transformDirection;
	int time = 0;
	char direction = 'D';
	for (int i = 0; i < L; i++)
	{
		cin >> time >> direction;
		transformDirection.push_back(time);//, direction }); //잉 이렇게 하는 게 맞나
		// 아몰랑 오늘은 여기까지만 할래...
	}
	
	for (int n = 0; n < N; n++)
		delete[] board[n];
	delete[] board;
	return 0;
	return 0;
}