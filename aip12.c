#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node {
	char* word;
	struct node* prev;
	struct node* next;
}node;

char* checkline(char* s) {   //  Проверка введенной строки на корректность и возвращение строки до первой точки
	int k = 0, t = 0;

	if (s[0] == '.')   //  Если начинается с точки
	{
		printf("Error: invalid input.\n");
		exit(-1);
	}

	for (int i = 0; i < strlen(s); i++) {
		if (s[i] == '.') {
			s[i] = '\0';
			k = i;
			break;
		}
		if (isalpha(s[i]) == 0 && s[i] != ' ') {
			printf("Error: invalid input.\n");
			exit(-1);
		}
		if (isalpha(s[i]) != 0) t++;
	}
	if (k == 0 || t == 0){
		printf("Error: invalid input.\n");
		exit(-1);
	}

	return s;
}

node* newnode(char* word, node* prev, node* next) {  // Создание элемента
	node* el = malloc(sizeof(node));
	el->next = next;
	el->prev = prev;
	el->word = word;
	return el;
}

void print_nodes(node *head)   //  ВЫвод списка
{
	node *temp;
	temp = head;
	while (temp != NULL){
		printf("%s ", temp->word);
		temp = temp->next;
	}
	printf("\n");
}

int min_len(node *head)   //  Поиск слова минимальной длины
{
	node *temp;
	temp = head;
	int min = strlen(temp->word);
	while (temp != NULL) {
		if (strlen(temp->word) < min)
			min = strlen(temp->word);
		temp = temp->next;
	}
	return min;
}

void delete_node(node *n) {    //  Удаление элемента
	node *pr, *ne;
	pr = n->prev;
	ne = n->next;
	if (pr != NULL)
		pr->next = ne;
	if (ne != NULL)
		ne->prev = pr;
	free(n);
}

void delete_head(node *head) {   // Удаление первого элемента
	node *temp;
	temp = head->next;
	if (head->next == NULL) {
		printf("All items of the list were deleted.\n");
		exit(0);
	}
	temp->prev = NULL;
	free(head);
	head = temp;
}

node *delete_min(node *head) {    //  Удаление минимальных слов
	node *temp, *temp1;
	int min = min_len(head);
	temp = head;
	while (temp != NULL){
		if (strlen(temp->word) == min) {
			if (temp->prev == NULL) {   //  В случае, если элемент - первый
				temp1 = temp->next;
				delete_head(temp);
				head = temp1;
				temp = temp1;
			}
			else {
				temp1 = temp->prev;
				delete_node(temp);
				temp = temp1;
			}
		}
		else 
			temp = temp->next;
	}
	return head;
}

void free_nodes(node* head) {   // Освобождение памяти
	node* n;
	while (head != NULL) {
		n = head;
		head = head->next;
		free(n);
	}
}

int task() {
	char string[300], *p;
	node *head, *temp;
	printf("Enter your string:\n");
	gets(string);
	checkline(string);

	p = strtok(string, " ");	//Разбиение строки на лексемы
	head = newnode(p, NULL, NULL);   // Создание элемента
	temp = head;
	p = strtok(NULL, " ");
	while (p != NULL) {   // Переход по лексемам и создание элементов
		temp->next = newnode(p, temp, NULL);
		temp = temp->next;
		p = strtok(NULL, " ");
	}
	printf("\n");
	print_nodes(head);
	head = delete_min(head);    //  Удаление минимальных слов
	print_nodes(head);
	free_nodes(head);
	return 0;
}

int main()
{
	task();
	return 0;
}
