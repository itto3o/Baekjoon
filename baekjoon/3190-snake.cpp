/*
* 2023-05-04
* 
* NXN ���簢 ����,
* ����� ��ġ�� �־�����,
* ������ ��ȭ�ڿ� ���� ���� �ִ�.
* 
* ���� �� �Ǵ� �ڱ��ڽ��� ���� �ε����� ������ ����
* 
* ���� ���۽� ���� ���� �������� ��ġ, ���̴� 1, �������� ����
* �� �ʸ��� �̵�,
* �Ӹ��� ����ĭ�� ��ġ��Ų ��, ���� ĭ�� ����� �ִٸ� ����� �������� ������ �������� ����
* ����� ���ٸ� �����̸� �ٿ��� ĭ�� �����(������ ��ȭx)
* 
* �����ġ, ���� �̵���ΰ� �־��� �� ������ �� �ʿ� ��������
* 
* �Է�)
* 1. ������ ũ�� N (2<=N<=100)
* 2. ����� ���� K(0 <= K <= 100)
* (���� ũ�⺸�� Ŭ �� �ֳ�..?)
* 
* 3. K���� �ٿ��� ���� ����� ��ġ�� �־���
* ��, ��,
* ����� ��ġ�� ��� �ٸ�, 1�� 1������ ����� ����
* 4. ���� ���� ��ȯ Ƚ�� L(1<=L<=100)
* 5. L���� �ٿ� ��ȯ ����, X, C(X�ʰ� ���� �� C�� ������ 90�� ȸ��(L�Ǵ� D)
*	X <= 10,000 ������ �ڿ���, X�� �����ϴ� ������ �־���
* 
* ���)
* ù° �ٿ� ������ �� �ʿ� �������� ���
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
* �ƴ� ���� ���ظ� �� ���ϰٴµ�
* ���ʿ� �����Ҷ� �ǿ��ʸ���ĭ���� 1�ʸ� ���°���
* ������ 2�ʾ����°ǰ�?
* ���� �� �ִ°ǰ� �׷�
* �׷� 1���� ��� ���̰ڳ�?
* ��� ��ġ�� �� �޶�����..?
* �ƴ� ������ ���� ��ģ����
* 
* 000000
* 0----0
* 0000|0
* 0000|0
* 0000|0
* 000000 �̷��� 7�Ƴ�?
* 
* ���� 1�ʰ� �����̶�� + ������ȯ���� 1�ʸ� ���ٸ�
* 000000
* 0--|00
* 000|00
* 000|00
* 000|00 �̷��� 8�ƴѰ�
* 000000 
* 
* // ���� ���ٸ�
* ---000
* 00|000
* 00|000
* 00|000
* 00|000
* 00|000 �̷� 9�� �ϳ�
* 
* ----000
* 000|00
* 000|00
* 000|00
* 000|00
* 000|00 8���� �� �������� ���°Ű�, 9 ������ �� ���̳�
* 
* ���
* ���� ���������δ� ����.
* ������ Ʈ�� �ð��� 1������ �ʴ°Ͱ���.
* ������ Ʈ�� �ð��� ���� ����, ���� ��Ͽ��� 1�ʸ� ���� �ʴ� �� ����.
* 8�ʱ��� ���� �� 9�ʿ� ���̸� 9�ʰ� ���̴�.
* 
* �ణ ������ �� �о�� ���� �ִ� �� ���⵵�ϴ�
* 
* ó���� ������ ������ ����, ���������� ������
* ������ �ð�����(3 D�� 4�� ���ۺ��� ���� ƴ)
* 1�ʰ� ���۵Ǹ� ���� �Ӹ��� ���� �ű��, ������ �ű�
* �Ӹ��� ����� ���̸� ������ �ű��� ����(����� ������)
* �Ӹ��� ���̳� �ڱ� ���� ���̸� ������ ����(�� �ð��� return)
* 
* ==> ó�� ������ �����U���� �صΰ�
* map�� ��� ��ġ�� ������ �ߴµ� �׳� ����ü x,y���ؼ� �迭�� �ϰ� �ֳ�
* ������ �������� �Ӹ��� ���� �����̰�, �׶� ����� ��Ҵٸ� ������ �ȿ����̱�, 
* �� �ٵ� �׳� ĭ�� �Դ� ������� �ұ�... board�� ���� �ִ� ���� ǥ���ϴ°���
* �׷��� ������ ������ �ٷ� �˰� �Ƴ�
* board�� 1�� ����鼭 �����°��� 0���� �����, �ٵ� �׷� ���� �����̰� ����?�� Ư������ �������
* ���� �𸣰ڵ� �Ӹ��� ���� �κ� ��ǥ�� �ʿ� ������?
* 
*/

#include <iostream>
#include <vector>
#include <map>

using namespace std;

enum {
	// �ð��������
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
	// �� �������� 1�� �����
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
		transformDirection.insert({ time, direction }); //, direction }); //�� �̷��� �ϴ� �� �³� (�׷��ä� map���� ��)
	}

	// ������ �������� �� ĭ �����̴µ�
	// �̶� �� ĭ�� ���� �ִ��� Ȯ��
	// �����̱� �� time+1
	while (true)
	{
		Position currentHead = snake.headPosition;

		Position forwardHead;
		// head�� ������ �� ĭ
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

		// ���� ������ �� ĭ�� ���̰ų�, �ڱ� �ڽ��̸� ���ӳ�
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

		// ���� �� �� �ƴ϶�� �ϴ� �ð��� +1
		answerTime++;

		// ���� �Űܾ� �ϴµ�
		// ���� ����� �ִٸ� GoHead��, board�� 1�� ä���
		for (int i = 0; i < K; i++)
		{
			if (forwardHead.y == apples[i].y && forwardHead.x == apples[i].x)
			{
				// ����� �ִ� ���̶�� GoHead()
				snake.GoHead();
				board[forwardHead.y][forwardHead.x] == 1;
			}
		}

		// ����� �����ٸ� GoHead, GoTail, board ��ĭ �̷��
		// �ٵ� ���� ���ڷ� ���� �־��ٸ� �Ӹ��� tail�� �ű�ٰ� �� ���� �ƴѵ�
		// board�� ĥ�ϴ� �κ��� ���� �������ϳ�..? ���� �� ����.......

		// ���� ���� �ð�(�ٲٰ� �� �� �ð�)�� ������ ��ȯ�ؾ��ϴ� �ð�(�� �ð��� ���� �� �ٲ�� ��)�̶��
		for (auto td : transformDirection)
		{
			if (td.first == answerTime)
			{
				// ������ �ٲ���
				// ���� ���⿡ +1�� �ϸ� ������, -1�� �ϸ� ����
				if (td.second == 'D')
				{
					snake.goingDirection = (snake.goingDirection + 1) % 4; // ��ȯ ������ ���� left(3)���� +1�� �ϸ� 0�� ��������
				}
				else if (td.second == 'L')
				{
					snake.goingDirection = (snake.goingDirection + 3) % 4; // ��ȯ ������ ���� up(0)���� -1�� �ϸ� 3�� ��������
				}
			}
		}


	}

	// ��� ���
	cout << answerTime << endl;
	
	for (int n = 0; n < N; n++)
		delete[] board[n];
	delete[] board;

	return 0;
}