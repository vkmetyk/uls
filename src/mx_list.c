#include "uls.h"

t_uni_list *mx_create_uni_list(char *data) {
	t_uni_list *new_uni_list = (t_uni_list *)malloc(sizeof(t_uni_list));

	if (new_uni_list) {
		new_uni_list->data = mx_strdup(data);
		new_uni_list->next = NULL;
	}
	return new_uni_list;
}
void mx_push_uni_list_back(t_uni_list **list, void *data) {
	t_uni_list *new_uni_list = NULL;
	t_uni_list *temp = *list;
	int id = 0;

	if (list && (new_uni_list = mx_create_uni_list(data)) != NULL) {
		if (*list) {
			while (temp->next)
				temp = temp->next;

			temp->next = new_uni_list;
		}
		else
			*list = new_uni_list;
	}
}

void mx_pop_uni_list_front(t_uni_list **head) {
	t_uni_list *temp = NULL;

	if (head && *head) {
		temp = *head;
		if (malloc_size(temp->data))
			mx_strdel(&(temp->data));
		*head = temp->next;
		free(temp);
	}
}

// for flag l

t_info_l *mx_create_info_l(char *data) {
	t_info_l *new_info_l = (t_info_l *)malloc(sizeof(t_info_l));

	if (new_info_l) {
		new_info_l->access = mx_strnew(mx_strlen(data) + 3);
		mx_strcpy(new_info_l->access, data);
		new_info_l->nlink = 0;
		new_info_l->login = 0;
		new_info_l->group_owner = 0;
		new_info_l->sym_num = 0;
		new_info_l->time_upd = 0;
		new_info_l->next = NULL;
	}
	return new_info_l;
}
void mx_push_info_l_back(t_info_l **list, char *data) {
	t_info_l *new_info_l = NULL;
	t_info_l *temp = *list;
	int id = 0;

	if (list && (new_info_l = mx_create_info_l(data)) != NULL) {
		if (*list) {
			while (temp->next)
				temp = temp->next;

			temp->next = new_info_l;
		}
		else
			*list = new_info_l;
	}
}

void mx_pop_info_l_front(t_info_l **head) {
	t_info_l *temp = NULL;

	if (head && *head) {
		temp = *head;
		if (malloc_size(temp->access))
			mx_strdel(&(temp->access));
		*head = temp->next;
		free(temp);
	}
}
