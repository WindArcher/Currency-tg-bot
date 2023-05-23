#include <tgbot/tgbot.h>
#include "currency_parser.h"
#include <vector>

class CurrencyTgBot
{
public:
    CurrencyTgBot();
    ~CurrencyTgBot();
    void start();
private:
    CurrencyParser m_parser;
    TgBot::Bot m_bot;
    TgBot::InlineKeyboardMarkup::Ptr m_keyboard;
    void setUp();
    void keyboardSetUp();
    std::vector<TgBot::InlineKeyboardButton::Ptr> buttons;
};