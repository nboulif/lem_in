/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <rhunders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 22:45:02 by rhunders          #+#    #+#             */
/*   Updated: 2019/09/05 18:40:40 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdlib.h>
# include <libft.h>
# include <unistd.h>

# include <stdio.h>
# include <limits.h>
# include <time.h>
# include <fcntl.h>

# include "lem_in_s_def.h"
# include "lem_in_s.h"
# include "lem_in_f.h"
# include "lem_in_f_init.h"

# define C_P_S CLOCKS_PER_SEC

# define SIZE_BUFF 150000

# define UNIDIR1		1
# define UNIDIR2		2
# define BIDIR		3
# define NODIR		0

# define NO_MODE		0
# define IN_MODE		1
# define OUT_MODE	2

# define START		1
# define END			2
# define SIZE_DEPART 2000

#endif
