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

void	ft_swap(int *a, int *b)
{
	int		tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_sort_int_tab(int *tab, int size)
{
	int		minindex;
	int		index1;
	int		index2;

	index1 = 0;
	while (index1 < size)
	{
		minindex = index1;
		index2 = index1 + 1;
		while (index2 < size)
		{
			if (tab[minindex] > tab[index2])
			{
				ft_swap(&tab[minindex], &tab[index2]);
			}
			index2++;
		}
		index1++;
	}
}

int	pexit()
{
	write(2, "Error\n", 6);
	exit(1);
}

/// 1 1 2 에서 됨, 다시짜야됨
int	binary_search(t_stack *s, int target)
{
	int	pivot;
	int	right;
	int	left;

	left = 0;
	right = s->top;
	if (right == -1)
		return (-1);
	while (right >= left)
	{
		pivot = (left+right) / 2;
		if (s->list[pivot] == target)
			return (pivot);
		else
		{
			if (s->list[pivot] > target)
				right = pivot - 1;
			else
				left = pivot + 1;
		}
	}
	return (-1);
}

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

void	init(t_stack *a, t_stack *b, int num, char **data)
{
	int	i;
	int	ret;
	int	sret;

	i = num - 1;
	a->list = (int *)malloc(sizeof(int) * num);
	a->top = -1;
	a->bottom = -1;
	a->size = 0;
	a->capacity = i;
	b->list = (int *)malloc(sizeof(int) * num);
	b->top = -1;
	b->bottom = -1;
	b->size = 0;
	b->capacity = i;
	while (i > 0)
	{
		ret = ft_atoi(data[i]); // atoi 내부에서 예외 처리하도록 해야함
		sret = binary_search(a, ret); 
		if (sret != -1)
			pexit();
		push(a , ret);
		//printf("push : %d\n", a->size);
		i--;
	}
}

// 범위의 피벗을 찾기 위해 중앙값의 인덱스를 리턴.
// 일단 그냥 찾고,
// 이게 효용성 있으면
// 구조체로 a의 인덱스를 arr에 넣어서 두번 찾는걸 개선하자.
int	*step1(t_stack *a, int l, int r)
{
	int	*arr;
	int	i;
	int	j;
	int	size;

	i = l;
	j = 0;
	size = r - l + 1;
	arr = (int *)malloc(sizeof(int) * size);
	if (!arr)
		return (NULL);
	while (j < size)
	{
		arr[j] = a->list[i];
		i++;
		j++;
	}
	ft_sort_int_tab(arr, size);
	i=0;
	int search_data[2];
	int	*index;
	index = (int *)malloc(sizeof(int) * 2);
	index[0] = -1;
	index[1] = -1;
	search_data[0] = arr[size / 3];
	search_data[1] = arr[size * 2 / 3];

	//printf("searchdat %d, size : %d, r : %d\n", search_data, a->size, r);
	i = a->size - 1;
	while (i >= 0)
	{
		if (search_data[0] == a->list[i])
			index[0] = i;
		if (search_data[1] == a->list[i])
			index[1] = i;
		if (index[0] != -1 && index[1] != -1)
			return (index);
		i--;
	}
	return (NULL);
}

int	confirm_ordered(t_stack *a, int l, int r)
{
	int	i;
	int	size;
	int	min;

	size = r - l + 1;
	i = r;
	min = a->list[r];
	while (i > 0)
	{
		if (a->list[i] > a->list[i - 1])
			return (0);
		i--;
	}
	return (1);
}

int	confirm_ordered_desc(t_stack *a, int l, int r)
{
	int	i;
	int	size;
	int	min;

	size = r - l + 1;
	i = r;
	min = a->list[r];
	while (i > 0)
	{
		if (a->list[i] < a->list[i - 1])
			return (0);
		i--;
	}
	return (1);
}

void	a_to_b(t_stack *a, t_stack *b, int l, int r)
{
	int	*pivot;
	int	size;
	int	i;
	int	ra_cnt;
	int	pb_cnt;
	int	data;
	ra_cnt = 0;
	pb_cnt = 0;
	i = 0;
	size = r - l + 1;
	if (size == 1)
	{
		//printf("size 1 return !!!!!!!!!!!!!!!!!!");
		return ;
	}
	int confirm = 0;
	confirm = confirm_ordered(a, l, r);
	if (confirm == 1)
		return ;
	//write(1,"\nahs===============\n",20);
	if (size == 2 && a->top == r)
	{
		if (a->list[r] > a->list[l])
		{
			sa(a);
			return ;
		}
		else
			return ;
	}
	if (a->capacity == 3)
	{
		if (a->list[r] > a->list[l + 1])
		{
			if (a->list[l + 1] > a->list[l])
			{	
				// 3 2 1
                ra(a);
				sa(a);
				return ;
			}
			else if (a->list[l] > a->list[r])
			{
				sa(a);
				return ;
			}
			else
			{
				// 3 1 2
                ra(a);
				return ;
			}
		}
		else
		{
			if (a->list[r] > a->list[l])
			{
				// 2 3 1
                rra(a, 1);
				return ;
			}
			else if (a->list[l] > a->list[l + 1])
			{
				return ;
			}
			else
			{	// 1 3 2
                rra(a, 1);
                sa(a);
				return ;
			}
		}
	}

	if (size == 3 && a->top == r)
	{
		if (a->list[r] > a->list[l + 1])
		{
			if (a->list[l + 1] > a->list[l])
			{	
				// 3 2 1
				sa(a);
				pb(a, b);
				sa(a);
				pa(b, a);
				sa(a);
				return ;
			}
			else if (a->list[l] > a->list[r])
			{
				sa(a);
				return ;
			}
			else
			{
				// 3 1 2
				sa(a);
				pb(a, b);
				sa(a);
				pa(b, a);
				return ;
			}
		}
		else
		{
			if (a->list[r] > a->list[l])
			{
				// 2 3 1
				pb(a, b);
				sa(a);
				pa(b, a);
				sa(a);
				return ;
			}
			else if (a->list[l] > a->list[l + 1])
			{
				return ;
			}
			else
			{	// 1 3 2
				pb(a, b);
				sa(a);
				pa(b, a);
				return ;
			}
		}
	}

	//write(1,"\nahe===============\n",20);
	pivot = step1(a, l, r);
	//printf("a pivot : %d, %d list : %d, size : %d\n", pivot[0], pivot[1], a->list[pivot[0]], a->list[pivot[1]]);
	data = a->list[pivot[1]];
	int data2 = a->list[pivot[0]];
	int	rb_cnt = 0;
	//write(1,"\ns=================\n",20);
	while (i < size)
	{
					//printf("a data : %d, list : %d\n", data, a->list[a->top]);
		if (data <= a->list[a->top])
		{
			ra(a);
			ra_cnt++;
		}
		else
		{
			pb(a, b);
			pb_cnt++;
			if (data2 <= b->list[b->top])
			{
					rb(b);
					rb_cnt++;
			}
		}
		i++;
	}
	i = 0;
	int j = 0;
	//if (l != 0)
	//{
		while (i < ra_cnt && j < rb_cnt)
		{
			rrr(a, b, 1);
			i++;
			j++;
		}
		while (i < ra_cnt)
		{
			rra(a, 1);
			i++;
		}
		while (j < rb_cnt)
		{
			rrb(b, 1);
			j++;
		}
	//}
//	char *str_ra = ft_itoa(ra_cnt);
//	write(1, str_ra, ft_strlen(str_ra));
//	write(1,"\ne=================\n",20);
	//else
	//	printf("rrf : %d\n", ra_cnt);
	//printf("top : %d, l : %d, r : %d\n", a->top, l, r);
	//	write(1,"l\n",2);
	//printf("a->top : %d, ra_cnt : %d, rb_cnt : %d\n",a->top, ra_cnt,rb_cnt);
	if (ra_cnt != 0)
		a_to_b(a, b, a->top - (ra_cnt -1), a->top);// ra호출개수
	//show(a);
	//show(b);
	if (rb_cnt !=0)
	b_to_a(a, b, 0, rb_cnt -1);// pb 호출개수 -> rb 호출횟수
	//show(a);
	//show(b);
	if (pb_cnt - rb_cnt != 0)
	b_to_a(a, b, b->top - (pb_cnt -rb_cnt -1), b->top); // pb호출개수 - rb 호출회수
	//show(a);
	//show(b);
}

void	b_to_a(t_stack *a, t_stack *b, int l, int r)
{
	int	*pivot;
	int	size;
	int	i;
	int	rb_cnt;
	int	pa_cnt;
	int	data;

	rb_cnt = 0;
	pa_cnt = 0;
	i = 0;
	size = r - l + 1;
	if (size == 1)
	{
		pa(b, a);
		return ;
	}
	int confirm = 0;
	if (b->top == r)
	{
	confirm = confirm_ordered_desc(a, l, r);
	if (confirm == 1)
		{
			while (i < size)
			{
				pa(b, a);
				i++;
			}
			return ;
		}
	}
	if (size == 2 && b->top == r)
	{
		if (b->list[r] > b->list[l])
		{
			pa(b, a);
			pa(b, a);
			return ;
		}
		else
		{
			sb(b);
			pa(b, a);
			pa(b, a);
			
			return ;
		}
	}
	if (size == 3 && b->top == r)
	{
		if (b->list[r] > b->list[l + 1])
		{
			if (b->list[l + 1] > b->list[l])
			{	
				// 3 2 1
				pa(b, a);
				pa(b, a);
				pa(b, a);
				return ;
			}
			else if (b->list[l] > b->list[r])
			{
				// 2 1 3
/*
				pa(b, a);
				sb(b);
				pb(a, b);
				sb(b);
				pa(b, a);
				pa(b, a);
				pa(b, a);
				*/
				rb(b);
				sb(b);
				pa(b, a);
				rrb(b, 1);
				pa(b, a);
				pa(b, a);
				return ;
			}
			else
			{
				// 3 1 2
				pa(b, a);
				sb(b);
				pa(b, a);
				pa(b, a);
				return ;
				
			}
		}
		else
		{
			if (b->list[r] > b->list[l])
			{
				// 2 3 1
				sb(b);
				pa(b, a);
				pa(b, a);
				pa(b, a);
				return ;
			}
			else if (b->list[l] > b->list[l + 1])
			{
				// 1 2 3
				sb(b);
				rb(b);
				sb(b);
				pa(b, a);
				rrb(b, 1);
				pa(b, a);
				pa(b, a);
				/*sb(b);
				pa(b, a);
				sb(b);
				pb(a, b);
				sb(b);
				pa(b, a);
				pa(b, a);
				pa(b, a);*/
				return ;
			}
			else
			{	// 1 3 2
				sb(b);
				pa(b, a);
				sb(b);
				pa(b, a);
				pa(b, a);
				return ;
			}
		}

	}
	pivot = step1(b, l, r);
	//pivot = 2;
	//show(b);
	//printf("b pivot : %d, %d list : %d, size : %d\n", pivot[0], pivot[1], b->list[pivot[0]], b->list[pivot[1]]);
	data = b->list[pivot[1]];
	
	int data2 = b->list[pivot[0]];
	int	ra_cnt = 0;
//		write(1,"\nbs================\n",20);
	while (i < size)
	{
		if (data2 < b->list[b->top])
		{
			pa(b, a);
			pa_cnt++;
			if (data > a->list[a->top])
			{
				ra(a);
				ra_cnt++;
			}
		}
		else
		{
			rb(b);
			rb_cnt++;
		}
		i++;
	}
	//printf("pacnt : %d, ra_cnt : %d, rb_cnt : %d\n",pa_cnt, ra_cnt, rb_cnt);
	if (pa_cnt -ra_cnt  != 0)
		a_to_b(a, b, a->top - (pa_cnt -ra_cnt -1), a->top); // pa호출횟수 - ra호출횟수
	i = 0;
	int j = 0;
	//if (l != 0)
	//{
		while (i < ra_cnt && j < rb_cnt)
		{
			rrr(a, b, 1);
			i++;
			j++;
		}
		while (i < ra_cnt)
		{
			rra(a, 1);
			i++;
		}
		while (j < rb_cnt)
		{
			rrb(b, 1);
			j++;
		}
	//}
//	char *str_rb = ft_itoa(rb_cnt);
//	write(1, str_rb, ft_strlen(str_rb));

//	write(1,"\nbe================\n",20);
	if (ra_cnt != 0)
		a_to_b(a, b, a->top - (ra_cnt -1), a->top); //  pa호출회수-> ra호출횟수  
	if (rb_cnt != 0)
		b_to_a(a, b, b->top - (rb_cnt -1), b->top); // pb 호출회수-> rb호출횟수
}

int	main(int argc, char **argv)
{

	if (argc < 2)
		pexit();
	//t_node	top;
	//t_node	bottom;
	t_stack	a;
	t_stack	b;
	init(&a, &b, argc, argv);
//show(&a);	
//	int pivot = step1(&a, 0, (&a)->size -1);	
//printf("pivot : %d\n", pivot);
	a_to_b(&a, &b, 0, (&a)->size -1);
//printf("\n======================프로그램 종료\n");	
//	show(&a);
//	show(&b);
	//show(&a);
	//show(&b);

	//printf("%d %d", (&a)->top, (&a)->list[5]);
	//printf("%d ",*(int*)((&top)->next->data));
	//printf("%d ",*(int*)((&top)->next->next->data));
	return (0);
}
