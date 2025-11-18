/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                            :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: dgajowni <dgajowni@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:38:59 by dgajowni          #+#    #+#             */
/*   Updated: 2025/09/28 14:39:00 by dgajowni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int	ft_printf_number_unsigned(unsigned int n);
int	ft_printf_number_base(unsigned int nbr, int base_version);
int	ft_printf_pointer(unsigned long ptr);
int	ft_printf_char(char c);
int	ft_printf_number(int n);
int	ft_printf_string(char *s);
int	ft_printf(const char *format, ...);

#endif
