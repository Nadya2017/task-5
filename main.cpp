#include <iostream>
#include <iomanip>

using namespace std;
struct bin_tree
{
    int weight;
    int id;
    struct bin_tree *left;
    struct bin_tree *right;
};

bin_tree *head = NULL;

void push(bin_tree*& head, int x, int w)
{
    if (!head)
    {
        bin_tree*t = new bin_tree;
        t->weight = w;
        t->id = x;
        t->left = NULL;
        t->right = NULL;
        head = t;
    }
    else
    {
        if (x < head->id)
            push(head->left, x, w);
        else
            push(head->right, x, w);
    }
}

void print (bin_tree*& head, int n)
{
    if (head != NULL)
    {
        print(head->left, n+1);
        cout << setw(n*3) << head->id <<'('<<head->weight<<')'<< endl;
        print(head->right, n+1);
    }
}

 bin_tree* del(bin_tree*& head, int x)
{
    bin_tree* P, *v;
    if (!head) cout << "Запрашиваемого элемента нет в дереве" << endl;
    else if (x < head->id) head->left = del(head->left, x);
        else if (x > head-> id) head->right = del(head->right, x);
            else {
                P = head;
                if (!head->right) head = head->left;
                else if (!head->left) head = head->right;
                    else {
                            v = head->left;
                            if (v->right)
                            {
                                while (v->right->right)
                                    v = v->right;
                                head->id = v->right->id;
                                head->weight = v->right->weight;
                                P = v->right; v->right = v->right->left;
                            }
                            else
                            {
                                head->id = v->id;
                                head->weight = v->weight;
                                P = v;
                                head->left=head->left->left;
                            }
                        }
                }
 return head;
}

int individual(bin_tree*& head, int s)
{
    if(head != NULL)
    {
        if(head->weight < 0)
        {
            s = head->id;
        }
        return s + individual(head->left, s) + individual(head->right, s);
    }
    else return 0;
}

void menu() {
	std::cout << "1 - Вставить элемент" << std::endl;
	std::cout << "2 - Удалить элемент" << std::endl;
	std::cout << "3 - Напечатать дерево" << std::endl;
	std::cout << "4 - Инд-е задание: подсчитать сумму элементов дерева с отрицательным весом" << std::endl;
	std::cout << "0 - Выход из программы" << std::endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    push(head, 21, 1);
    push(head, 42, 0);
    push(head, 76, 1);
    push(head, 53, -1);
    push(head, 34, 1);
    push(head, 55, -1);
    push(head, 60, -1);
    int action, w, x, s; s=0;
   while (true) {
		menu();
		int action;
		std::cin >> action;
		switch (action) {
		case(1):
			std::cout << "Введите значение и вес:" << std::endl;
			cin >> x;
			cin >> w;
			push(head, x, w);
			break;
		case(2):
			std::cout << "Введите значение:" << std::endl;
			cin >> x;
			del(head, x);
			break;
		case(3):
			print(head, 1);
			break;
		case(4):
		    cout << individual(head, s);
		    std::cout << "\n" << std::endl;
		    break;
		case(0):
			return 0;
		}
	}
}
