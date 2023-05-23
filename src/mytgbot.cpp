#include "mytgbot.h"
#include <filesystem>

const auto BOTKEY = "6054289843:AAHkZu3bFTBi8Ov1eR74SyrhqLqedhAqh1U"; 

CurrencyTgBot::CurrencyTgBot() : m_bot(BOTKEY), m_keyboard(new TgBot::InlineKeyboardMarkup)
{
    CurrencyTgBot::currencyButtonsSetUp();
    CurrencyTgBot::setUp();
}

void CurrencyTgBot::setUp()
{  
    startCommandReplySetUp();
    currencyCommandReplySetUp();
    onQueryResponseSetUp();
}

void CurrencyTgBot::currencyButtonsSetUp()
{
    addButton("USD", "USD");
    addButton("EUR", "EUR");
    addButton("RUB","RUB");
    m_keyboard->inlineKeyboard.push_back(m_buttons);
}

void CurrencyTgBot::startCommandReplySetUp()
{
    m_bot.getEvents().onCommand("start", [&](TgBot::Message::Ptr message) 
    {
        m_bot.getApi().sendMessage(message->chat->id, "Hi! I am currency bot!"); 
        m_parser.requestData();//should it be so?
    } );
}

void CurrencyTgBot::currencyCommandReplySetUp()
{
    
    m_bot.getEvents().onCommand("currency", [&](TgBot::Message::Ptr message) 
    {
        m_bot.getApi().sendMessage(message->chat->id, "What currency?", false, 0, m_keyboard); 
    });
}

void CurrencyTgBot::onQueryResponseSetUp()
{
     m_bot.getEvents().onCallbackQuery([&](TgBot::CallbackQuery::Ptr query)
    {
        if(query->data == "USD") 
            m_bot.getApi().sendMessage(query->message->chat->id, m_parser.rateToUAH(CurrencyParser::Currency::usd));
        else if(query->data == "EUR") 
            m_bot.getApi().sendMessage(query->message->chat->id, m_parser.rateToUAH(CurrencyParser::Currency::eur));
        else if(query->data == "GBP")
            m_bot.getApi().sendMessage(query->message->chat->id, m_parser.rateToUAH(CurrencyParser::Currency::gbp));
        else if(query->data == "RUB")
        {
            static std::string imagePath = std::filesystem::current_path().string() + "/decringe.png"; 
            if(std::filesystem::exists(imagePath))
                m_bot.getApi().sendPhoto(query->message->chat->id, TgBot::InputFile::fromFile(imagePath,"image/png"));
            else
                std::cout << "Not found";
        }
        else
            m_bot.getApi().sendMessage(query->message->chat->id, "Magic query: don`t know what to do" );
    });
}

void CurrencyTgBot::addButton(std::string buttonText, std::string callbackData)
{
    m_buttons.emplace_back(new TgBot::InlineKeyboardButton);
    m_buttons.back()->text = buttonText;
    m_buttons.back()->callbackData = callbackData;
}

void CurrencyTgBot::start()
{
    try {
        printf("Bot username: %s\n", m_bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(m_bot);
        while (true) {
            printf("Long poll started\n");
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }
}
