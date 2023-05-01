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

#define MAX_NUM 11

using namespace std;

struct coordinate{
	int y;
	int x; //배열 상 [y][x]기 때문에
};

char direction(coordinate A, coordinate B)
{
	int subX = abs(A.x - B.x); // 음수가 나올 걸 대비해서 절대값
	int subY = abs(A.y - B.y);
	if (subX > subY)
		return 'x';
	else if (subX < subY)
		return 'y';
	else
		return 'o';
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
					char d = direction(number[i].at(j), number[i].at(k));
					if (d == 'x')
						(*countX)++;
					else if(d == 'y')
						(*countY)++;
				}

			}
		}
	}

	return (*countX) + (*countY);
}

void push_left(int** block, int N)
{
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
				if (block[j][k - 1] == block[j][k] || block[j][k - 1] == 0)
				{
					block[j][k - 1] += block[j][k];
					block[j][k] = 0;
				}
			}

		}
	}
}

void push_right(int** block, int N)
{
	// 0,3 1,3 2,3 3,3
	// 0,2 0,3 1,2 1,3 2,2 2,3 3,2 3,3
	for (int i = N - 1; i > 0; i--)
	{
		for (int j = 0; j < N; j++)
		{
			for (int k = i; k < N; k++)
			{
				if (block[j][k] == block[j][k - 1] || block[j][k] == 0)
				{
					block[j][k] += block[j][k - 1];
					block[j][k - 1] = 0;
				}
			}
		}
	}
}

void push_up(int** block, int N)
{
	// 1,0 1,1 1,2 1,3
	// 2,0 1,0  2,1 1,1  2,2 1,2  2,3 1,3
	for (int i = 1; i < N; i++)
	{
		for (int k = i; k > 0; k--)
		{
			for (int j = 0; j < N; j++)
			{
				if (block[k - 1][j] == block[k][j] || block[k - 1][j] == 0)
				{
					// 4
					// 4
					// 8
					// 8
					// 일 경우에 8로 합쳐졌는데 뒤에 바로 8이랑 합쳐져서 16이 됨...
					// ==> 이미 합쳐진 좌표면 제외하는걸 넣어야하나
					block[k - 1][j] += block[k][j];
					block[k][j] = 0;
				}
			}
		}
	}
}

void push_down(int** block, int N)
{
	// 3,0 3,1 3,2 3,3
	// 2,0 3,0  2,1 3,1  2,2 3,2  2,3 3,3
	for (int i = N - 1; i > 0; i--)
	{
		for (int j = 0; j < N; j++)
		{
			for (int k = i; k < N; k++)
			{
				if (block[k][j] == block[k - 1][j] || block[k][j] == 0)
				{
					block[k][j] += block[k - 1][j];
					block[k - 1][j] = 0;
				}
			}
		}
	}
}

int main() {
	// 결과 값
	int maxNumber_ans = 0;

	// 일단 배열 만들기
	int N = 0;
	cin >> N;

	int** block = new int*[N];
	for (int i = 0; i < N; i++)
		block[i] = new int[N];

	// 입력값 받기
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			cin >> block[i][j];
	}

	vector<coordinate> number[MAX_NUM];
	// 총 5번 반복
	for (int n = 0; n < 5; n++)
	{
		// 1. 같은 숫자가 어디에 있는지 확인하기
		// 숫자마다 개수랑 위치를 적기엔 좀 그런가 1024까지 10개..? 괜찮을지도..?
		// 위 방법이 괜찮으려나
		// struct로 좌표를 만들어서 그걸 vector안에 넣어서 배열로 10개 관리...
		make_vector(block, number, N);
		// vector안에 같은수(개수)가 2개 이상인 애들을 대상으로,
		// x좌표, y좌표끼리 빼서 더 큰 쪽의 방향으로 밀기
		// (y끼리 뺐는데 0이라면 가로에 있는 애들이 같은 선상에 있다는 얘기, 좌우(x쪽)로 밀어야함)
		// 아니지, 다른 애들 상태도 봐야하는데
		// 좌표 빼서 0인 애들이 많은 방향으로 밀기
		// 양쪽 중에 둘다 해보고? 다음에 할 일이 많은 쪽으로 밀기...

		// 음...
		// 근데 같은 수가 3개 이상일땐 차이도 3개가 나와야할텐디
		// 으아아아아아아아ㅓㅁㅇ리ㅏㅁ어 ㅁ이ㅏㅓㅁ이ㅏㅇㄴ머ㅏㅣㅁㅇ
		// 그럼 빼서 더 큰쪽으로 방향을 정해서 return, 그 방향이 더 많은 쪽으로 밀기

		// 좌표 차에 따라 count
		int countX = 0;
		int countY = 0;
		decide_diretion(number, &countX, &countY);

		// direction_X, Y에 담긴 숫자를 비교해서 더 많은 쪽의 방향으로 밀기,
		// x라면 그 중에서도 왼쪽, 오른쪽 둘 다 밀어보고 다음에 할일이 더 많은 쪽으로 밀건데...
		// 이게 되나? 미는 것도 문제같은데 ㅋㅋㅋ
		// 뭐 해보면 알겠징...

		// 역시 근데 둘다 해보는건 좀 그런듯
		// 아닌가 ㅁ?ㄹ
		// 일단 한번만 해보는 걸로 할까...
		// 근데 그러면 합쳐질 수, 합쳐지고 난 수, 합쳐지고 난 수와 같은 수의 위치, 다른 수의 위치를 모두 알고 있어야 할 것 같은뎅
		//int** block_copy = block; //이게 되나? 생각해보니까 포인터라 그냥 참조하는 거네 ㅋㅋ
		int** block_copy = new int* [N];
		for (int i = 0; i < N; i++)
			block_copy[i] = new int[N];

		// 입력값 받기
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
				block_copy[i][j] = block[i][j];
		}

		//int** block_copy2 = block; // 메모리 제한에서 걸리면 어떡하지 ㅋㅋㅋㅋㅋㅋㅋㅋ
		int** block_copy2 = new int* [N];
		for (int i = 0; i < N; i++)
			block_copy2[i] = new int[N];

		// 입력값 받기
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
				block_copy2[i][j] = block[i][j];
		}

		vector<coordinate> number_copy[MAX_NUM];
		int countX_copy = 0;
		int countY_copy = 0;

		if (countX > countY)
		{
			// 왼쪽
			push_left(block_copy, N);
			// 이 다음에 count 더해보기..?
			make_vector(block_copy, number_copy, N);
			int leftCount = decide_diretion(number_copy, &countX_copy, &countY_copy);

			// 오른쪽
			push_right(block_copy2, N);
			make_vector(block_copy2, number_copy, N);
			int rightCount = decide_diretion(number_copy, &countX_copy, &countY_copy);


			// 둘이 비교해서 이후에 할 게 더 많은 쪽?으로 옮기기
			if (leftCount > rightCount)
				push_left(block, N); // 찐으로 옮기기
			else
				push_right(block, N);

			// 결과 보기
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
					cout << block[i][j] << "\t";
				cout << endl;
			}
			cout << endl;
		}
		else
		{
			// 위쪽
			push_up(block_copy, N);
			// 이 다음에 count 더해보기..?
			make_vector(block_copy, number_copy, N);
			int upCount = decide_diretion(number_copy, &countX_copy, &countY_copy);

			// 오른쪽
			push_down(block_copy2, N);
			make_vector(block_copy2, number_copy, N);
			int downCount = decide_diretion(number_copy, &countX_copy, &countY_copy);


			// 둘이 비교해서 이후에 할 게 더 많은 쪽?으로 옮기기
			if (upCount > downCount)
				push_up(block, N); // 찐으로 옮기기
			else
				push_down(block, N);

			// 결과 보기
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
					cout << block[i][j] << "\t";
				cout << endl;
			}
			cout << endl;
		}

		for (int n = 0; n < N; n++)
			delete[] block_copy[n];
		delete[] block_copy;
		for (int n = 0; n < N; n++)
			delete[] block_copy2[n];
		delete[] block_copy2;
	}

	// 반복이 끝난 후
	// block에서 가장 큰 값을 가져오기
	// block을 for 2번으로 가져오든,
	// vector를 또 만들어서 가져오든?
	make_vector(block, number, N);
	for (int i = MAX_NUM - 1; i >= 0; i--)
	{
		if (number[i].size() > 0)
		{
			cout << pow(2, i);
			break;
		}
	}

	for (int n = 0; n < N; n++)
		delete[] block[n];
	delete[] block;
	return 0;
}

