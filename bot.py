from telegram.ext import Updater, CommandHandler, MessageHandler, Filters

def send_poem(update, context):
    chat_id = update.effective_chat.id
    poem = """Dear Uncle Elyor,
                My name is [Your Name],
                I hope you're doing well,
                Here's a poem I wrote for you,
                I hope it brings you joy and a smile as well.

                [Insert your joyful poem here]

                Love,
                [Your Name]"""
    context.bot.send_message(chat_id=chat_id, text=poem)

updater = Updater('5059009542:AAHHd0bAnKJtsN18D8hDwjUaI__b5eKjkes', use_context=True)

updater.dispatcher.add_handler(MessageHandler(Filters.text, send_poem))

updater.start_polling()
updater.idle()
