#include <memory>
class List
{
private:
    struct Link
    {
        Link() : value{} {};
        Link(int i) : value{i} {};

        int value;
        std::unique_ptr<Link> nxt = nullptr;
        bool print_link();
    };

    std::unique_ptr<Link> head;

public:
    List() : head{nullptr} {};
    List(int i) : head{new Link(i)} {};

    ~List();

    void insert(int);
    void insert_next(std::unique_ptr<Link> &, std::unique_ptr<Link> &);

    void remove(int);
    void remove_next(std::unique_ptr<Link> &, std::unique_ptr<Link> &, int);

    int at(int);
    int find(std::unique_ptr<Link> &, int);

    void print_list();
};