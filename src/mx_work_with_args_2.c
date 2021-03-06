#include "uls.h"

static bool check_sub_argv(t_info *info, char *arg, t_uni_list *save);
static bool else_look(t_info *info, char *arg, char *file, t_uni_list *save);
static bool look_2(t_info *info, char *arg, t_uni_list *save);

bool mx_look_sub_argv(t_info *info, char *arg, t_uni_list *save) {
	char *file;

	if (malloc_size(info->path))
		mx_strdel(&info->path);
	if (check_sub_argv(info, arg, save)) // спроба відкрити аргумент
		return 1;
	else {
		file = mx_up_to_one(arg);
		if (else_look(info, arg, file, save)) {
			free(file);
			return 1;
		}
		free(file);
	}
	return 0;
}

static bool check_sub_argv(t_info *info, char *arg, t_uni_list *save) {
	int num_of_sub = 0;
	struct dirent *d = NULL;
	DIR *f = NULL;

	if ((f = opendir(arg))) { // намагаємося відкрити агрумент
		info->path = mx_strjoin(arg, "/");
		if (info->flag_a || info->flag_A)
			mx_look_sub_argv_2(info, f, save);
		else {
			while ((d = readdir(f)))
				if (d->d_name[0] != '.') {
					mx_push_uni_list_back(info, &(save), d->d_name, d->d_type);
					++num_of_sub;
				}
			info->num_of_sub = num_of_sub;
		}
		closedir(f);
		return 1;
	}
	return 0;
}

static bool else_look(t_info *info, char *arg, char *file, t_uni_list *save) {
	DIR *f;
	struct dirent *d;
	int num_of_sub = 0;

	if ((f = opendir(file))) {
		while((d = readdir(f))) {
			if (!mx_strcmp(d->d_name, arg + mx_strlen(file) + 1)) {
				mx_push_uni_list_back(info, &(save), arg, d->d_type);
				++num_of_sub;
			}
		}
		closedir(f);
		info->num_of_sub = num_of_sub;
		info->path = mx_strjoin(file, "/");
		return 1;
	}
	else {
		return look_2(info, arg, save);
	}
	return 0;
}

static bool look_2(t_info *info, char *arg, t_uni_list *save) {
	DIR *f = opendir("."); // шукаємо файл в папці де ми знаходимося
	struct dirent *d;

	while((d = readdir(f)))
		if (!mx_strcmp(d->d_name, arg)) {
			mx_push_uni_list_back(info, &(save), arg, d->d_type);
			info->path = mx_strdup("./");
			info->num_of_sub = 1;
		}
	closedir(f);
	return 1;
}
