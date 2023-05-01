/* 2023-04-30
* baekjoon 12100
* 4X4 ũ���� ����, �ѹ��� �̵��� ���� �� ��ü ����� �����¿� �� ���� �� �ϳ��� �̵�
* ���� ���� ���� �� ����� �浹�ϸ� �ϳ��� ������
* �� ���� �̵����� �̹� ������ ����� �� �ٸ� �ҷϰ� �ٽ� ������ �� ���� (�� ���� �̵������� �� 2���� �������µ�)
* �Ȱ��� �� ������ �ִ� ��쿣 �̵��Ϸ��� �ϴ� ���� ī�� ���� ������
* (���� �̵���Ű�� ���ʿ� �ִ� ����� ������)
* 
* N X Nũ�Ⱑ �־����� ��, �ִ� 5�� �̵��ؼ� ���� �� �ִ� ���� ū ����� ���� ���ϴ� ���α׷�
* 0�� ��ĭ, 2 <= �־����� ��(2�� ������) <= 1024
* 
* ����)
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
* ���) 16
* 
* ä���غôµ�
* ä�� �غ�? -> ���� -> ä����() -> �ٷ� Ʋ�Ƚ��ϴ� �ߴµ� ������������
* �Ƴ� %�� �ȳ����°� ó���̳�..
* �ٵ� �����Ѱ� �� �Ǵµ� �� õ���ΰ� ���� ����
* ������ �ٵ� ����ó���� �� ����� �Ѵ�...
* ���ظ԰ڳ�....
* 
* �����غ��ϱ� 1024�� ���ĵ� �ż� vector�� 10������ ������ �� �� �ƴϳ�
* �׸��� �ƹ� �����̳� �ص� ������� �� ��� ������ ������
* �Ÿ��� 1�϶��� �� �������� return�ǰ� �س��µ� �� ������ ���� �� �� �ִ����� �ǹ�...
* �������� ���ľ��� �� ���Ƽ� ���뿡�� ����...
*/

// 1. 0�� ������ ��� �� ���� �� ������ �ϴ� ���� ���� �ֵ��� �ؾ��ϳ�
// 2. �׷� ������ ���������� (�ٵ� ���� ū ����� ���� ���ϵ����� ��� ����)
// ���ļ� ���ϴ� ��쵵 ���ݾ� 
// ����� ���� �� ���غ����ұ�..?
// �ƴϸ� �˰����� �����غ����ұ�(�̰� �°���)
// 2-1. ��ĥ �� ������ �� �ִ� ���ڰ� ���� ������ ��������
// 2-2. (���� �� ���� ��찡 ���� �ٵ�, ���� �� �Ǵ� ��찡 �־)
//		��ĭ�� �ִ� ��...? ���� ���� �ݴ���..? ������ ���� �������? 
//		�������� ���� ������ ���� ������ �� ���ٸ� �� �ݴ������� �б�
// 
// 1-1. ���� ���� �ֵ��� �ϴ� ���?
//		��ǥ�� �� ���� ���� �ִ°� �ִٸ� �ٷ� 2������ �Ѿ��,
//		�װ� �ƴ϶�� 2-2ó��?
// �ƴϸ� �׳� �̸� �о�� �������� ������ ���� �� ���� ������

#include <iostream>
#include <vector>
#include <cmath>
#include <random>

#define MAX_NUM 11

using namespace std;

struct coordinate{
	int y;
	int x; //�迭 �� [y][x]�� ������
};

struct DR {
	char dr = 'o';
	int delta = 0;
};

DR direction(coordinate A, coordinate B)
{
	DR dr;

	int subX = abs(A.x - B.x); // ������ ���� �� ����ؼ� ���밪
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
	// �ϱ� ���� �ʱ�ȭ
	for(int i = 0; i < MAX_NUM; i++)
		number[i].clear();

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			int current = block[i][j];
			// ���� ���ڸ� 2�� ��� ������ �ش��ϴ� ��ġ�� ��ǥ�� �ֱ�
			// 4��� 2�� 2���̴ϱ� number[2]�� ��ǥ�� �ְԵ�
			number[divideBy2(current)].push_back(coordinate{ i, j });
		}
	}
}

int decide_diretion(vector<coordinate>* number, int *countX, int *countY)
{
	// Ȥ�� �𸣴ϱ� �ʱ�ȭ
	*countX = 0;
	*countY = 0;
	//int sum = 0;

	// 0�� �����ϰ�
	for (int i = 1; i < MAX_NUM; i++)
	{
		// ���� ���� 2�� �̻��̶��
		if (number[i].size() > 1)
		{
			// ��ǥ�� ���� ���ؼ� �� ū���� ������ return�ؼ� vector�� �ֱ�
			// ��ǥ�� 2����� ���̰� 1 1
			// 3����� 3 2+1
			// 4����� A-B, A-C, A-D, B-C, B-D, C-D ==> 6 3+2+1
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

void push_left(int** block, int N)
{
	vector<coordinate> updatedNumber;
	// 0,1				1,1				2,1				3,1
	// 0,2 0,1			1,2 1,1			2,2 2,1			3,2 3,1
	// 0,3 0,2 0,1 0,0	1,3 1,2 1,1 1,0	 2,3 2,2 2,1 2,0  3,3 3,2 3,1 3,0
	// �˾Ƴ��� �̳� �����...
	for (int i = 1; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			for (int k = i; k > 0; k--)
			{
				// �ٲٷ��� ���� 0�̶�� ��ȯ
				if (block[j][k - 1] == 0)
				{
					int temp = block[j][k - 1];
					block[j][k - 1] = block[j][k];
					block[j][k] = temp;
				}

				else if (block[j][k - 1] == block[j][k])
				{
					bool flag = false;
					// ���� ����� ���ľ� �ϴµ�,
					// �̹� ������ ���� pass
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
				// �ٲٷ��� ���� 0�̶�� ��ȯ
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
				// �ٲٷ��� ���� 0�̶�� ��ȯ
				if (block[k - 1][j] == 0)
				{
					// 4
					// 4
					// 8
					// 8
					// �� ��쿡 8�� �������µ� �ڿ� �ٷ� 8�̶� �������� 16�� ��...
					// ==> �̹� ������ ��ǥ�� �����ϴ°� �־���ϳ�
					// �̹� ������ ��ǥ�� vector�� �ְ� foreach������ �ְ� ���̻� ����������,
					// 0�� ��츦 ���� ������
					int temp = block[k - 1][j];
					block[k - 1][j] = block[k][j];
					block[k][j] = temp;
				}

				else if (block[k - 1][j] == block[k][j])
				{
					bool flag = false;
					// ���� ����� ���ľ� �ϴµ�,
					// �̹� ������ ���� pass
					for (coordinate& un : updatedNumber)
					{
						// ��ġ���� ���� un�� ���ԵǾ��ִ� ��ǥ���
						if ((un.y == k - 1 && un.x == j) || (un.y == j && un.x == k))
						{
							flag = true;
							break;
						}
						// ����� continue�� ����� foreach���� �ٽ� ���Ƽ�...
						// ��¿������ �÷��� ���
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

void init(int N, int** block, int** block_copy, vector<coordinate>* number, int* countX, int* countY)
{
	// number init
	for (int i = 0; i < MAX_NUM; i++)
		number[i].clear();

	// block init
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			block_copy[i][j] = block[i][j];
	}

	// X, Y init
	*countX = 0;
	*countY = 0;
}

int main() {
	// ��� ��
	int maxNumber_ans = 0;

	// �ϴ� �迭 �����
	int N = 0;
	cin >> N;

	int** block = new int*[N];
	for (int i = 0; i < N; i++)
		block[i] = new int[N];

	// �Է°� �ޱ�
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			cin >> block[i][j];
	}

	vector<coordinate> number[MAX_NUM];

	// �� 5�� �ݺ�
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
		// block, number�� ���� �� count�� �ʱ�ȭ
		init(N, block, block_copy, number_copy, &countX_copy, &countY_copy);

		// ����
		push_left(block_copy, N);
		// �� ������ count ���غ���..?
		make_vector(block_copy, number_copy, N);
		countDirection[LEFT] = decide_diretion(number_copy, &countX_copy, &countY_copy);
		//for (int i = 0; i < N; i++)
		//{
		//	for (int j = 0; j < N; j++)
		//		cout << block_copy[i][j] << "\t";
		//	cout << endl;
		//}
		//cout << endl;


		// ������(�ϱ� ���� block_copy���� �����·�
		init(N, block, block_copy, number_copy, &countX_copy, &countY_copy);

		// ������
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


		// ����
		init(N, block, block_copy, number_copy, &countX_copy, &countY_copy);
		push_up(block_copy, N);
		// �� ������ count ���غ���..?
		make_vector(block_copy, number_copy, N);
		countDirection[UP] = decide_diretion(number_copy, &countX_copy, &countY_copy);
		//for (int i = 0; i < N; i++)
		//{
		//	for (int j = 0; j < N; j++)
		//		cout << block_copy[i][j] << "\t";
		//	cout << endl;
		//}
		//cout << endl;


		// �Ʒ���
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

		// ���� ū ���� ã�Ƽ� �� �������� ���� �����̱�
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
		// ���� ����
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int> dis(0, maxDirection.size() - 1);

		if (maxDirection.size() > 0)
		{
			// 0���� size -1 ��ŭ����
			maxIdx = maxDirection.at(dis(gen));
		}

		// maxIdx�� ���� �ִ� �ϳ��� �� �ְ�,
		// �������� ���� �ְ� ������ �̤ä��̸��ṳ̀��ӤӤ�

		// ���� ������ ������ �� ���� ���´ٸ�
		// 0�� �� ���� ������ ����
		// �׷��� �𸣰ڴٸ� ����..?��������������
		// ����? ��������

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

		 //��� ����
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

	//	// 1. ���� ���ڰ� ��� �ִ��� Ȯ���ϱ�
	//	// ���ڸ��� ������ ��ġ�� ���⿣ �� �׷��� 1024���� 10��..? ����������..?
	//	// �� ����� ����������
	//	// struct�� ��ǥ�� ���� �װ� vector�ȿ� �־ �迭�� 10�� ����...
	//	make_vector(block, number, N);
	//	// vector�ȿ� ������(����)�� 2�� �̻��� �ֵ��� �������,
	//	// x��ǥ, y��ǥ���� ���� �� ū ���� �������� �б�
	//	// (y���� ���µ� 0�̶�� ���ο� �ִ� �ֵ��� ���� ���� �ִٴ� ���, �¿�(x��)�� �о����)
	//	// �ƴ���, �ٸ� �ֵ� ���µ� �����ϴµ�
	//	// ��ǥ ���� 0�� �ֵ��� ���� �������� �б�
	//	// ���� �߿� �Ѵ� �غ���? ������ �� ���� ���� ������ �б�...

	//	// ��...
	//	// �ٵ� ���� ���� 3�� �̻��϶� ���̵� 3���� ���;����ٵ�
	//	// ���ƾƾƾƾƾƾƤä����������� ���̤��ä��̤������Ӥ��Ӥ���
	//	// �׷� ���� �� ū������ ������ ���ؼ� return, �� ������ �� ���� ������ �б�

	//	// ��ǥ ���� ���� count
	//	int countX = 0;
	//	int countY = 0;
	//	decide_diretion(number, &countX, &countY);
	//	// �̷����ϴϱ� 4242�� ���ϴµ��� countX +2�� �Ź�����
	//	// �׳� �پ��ִ°� ������ 1������ �ٲٱ� �̷��� �ؾ��� �� ������
	//	// �̷��� ���̻� �׳� 4���� ���غ��� �����ɷ� �ұ�..?(�̰� ��¥ ��������ϼ��� ����)
	//	// �ٵ� �װ� �˰����� �³�...?

	//	// direction_X, Y�� ��� ���ڸ� ���ؼ� �� ���� ���� �������� �б�,
	//	// x��� �� �߿����� ����, ������ �� �� �о�� ������ ������ �� ���� ������ �аǵ�...
	//	// �̰� �ǳ�? �̴� �͵� ���������� ������
	//	// �� �غ��� �˰�¡...

	//	// ���� �ٵ� �Ѵ� �غ��°� �� �׷���
	//	// �ƴѰ� ��?��
	//	// �ϴ� �ѹ��� �غ��� �ɷ� �ұ�...
	//	// �ٵ� �׷��� ������ ��, �������� �� ��, �������� �� ���� ���� ���� ��ġ, �ٸ� ���� ��ġ�� ��� �˰� �־�� �� �� ������
	//	//int** block_copy = block; //�̰� �ǳ�? �����غ��ϱ� �����Ͷ� �׳� �����ϴ� �ų� ����
	//	int** block_copy = new int* [N];
	//	for (int i = 0; i < N; i++)
	//		block_copy[i] = new int[N];

	//	// �Է°� �ޱ�
	//	for (int i = 0; i < N; i++)
	//	{
	//		for (int j = 0; j < N; j++)
	//			block_copy[i][j] = block[i][j];
	//	}

	//	//int** block_copy2 = block; // �޸� ���ѿ��� �ɸ��� ����� ����������������
	//	int** block_copy2 = new int* [N];
	//	for (int i = 0; i < N; i++)
	//		block_copy2[i] = new int[N];

	//	// �Է°� �ޱ�
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
	//		// ����
	//		push_left(block_copy, N);
	//		// �� ������ count ���غ���..?
	//		make_vector(block_copy, number_copy, N);
	//		int leftCount = decide_diretion(number_copy, &countX_copy, &countY_copy);

	//		// ������
	//		push_right(block_copy2, N);
	//		make_vector(block_copy2, number_copy, N);
	//		int rightCount = decide_diretion(number_copy, &countX_copy, &countY_copy);


	//		// ���� ���ؼ� ���Ŀ� �� �� �� ���� ��?���� �ű��
	//		// �Ÿ��� �� ����� ���� �����ϱ�
	//		if (leftCount < rightCount)
	//			push_left(block, N); // ������ �ű��
	//		else
	//			push_right(block, N);

	//		// ��� ����
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
	//		// ����
	//		push_up(block_copy, N);
	//		// �� ������ count ���غ���..?
	//		make_vector(block_copy, number_copy, N);
	//		int upCount = decide_diretion(number_copy, &countX_copy, &countY_copy);

	//		// ������
	//		push_down(block_copy2, N);
	//		make_vector(block_copy2, number_copy, N);
	//		int downCount = decide_diretion(number_copy, &countX_copy, &countY_copy);


	//		// ���� ���ؼ� ���Ŀ� �� �� �� ���� ��?���� �ű��
	//		if (upCount < downCount)
	//			push_up(block, N); // ������ �ű��
	//		else
	//			push_down(block, N);

	//		 //��� ����
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

	// �ݺ��� ���� ��
	// block���� ���� ū ���� ��������
	// block�� for 2������ ��������,
	// vector�� �� ���� ��������?
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

