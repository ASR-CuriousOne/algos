#pragma once

#include <print>
template <typename T> struct Node {
  T value;
  Node *next = nullptr;

  Node() : next(nullptr) {}
  Node(T value) : value(value) {}
  Node(T value, Node *next) : value(value), next(next) {}
};

template <typename T> class LinkedList {
  Node<T> *head = nullptr;

public:
  LinkedList() : head(nullptr) {}

  void insert(T value) {
    if (head == nullptr)
      head = new Node<T>(value, nullptr);
    else {
      Node<T> *newNode = new Node<T>(value, nullptr);
      Node<T> *temp = head;
      for (; temp->next != nullptr; temp = temp->next) {
      }

      temp->next = newNode;
    }
  }

  void printList() {
    Node<T> *temp = head;
    for (; temp != nullptr; temp = temp->next) {
      std::print("{} ", temp->value);
    }
  }
};
