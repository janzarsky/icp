#include <string>

using namespace std;

namespace solitaire
{
    class InvalidActionException: public exception
    {
        string msg;

    public:
        InvalidActionException(string message): msg{message} {}

        string message() {
            return msg;
        }
    };
}
