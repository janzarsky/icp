namespace solitaire
{
    enum CmdType { help, new_game, close_game, switch_game, games, quit, invalid };

    struct UICommand
    {
        CmdType type;
        int switch_to;

        UICommand(CmdType type): type{type} {}
        UICommand() {}
    };

    class TextUIParser
    {
    public:
        UICommand getCommand();
    };
}
