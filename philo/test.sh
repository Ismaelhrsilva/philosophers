# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/18 20:14:28 by maurodri          #+#    #+#              #
#    Updated: 2024/08/01 21:02:30 by ishenriq         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

set +x

if [[ "$2" =~ ^[Ll] ]]; then
	VALG="valgrind --leak-check=full "
elif [[ "$2" =~ ^[Tt] ]]; then
	VALG="valgrind --tool=helgrind "
else
	VALG=" "
fi

if [[ "$1" =~ ^[aA] ]]; then
	ARGS="1 800 200 200"
elif [[ "$1" =~ ^[bB] ]]; then
	ARGS="5 800 200 200 100"
elif [[ "$1" =~ ^[cC] ]]; then
	ARGS="5 800 200 200 7"
elif [[ "$1" =~ ^[dD] ]]; then
	ARGS="4 410 200 200 100"
elif [[ "$1" =~ ^[eE] ]]; then
	ARGS="4 310 200 200 100"
else
	ARGS="3 600 200 200 100"
fi

make && $VALG ./philo $ARGS
