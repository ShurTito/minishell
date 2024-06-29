/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:37:42 by anttorre          #+#    #+#             */
/*   Updated: 2024/02/15 19:29:04 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief 
 * Comprueba si es caracter es imprimible (32 - 126)
 * 
 * @param c char | Caracter
 * @return int - 0 si es false 1 si es true
 */
int	ft_isprint(int c)
{
	if ((unsigned char)(c >= 32 && c <= 126))
		return (1);
	return (0);
}
