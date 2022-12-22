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
*/

// R의 위치를 파악해서
// 갈 수 있는 길의 방향을 정함 (만약 둘다 갈 수 있다면..? (이 경우는 잘 모르겠네..))
// 그 방향으로 한 칸씩 R과 B를 움직여가면서
// R이 더이상 갈 곳이 없으면 다시 방향을 선택

#include <iostream>
using namespace std;

int main()
{
	// count, 답
	int count_ans = 0;

	// 방향 정하기
	char direction = 'n';

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
		
	// R의 위치를 파악해서 //근데 Ox로 선언해도 되나..? 아 그건 0x구나
	int Rx = 0, Ry = 0, Bx = 0, By = 0, Ox = 0, Oy = 0;
	for (int n = 0; n < N; n++)
	{
		for (int m = 0; m < M; m++)
		{
			if (board[n][m] == 'R') 
			{
				Ry = m;
				Rx = n;
			}

			if (board[n][m] == 'B')
			{
				By = m;
				Bx = n;
			}

			if (board[n][m] == 'O')
			{
				Oy = m;
				Ox = n;
			}
		}
	}

	for (int i = 0; i < 10; i++)
	{
		// 갈 수 있는 길의 방향을 정함 (만약 둘다 갈 수 있다면..? (이 경우는 잘 모르겠네..))
		// 위, 아래, 왼쪽, 오른쪽 모두 파악 (u, d, l, r)
		//direction = 'n';

		// u
		// 위로 갈 수 있고, 이전 direction이 d가 아닐 때 (다시 돌아가지 않기 위해) u으로바꾸기

		// 아니 이거 == 할때는 (x,y)로 받고 =인건 (y,x)라서 하..
		// 근데 그게 아니라 x-1로 해서 하면 될듯?
		if (board[Rx - 1][Ry] == '.' && direction != 'd')
		{
			direction = 'u';
			count_ans++;
		}

		// d
		else if (board[Rx + 1][Ry] == '.' && direction != 'u')
		{
			direction = 'd';
			count_ans++;
		}

		// l
		else if (board[Rx][Ry - 1] == '.' && direction != 'r')
		{
			direction = 'l';
			count_ans++;
		}

		// r
		else if (board[Rx][Ry + 1] == '.' && direction != 'l')
		{
			direction = 'r';
			count_ans++;
		}

		// none : #이거나 o이거나..?
		else
			direction = 'n';


		// 그 방향으로 한 칸씩 R과 B를 움직여가면서
		switch (direction)
		{
		case 'u':
			while (true) 
			{
				if (board[Rx - 1][Ry] == 'O') 
				{
					direction = 'o';
					break;
				}

				if (board[Rx - 1][Ry] == '.')
				{
					board[Rx - 1][Ry] = 'R';
					// 여기서만 갑자기 [Rx][Ry]하니까 Rx번째 줄의 Ry번째를 읽어와서 바꿈
					// ==> (y,x)좌표를 읽어온단 뜻... ==> Ry, Rx로 바꿔줌
					// ==> (x,y) 하려고 했었는데 그러려면 처음부터 Ry, Rx를 해야했던것
					board[Rx][Ry] = '.';
					Rx -= 1;

					if (board[Bx - 1][By] == '.')
					{
						board[Bx - 1][By] = 'B';
						board[Bx][By] = '.';
						Bx -= 1;
					}
				}

				else
				{
					direction = 'n';
					break;
				}
			}
			break;
		case 'd':
			while (true) 
			{
				if (board[Rx + 1][Ry] == 'O') 
				{
					direction = 'o';
					break;
				}

				if (board[Rx + 1][Ry] == '.') 
				{
					board[Rx + 1][Ry] = 'R';
					board[Rx][Ry] = '.';
					Rx += 1;
					if (board[Bx + 1][By] == '.')
					{
						board[Bx + 1][By] = 'B';
						board[Bx][By] = '.';
						Bx += 1;
					}
				}

				else
				{
					direction = 'n';
					break;
				}
			}
			break;
		case 'l':
			while (true)
			{
				if (board[Rx][Ry - 1] == 'O')
				{
					direction = 'o';
					break;
				}

				if (board[Rx][Ry - 1] == '.')
				{
					board[Rx][Ry - 1] = 'R';
					board[Rx][Ry] = '.';
					Ry -= 1;
					if (board[Bx][By - 1] == '.')
					{
						board[Bx][By - 1] = 'B';
						board[Bx][By] = '.';
						By -= 1;
					}
				}

				else
				{
					direction = 'n';
					break;
				}
			}
			break;
		case 'r':
			while (true)
			{
				if (board[Rx][Ry + 1] == 'O')
				{
					direction = 'o';
					break;
				}

				if (board[Rx][Ry + 1] == '.') 
				{
					board[Rx][Ry + 1] = 'R';
					board[Rx][Ry] = '.';
					Ry += 1;
					if (board[Bx][By + 1] == '.')
					{
						board[Bx][By + 1] = 'B';
						board[Bx][By] = '.';
						By += 1;
					}
				}
				else
				{
					direction = 'n';
					break;
				}
			}
			break;
		default:
			break;
		}

		if (direction == 'n' || direction == 'o')
			break;
		// R이 더이상 갈 곳이 없으면 다시 방향을 선택
	}

	if (direction == 'n')
		count_ans = -1;

	std::cout << count_ans << endl;

	for (int n = 0; n < N; n++)
		delete[] board[n];
	delete[] board;
}