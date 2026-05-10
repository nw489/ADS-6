// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <stdexcept>

struct SYM {
  char ch;
  int prior;
};

template<typename T>
struct Node {
  T data;
  Node* next;

  explicit Node(const T& value) : data(value), next(nullptr) {}
};

template<typename T>
class TPQueue {
 private:
  Node<T>* head;

 public:
  TPQueue() : head(nullptr) {}

  ~TPQueue() {
    while (head != nullptr) {
      Node<T>* temp = head;
      head = head->next;
      delete temp;
    }
  }

  void push(const T& value) {
    Node<T>* newNode = new Node<T>(value);

    if (head == nullptr) {
      head = newNode;
      return;
    }

    if (value.prior > head->data.prior) {
      newNode->next = head;
      head = newNode;
      return;
    }

    Node<T>* current = head;
    while (current->next != nullptr &&
           current->next->data.prior >= value.prior) {
      current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
  }

  T pop() {
    if (head == nullptr) {
      throw std::underflow_error("Queue is empty!");
    }

    Node<T>* temp = head;
    T data = head->data;
    head = head->next;
    delete temp;

    return data;
  }
};

#endif  // INCLUDE_TPQUEUE_H_
