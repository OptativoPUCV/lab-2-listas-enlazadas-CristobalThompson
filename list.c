#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List* L = (List *) malloc(sizeof(List));
    if (L == NULL) exit(1);
    L->head = NULL;
    L->tail = NULL;
    L->current = NULL;
    return L;
}

void * firstList(List * list) {
    list->current = list->head;
    if (list == NULL || list->head == NULL) return NULL;
    return list->head->data;
}

void * nextList(List * list) {
    if (list->current == NULL || list->current->next == NULL) return NULL;
    list->current = list->current->next;
    return list->current->data;
}

void * lastList(List * list) {
    if (list->tail == NULL) return NULL;
    list->current = list->tail;
    return list->tail->data;
}

void * prevList(List * list) {
    if (list->current == NULL || list->current->prev == NULL) return NULL;
    list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {
    Node* newNodo = createNode(data);
    if (list->head == NULL){
        list->head = newNodo;
        list->tail = newNodo;
        return;
    }
    Node* anterior = list->head;
    anterior->prev = newNodo;
    newNodo->next = anterior;
    list->head = newNodo;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    if (list == NULL || list->current == NULL) exit(1);
    Node* newNodo = createNode(data);
    if (list->current->next == NULL){
        list->current->next = newNodo;
        newNodo->prev = list->current;
        list->tail = newNodo;
        return;
    }
    if (list->current->prev == NULL){
        Node* anterior = list->head;
        anterior->prev = newNodo;
        newNodo->next = anterior;
        list->head = newNodo;
        return;
    }
    Node* pos = list->current->next;
    pos->prev = newNodo;
    newNodo->next = pos;
    list->current->next = newNodo;
    newNodo->prev = list->current;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if (list == NULL || list->head == NULL || list->current == NULL) return NULL;
    void* eliminado = list->current->data;
    if (list->current->next == NULL){
        list->tail = list->current->prev;
        free(list->current);
        list->current = list->tail;
        list->tail->next = NULL;
        return eliminado;
    }
    if (list->current->prev == NULL){
        Node* aux = list->current;
        list->head = aux->next;
        list->head->prev = NULL;
        list->current = aux->next;
        free(aux);
        return eliminado;
    }
    Node* aux = list->current;
    aux->prev->next = aux->next;
    aux->next->prev = aux->prev;
    free(aux);
    return eliminado;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}