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
* 8초까지 지난 후 9초에 닿이면 9초가 답이다.
* 
* 약간 문제를 잘 읽어보면 답이 있는 것 같기도하다
* 
* 처음엔 오른쪽 위에서 시작, 오른쪽으로 가야함
* 지정된 시간까지(3 D면 4초 시작부터 방향 틈)
* 1초가 시작되면 뱀은 머리를 먼저 옮기고, 꼬리를 옮김
* 머리가 사과에 닿이면 꼬리는 옮기지 않음(사과는 없어짐)
* 머리가 벽이나 자기 몸에 닿이면 게임이 끝남(그 시간을 return)
* 
* ==> 처음 방향은 오른쪾으로 해두고
* map에 사과 위치를 넣을까 했는데 그냥 구조체 x,y구해서 배열로 하고 있네
* 정해진 방향으로 머리를 먼저 움직이고, 그때 사과랑 닿았다면 꼬리는 안움직이기, 
* 아 근데 그냥 칸을 먹는 방식으로 할까... board에 뱀이 있는 곳을 표시하는거지
* 그러면 꼬리에 닿으면 바로 알거 아냐
* board에 1로 만들면서 지나온곳은 0으로 만들고, 근데 그럼 꼬리 움직이고 말고?를 특정짓기 힘들려나
* 으악 모르겠따 머리랑 꼬리 부분 좌표가 필요 없을까?
* 
*/

#include <iostream>
#include <vector>
#include <map>

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
	int snakeLen;
	Position headPosition;
	Position tailPosition;
	vector<Position> chargePosition;
	int goingDirection;

	Snake()
	{
		snakeLen = 1;
		headPosition.x = 0;
		headPosition.y = 0;
		tailPosition.x = 0;
		tailPosition.y = 0;
		goingDirection = RIGHT;
	}

	void GoHead()
	{

	}

	void GoTail()
	{

	}
};

int main()
{
	int answerTime = 0;
	Snake snake;
	int N = 0;
	int K = 0;

	cin >> N;
	if (N < 2 || N > 100)
		return -1;

	int** board = new int* [N];
	for (int i = 0; i < N; i++)
		board[i] = new int[N];

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			board[i][j] = 0;
		}
	}
	// 뱀 시작점은 1로 만들기
	board[0][0] = 1;

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

	map<int, char> transformDirection;
	int time = 0;
	char direction = 'D';
	for (int i = 0; i < L; i++)
	{
		cin >> time >> direction;
		transformDirection.insert({ time, direction }); //, direction }); //잉 이렇게 하는 게 맞나 (그래ㅓㅅ map으로 함)
	}

	// 정해진 방향으로 한 칸 움직이는데
	// 이때 앞 칸에 뭔가 있는지 확인
	// 움직이기 전 time+1
	while (true)
	{
		Position currentHead = snake.headPosition;

		Position forwardHead;
		// head가 앞으로 갈 칸
		switch (snake.goingDirection)
		{
		case UP :
			forwardHead = { currentHead.y - 1, currentHead.x };
			break;
		case DOWN:
			forwardHead = { currentHead.y + 1, currentHead.x };
			break;

		case LEFT :
			forwardHead = { currentHead.y, currentHead.x - 1 };
			break;

		case RIGHT:
			forwardHead = { currentHead.y, currentHead.x + 1 };
			break;

		default:
			break;
		}

		// 만약 앞으로 갈 칸이 벽이거나, 자기 자신이면 게임끝
		if (forwardHead.x < 0 || forwardHead.x >= N || forwardHead.y < 0 || forwardHead.y >= N)
		{
			answerTime++;
			break;
		}

		if (board[forwardHead.y][forwardHead.x] == 1)
		{
			answerTime++;
			break;
		}

		// 만약 둘 다 아니라면 일단 시간은 +1
		answerTime++;

		// 이제 옮겨야 하는데
		// 만약 사과가 있다면 GoHead만, board를 1로 채우기
		for (int i = 0; i < K; i++)
		{
			if (forwardHead.y == apples[i].y && forwardHead.x == apples[i].x)
			{
				// 사과가 있는 곳이라면 GoHead()
				snake.GoHead();
				board[forwardHead.y][forwardHead.x] == 1;
			}
		}

		// 사과가 없었다면 GoHead, GoTail, board 한칸 미루기
		// 근데 만약 ㄱ자로 뱀이 있었다면 머리랑 tail만 옮긴다고 될 일은 아닌데
		// board를 칠하는 부분을 따로 만들어야하나..? 으악 좀 쉴까.......

		// 만약 지금 시간(바꾸고 난 후 시간)이 방향을 전환해야하는 시간(이 시간이 끝난 후 바꿔야 함)이라면
		for (auto td : transformDirection)
		{
			if (td.first == answerTime)
			{
				// 방향을 바꿔줌
				// 현재 방향에 +1을 하면 오른쪽, -1을 하면 왼쪽
				if (td.second == 'D')
				{
					snake.goingDirection = (snake.goingDirection + 1) % 4; // 순환 구조로 만약 left(3)에서 +1을 하면 0이 나오도록
				}
				else if (td.second == 'L')
				{
					snake.goingDirection = (snake.goingDirection + 3) % 4; // 순환 구조로 만약 up(0)에서 -1을 하면 3이 나오도록
				}
			}
		}


	}

	// 결과 출력
	cout << answerTime << endl;
	
	for (int n = 0; n < N; n++)
		delete[] board[n];
	delete[] board;

	return 0;
}