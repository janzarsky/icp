#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QBoxLayout>

using namespace std;

namespace solitaire
{
    class GUIGame: public QBoxLayout
    {
        void initLayout();

    public:
        GUIGame();
    };
}
