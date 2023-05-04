/* 2023-04-30
* baekjoon 12100
* 4X4 크기의 보드, 한번의 이동은 보드 위 전체 블록을 상하좌우 네 방향 중 하나로 이동
* 같은 값을 갖는 두 블록이 충돌하면 하나로 합쳐짐
* 한 번의 이동에서 이미 합쳐진 블록은 또 다른 불록과 다시 합쳐질 수 없음 (한 번의 이동에서는 꼭 2개만 합쳐지는듯)
* 똑같은 수 세개가 있는 경우엔 이동하려고 하는 쪽의 카이 먼저 합쳐짐
* (위로 이동시키면 위쪽에 있는 블록이 합쳐짐)
* 
* N X N크기가 주어졌을 때, 최대 5번 이동해서 만들 수 있는 가장 큰 블록의 값을 구하는 프로그램
* 0은 빈칸, 2 <= 주어지는 수(2의 제곱꼴) <= 1024
* 
* 예제)
* 3
* 2 2 2
* 4 4 4
* 8 8 8
* 
* 4 2 0
* 8 4 0
* 16 8 0
* 
* 2 0 0 0
* 8 0 0 0
* 16 8 16 0
* 2 16 4 0
* 
* 출력) 16
* 
* 채점해봤는데
* 채점 준비? -> 시작 -> 채점중() -> 바로 틀렸습니다 뜨는데 ㅋㅋㅋㅋㅋㅋ
* 아나 %도 안나오는건 처음이네..
* 근데 웬만한건 다 되는듯 얘 천재인가 싶음 ㄹㅇ
* 백준은 근데 예외처리를 다 해줘야 한대...
* 못해먹겠네....
* 
* 생각해보니까 1024들 합쳐도 돼서 vector에 10까지만 있으면 될 게 아니네
* 그리고 아무 방향이나 해도 상관없을 때 어떻게 할지도 문제고
* 거리가 1일때만 그 방향으로 return되게 해놨는데 왜 저렇게 많이 뜰 수 있는지도 의문...
* 생각보다 고쳐야할 게 많아서 이쯤에서 포기...
* 
* 2023-05-02
* 블록마다 4방향 중에 똑같은숫자가 있다면 그 방향으로 +1 count
* 0이 있으면 숫자가 나올때까지
* 그 후에 방향카운트가 가장 큰 방향으로 ㄱㄱ
* 만약 카운트가 같은 게 있다면 둘 중 랜덤?
* 
* 위와 같은 방식으로 다시 새로 만들어봤는데
* 또 입구컷당함 ㅋㅅㅋ..
* 반례도 사람들 것 중에
0 64 2 1024
2 512 8 0
0 32 512 256
64 64 8 2

이게 너무 강력했타
답은 2048.. 머리로 풀어도 어려움 ㄷㄷ
왼 - 위 - 왼 - 아래 - 왼(오)
*/

// 1. 0을 제외한 블록 중 같은 게 있으면 일단 같은 선상에 있도록 해야하나
// 2. 그런 다음에 합쳐지도록 (근데 가장 큰 블록의 값을 구하도록은 어떻게 하지)
// 합쳐서 망하는 경우도 있잖아 
// 경우의 수를 다 구해봐야할까..?
// 아니면 알고리즘을 생각해봐야할까(이게 맞겠지)
// 2-1. 합칠 때 합쳐질 수 있는 숫자가 많은 쪽으로 합쳐지기
// 2-2. (보통 두 가지 경우가 나올 텐데, 양쪽 다 되는 경우가 있어서)
//		빈칸이 있는 쪽...? 높은 수의 반대쪽..? 합쳐질 수가 가까운쪽? 
//		합쳐지고 나서 주위의 값과 합쳐질 수 없다면 그 반대쪽으로 밀기
// 
// 1-1. 같은 선상에 있도록 하는 방법?
//		좌표를 찍어서 같은 선상에 있는게 있다면 바로 2번으로 넘어가고,
//		그게 아니라면 2-2처럼?
// 아니면 그냥 미리 밀어보고 다음으로 합쳐질 수가 더 많은 곳으로

#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>

#define MAX_NUM 11
enum {
	UP, DOWN, LEFT, RIGHT
};

using namespace std;

struct coordinate{
	int y;
	int x; //배열 상 [y][x]기 때문에
};

struct DR {
	char dr = 'o';
	int delta = 0;
};

// (숫자가 있는 블록이라면) 왼쪽 방향으로 쭉 가보기
int UpCount(int** block, int N)
{
	int count = 0;
	// (숫자가 있는) 블록마다
	// 위 방향으로 쭉 가면서 숫자가 나오면
	// 그 숫자와 비교해서 같으면 count++
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			int current = block[i][j];
			for (int k = i - 1; k >= 0; k--)
			{
				if (block[k][j] == 0) // 0이라면 다음 블록으로
					continue;
				else if (block[k][j] > 0) // 숫자가 있다면
				{
					if (current == block[k][j]) // 그리고 그 숫자가 자신과 같은 숫자라면
						count++;
					break; // 이 블록은 끝
				}
			}
		}
	}

	return count;
}

int DownCount(int** block, int N)
{
	int count = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			int current = block[i][j];
			for (int k = i + 1; k < N; k++)
			{
				if (block[k][j] == 0) // 0이라면 다음 블록으로
					continue;
				else if (block[k][j] > 0) // 숫자가 있다면
				{
					if (current == block[k][j]) // 그리고 그 숫자가 자신과 같은 숫자라면
						count++;
					break; // 같은 숫자가 아니어도 이 블록은 끝
				}
			}
		}
	}
	return count;
}

int LeftCount(int** block, int N)
{
	int count = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			int current = block[i][j];
			for (int k = j - 1; k >= 0; k--)
			{
				if (block[i][k] == 0) // 0이라면 다음 블록으로
					continue;
				else if (block[i][k] > 0) // 숫자가 있다면
				{
					if (current == block[i][k]) // 그리고 그 숫자가 자신과 같은 숫자라면
						count++;
					break; // 같은 숫자가 아니어도 이 블록은 끝
				}
			}
		}
	}
	return count;
}

int RightCount(int** block, int N)
{
	int count = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			int current = block[i][j];
			for (int k = j + 1; k < N; k++)
			{
				if (block[i][k] == 0) // 0이라면 다음 블록으로
					continue;
				else if (block[i][k] > 0) // 숫자가 있다면
				{
					if (current == block[i][k]) // 그리고 그 숫자가 자신과 같은 숫자라면
						count++;
					break; // 같은 숫자가 아니어도 이 블록은 끝
				}
			}
		}
	}
	return count;
}

/*
DR direction(coordinate A, coordinate B)
{
	DR dr;

	int subX = abs(A.x - B.x); // 음수가 나올 걸 대비해서 절대값
	int subY = abs(A.y - B.y);

	if (subX == 1 || subY == 1)
	{
		if (subX > subY)
		{
			dr.dr = 'x';
			dr.delta = subX;
			return dr;
		}
		else if (subX < subY)
		{
			dr.dr = 'y';
			dr.delta = subY;
			return dr;
		}
	}
	return dr;
}

int divideBy2(int number)
{
	int count = 0;
	while (number > 1)
	{
		number /= 2;
		count++;
	}

	return count;
}

void make_vector(int** block, vector<coordinate>* number, int N)
{
	// 하기 전에 초기화
	for(int i = 0; i < MAX_NUM; i++)
		number[i].clear();

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			int current = block[i][j];
			// 현재 숫자를 2로 계속 나눠서 해당하는 위치에 좌표를 넣기
			// 4라면 2의 2승이니까 number[2]에 좌표를 넣게됨
			number[divideBy2(current)].push_back(coordinate{ i, j });
		}
	}
}

int decide_diretion(vector<coordinate>* number, int *countX, int *countY)
{
	// 혹시 모르니까 초기화
	*countX = 0;
	*countY = 0;
	//int sum = 0;

	// 0은 제외하고
	for (int i = 1; i < MAX_NUM; i++)
	{
		// 같은 수가 2개 이상이라면
		if (number[i].size() > 1)
		{
			// 좌표의 차를 구해서 더 큰쪽의 방향을 return해서 vector에 넣기
			// 좌표가 2개라면 차이가 1 1
			// 3개라면 3 2+1
			// 4개라면 A-B, A-C, A-D, B-C, B-D, C-D ==> 6 3+2+1
			for (int j = 0; j < number[i].size() - 1; j++)
			{
				for (int k = j + 1; k < number[i].size(); k++)
				{
					// 3
					// 0,1 0,2 1,2

					// 4
					// 0,1  0,2  0,3  1,2  1,3  2,3
					DR dr = direction(number[i].at(j), number[i].at(k));
					if (dr.dr == 'x')
					{
						(*countX)++;
						//sum += dr.delta;
					}
					else if (dr.dr == 'y')
					{
						(*countY)++;
						//sum += dr.delta;
					}
				}

			}
		}
	}

	return (*countX) + (*countY);
}

*/

void push_left(int** block, int N)
{
	vector<coordinate> updatedNumber;
	// 0,1				1,1				2,1				3,1
	// 0,2 0,1			1,2 1,1			2,2 2,1			3,2 3,1
	// 0,3 0,2 0,1 0,0	1,3 1,2 1,1 1,0	 2,3 2,2 2,1 2,0  3,3 3,2 3,1 3,0
	// 알아내기 겁나 힘드네...
	for (int i = 1; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			for (int k = i; k > 0; k--)
			{
				// 바꾸려는 곳이 0이라면 교환
				if (block[j][k - 1] == 0)
				{
					int temp = block[j][k - 1];
					block[j][k - 1] = block[j][k];
					block[j][k] = temp;
				}

				else if (block[j][k - 1] == block[j][k])
				{
					bool flag = false;
					// 같은 경우라면 합쳐야 하는데,
					// 이미 합쳐진 경우면 pass
					for (coordinate& un : updatedNumber)
					{
						if ((un.y == j && un.x == k - 1) || (un.y == j && un.x == k))
						{
							flag = true;
							break;
						}
					}
					if (flag == true)
						continue;

					block[j][k - 1] += block[j][k];
					block[j][k] = 0;
					updatedNumber.push_back(coordinate{ j, k - 1 });
					//updatedNumber.push_back(coordinate{ j, k });
				}
			}

		}
	}
	updatedNumber.clear();
	//delete &updatedNumber;
}

void push_right(int** block, int N)
{
	vector<coordinate> updatedNumber;
	// 0,3 1,3 2,3 3,3
	// 0,2 0,3 1,2 1,3 2,2 2,3 3,2 3,3
	for (int i = N - 1; i > 0; i--)
	{
		for (int j = 0; j < N; j++)
		{
			for (int k = i - 1; k < N - 1; k++)
			{
				// 바꾸려는 곳이 0이라면 교환
				if (block[j][k + 1] == 0)
				{
					int temp = block[j][k + 1];
					block[j][k + 1] = block[j][k];
					block[j][k] = temp;
				}

				else if (block[j][k + 1] == block[j][k])
				{
					bool flag = false;
					for (coordinate& un : updatedNumber)
					{
						if ((un.y == j && un.x == k + 1) || (un.y == j && un.x == k))
						{
							flag = true;
							break;
						}
					}
					if (flag == true)
						continue;

					block[j][k + 1] += block[j][k];
					block[j][k] = 0;
					updatedNumber.push_back(coordinate{ j, k + 1 });
					//updatedNumber.push_back(coordinate{ j, k });
				}
			}
		}
	}
	updatedNumber.clear();
}

void push_up(int** block, int N)
{
	vector<coordinate> updatedNumber;
	// 1,0 1,1 1,2 1,3
	// 2,0 1,0  2,1 1,1  2,2 1,2  2,3 1,3
	for (int i = 1; i < N; i++)
	{
		for (int k = i; k > 0; k--)
		{
			for (int j = 0; j < N; j++)
			{
				// 바꾸려는 곳이 0이라면 교환
				if (block[k - 1][j] == 0)
				{
					// 4
					// 4
					// 8
					// 8
					// 일 경우에 8로 합쳐졌는데 뒤에 바로 8이랑 합쳐져서 16이 됨...
					// ==> 이미 합쳐진 좌표면 제외하는걸 넣어야하나
					// 이미 합쳐진 좌표면 vector에 넣고 foreach문으로 넣고 더이상 안합쳐지게,
					// 0인 경우를 따로 만들자
					int temp = block[k - 1][j];
					block[k - 1][j] = block[k][j];
					block[k][j] = temp;
				}

				else if (block[k - 1][j] == block[k][j])
				{
					bool flag = false;
					// 같은 경우라면 합쳐야 하는데,
					// 이미 합쳐진 경우면 pass
					for (coordinate& un : updatedNumber)
					{
						// 합치려는 곳이 un에 포함되어있는 좌표라면
						if ((un.y == k - 1 && un.x == j) || (un.y == j && un.x == k))
						{
							flag = true;
							break;
						}
						// 여기다 continue를 썼더니 foreach문을 다시 돌아서...
						// 어쩔수없이 플래그 사용
					}
					if (flag == true)
						continue;

					block[k - 1][j] += block[k][j];
					block[k][j] = 0;
					updatedNumber.push_back(coordinate{ k - 1, j });
					//updatedNumber.push_back(coordinate{ k, j });
				}
			}
		}
	}
	updatedNumber.clear();
}

void push_down(int** block, int N)
{
	vector<coordinate> updatedNumber;
	// 3,0 3,1 3,2 3,3
	// 2,0 3,0  2,1 3,1  2,2 3,2  2,3 3,3
	for (int i = N - 1; i > 0; i--)
	{
		for (int j = 0; j < N; j++)
		{
			for (int k = i - 1; k < N - 1; k++)
			{
				if (block[k + 1][j] == 0)
				{
					int temp = block[k + 1][j];
					block[k + 1][j] = block[k][j];
					block[k][j] = temp;
				}

				else if (block[k + 1][j] == block[k][j])
				{
					bool flag = false;
					for (coordinate& un : updatedNumber)
					{
						if ((un.y == k + 1 && un.x == j) || (un.y == j && un.x == k))
						{
							flag = true;
							break;
						}
					}
					if (flag == true)
						continue;

					block[k + 1][j] += block[k][j];
					block[k][j] = 0;
					updatedNumber.push_back(coordinate{ k + 1, j });
					//updatedNumber.push_back(coordinate{ k, j });
				}
			}
		}
	}
	updatedNumber.clear();
}


void InitBlock(int N, int** block, int** block_copy, int* futureCount) //, vector<coordinate>* number, int* countX, int* countY)
{
	// number init
	//for (int i = 0; i < MAX_NUM; i++)
	//	number[i].clear();

	// block init
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			block_copy[i][j] = block[i][j];
	}

	for (int i = 0; i < 4; i++)
	{
		futureCount[i] = 0;
	}

	//// X, Y init
	//*countX = 0;
	//*countY = 0;
}

int MaxFutureCount(int** block, int N, int futureCount[])
{
	futureCount[UP] = UpCount(block, N);// *2;
	futureCount[DOWN] = DownCount(block, N);// *2;
	futureCount[LEFT] = LeftCount(block, N);// *2;
	futureCount[RIGHT] = RightCount(block, N);// *2;

	int max = 0;
	for (int i = 0; i < 4; i++)
	{
		if (max <= futureCount[i])
			max = futureCount[i];
	}
	return max;
}

/*int main() {
	// 결과 값
	int maxNumber_ans = 0;

	// 일단 배열 만들기
	int N = 0;
	cin >> N;
	if (N < 1 || N > 20)
		return 0;

	int** block = new int*[N];
	for (int i = 0; i < N; i++)
		block[i] = new int[N];

	// 입력값 받기
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			int input = 0;
			cin >> input;
			if ((input != 0 && input < 2) || (input > 1024) || (input % 2 == 1))
				return 0;
			block[i][j] = input;
		}
	}

	// block의 복사본 만들기
	int** block_copy = new int* [N];
	for (int i = 0; i < N; i++)
		block_copy[i] = new int[N];


	int counts[4] = { 0, };

	// 랜덤 시드
	srand(time(NULL));

	for (int n = 0; n < 5; n++)
	{
		// 미래의 방향도 생각할 플래그
		//bool futureFlag = true;
		// 방향별로 count를 재서
		counts[UP] = UpCount(block, N);
		counts[DOWN] = DownCount(block, N);
		counts[LEFT] = LeftCount(block, N);
		counts[RIGHT] = RightCount(block, N);

		//for (int i = 0; i < 4; i++)
		//{
		//	if (counts[i] > 0)
		//		futureFlag = false;
		//}

		// 미래의 방향을 생각한다면 count 갱신
		// 근데 이렇게 하니까
		// 네 방향으로 움직였다고 가정한 뒤, count를 세려면
		// 방향마다 네 방향으로 움직인 count를 세야되네
		// 그 중에서도 가장 큰 count가 나온 애를 걔의 count로 써야하네
		// ....16번?
		int futureCount[4] = { 0, };
		//if (futureFlag == true)
		//{
			InitBlock(N, block, block_copy, futureCount);
			//UP
			push_up(block_copy, N);
			counts[UP]  += MaxFutureCount(block_copy, N, futureCount);

			//DOWN
			InitBlock(N, block, block_copy, futureCount);
			push_down(block_copy, N);
			counts[DOWN] += MaxFutureCount(block_copy, N, futureCount);

			//LEFT
			InitBlock(N, block, block_copy, futureCount);
			push_left(block_copy, N);
			counts[LEFT] += MaxFutureCount(block_copy, N, futureCount);

			//RIGHT
			InitBlock(N, block, block_copy, futureCount);
			push_right(block_copy, N);
			counts[RIGHT] += MaxFutureCount(block_copy, N, futureCount);
		//}


		// 근데 이렇게하니까
		// 오른쪽으로 간 뒤에 알 수 있는 방향은 생각못하니까
		// 미래의 count를 재야하나
		// 
		// 미래의 count재기..
		// 우선 block의 복사본을 만든 다음에
		// 그 복사본을 이리저리 움직여보고
		// 그러고 난 뒤의 count를 재기
		// 어차피 init할거면

		// 근데 이렇게 하니까
		// 위, 아래 랜덤으로 나와서
		// 위로 가야 다음께 좋은데
		// 그럼 +=을 해서 구하자
		// 위로 가야 다음 거 할게 나오는데
		// 근데 그럼 1번 옮겨서 다음에 할게 없는거랑
		// 1번 옮겨서 다음에 할게 하나 있는거랑 똑같이 나오자나
		// 그럼 다음에 할 게 있는게 우선적으로 뽑히게 해야하나;;;;
		// 그럼 미래카운트가 2배의 가중치를 갖도록 하자
		

		// 이렇게하니까
		// 현재 합쳐서 게임을 끝낼 수 있는데 합치면 count가 0이 되니까
		// 합치지 않는 방향으로 push하네
		// 흠....
		// 현재 count도 다 구해서 그게 모두 0이면 미래의 것으로?
		// 
		
		// 왼쪽으로 틀어본 다음에


		// 가장 높은 방향으로 밀기
		// 근데 count가 서로 같은게 있다면 그들 중에서 랜덤하게 나오기
		vector<int> equalCountIdxs;
		int maxCountIdx = UP;
		for (int i = 1; i < 4; i++)
		{
			// 근데 2 2 3 4 이런식으로 있다면?
			// max를 구한 다음에 비교를 해야겠네
			if (counts[maxCountIdx] < counts[i])
				maxCountIdx = i;
		}

		for (int i = 0; i < 4; i++)
		{
			if (counts[maxCountIdx] == counts[i])
			{
				equalCountIdxs.push_back(i);
			}
		}

		if (equalCountIdxs.size() > 0)
		{
			maxCountIdx = equalCountIdxs.at(rand() % equalCountIdxs.size()); // 0부터 size-1 만큼
		}

		// 최종 maxCountIdx로 나온 방향으로 push
		switch (maxCountIdx)
		{
		case UP:
			push_up(block, N);
			break;
		case DOWN:
			push_down(block, N);
			break;
		case LEFT:
			push_left(block, N);
			break;
		case RIGHT:
			push_right(block, N);
			break;
		default:
			break;
		}

		////결과 보기
		//for (int i = 0; i < N; i++)
		//{
		//	for (int j = 0; j < N; j++)
		//		std::cout << block[i][j] << "\t";
		//	std::cout << endl;
		//}
		//std::cout << endl;
	}

	// 블록들 중에서 가장 큰 숫자를 출력
	int max = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (max < block[i][j])
				max = block[i][j];
		}
	}

	if (max < 2)
		max = 2;

	std::cout << max;

	
	/*
	vector<coordinate> number[MAX_NUM];

	// 총 5번 반복
	for (int n = 0; n < 5; n++)
	{
		vector<coordinate> number_copy[MAX_NUM];
		int countX_copy = 0;
		int countY_copy = 0;

		int** block_copy = new int* [N];
		for (int i = 0; i < N; i++)
			block_copy[i] = new int[N];

		enum {
			UP, DOWN, LEFT, RIGHT
		};

		int countDirection[4] = { 0, };
		// block, number를 복사 및 count들 초기화
		init(N, block, block_copy, number_copy, &countX_copy, &countY_copy);

		// 왼쪽
		push_left(block_copy, N);
		// 이 다음에 count 더해보기..?
		make_vector(block_copy, number_copy, N);
		countDirection[LEFT] = decide_diretion(number_copy, &countX_copy, &countY_copy);
		//for (int i = 0; i < N; i++)
		//{
		//	for (int j = 0; j < N; j++)
		//		cout << block_copy[i][j] << "\t";
		//	cout << endl;
		//}
		//cout << endl;


		// 오른쪽(하기 전에 block_copy부터 원상태로
		init(N, block, block_copy, number_copy, &countX_copy, &countY_copy);

		// 오른쪽
		push_right(block_copy, N);
		make_vector(block_copy, number_copy, N);
		countDirection[RIGHT] = decide_diretion(number_copy, &countX_copy, &countY_copy);
		//for (int i = 0; i < N; i++)
		//{
		//	for (int j = 0; j < N; j++)
		//		cout << block_copy[i][j] << "\t";
		//	cout << endl;
		//}
		//cout << endl;


		// 위쪽
		init(N, block, block_copy, number_copy, &countX_copy, &countY_copy);
		push_up(block_copy, N);
		// 이 다음에 count 더해보기..?
		make_vector(block_copy, number_copy, N);
		countDirection[UP] = decide_diretion(number_copy, &countX_copy, &countY_copy);
		//for (int i = 0; i < N; i++)
		//{
		//	for (int j = 0; j < N; j++)
		//		cout << block_copy[i][j] << "\t";
		//	cout << endl;
		//}
		//cout << endl;


		// 아래쪽
		init(N, block, block_copy, number_copy, &countX_copy, &countY_copy);
		push_down(block_copy, N);
		make_vector(block_copy, number_copy, N);
		countDirection[DOWN] = decide_diretion(number_copy, &countX_copy, &countY_copy);
		//for (int i = 0; i < N; i++)
		//{
		//	for (int j = 0; j < N; j++)
		//		cout << block_copy[i][j] << "\t";
		//	cout << endl;
		//}
		//cout << endl;

		// 가장 큰 값을 찾아서 그 방향으로 실제 움직이기
		vector<int> maxDirection;
		int maxIdx = 0;
		for (int i = 1; i < 4; i++)
		{
			if (countDirection[maxIdx] == countDirection[i])
			{
				maxDirection.push_back(maxIdx);
				maxDirection.push_back(i);
			}


			else if (countDirection[maxIdx] < countDirection[i])
				maxIdx = i;

		}
		// 난수 생성
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int> dis(0, maxDirection.size() - 1);

		if (maxDirection.size() > 0)
		{
			// 0부터 size -1 만큼까지
			maxIdx = maxDirection.at(dis(gen));
		}

		// maxIdx랑 같은 애는 하나는 꼭 있고,
		// 다음으로 같은 애가 있으면 미ㅓㄹ이마ㅓ미ㅏ머ㅣㅏ

		// 만약 가야할 방향이 다 같이 나온다면
		// 0이 더 많은 쪽으로 가기
		// 그래도 모르겠다면 랜덤..?ㅋㅋㅋㅋㅋㅋㅋ
		// 랜덤? 좋을지도

		switch (maxIdx)
		{
		case UP :
			push_up(block, N);
			break;

		case DOWN :
			push_down(block, N);
			break;

		case LEFT :
			push_left(block, N);
			break;

		case RIGHT :
			push_right(block, N);
			break;

		default:
			break;
		}

		 //결과 보기
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
				cout << block[i][j] << "\t";
			cout << endl;
		}
		cout << endl;

		for (int n = 0; n < N; n++)
			delete[] block_copy[n];
		delete[] block_copy;

	//	// 1. 같은 숫자가 어디에 있는지 확인하기
	//	// 숫자마다 개수랑 위치를 적기엔 좀 그런가 1024까지 10개..? 괜찮을지도..?
	//	// 위 방법이 괜찮으려나
	//	// struct로 좌표를 만들어서 그걸 vector안에 넣어서 배열로 10개 관리...
	//	make_vector(block, number, N);
	//	// vector안에 같은수(개수)가 2개 이상인 애들을 대상으로,
	//	// x좌표, y좌표끼리 빼서 더 큰 쪽의 방향으로 밀기
	//	// (y끼리 뺐는데 0이라면 가로에 있는 애들이 같은 선상에 있다는 얘기, 좌우(x쪽)로 밀어야함)
	//	// 아니지, 다른 애들 상태도 봐야하는데
	//	// 좌표 빼서 0인 애들이 많은 방향으로 밀기
	//	// 양쪽 중에 둘다 해보고? 다음에 할 일이 많은 쪽으로 밀기...

	//	// 음...
	//	// 근데 같은 수가 3개 이상일땐 차이도 3개가 나와야할텐디
	//	// 으아아아아아아아ㅓㅁㅇ리ㅏㅁ어 ㅁ이ㅏㅓㅁ이ㅏㅇㄴ머ㅏㅣㅁㅇ
	//	// 그럼 빼서 더 큰쪽으로 방향을 정해서 return, 그 방향이 더 많은 쪽으로 밀기

	//	// 좌표 차에 따라 count
	//	int countX = 0;
	//	int countY = 0;
	//	decide_diretion(number, &countX, &countY);
	//	// 이렇게하니까 4242는 못하는데도 countX +2가 돼버리네
	//	// 그냥 붙어있는게 있으면 1순위로 바꾸기 이런거 해야할 것 같은데
	//	// 이렇게 된이상 그냥 4방향 다해보고 좋은걸로 할까..?(이게 진짜 좋은방법일수도 ㅋㅋ)
	//	// 근데 그게 알고리즘이 맞나...?

	//	// direction_X, Y에 담긴 숫자를 비교해서 더 많은 쪽의 방향으로 밀기,
	//	// x라면 그 중에서도 왼쪽, 오른쪽 둘 다 밀어보고 다음에 할일이 더 많은 쪽으로 밀건데...
	//	// 이게 되나? 미는 것도 문제같은데 ㅋㅋㅋ
	//	// 뭐 해보면 알겠징...

	//	// 역시 근데 둘다 해보는건 좀 그런듯
	//	// 아닌가 ㅁ?ㄹ
	//	// 일단 한번만 해보는 걸로 할까...
	//	// 근데 그러면 합쳐질 수, 합쳐지고 난 수, 합쳐지고 난 수와 같은 수의 위치, 다른 수의 위치를 모두 알고 있어야 할 것 같은뎅
	//	//int** block_copy = block; //이게 되나? 생각해보니까 포인터라 그냥 참조하는 거네 ㅋㅋ
	//	int** block_copy = new int* [N];
	//	for (int i = 0; i < N; i++)
	//		block_copy[i] = new int[N];

	//	// 입력값 받기
	//	for (int i = 0; i < N; i++)
	//	{
	//		for (int j = 0; j < N; j++)
	//			block_copy[i][j] = block[i][j];
	//	}

	//	//int** block_copy2 = block; // 메모리 제한에서 걸리면 어떡하지 ㅋㅋㅋㅋㅋㅋㅋㅋ
	//	int** block_copy2 = new int* [N];
	//	for (int i = 0; i < N; i++)
	//		block_copy2[i] = new int[N];

	//	// 입력값 받기
	//	for (int i = 0; i < N; i++)
	//	{
	//		for (int j = 0; j < N; j++)
	//			block_copy2[i][j] = block[i][j];
	//	}

	//	vector<coordinate> number_copy[MAX_NUM];
	//	int countX_copy = 0;
	//	int countY_copy = 0;

	//	if (countX > countY)
	//	{
	//		// 왼쪽
	//		push_left(block_copy, N);
	//		// 이 다음에 count 더해보기..?
	//		make_vector(block_copy, number_copy, N);
	//		int leftCount = decide_diretion(number_copy, &countX_copy, &countY_copy);

	//		// 오른쪽
	//		push_right(block_copy2, N);
	//		make_vector(block_copy2, number_copy, N);
	//		int rightCount = decide_diretion(number_copy, &countX_copy, &countY_copy);


	//		// 둘이 비교해서 이후에 할 게 더 많은 쪽?으로 옮기기
	//		// 거리가 더 가까운 쪽을 먼저하기
	//		if (leftCount < rightCount)
	//			push_left(block, N); // 찐으로 옮기기
	//		else
	//			push_right(block, N);

	//		// 결과 보기
	//		for (int i = 0; i < N; i++)
	//		{
	//			for (int j = 0; j < N; j++)
	//				cout << block[i][j] << "\t";
	//			cout << endl;
	//		}
	//		cout << endl;
	//	}
	//	else
	//	{
	//		// 위쪽
	//		push_up(block_copy, N);
	//		// 이 다음에 count 더해보기..?
	//		make_vector(block_copy, number_copy, N);
	//		int upCount = decide_diretion(number_copy, &countX_copy, &countY_copy);

	//		// 오른쪽
	//		push_down(block_copy2, N);
	//		make_vector(block_copy2, number_copy, N);
	//		int downCount = decide_diretion(number_copy, &countX_copy, &countY_copy);


	//		// 둘이 비교해서 이후에 할 게 더 많은 쪽?으로 옮기기
	//		if (upCount < downCount)
	//			push_up(block, N); // 찐으로 옮기기
	//		else
	//			push_down(block, N);

	//		 //결과 보기
	//		for (int i = 0; i < N; i++)
	//		{
	//			for (int j = 0; j < N; j++)
	//				cout << block[i][j] << "\t";
	//			cout << endl;
	//		}
	//		cout << endl;
	//	}

	//	for (int n = 0; n < N; n++)
	//		delete[] block_copy[n];
	//	delete[] block_copy;
	//	for (int n = 0; n < N; n++)
	//		delete[] block_copy2[n];
	//	delete[] block_copy2;
	}

	// 반복이 끝난 후
	// block에서 가장 큰 값을 가져오기
	// block을 for 2번으로 가져오든,
	// vector를 또 만들어서 가져오든?
	make_vector(block, number, N);

	int max = 0;
	for (int i = MAX_NUM - 1; i > 0; i--)
	{
		if (number[i].size() > 0)
		{
			max = pow(2, i);
			break;
		}
	}

	if (max < 2)
		max = 2;

	cout << max;
	

	for (int n = 0; n < N; n++)
		delete[] block[n];
	delete[] block;
	return 0;
}
*/

