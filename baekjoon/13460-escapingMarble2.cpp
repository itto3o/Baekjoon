/* 2022-12-21
* baekjoon 13460
* 보드의 세로크기는 N, 가로 크기는 M, 1X1 크기의 칸으로 나누어져 있음
* 가장 바깥 행, 열은 모두 #으로 막혀져 있고, 보드에는 구멍이 하나 있다.
* 빨간 구슬과 파란 구슬이 각 한 칸을 차지하고, 게임의 목표는 빨간 구슬을 구멍으로 빼내는 것이다.
* 
* 구슬을 손으로 건드릴 수는 없고, 중력으로 이리저리 굴려야 한다.
* 왼쪽, 오른쪽, 위쪽, 아래쪽 네 방향으로 기울일 수 있다.
* 
* 각 동작에서 공들은 동시에 움직인다. 파란 구슬이 구멍에 빠지면 실패, 동시에 두 구슬이 구멍에 빠져도 실패
* 
* 보드의 상태가 주어졌을 때, 최소 몇 번 만에 빨간 구슬을 구멍을 통해 빼낼 수 있는지 구하는 프로그램을 작성하시오.
* 
* 입력) N, M (3<=N, M<=10),
*		N개의 줄에 보드의 모양을 나타내는 길이 M의 문자열 (.은 빈칸, #은 벽, o는 구멍, R은 빨간 구슬, B는 파란 구슬
* 
* 출력) 최소 몇 번 만에 빼낼 수 있는지 출력, 만약 10번 이하로 움직여서 빼낼 수 없으면 -1
* 
* 2023-04-27
* 예제는 다 했는데
* 7%? 에서 틀렸습니다 뜸
* 진짜 테스트케이스 물어보고 싶네..
*/

// R, B는 모두 4방향 주위 한칸의 상태를 갖고있고,
// 어디로 기울이든 .이 있는 방향으로 기울이기(기울였다면 count +1)
// 상태를 변화하는 go 함수 4개, (lrud)
// 항상 R중심, R먼저 움직이기
// 
// 1. 일단 R, B의 값을 세팅하고
// 2. R을 기준으로 .으로 이동하기(.이 두개라면..? 일단 예제에는 없는데 잘 모르겠네) ㅁㅊ 아래랑 똑같이 말해 ㅋㅋ
// 벽에 부딪혀서 방향을 바꿀때마다 count+1

// R의 위치를 파악해서
// 갈 수 있는 길의 방향을 정함 (만약 둘다 갈 수 있다면..? (이 경우는 잘 모르겠네..))
// 그 방향으로 한 칸씩 R과 B를 움직여가면서
// R이 더이상 갈 곳이 없으면 다시 방향을 선택

#include <iostream>
using namespace std;

class Marble
{
public :
	// (0,0)은 왼쪽 위
	int x; //x가 가로,(m) 행
	int y; // y가 세로(n) 열

	Marble() {
		this->x = 0;
		this->y = 0;
	}

	int go_up(char** board)
	{
		// 바꿀위치가 .이거나 O일때만 움직이기
		// 아마 여기서 하는게 아니라 1칸씩 움직여야 테스트케이스도 통과하지 않을까...
		// 몰라 포기 ㅋㅅㅋ
		char change = board[this->y - 1][this->x];
		while (change == '.' || change == 'O')
		{
			// O찾았으면 자신은 .으로 바꾸기
			if (change == 'O') 
			{
				board[this->y][this->x] = '.';
				return 1;
			}

			// .이랑 자신 위치랑 바꾸기
			char temp = board[this->y][this->x];
			board[this->y][this->x] = change;
			board[this->y - 1][this->x] = temp;

			this->y--;
			change = board[this->y - 1][this->x];
		}
		return 0;
	}

	int go_down(char** board)
	{
		char change = board[this->y + 1][this->x];
		while (change == '.' || change == 'O')
		{
			
			if (change == 'O')
			{
				board[this->y][this->x] = '.';
				return 1;
			}

			char temp = board[this->y][this->x];
			board[this->y][this->x] = change;
			board[this->y + 1][this->x] = temp;

			this->y++;
			change = board[this->y + 1][this->x];
		}
		return 0;
	}

	int go_left(char** board)
	{
		char change = board[this->y][this->x - 1];
		while (change == '.' || change == 'O')
		{
			if (change == 'O')
			{
				board[this->y][this->x] = '.';
				return 1;
			}

			char temp = board[this->y][this->x];
			board[this->y][this->x] = change;
			board[this->y][this->x - 1] = temp;

			this->x--;
			change = board[this->y][this->x - 1];
		}
		return 0;
	}

	int go_right(char** board)
	{
		char change = board[this->y][this->x + 1];
		while (change == '.' || change == 'O')
		{
			if (change == 'O')
			{
				board[this->y][this->x] = '.';
				return 1;
			}
			char temp = board[this->y][this->x];
			board[this->y][this->x] = change;
			board[this->y][this->x + 1] = temp;

			this->x++;
			change = board[this->y][this->x + 1];
		}
		return 0;
	}
};

/* 다른 cpp파일에서 main이 중복선언 되었다고 떠서
int main()
{
	Marble* R = new Marble();
	Marble* B = new Marble();

	// count, 답
	int count_ans = 0;

	// N, M 받기
	int N = 0;
	int M = 0;
	cin >> N >> M;

	// 동적할당 해야되네...
	// 행이 N, 행 마다 M씩
	char** board = new char*[N];

	for (int n = 0; n < N; n++)
	{
		board[n] = new char[M];
	}

	for (int n = 0; n < N; n++)
	{
		for (int m = 0; m < M; m++)
		{
			cin >> board[n][m];
		}
	}

	//for (int n = 0; n < N; n++)
	//{
	//	for (int m = 0; m < M; m++)
	//		cout << "(" << n << "," << m << "), " << board[n][m] << "\t";
	//	cout << endl;
	//}

	// R, B, O 위치 파악
	int Ox = 0, Oy = 0;
	// n이 상하, y, m이 x
	for (int n = 0; n < N; n++)
	{
		for (int m = 0; m < M; m++)
		{
			if (board[n][m] == 'R')
			{
				//cout << n << m;
				R->y = n;
				R->x = m;
			}

			if (board[n][m] == 'B')
			{
				//cout << n << m;
				B->y = n;
				B->x = m;
			}

			if (board[n][m] == 'O')
			{
				//cout << n << m;
				Oy = n;
				Ox = m;
			}
		}
	}

	// O까지의 최적 경로?
	// ㅁ?ㄹ... 일단 R, B의 위치를 생각해서 움직이려는 방향으로 더 큰 쪽을 먼저 움직이자
	// 아 움직이면서 값도 바꿔야되네
	// 아닌가, .이랑 R이랑 바꿔야되네 ㅇㅇ

	// .과 ., .과 O이 있다면?
	// O와의 x, y를 따져서 우선적으로 할 수 있도록..?
	// 우선순위..?를 만들어야하나
	char priority = 'o';

	// 차의 제곱(-방지)의 값이 더 큰 값을 우선적으로 함수실행하도록?
	if (((Ox - R->x) * (Ox - R->x)) > ((Oy - R->y) * (Oy - R->y)))
	{
		priority = 'x';
	}
	else
		priority = 'y';



	//지나온 길을 안가게 할 수 있는 방법?
	// direction을 만들어서 현재 갔던 방향이라면 그냥 continue;
	// 근데 반드시 뒤로 가야하는 상황이라면?
	// 갔는데 3방향이 막혀있는거면...

	// 주위에 .(이나 O)이 두개 있다면 direction으로 반대방향으로 가지 않게 함,
	// 하나뿐이라면 그 길로 갈 수 있도록
	char direction = 'o';
	int R_result = -1;
	int B_result = -1;

	while (R_result != 1 && count_ans <= 10)
	{
		//for (int n = 0; n < N; n++)
		//{
		//	for (int m = 0; m < M; m++)
		//		cout << "(" << n << "," << m << "), " << board[n][m] << "\t";
		//	cout << endl;
		//}

		// R의 주위를 살펴보고, 움직일 방향이 있다면 그쪽으로 움직이기
		char R_up = board[R->y - 1][R->x];
		char R_down = board[R->y + 1][R->x];
		char R_left = board[R->y][R->x - 1];
		char R_right = board[R->y][R->x + 1];

		// 점 개수
		int pointCount = 0;
		// case문의 if문에 넣고 싶어도 완벽한 개수를 모르니까...
		if ((R_left == '.' || R_left == 'O'))
			pointCount++;
		if ((R_right == '.' || R_right == 'O'))
			pointCount++;
		if ((R_up == '.' || R_up == 'O'))
			pointCount++;
		if ((R_down == '.' || R_down == 'O'))
			pointCount++;

		// 갈 수 있는 길이 하나면 direction 초기화 ==> 다시 돌아갈 수 있도록
		if (pointCount == 1)
			direction = 'o';

		// priority가 x면 left, right를 먼저 실행
		// 어떻게 하든 코드 중복이 일어나네... 어떡하지
		switch (priority)
		{
		case 'x':
			if (direction != 'r' && (R_left == '.' || R_left == 'O')) {
				if (R->x > B->x)
				{
					B_result = B->go_left(board);
					R_result = R->go_left(board);
				}

				else {
					R_result = R->go_left(board);
					B_result = B->go_left(board);
				}

				count_ans++;
				direction = 'l';
				continue;
			}

			if (direction != 'l' && (R_right == '.' || R_right == 'O')) {
				if (R->x < B->x)
				{
					B_result = B->go_right(board);
					R_result = R->go_right(board);
				}

				else {
					R_result = R->go_right(board);
					B_result = B->go_right(board);
				}

				count_ans++;
				direction = 'r';
				continue;
			}

			if (direction != 'd' && (R_up == '.' || R_up == 'O')) {
				if (R->y > B->y)
				{
					B_result = B->go_up(board);
					R_result = R->go_up(board);
				}

				else {
					R_result = R->go_up(board);
					B_result = B->go_up(board);
				}
				count_ans++;
				direction = 'u';
				continue;
			}

			if (direction != 'u' && (R_down == '.' || R_down == 'O')) {
				if (R->y < B->y)
				{
					B_result = B->go_down(board);
					R_result = R->go_down(board);
				}

				else {
					R_result = R->go_down(board);
					B_result = B->go_down(board);
				}
				count_ans++;
				direction = 'd';
				continue;
			}
			break;

		case 'y' :
			if (direction != 'd' && (R_up == '.' || R_up == 'O')) {
				if (R->y > B->y)
				{
					B_result = B->go_up(board);
					R_result = R->go_up(board);
				}

				else {
					R_result = R->go_up(board);
					B_result = B->go_up(board);
				}
				count_ans++;
				direction = 'u';
				continue;
			}

			if (direction != 'u' && (R_down == '.' || R_down == 'O')) {
				if (R->y < B->y)
				{
					B_result = B->go_down(board);
					R_result = R->go_down(board);
				}

				else {
					R_result = R->go_down(board);
					B_result = B->go_down(board);
				}
				count_ans++;
				direction = 'd';
				continue;
			}
			if (direction != 'r' && (R_left == '.' || R_left == 'O')) {
				if (R->x > B->x)
				{
					B_result = B->go_left(board);
					R_result = R->go_left(board);
				}

				else {
					R_result = R->go_left(board);
					B_result = B->go_left(board);
				}
				count_ans++;
				direction = 'l';
				continue;
			}

			if (direction != 'l' && (R_right == '.' || R_right == 'O')) {
				if (R->x < B->x)
				{
					B_result = B->go_right(board);
					R_result = R->go_right(board);
				}

				else {
					R_result = R->go_right(board);
					B_result = B->go_right(board);
				}
				count_ans++;
				direction = 'r';
				continue;
			}
			break;
		default:
			break;
		}
	}

	if ((R_result == 1 && B_result == 1) || count_ans > 10)
		cout << -1;
	else
		cout << count_ans;

	for (int n = 0; n < N; n++)
		delete[] board[n];
	delete[] board;
} */