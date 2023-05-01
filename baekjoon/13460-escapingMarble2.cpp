/* 2022-12-21
* baekjoon 13460
* ������ ����ũ��� N, ���� ũ��� M, 1X1 ũ���� ĭ���� �������� ����
* ���� �ٱ� ��, ���� ��� #���� ������ �ְ�, ���忡�� ������ �ϳ� �ִ�.
* ���� ������ �Ķ� ������ �� �� ĭ�� �����ϰ�, ������ ��ǥ�� ���� ������ �������� ������ ���̴�.
* 
* ������ ������ �ǵ帱 ���� ����, �߷����� �̸����� ������ �Ѵ�.
* ����, ������, ����, �Ʒ��� �� �������� ����� �� �ִ�.
* 
* �� ���ۿ��� ������ ���ÿ� �����δ�. �Ķ� ������ ���ۿ� ������ ����, ���ÿ� �� ������ ���ۿ� ������ ����
* 
* ������ ���°� �־����� ��, �ּ� �� �� ���� ���� ������ ������ ���� ���� �� �ִ��� ���ϴ� ���α׷��� �ۼ��Ͻÿ�.
* 
* �Է�) N, M (3<=N, M<=10),
*		N���� �ٿ� ������ ����� ��Ÿ���� ���� M�� ���ڿ� (.�� ��ĭ, #�� ��, o�� ����, R�� ���� ����, B�� �Ķ� ����
* 
* ���) �ּ� �� �� ���� ���� �� �ִ��� ���, ���� 10�� ���Ϸ� �������� ���� �� ������ -1
* 
* 2023-04-27
* ������ �� �ߴµ�
* 7%? ���� Ʋ�Ƚ��ϴ� ��
* ��¥ �׽�Ʈ���̽� ����� �ͳ�..
*/

// R, B�� ��� 4���� ���� ��ĭ�� ���¸� �����ְ�,
// ���� ����̵� .�� �ִ� �������� ����̱�(��￴�ٸ� count +1)
// ���¸� ��ȭ�ϴ� go �Լ� 4��, (lrud)
// �׻� R�߽�, R���� �����̱�
// 
// 1. �ϴ� R, B�� ���� �����ϰ�
// 2. R�� �������� .���� �̵��ϱ�(.�� �ΰ����..? �ϴ� �������� ���µ� �� �𸣰ڳ�) ���� �Ʒ��� �Ȱ��� ���� ����
// ���� �ε����� ������ �ٲܶ����� count+1

// R�� ��ġ�� �ľ��ؼ�
// �� �� �ִ� ���� ������ ���� (���� �Ѵ� �� �� �ִٸ�..? (�� ���� �� �𸣰ڳ�..))
// �� �������� �� ĭ�� R�� B�� ���������鼭
// R�� ���̻� �� ���� ������ �ٽ� ������ ����

#include <iostream>
using namespace std;

class Marble
{
public :
	// (0,0)�� ���� ��
	int x; //x�� ����,(m) ��
	int y; // y�� ����(n) ��

	Marble() {
		this->x = 0;
		this->y = 0;
	}

	int go_up(char** board)
	{
		// �ٲ���ġ�� .�̰ų� O�϶��� �����̱�
		// �Ƹ� ���⼭ �ϴ°� �ƴ϶� 1ĭ�� �������� �׽�Ʈ���̽��� ������� ������...
		// ���� ���� ������
		char change = board[this->y - 1][this->x];
		while (change == '.' || change == 'O')
		{
			// Oã������ �ڽ��� .���� �ٲٱ�
			if (change == 'O') 
			{
				board[this->y][this->x] = '.';
				return 1;
			}

			// .�̶� �ڽ� ��ġ�� �ٲٱ�
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

/* �ٸ� cpp���Ͽ��� main�� �ߺ����� �Ǿ��ٰ� ����
int main()
{
	Marble* R = new Marble();
	Marble* B = new Marble();

	// count, ��
	int count_ans = 0;

	// N, M �ޱ�
	int N = 0;
	int M = 0;
	cin >> N >> M;

	// �����Ҵ� �ؾߵǳ�...
	// ���� N, �� ���� M��
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

	// R, B, O ��ġ �ľ�
	int Ox = 0, Oy = 0;
	// n�� ����, y, m�� x
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

	// O������ ���� ���?
	// ��?��... �ϴ� R, B�� ��ġ�� �����ؼ� �����̷��� �������� �� ū ���� ���� ��������
	// �� �����̸鼭 ���� �ٲ�ߵǳ�
	// �ƴѰ�, .�̶� R�̶� �ٲ�ߵǳ� ����

	// .�� ., .�� O�� �ִٸ�?
	// O���� x, y�� ������ �켱������ �� �� �ֵ���..?
	// �켱����..?�� �������ϳ�
	char priority = 'o';

	// ���� ����(-����)�� ���� �� ū ���� �켱������ �Լ������ϵ���?
	if (((Ox - R->x) * (Ox - R->x)) > ((Oy - R->y) * (Oy - R->y)))
	{
		priority = 'x';
	}
	else
		priority = 'y';



	//������ ���� �Ȱ��� �� �� �ִ� ���?
	// direction�� ���� ���� ���� �����̶�� �׳� continue;
	// �ٵ� �ݵ�� �ڷ� �����ϴ� ��Ȳ�̶��?
	// ���µ� 3������ �����ִ°Ÿ�...

	// ������ .(�̳� O)�� �ΰ� �ִٸ� direction���� �ݴ�������� ���� �ʰ� ��,
	// �ϳ����̶�� �� ��� �� �� �ֵ���
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

		// R�� ������ ���캸��, ������ ������ �ִٸ� �������� �����̱�
		char R_up = board[R->y - 1][R->x];
		char R_down = board[R->y + 1][R->x];
		char R_left = board[R->y][R->x - 1];
		char R_right = board[R->y][R->x + 1];

		// �� ����
		int pointCount = 0;
		// case���� if���� �ְ� �; �Ϻ��� ������ �𸣴ϱ�...
		if ((R_left == '.' || R_left == 'O'))
			pointCount++;
		if ((R_right == '.' || R_right == 'O'))
			pointCount++;
		if ((R_up == '.' || R_up == 'O'))
			pointCount++;
		if ((R_down == '.' || R_down == 'O'))
			pointCount++;

		// �� �� �ִ� ���� �ϳ��� direction �ʱ�ȭ ==> �ٽ� ���ư� �� �ֵ���
		if (pointCount == 1)
			direction = 'o';

		// priority�� x�� left, right�� ���� ����
		// ��� �ϵ� �ڵ� �ߺ��� �Ͼ��... �����
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