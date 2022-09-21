class List
{
private:
    struct Link
    {
        Link() : value{} {};
        Link(int i) : value{i} {};

        int value;
        Link *nxt = nullptr;
        bool print_link();
    };

    Link *head;

public:
    List() : head{nullptr} {};
    List(int i) : head{new Link(i)} {};

    ~List();

    void insert(int);
    void insert_next(Link *, Link *);

    void remove(int);
    void remove_next(Link *, Link *, int);

    int at(int);
    int find(Link *, int);

    void print_list();
};