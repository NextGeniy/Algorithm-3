#include <iostream>
#include <stack>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};


Node* newNode(int data) {
    Node* node = new Node;
    node->data = data;
    node->left = node->right = NULL;
    return node;
}
struct Trunk
{
    Trunk* prev;
    string str;
    Trunk(Trunk* prev, string str) {
        this->prev = prev;
        this->str = str;
    }
};
struct AVLTree {

    struct TreeNode {
        int data;
        int height;
        TreeNode* left;
        TreeNode* right;

        TreeNode(int value)
            : data(value), height(1), left(nullptr), right(nullptr) {}
    };

    TreeNode* root;



public:
    AVLTree() : root(nullptr) {}

    void insert(int value);
    TreeNode* insertAVL(TreeNode* root, int value) {
        if (root == nullptr) {
            root = new TreeNode(value);
            return root;
        }

        if (value < root->data) {
            root->left = insertAVL(root->left, value);
        }
        else if (value > root->data) {
            root->right = insertAVL(root->right, value);
        }

        // Обновление высоты узла
        root->height = 1 + max(getHeight(root->left), getHeight(root->right));

        // Проверка нарушения баланса
        int balance = getBalance(root);

        // Малое правое вращение (RR)
        if (balance < -1 && value > root->right->data) {
            return rotateLeft(root);
        }

        // Малое левое вращение (LL)
        if (balance > 1 && value < root->left->data) {
            return rotateRight(root);
        }

        // Большое правое вращение (RL)
        if (balance < -1 && value < root->right->data) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        // Большое левое вращение (LR)
        if (balance > 1 && value > root->left->data) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        return root;
    }

    // Получение высоты поддерева
    int getHeight(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }

        return node->height;
    }

    // Получение баланса узла
    int getBalance(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }

        return getHeight(node->left) - getHeight(node->right);
    }

    // Вращение влево
    TreeNode* rotateLeft(TreeNode* root) {
        TreeNode* newRoot = root->right;
        TreeNode* subtree = newRoot->left;

        newRoot->left = root;
        root->right = subtree;

        root->height = 1 + max(getHeight(root->left), getHeight(root->right));
        newRoot->height = 1 + max(getHeight(newRoot->left), getHeight(newRoot->right));

        return newRoot;
    }

    // Вращение вправо
    TreeNode* rotateRight(TreeNode* root) {
        TreeNode* newRoot = root->left;
        TreeNode* subtree = newRoot->right;

        newRoot->right = root;
        root->left = subtree;

        root->height = 1 + max(getHeight(root->left), getHeight(root->right));
        newRoot->height = 1 + max(getHeight(newRoot->left), getHeight(newRoot->right));

        return newRoot;
    }
    void showTrunk(Trunk* p, int& count) {//функция вывода связей дерева
        if (p == NULL)//если нет поддеревьев
            return;
        showTrunk(p->prev, count);//выводим предыдущий узел
        count++;//увеличиваем уровень
        cout << p->str;//выводим отступы и связи
    }
    void printAVL(TreeNode* aBranch, Trunk* prev, bool isRight) {
        if (aBranch == NULL)//пустое дерево
            return;
        string prev_str = "    ";//отступ по уровням (длина как для стрелки)
        Trunk* tmp = new Trunk(prev, prev_str);//новая связь
        printAVL(aBranch->right, tmp, 1);//правое поддерево
        if (!prev)//если нет предыдущего узла (предка) -> корень дерева
            tmp->str = "-->";//связь корня дерева
        else if (isRight) {//если правое поддерево
            tmp->str = ".-->";//связь правого поддерева
            prev_str = "   |";//в отступ по уровням добавляем черту (дерево идет вширь)
        }
        else {//в противном случае - левое поддерево
            tmp->str = "`-->";//левое поддерево
            prev->str = prev_str;//отступ по уровням не меняется
        }
        int count = 0;//уровень узла
        showTrunk(tmp, count);//выводим связи дерева - стебли
        cout << aBranch->data << endl;//выводим значение узла
        if (prev)//задаем строку отступов для узла, если есть поддеревья
            prev->str = prev_str;
        tmp->str = "   |";//в отступ по уровням добавляем черту (дерево идет вширь)
        printAVL(aBranch->left, tmp, 0);//левое поддерево
    }
    void printBFS(TreeNode* root) {
        if (root == nullptr) {
            return;
        }

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* node = q.front();
            cout << node->data << " ";
            q.pop();

            if (node->left != nullptr) {
                q.push(node->left);
            }
            if (node->right != nullptr) {
                q.push(node->right);
            }
        }
    }

    // Распечатка узлов дерева в префиксном порядке
    void printPreOrder(TreeNode* node) {
        if (node == nullptr) {
            return;
        }

        cout << node->data << " ";
        printPreOrder(node->left);
        printPreOrder(node->right);
    }

    // Распечатка узлов дерева в инфиксном порядке
    void printInOrder(TreeNode* node) {
        if (node == nullptr) {
            return;
        }

        printInOrder(node->left);
        cout << node->data << " ";
        printInOrder(node->right);
    }

    // Распечатка узлов дерева в постфиксном порядке
    void printPostOrder(TreeNode* node) {
        if (node == nullptr) {
            return;
        }

        printPostOrder(node->left);
        printPostOrder(node->right);
        cout << node->data << " ";
    }
    void printTree(TreeNode* root) {
        if (root == NULL)
            return;

        cout << root->data;

        if (root->left != NULL) {
            cout << "(";
            printTree(root->left);
            cout << ")";
        }

        if (root->right != NULL) {
            cout << "(";
            printTree(root->right);
            cout << ")";
        }
    }
};

Node* buildTree(string str) {
    stack<Node*> st;

    Node* root = NULL;
    Node* cur = NULL;

    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '(') {
            st.push(cur);
            cur = NULL;
        }
        else if (isdigit(str[i])) {
            int num = 0;
            while (i < str.length() && isdigit(str[i])) {
                num = num * 10 + (str[i] - '0');
                i++;
            }
            i--;

            cur = newNode(num);

            if (root == NULL) {
                root = cur;
            }
            else {
                Node* parent = st.top();
                if (parent->left == NULL) {
                    parent->left = cur;
                }
                else {
                    parent->right = cur;
                }
            }
        }
        else if (str[i] == ')') {
            cur = st.top();
            st.pop();
        }
    }

    return root;
}

// Вывод двоичного дерева

int countNodeTree(Node* root,int temp=0) {
    if (root == NULL) {
        return temp;
    }
    temp++;
    countNodeTree(root->left,temp);
    countNodeTree(root->right,temp);
}
void dataTree(Node* root, vector<int> &data) {
    if (root == NULL)
        return;
    
    data.push_back(root->data);
    dataTree(root->left,data);
    dataTree(root->right,data);
}
vector<int> DataTree(Node* root) {
    vector<int> data;
    dataTree(root, data);
    return data;
}
void readExpressionFromFile(const string& aboba, string& expression)
{
    ifstream file(aboba);
    if (file.is_open())
    {
        getline(file, expression);
        file.close();
    }
    else {
        cout << "Ошибка при открытии файла!" << endl;
    }
}
void writeBinaryTreeToFile(Node* root, std::ofstream& file) {
    if (root == nullptr) {
        return;
    }

    file << root->data;

    if (root->left != nullptr || root->right != nullptr) {
        file << "(";
        writeBinaryTreeToFile(root->left, file);

        if (root->right != nullptr) {
            file << ",";
            writeBinaryTreeToFile(root->right, file);
        }

        file << ")";
    }
}
void showTrunk(Trunk* p, int& count) {//функция вывода связей дерева
    if (p == NULL)//если нет поддеревьев
        return;
    showTrunk(p->prev, count);//выводим предыдущий узел
    count++;//увеличиваем уровень
    cout << p->str;//выводим отступы и связи
}
void print(Node* aBranch, Trunk* prev, bool isRight) {
    if (aBranch == NULL)//пустое дерево
        return;
    string prev_str = "    ";//отступ по уровням (длина как для стрелки)
    Trunk* tmp = new Trunk(prev, prev_str);//новая связь
    print(aBranch->right, tmp, 1);//правое поддерево
    if (!prev)//если нет предыдущего узла (предка) -> корень дерева
        tmp->str = "-->";//связь корня дерева
    else if (isRight) {//если правое поддерево
        tmp->str = ".-->";//связь правого поддерева
        prev_str = "   |";//в отступ по уровням добавляем черту (дерево идет вширь)
    }
    else {//в противном случае - левое поддерево
        tmp->str = "`-->";//левое поддерево
        prev->str = prev_str;//отступ по уровням не меняется
    }
    int count = 0;//уровень узла
    showTrunk(tmp, count);//выводим связи дерева - стебли
    cout << aBranch->data << endl;//выводим значение узла
    if (prev)//задаем строку отступов для узла, если есть поддеревья
        prev->str = prev_str;
    tmp->str = "   |";//в отступ по уровням добавляем черту (дерево идет вширь)
    print(aBranch->left, tmp, 0);//левое поддерево
}
bool checkParentheses(const std::string& expression) {
    std::stack<char> st;
    for (char c : expression) {
        if (c == '(') {
            st.push(c);
        }
        else if (c == ')') {
            if (st.empty()) {
                return false; // Неправильная скобочная последовательность
            }
            st.pop();
        }
    }
    return st.empty(); // Скобки сбалансированы, если стек пуст
}
int main() {
    setlocale(0, "rus");
    string str;
    Node* root;
    readExpressionFromFile("input.txt", str);
    cout<<"Скобочная форма из файла: " << str << endl;
    if (!checkParentheses(str)) {
        cout << "Invalid expression" << std::endl;
        return 0;
    }
    root = buildTree(str);
    if (root != nullptr)
    {
        print(root, NULL, 0);
        cout << endl;
        cout << "Двоичное дерево построено успешно!" << endl;
    }
    else
    {
        cout << "Ошибка при построении дерева!" << endl;
    }
    
    AVLTree avlTree;
    AVLTree::TreeNode* avlRoot = nullptr;
    vector<int> data;
    data = DataTree(root);
    cout << "\n";
    for (int i = 0; i <7; i++) {
        avlRoot = avlTree.insertAVL(avlRoot, data[i]);
    }
    cout << "АВЛ ДЕРЕВО:\n";
    avlTree.printAVL(avlRoot,NULL,0);
    cout << "Переведенное АВЛ дерево: ";
    avlTree.printTree(avlRoot);
    cout << "\n";
    if (root != nullptr) {
        cout << "Обход в ширину: ";
        avlTree.printBFS(avlRoot);
        cout << endl;
        cout << "Обход в префиксном порядке: ";
        avlTree.printPreOrder(avlRoot);
        cout << endl;
        cout << "Обход в инфиксном порядке: ";
        avlTree.printInOrder(avlRoot);
        cout << endl;
        cout << "Обход в постфиксном порядке: ";
        avlTree.printPostOrder(avlRoot);
        cout << endl;
    }
    return 0;
}