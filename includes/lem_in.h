/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <rhunders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 22:45:02 by rhunders          #+#    #+#             */
/*   Updated: 2019/03/27 02:17:19 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __LEM_IN_H__
# define __LEM_IN_H__

#include <stdlib.h>
#include <libft.h>
#include <unistd.h>

#include <stdio.h>
#include <time.h>

#include "lem_in_s.h"
#include "lem_in_f.h"
#include "lem_in_f_init.h"

#define SIZE_BUFF 150000

#define UNIDIR1		1 // node1 to node2
#define UNIDIR2		2
#define BIDIR		3
#define NODIR		0

#define NO_MODE		0
#define IN_MODE		1
#define OUT_MODE	2


#define START		1
#define END			2
#define SIZE_DEPART 2000


t_objectif					*obj;

#endif
