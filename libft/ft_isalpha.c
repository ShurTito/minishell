/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:31:46 by anttorre          #+#    #+#             */
/*   Updated: 2024/02/15 19:28:20 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief 
 * Comprueba si el caracter es alfabetico A-Z a-z
 * 
 * @param c char | Caracter
 * @return int - 0 si es false 1 si es true
 */
int	ft_isalpha(int c)
{
	if ((unsigned char)((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')))
		return (1);
	return (0);
}
