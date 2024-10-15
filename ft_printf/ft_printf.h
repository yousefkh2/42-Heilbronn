/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:06:29 by ykhattab          #+#    #+#             */
/*   Updated: 2024/10/15 21:59:25 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *format, ...);
int		ft_putchar(char c);
int		ft_putstr(char *str);
int		handle_char(va_list args);
int		handle_string(va_list args);
int		handle_int(va_list args);
int		handle_unsigned(va_list args);
int		handle_pointer(va_list args);
int		handle_hex(va_list args, char format);

#endif
