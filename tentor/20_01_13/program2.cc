#include <vector>
#include <string>
#include <sstream>
#include <iostream>

/* This function is an implementation for the parse function of the
   Parser class. You will have to include this implementation as a
   member function in the Parser class.

   The goal of this function is to match each option in the options
   vector with an argument from the args vector (i.e. parse the
   arguments).

   In this simplified framework the position of each argument and flag
   matters. Example:
   
   In main we create a parser that has two flags: -a, and --b-flag as
   well as two arguments: int and string. The following cases are allowed:

   ./a.out -a --b-flag 5 hello
   ./a.out -a 5 hello
   ./a.out --b-flag 5 hello
   ./a.out 5 hello

   While cases such as:

   ./a.out 5 -a hello
   ./a.out 5 hello --b-flag
   ./a.out --b-flag -a 5 hello

   are not. Meaning that the order is important, if the -a flag is
   present it must be the first argument, and if --b-flag is present
   it must come before the int argument. The int and string arguments
   must be given in order. This is because we parse each option in the
   same order as they appear in the options vector. Flags can be
   skipped but the order must still be preserved.

   The parse function already deals with this case but you have to
   complete the implementation by replacing the comments with actual
   code.
 */
class Option{
    public:
        Option(std::string const& n) : name{n}{};

        Option& operator=(Option const&) = delete;
        Option(Option&) = delete;


        virtual ~Option() = default;
        virtual bool parse(std::string const& args) const = 0;
        virtual void print(std::ostream& os) const;
    protected:
        std::string name;
};

class Flag : public Option{
    public:
        Flag(std::string const& n, bool& b) : Option(n),is_present{b}{is_present = false;}
        bool parse(std::string const& args) const override;
        void print(std::ostream& os) const override;
    private:
        bool& is_present;
};

template <typename T>
class Argument : public Option
{
    public:
        Argument(std::string const& n, T & t) : Option(n),target{t}{};
        bool parse(std::string const& args) const override;

    private:
        T& target;
};

class Parser
{
    public:
        bool parse(std::vector<std::string> const& args);
        void print(std::ostream& os, std::string const& program) const;
        void add(Option* option);
        ~Parser()
        {
            for(auto e : options)
                delete e;
        }
    private:
    std::vector<Option*> options;
};

// Option
void Option::print(std::ostream& os) const
{
    os<<name;
}

// Flag
bool Flag::parse(std::string const& args) const {
    if(args == name)
        {
        is_present = true;
        return true;
        }
    else
    {
        return false;
    }
}
void Flag::print(std::ostream& os) const {
    os<<'['<<name<<']';
}

// Argument
template<typename T>
bool Argument<T>::parse(std::string const& args) const {
    std::istringstream iss{args};

    if(iss>>target)
    {
        std::cout<<"Argument added to target: "<<target<<std::endl;
        return true;
    }
    else
    {
        return false;
    }
}


// Parser
bool Parser::parse(std::vector<std::string> const& args)
{
    if (args.empty())
    {
        std::cerr << "No arguments given." << std::endl;
        return false;
    }

    int i{0};
    
    for (Option* option : options)
    {

        if (i < args.size())
        {
            if (option->parse(args[i]))/* call parse(args[i]) on option */ 
            {
                ++i;
            }
            else if (typeid(Flag) != typeid(*option))/* option is not of type Flag */
            {
                std::cerr << "Unknown argument: " << args[i] << std::endl;
                return false;
            }
        }
        else if (typeid(Flag) != typeid(*option))/* option is not of type Flag */
        {
            std::cerr << "Too few arguments" << std::endl;
            return false;
        }
        
    }

    if (i < args.size())
    {
        std::cerr << "Too many arguments." << std::endl;
        return false;
    }
    std::cout<<"Hit-sist"<<std::endl;
    
    return true;
}
/* print algorithm for Parser */
void Parser::print(std::ostream& os, std::string const& program) const
{
    os << "Usage: " << program;
    for (Option * option : options)
    {
        os << " ";
        /* call print(os) on option */
        option->print(os);
    }
    os << std::endl;
}

void Parser::add(Option* option)
{
    options.push_back(option);    
}


/*

  Example of usage:

$ ./a.out 
No arguments given.
Usage: ./a.out [-a] [--b-flag] int string

$ ./a.out -a 5
Too few arguments
Usage: ./a.out [-a] [--b-flag] int string

$ ./a.out -a hello
Unknown argument: hello
Usage: ./a.out [-a] [--b-flag] int string

$ ./a.out --b-flag -a 5 hello
Unknown argument: -a
Usage: ./a.out [-a] [--b-flag] int string

$ ./a.out -a 5 hello
a == 1
b == 0
num == 5
str == hello

$ ./a.out -a --b-flag 5 hello
a == 1
b == 1
num == 5
str == hello

 */
int main(int argc, char** argv)
{
    std::vector<std::string> args {argv + 1, argv + argc};
    Parser p{};

    bool a{};
    p.add( new Flag{"-a", a});

    bool b{};
    p.add(new Flag{"--b-flag", b} );

    int num{};
    p.add(new Argument<int>{"int", num} );

    std::string str{};
    p.add(new Argument<std::string>{"string", str});
    if (!p.parse(args))
    {
         p.print(std::cerr, argv[0]);
         
    }
    else
    {
        std::cout << "a == " << a << std::endl
                  << "b == " << b << std::endl
                  << "num == " << num << std::endl
                  << "str == " << str << std::endl;
    }
}