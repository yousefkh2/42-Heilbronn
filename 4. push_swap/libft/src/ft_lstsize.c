int ft_lstsize(t_list *lst)
{
	int count = 0;
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return count;
}