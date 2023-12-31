#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Node {
public:
    int Value;
    Node* Next;

public:
    Node(int value) {
        Value = value;
        Next = nullptr;
    }

    void setNext(Node* next) {
        Next = next;
    }

    Node* getNext() {
        return Next;
    }

    int getValue() {
        return Value;
    }
};

class singlyLinkedList {
private:
    Node* first;

public:
    singlyLinkedList() {
        first = nullptr;
    }

    void add(int value) {
        Node* newNode = new Node(value);
        if (!first) {
            first = newNode;
        } else {
            Node* current = first;
            while (current->getNext()) {
                current = current->getNext();
            }
            current->setNext(newNode);
        }
    }

    void insert(int value, int index) {
        if (first == nullptr) {
            cout << "The given previous node cannot be NULL";
            return;
        }

        Node* newNode = new Node(value);

        if (index == 0) {
            newNode->setNext(first);
            first = newNode;
            return;
        }

        Node* current = first;
        for (int i = 0; i < index - 1 && current != nullptr; i++) {
            current = current->getNext();
        }

        if (current == nullptr) {
            cout << "Index out of range";
            return;
        }

        newNode->setNext(current->getNext());
        current->setNext(newNode);
    }

    void remove(int index) {
        if (index < 0) {
            cout << "Invalid index";
            return;
        }

        if (index == 0) {
            if (first) {
                Node* temp = first;
                first = first->getNext();
                delete temp;
                return;
            }
        }

        Node* current = first;
        for (int i = 0; current != nullptr && i < index - 1; i++) {
            current = current->getNext();
        }

        if (current == nullptr || current->getNext() == nullptr) {
            cout << "Index out of range";
            return;
        }

        Node* temp = current->getNext();
        current->setNext(temp->getNext());
        delete temp;
    }

    void swap(int index1, int index2) {
        if (index1 == index2) {
            return;
        }

        Node* prev1 = nullptr;
        Node* curr1 = first;
        for (int i = 0; curr1 != nullptr && i < index1; i++) {
            prev1 = curr1;
            curr1 = curr1->getNext();
        }

        Node* prev2 = nullptr;
        Node* curr2 = first;
        for (int i = 0; curr2 != nullptr && i < index2; i++) {
            prev2 = curr2;
            curr2 = curr2->getNext();
        }

        if (curr1 == nullptr || curr2 == nullptr) {
            cout << "Invalid indices for swapping";
            return;
        }

        if (prev1) {
            prev1->setNext(curr2);
        } else {
            first = curr2;
        }

        if (prev2) {
            prev2->setNext(curr1);
        } else {
            first = curr1;
        }

        Node* temp = curr1->getNext();
        curr1->setNext(curr2->getNext());
        curr2->setNext(temp);

    }

    void printList() {
        Node* current = first;
        while (current) {
            cout << current->getValue() << " ";
            current = current->getNext();
        }
        cout << endl;
    }

    void insertionSort() {
        if (!first || !first->getNext()) {
            return;
        }

        Node* sorted = nullptr;
        Node* current = first;

        while (current != nullptr) {
            Node* next = current->getNext();
            if (!sorted || sorted->getValue() >= current->getValue()) {
                current->setNext(sorted);
                sorted = current;
            } else {
                Node* traverse = sorted;
                while (traverse->getNext() != nullptr && traverse->getNext()->getValue() < current->getValue()) {
                    traverse = traverse->getNext();
                }
                current->setNext(traverse->getNext());
                traverse->setNext(current);
            }
            current = next;
        }
        first = sorted;
    }

    int get(int index) {
        Node* current = first;
        int currentIndex = 0;

        while (current) {
            if (currentIndex == index) {
                return current->getValue();
            }

            current = current->getNext();
            currentIndex++;
        }
        throw out_of_range("Anda keluar dari batas index");
    }

    int length() {
        int count = 0;
        Node* current = first;
        while (current) {
            count++;
            current = current->getNext();
        }
        return count;
    }

};

class LinkedListGenerator {
public:
    static void generateRandomValues(singlyLinkedList& list, int n) {
        srand(time(0));  // Inisialisasi seed acak berdasarkan waktu
        for (int i = 0; i < n; i++) {
            int randomValue = 1 + rand() % 1000; // Nilai acak antara 1 dan 1000
            list.add(randomValue);
        }
    }

    static void generateReversedValues(singlyLinkedList& list, int n) {
        for (int i = n; i >= 1; i--) {
            list.add(i);
        }
    }
};

int main() {
    singlyLinkedList list;
    LinkedListGenerator random, nearlySorted, reversedValue;
    int menu;
    while (true) {
        cout << "Pilih Angka Menu yang Tersedia : \n"
        "1.Add\n"
        "2.Insert\n"
        "3.Remove\n"
        "4.Swap\n"
        "5.Get Value\n"
        "6.Generate Value\n"
        "7.Insertion Sort\n"
        "8.Selesai" << endl;
        cin >> menu;
        if (menu == 1) {
            // add value
            int value;
            cout << "Masukkan nilai (0 untuk selesai): ";
            cin >> value;

            while (value != 0) {
                list.add(value);
                cout << "Masukkan nilai (0 untuk selesai): ";
                cin >> value;
            }

            cout << "Linked List setelah menggunakan fungsi add: ";
            list.printList();
            cout << endl;
        } else if (menu == 2) {
            // insert value berdasarkan index
            int value, index;
            cout << "Masukkan nilai yang ingin disisipkan: ";
            cin >> value;

            cout << "Masukkan indeks di mana nilai akan disisipkan: ";
            cin >> index;

            list.insert(value, index);

            cout << "Linked List setelah menggunakan fungsi insert: ";
            list.printList();
            cout << endl;
        } else if (menu == 3) {
            // remove value berdasarkan index
            int index;
            cout << "Masukkan indeks yang ingin dihapus: ";
            cin >> index;

            list.remove(index);

            cout << "Linked List setelah menggunakan fungsi remove: ";
            list.printList();
            cout << endl;
        } else if(menu == 4) {
            // swap value berdasarkan index
            int index1, index2;
            cout << "Masukkan indeks pertama untuk penukaran: ";
            cin >> index1;

            cout << "Masukkan indeks kedua untuk penukaran: ";
            cin >> index2;

            list.swap(index1, index2);

            cout << "Linked List setelah menggunakan fungsi remove: ";
            list.printList();
            cout << endl;
        } else if (menu == 5) {
            // get value berdasarkan input index
            int index;
            cout << "Masukkan indeks untuk mendapatkan nilai: ";
            cin >> index;

            try {
                int value = list.get(index);
                cout << "Nilai pada index " << index << ": " << value << endl;
            } catch (const out_of_range& e) {
                cerr << "Error: " << e.what() << endl;
            }
        } else if (menu == 6) {
            int generator;
            while (true) {
                cout << "Pilih Generator yang ingin digunakan : \n"
                "1.Random\n"
                "2.Reversed\n"
                "3.Keluar" << endl;
                cin >> generator;
                if (generator == 1) {
                    // generate random value
                    int numValues;
                    cout << "Masukkan banyak nilai acak yang ingin di-generate: ";
                    cin >> numValues;

                    random.generateRandomValues(list, numValues);

                    cout << "Linked List setelah menggunakan fungsi generateRandomValues: ";
                    list.printList();
                    cout << endl;
                    break;
                } else if (generator == 2) {
                    // generate reversed values
                    int numValues;
                    cout << "Masukkan banyak nilai terurut terbalik yang ingin di-generate: ";
                    cin >> numValues;

                    reversedValue.generateReversedValues(list, numValues);

                    cout << "Linked List setelah menggunakan fungsi generateReversedValues: ";
                    list.printList();
                    cout << endl;
                    break;
                } else if (generator == 3) {
                    break;
                } else {
                    cout << "invalid input" << endl;
                }
            }
        } else if(menu == 7) {
            // Insertion sort dan waktu lamanya eksekusi
            high_resolution_clock::time_point startTime = high_resolution_clock::now();
            list.insertionSort();
            high_resolution_clock::time_point endTime = high_resolution_clock::now();
            duration<double> timeElapsed = duration_cast<duration<double>>(endTime - startTime);

            list.printList();
            cout << "Waktu yang diperlukan untuk Insertion Sort: " << timeElapsed.count() << " detik" << endl;
            cout << endl;
        } else if (menu == 8) {
            break;
        } else {
            cout << "invalid input" << endl;
        }

    }

    return 0;
}
