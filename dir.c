/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 12:55:54 by seyun             #+#    #+#             */
/*   Updated: 2022/01/31 13:44:00 by seyun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char **argv)
{
	DIR *dir_ptr = NULL;
	struct dirent *file = NULL;
	char home[1024];

	strncpy(home, getenv("HOME"), sizeof(home));
	printf("%s \n", home);
	if ((dir_ptr = opendir(home)) == NULL)
	{
		fprintf(stderr," %s directory error.\n", home);
		return -1;
	}
	while((file = readdir(dir_ptr)) != NULL)
	{
		printf("%s\n", file->d_name);
	}
	closedir(dir_ptr);
	return 0;
}
