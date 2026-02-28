#pragma once

#include <cstddef>
#include <iterator>
#include <print>
#include <stdexcept>
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

  void insert(T value, size_t position) {
    if (head == nullptr)
      head = new Node<T>(value, nullptr);
    else if (position == 0) {
      Node<T> *newHead = new Node<T>(value, head);
      head = newHead;
    } else {
      Node<T> *newNode = new Node<T>(value);
      Node<T> *temp = head;
      size_t i = 0;
      for (i = 0; temp->next != nullptr && i < position - 1;
           temp = temp->next, i++) {
      }

      if (i != position - 1) {
        throw std::runtime_error("Not a valid position");
      }

      newNode->next = temp->next;
      temp->next = newNode;
    }
  }

  void insertAtEnd(T value) {
    if (head == nullptr) {
      head = new Node<T>(value, nullptr);
    } else {
      Node<T> *newNode = new Node<T>(value, nullptr);
      Node<T> *temp = head;
      for (; temp->next != nullptr; temp = temp->next) {
      }
      temp->next = newNode;
    }
  }

  void reverse() {
    Node<T> *prev = nullptr;
    Node<T> *curr = head;
    Node<T> *next = head->next;

    while (next != nullptr) {
      curr->next = prev;
      prev = curr;
      curr = next;
      next = next->next;
    }

		curr->next = prev;

		head = curr;
  }

  void printList() {
    Node<T> *temp = head;
    for (; temp != nullptr; temp = temp->next) {
      std::println("v:{} n: {}", temp->value, static_cast<void*>(temp->next));
    }

    std::println();
  }
};
