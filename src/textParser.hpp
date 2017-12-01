#ifndef TEXT_PARSER
#define TEXT_PARSER
#include <string>

class Parser
{
public:
Parser();
void getInput();
void commands();
private:
//int _parameter;
enum verb{move, stop, jump}
};

#endif