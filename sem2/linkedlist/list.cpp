#include "list.h"

void List::insert(int i)
{
    Link *tmp = new Link{i};
    if (head == nullptr)
    {
        head = tmp;
    }
    else if (i < head->value)
    {
        tmp->nxt = head;
        head = tmp;
    }
}