class List
{
private:
    struct Link
    {
        Link() : value{} {};
        Link(int i) : value{i} {};

        int value;
        Link *nxt = nullptr;
    };

    Link *head;

public:
    List() : head{nullptr} {};
    List(int i) : head{new Link(i)} {};

    void insert(int);
    void print_list();
};