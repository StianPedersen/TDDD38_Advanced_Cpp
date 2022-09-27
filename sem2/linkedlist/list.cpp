#include "list.h"
#include <iostream>

List::~List(){};

void List::insert_next(std::unique_ptr<Link> &cur, std::unique_ptr<Link> &ins)
{
    if (cur->nxt == nullptr)
    {
        cur->nxt = std::move(ins);
        ins->nxt = nullptr;
        return;
    }
    else if (ins->value < cur->value)
    {
        ins->nxt = std::move(cur->nxt);
        cur->nxt = std::move(ins);
        return;
    }
    else
    {
        insert_next(cur->nxt, ins);
    }
};

void List::insert(int i)
{
    std::unique_ptr<Link> tmp(std::make_unique<Link>(i));
    if (head == nullptr)
    {
        head = std::move(tmp);
        return;
    }
    else if (i < head->value)
    {
        tmp->nxt = std::move(head);
        head = std::move(tmp);
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

void List::remove_next(std::unique_ptr<Link> &cur, std::unique_ptr<Link> &check, int i)
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
            cur->nxt = std::move(check->nxt);
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
            head = std::move(head->nxt);
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

int List::find(std::unique_ptr<Link> &cur, int i)
{
    if (i == 0)
        return cur->value;
    else
        return find(cur->nxt, i - 1);
}
