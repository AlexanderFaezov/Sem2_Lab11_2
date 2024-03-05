#include <iostream>
#include <cstring>

using namespace std;

// Структура элемента двунаправленного списка
struct Node {
    char key[50];
    Node* prev;
    Node* next;

    // Конструктор для создания нового узла
    Node(const char* k, Node* p = nullptr, Node* n = nullptr) : prev(p), next(n) {
        strcpy_s(key, k);
    }
};

// Класс для двунаправленного списка
class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    // Конструктор для инициализации пустого списка
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Деструктор для освобождения памяти
    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Метод для добавления элемента в конец списка
    void append(const char* key) {
        Node* newNode = new Node(key);
        if (!head) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Метод для удаления элемента с заданным ключом
    void remove(const char* key) {
        Node* current = head;
        while (current) {
            if (strcmp(current->key, key) == 0) {
                if (current->prev) {
                    current->prev->next = current->next;
                }
                else {
                    head = current->next;
                }
                if (current->next) {
                    current->next->prev = current->prev;
                }
                else {
                    tail = current->prev;
                }
                delete current;
                return;
            }
            current = current->next;
        }
    }

    // Метод для добавления K элементов после элемента с заданным ключом
    void insertKNodesAfter(const char* key, int K) {
        Node* current = head;
        while (current) {
            if (strcmp(current->key, key) == 0) {
                for (int i = 0; i < K; ++i) {
                    Node* newNode = new Node("New Node");
                    newNode->next = current->next;
                    if (current->next) {
                        current->next->prev = newNode;
                    }
                    current->next = newNode;
                    newNode->prev = current;
                    current = newNode;
                }
                return;
            }
            current = current->next;
        }
    }

    // Метод для печати списка в прямом порядке
    void printForward() const {
        Node* current = head;
        while (current) {
            cout << current->key << " ";
            current = current->next;
        }
        cout << endl;
    }

    // Метод для печати списка в обратном порядке
    void printBackward() const {
        Node* current = tail;
        while (current) {
            cout << current->key << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    setlocale(LC_ALL, "ru");

    DoublyLinkedList list;

    list.append("Node 1");
    list.append("Node 2");
    list.append("Node 3");

    cout << "Список в прямом порядке:" << endl;
    list.printForward();

    cout << "Список в обратном порядке:" << endl;
    list.printBackward();

    list.remove("Node 2");

    cout << "Список после удаления 'Node 2':" << endl;
    list.printForward();

    list.insertKNodesAfter("Node 1", 2);

    cout << "Список после добавления 2 элементов после 'Node 1':" << endl;
    list.printForward();

    return 0;
}
