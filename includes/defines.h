/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 22:45:43 by jbenjy            #+#    #+#             */
/*   Updated: 2021/09/16 16:36:03 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define READLINE_WORDS "\033[0;32mcool_bash \033[0m>> "
# define ERROR_SYNTAX "\033[0;31mError:\033[0m "
# define GOOD_BYE "\033[0;35mGood bye!\033[0m "

# define ERROR_QUOTES "bad number of quotes"
# define ERROR_NOT_FOUND "command not found"
# define ERROR_BAD_FLAG "not supported flag(s)"
# define ERROR_TOO_MANY_ARG "too many arguments"

# define SINGLE_IN 1
# define SINGLE_OUT 2
# define DOUBLE_IN 3
# define DOUBLE_OUT 4
# define TYPE_COMMAND 5
# define TYPE_PIPE 6

# define COMMAND_ECHO 7
# define COMMAND_CD 8
# define COMMAND_PWD 9
# define COMMAND_EXPORT 10
# define COMMAND_UNSET 11
# define COMMAND_ENV 12
# define COMMAND_EXIT 13
# define COMMAND_IN_PWD -2
# define COMMAND_EMPTY -3
# define COMMAND_DEFAULT 15
# define COMMAND_NOT_DEFAULT 16
# define COMMAND_FULL -4

#endif