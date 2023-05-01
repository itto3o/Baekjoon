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

#define MAX_NUM 11

using namespace std;

struct coordinate{
	int y;
	int x; //�迭 �� [y][x]�� ������
};

char direction(coordinate A, coordinate B)
{
	int subX = abs(A.x - B.x); // ������ ���� �� ����ؼ� ���밪
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
	// �˾Ƴ��� �̳� �����...
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
					// �� ��쿡 8�� �������µ� �ڿ� �ٷ� 8�̶� �������� 16�� ��...
					// ==> �̹� ������ ��ǥ�� �����ϴ°� �־���ϳ�
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
		// 1. ���� ���ڰ� ��� �ִ��� Ȯ���ϱ�
		// ���ڸ��� ������ ��ġ�� ���⿣ �� �׷��� 1024���� 10��..? ����������..?
		// �� ����� ����������
		// struct�� ��ǥ�� ���� �װ� vector�ȿ� �־ �迭�� 10�� ����...
		make_vector(block, number, N);
		// vector�ȿ� ������(����)�� 2�� �̻��� �ֵ��� �������,
		// x��ǥ, y��ǥ���� ���� �� ū ���� �������� �б�
		// (y���� ���µ� 0�̶�� ���ο� �ִ� �ֵ��� ���� ���� �ִٴ� ���, �¿�(x��)�� �о����)
		// �ƴ���, �ٸ� �ֵ� ���µ� �����ϴµ�
		// ��ǥ ���� 0�� �ֵ��� ���� �������� �б�
		// ���� �߿� �Ѵ� �غ���? ������ �� ���� ���� ������ �б�...

		// ��...
		// �ٵ� ���� ���� 3�� �̻��϶� ���̵� 3���� ���;����ٵ�
		// ���ƾƾƾƾƾƾƤä����������� ���̤��ä��̤������Ӥ��Ӥ���
		// �׷� ���� �� ū������ ������ ���ؼ� return, �� ������ �� ���� ������ �б�

		// ��ǥ ���� ���� count
		int countX = 0;
		int countY = 0;
		decide_diretion(number, &countX, &countY);

		// direction_X, Y�� ��� ���ڸ� ���ؼ� �� ���� ���� �������� �б�,
		// x��� �� �߿����� ����, ������ �� �� �о�� ������ ������ �� ���� ������ �аǵ�...
		// �̰� �ǳ�? �̴� �͵� ���������� ������
		// �� �غ��� �˰�¡...

		// ���� �ٵ� �Ѵ� �غ��°� �� �׷���
		// �ƴѰ� ��?��
		// �ϴ� �ѹ��� �غ��� �ɷ� �ұ�...
		// �ٵ� �׷��� ������ ��, �������� �� ��, �������� �� ���� ���� ���� ��ġ, �ٸ� ���� ��ġ�� ��� �˰� �־�� �� �� ������
		//int** block_copy = block; //�̰� �ǳ�? �����غ��ϱ� �����Ͷ� �׳� �����ϴ� �ų� ����
		int** block_copy = new int* [N];
		for (int i = 0; i < N; i++)
			block_copy[i] = new int[N];

		// �Է°� �ޱ�
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
				block_copy[i][j] = block[i][j];
		}

		//int** block_copy2 = block; // �޸� ���ѿ��� �ɸ��� ����� ����������������
		int** block_copy2 = new int* [N];
		for (int i = 0; i < N; i++)
			block_copy2[i] = new int[N];

		// �Է°� �ޱ�
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
			// ����
			push_left(block_copy, N);
			// �� ������ count ���غ���..?
			make_vector(block_copy, number_copy, N);
			int leftCount = decide_diretion(number_copy, &countX_copy, &countY_copy);

			// ������
			push_right(block_copy2, N);
			make_vector(block_copy2, number_copy, N);
			int rightCount = decide_diretion(number_copy, &countX_copy, &countY_copy);


			// ���� ���ؼ� ���Ŀ� �� �� �� ���� ��?���� �ű��
			if (leftCount > rightCount)
				push_left(block, N); // ������ �ű��
			else
				push_right(block, N);

			// ��� ����
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
			// ����
			push_up(block_copy, N);
			// �� ������ count ���غ���..?
			make_vector(block_copy, number_copy, N);
			int upCount = decide_diretion(number_copy, &countX_copy, &countY_copy);

			// ������
			push_down(block_copy2, N);
			make_vector(block_copy2, number_copy, N);
			int downCount = decide_diretion(number_copy, &countX_copy, &countY_copy);


			// ���� ���ؼ� ���Ŀ� �� �� �� ���� ��?���� �ű��
			if (upCount > downCount)
				push_up(block, N); // ������ �ű��
			else
				push_down(block, N);

			// ��� ����
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

	// �ݺ��� ���� ��
	// block���� ���� ū ���� ��������
	// block�� for 2������ ��������,
	// vector�� �� ���� ��������?
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

