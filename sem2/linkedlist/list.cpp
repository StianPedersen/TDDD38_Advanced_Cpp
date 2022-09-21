#include "list.h"
#include <iostream>

List::~List(){};

void List::insert_next(Link *cur, Link *ins)
{
    if (cur->nxt == nullptr)
    {
        cur->nxt = ins;
        ins->nxt = nullptr;
        return;
    }
    else if (ins->value < cur->value)
    {
        ins->nxt = cur->nxt;
        cur->nxt = ins;
        return;
    }
    else
    {
        insert_next(cur->nxt, ins);
    }
};

void List::insert(int i)
{
    Link *tmp = new Link{i};
    if (head == nullptr)
    {
        head = tmp;
        return;
    }
    else if (i < head->value)
    {
        tmp->nxt = head;
        head = tmp;
        return;
    }
    else
    {
        insert_next(head, tmp);
    }
}

void List::print_list()
{
    head->print_link();
};

bool List::Link::print_link()
{
    std::cout << value << " ";
    if (nxt != nullptr)
        return nxt->print_link();
    else
    {
        std::cout << "\n";
        return false;
    }
}

void List::remove_next(Link *cur, Link *check, int i)
{
    if (check->value == i)
    {
        if (check->nxt == nullptr)
        {
            cur->nxt = nullptr;
            return;
        }
        else
        {
            cur->nxt = check->nxt;
            return;
        }
    }
    else
    {
        remove_next(check, check->nxt, i);
    }
}

void List::remove(int i)

{

    if (head->value == i)
    {
        if (head->nxt != nullptr)
        {
            head = head->nxt;
            return;
        }
        else
        {
            head = nullptr;
            return;
        }
    }
    else
    {
        remove_next(head, head->nxt, i);
    }
}

int List::at(int i)
{
    if (i == 0)
        return head->value;
    else
    {
        return find(head->nxt, i - 1);
    }
}

int List::find(Link *cur, int i)
{
    if (i == 0)
        return cur->value;
    else
        return find(cur->nxt, i - 1);
}
