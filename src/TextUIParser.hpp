namespace solitaire
{
    // TODO
    enum CmdType { help, new_game, close_game, exit, move_card, invalid };

    struct UICommand
    {
        CmdType type;

        UICommand(CmdType type): type{type} {}
        UICommand() {}
    };

    class TextUIParser
    {
    public:
        UICommand getCommand();
    };
}
