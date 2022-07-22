/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongtki <seongtki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 13:30:57 by seongtki          #+#    #+#             */
/*   Updated: 2022/07/20 13:52:34 by seongtki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"


char	*set_print_data(t_format *f, t_options *o, va_list *ap)
{
	int	space;
	char *(*fp[10])(va_list *, t_options *, t_format *) 
		= {c_proc, s_proc, di_proc, u_proc, x_proc, x_proc, p_proc};
	space = 0;

	// 1. format 생성
	set_format(o, f);

/*	
	printf("format : ==========\n");
	printf("format.tot_len : %zu\n",f->tot_len);
	printf("format.zero : %d\n",f->zero);
	printf("format.zero_size : %zu\n",f->zero_size);
	printf("format.left_align : %d\n",f->left_align);
	printf("format.hash_val : %s\n",f->hash_val);
	printf("format.is_show_sign : %d\n",f->is_show_sign);
	printf("format : ==========\n");
*/
	char	*data;
	char	*type_data;
	type_data = (*fp[o->type])(ap, o, f);
	if (!f->is_print)
	{
		data = (char *)malloc(sizeof(char));
		data[0] = '\0';
		return (data);
	}
	printf("type data : %s\n", type_data);
	size_t	str_size = ft_strlen(type_data);
	//f->tot_len += str_size;
	data = (char *)malloc(sizeof(char) * (f->tot_len + 1 + (o->plus || o->space)));
	size_t index = 0;
	size_t	jndex = 0;
	printf("tot : %zu, sign : %c\n", f->tot_len, f->sign);
	if (f->left_align)
	{
		if (f->sign)
			data[index++] = f->sign;
		while (type_data[jndex])
		{
			data[index] = type_data[jndex++];
			index++;
		}
		while (index < f->tot_len - f->is_show_sign)
			data[index++] = ' ';
	}
	else
	{
		if (f->sign)
			data[index++] = f->sign;
		while (jndex++ < (f->tot_len - f->zero_size - str_size))
			data[index++] = ' ';
		jndex = 0;
		while (f->zero && jndex++ < (f->zero_size - str_size)) 
			data[index++] = '0';
		while (*type_data)
		{
			data[index] = *type_data;
			index++;
			type_data++;
		}
	}
	return (data);
}

void	show(char *str)
{
	while (*str)
		write(1, str++, 1);
}

int	do_printf(va_list *ap, const char *format_syntax)
{
	char		*data;
	t_options	options;
	t_format	format;
	int			format_len;

	init(&options, &format);
	format_len = set_option(&options, format_syntax);
	/*
	printf("=================\n");
	printf("options.space : %d\n", options.space);
	printf("options.plus : %d\n", options.plus);
	printf("options.minus : %d\n", options.minus);
	printf("options.width : %d\n", options.width);
	printf("options.p_width : %d\n", options.p_width);
	printf("options.zero : %d\n", options.zero);
	printf("options.hash : %d\n", options.hash);
	printf("options.precision : %d\n", options.precision);
	printf("options.type: %c\n", options.type);
	printf("=================\n");
	*/
	data = set_print_data(&format, &options, ap);
	show(data);
	return (format_len);
}

int	ft_printf(const char *data, ...)
{
	va_list ap;
	int	format_len;

	va_start(ap, data);
	while (*data)
	{
		if (*data == '%')
		{
			format_len = do_printf(&ap, ++data);
			data = data + format_len;
		}
		else
			write(1, &(*data), 1);
		data++;
	}
	va_end(ap);
	return (0);
}

int	main(void)
{
	//const char	a = 'a';
	//const char	*str = "abcde";	
	//ft_printf("test%5c$\n", a);
	//printf("test%5c$\n", a);
	//ft_printf("%010.s\n", str);
	//printf("%10.s\n", str);
	//ft_printf("%-10.s\n", str);
	printf("%+04d$\n",  11);
	printf("%+04d$\n",  1111);
	printf("%+04d$\n\n",  11111);
	
	printf("%+04d$\n",  11);
	printf("%+04d$\n",  1111);
	printf("%+04d$\n\n",  11111);

	printf("%-04d$\n",  111);
	printf("%-04d$\n",  1111);
	printf("%-04d$\n\n",  11111);

	printf("====== . ======\n");
	printf("%04.d$\n",  111);
	printf("%04.d$\n",  1111);
	printf("%04.d$\n\n",  11111);

	printf("%+04.d$\n",  11);
	printf("%+04.d$\n",  1111);
	printf("%+04.d$\n\n",  11111);
	
	printf("%-04.d$\n",  11);
	printf("%-04.d$\n",  1111);
	printf("%-04.d$\n\n",  11111);


	printf("===== .M =====\n");
	printf("%4.01d$\n",  111);
	printf("%4.04d$\n",  111);
	printf("%4.05d$\n\n",  111);

	printf("%+4.01d$\n",  111);
	printf("%+4.04d$\n",  111);
	printf("%+4.05d$\n\n",  111);

	printf("%-+4.01d$\n",  111);
	printf("%-+4.04d$\n",  111);
	printf("%-+4.05d$\n",  111);

	
	printf("===== .M =====\n");
	printf("%4.01s$\n",  "111");
	printf("%4.01s$\n",  "1111");
	printf("%4.01s$\n",  "11111");
	
	//ft_printf("%+-4.5d$\n",111);
	return (0);
}












