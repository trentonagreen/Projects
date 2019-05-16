#include <vector>
#include <string>

class Parser{
    private:
        bool isNumber(std::string s);
    public:
        Parser();
        ~Parser();
        bool Parse(std::vector<std::string> vec);
};
