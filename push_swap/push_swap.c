/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongtki <seongtki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:06:37 by seongtki          #+#    #+#             */
/*   Updated: 2022/08/20 19:47:56 by seongtki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// 삭제 
void	show(t_stack *s)
{
	int	top;
	int	bottom;

	top = s->top;
	bottom = s->bottom;
	if (s->top == -1)
		return ;
	printf("show data =============\n");
	while (top >= bottom)
	{
		printf("%d ", s->list[top]);
		top--;
	}
	printf("\n");
	printf("=======================\n");
}

// int	break_ra(t_stack *a, t_stack *b, int i, int size)
// {
// 	int j=i;
// 	int k=1;
// 	int	flag = 1;
	
// 	if (i + 1 ==  size && data > a->list[a->top -1])
// 	{
// 		sab(a, "sa");
// 		pab(a, b, "pa");
// 		return (1);
// 	}

// 	while (j < size)
// 	{
// 		if (j + 1 < size && data <= a->list[a->top -k])
// 			flag = 1;
// 		else
// 		{
// 			flag = 0;
// 			break ;
// 		}
// 	j++;
// 	k--;
// 	}	
// 	if (flag == 1)
// 		return (1);
// 	return (0);
// }
void	swap_a(t_stack *a, t_stack *b, int l, int r)
{
	int	*pivot;
	int	size;
	int	i;
	int	ra_cnt;
	int	pb_cnt;
	int	data;
	int data2;

	ra_cnt = 0;
	pb_cnt = 0;
	i = 0;
	size = r - l + 1;
	if (size == 1)
		return ;
	if (confirm_ordered(a, l, r) == 1)
		return ;
	if (process1(a, b, l, r))
		return ;
	pivot = get_pivot(a, l, r);
	data = a->list[pivot[1]];
	data2 = a->list[pivot[0]];
	free(pivot);
	int	rb_cnt = 0;
	while (i < size)
	{
		if (data <= a->list[a->top])
		{
			if (i + 1 ==  size && data > a->list[a->top -1])
			{
				sab(a, "sa");
				pab(a, b, "pa");
				break ;
			}

			int j=i;
			int k=1;
			int	flag = 1;
			
			while (j < size)
			{
				if (j + 1 < size && data <= a->list[a->top -k])
					flag = 1;
				else
				{
					flag = 0;
					break ;
				}
			j++;
			k--;
			}	
			if (flag == 1)
				break ;
			
			
			rab(a, "ra");
			ra_cnt++;
		}
		else
		{
			pab(a, b, "pb");
			pb_cnt++;
			if (data2 < b->list[b->top])
			{
					rab(b, "rb");
					rb_cnt++;
			}
		}
		i++;
	}
	i = 0;
	int j = 0;
	if (l == 0)
	{
		while (j++ < rb_cnt)
			rrab(b, "rrb");
	}
	else
	{
		while (i < ra_cnt && j < rb_cnt)
		{
			rrr(a, b);
			i++;
			j++;
		}
		while (i++ < ra_cnt)
			rrab(a, "rra");
		while (j++ < rb_cnt)
			rrab(b, "rrb");
	}
	if (ra_cnt != 0)
		swap_a(a, b, a->top - (ra_cnt -1), a->top);// ra호출개수
	if (rb_cnt !=0)
		swap_b(a, b, 0, rb_cnt -1);// pb 호출개수 -> rb 호출횟수
	if (pb_cnt - rb_cnt != 0)
		swap_b(a, b, b->top - (pb_cnt -rb_cnt -1), b->top); // pb호출개수 - rb 호출회수
}

void	swap_b(t_stack *a, t_stack *b, int l, int r)
{
	int	*pivot;
	int	size;
	int	i;
	int	rb_cnt;
	int	pa_cnt;
	int	data[2];	
	int	ra_cnt;
	
	rb_cnt = 0;
	pa_cnt = 0;
	i = 0;
	size = r - l + 1;
	if (size == 1)
	{
		pab(b, a, "pa");
		return ;
	}
	int confirm = 0;
	if (b->top == r)
	{
		confirm = confirm_ordered_desc(a, l, r);
		if (confirm == 1)
			{
				while (i++ < size)
					pab(b, a, "pa");
				return ;
			}
	}
	if (process2(a, b, l, r))
		return ;
	pivot = get_pivot(b, l, r);
	data[0] = b->list[pivot[1]];
	data[1] = b->list[pivot[0]];
	free(pivot);
	ra_cnt = 0;
	while (i < size)
	{
		if (data[1] < b->list[b->top])
		{
			pab(b, a, "pa");
			pa_cnt++;
			if (data[0] > a->list[a->top])
			{
				rab(a, "ra");
				ra_cnt++;
			}
		}
		else
		{
			if (i + 1 ==  size && data[0] < b->list[b->top -1])
			{
				sab(b, "sb");
				pab(b, a, "pb");
				break ;
			}
			rab(b, "rb");
			rb_cnt++;
		}
		i++;
	}
	if (pa_cnt -ra_cnt  != 0)
		swap_a(a, b, a->top - (pa_cnt -ra_cnt -1), a->top); // pa호출횟수 - ra호출횟수
	i = 0;
	int j = 0;
		while (i < ra_cnt && j < rb_cnt)
		{
			rrr(a, b);
			i++;
			j++;	
		}
		while (i++ < ra_cnt)
			rrab(a, "rra");
		while (j++ < rb_cnt)
			rrab(b, "rrb");
	if (ra_cnt != 0)
		swap_a(a, b, a->top - (ra_cnt -1), a->top); //  pa호출회수-> ra호출횟수  
	if (rb_cnt != 0)
		swap_b(a, b, b->top - (rb_cnt -1), b->top); // pb 호출회수-> rb호출횟수
}

int	main(int argc, char **argv)
{
	if (argc < 2)
		pexit();
	t_stack	a;
	t_stack	b;
	init(&a, &b, argc, argv);
	swap_a(&a, &b, 0, (&a)->size -1);
//printf("\n======================프로그램 종료\n");	
//	show(&a);
//	show(&b);
	free((&a)->list);
	free((&b)->list);
	return (0);
}