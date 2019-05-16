#include <vector>
#include <string>

class Tokenizer {
    private:
        //std::vector<int> *data;
        bool isNumber(std::string s);
        std::vector<std::string> svec;
    public:
        Tokenizer();
        ~Tokenizer();
        void Tokenize(std::string tokenize);
        std::vector<std::string> GetTokens();
        std::vector<std::string> *data;
        std::vector<std::string> garbagecontainer;
        std::vector<std::string> scontainer;
};
