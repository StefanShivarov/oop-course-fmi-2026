#include <iostream>
#include <cstring>
#include <print>
#pragma warning(disable:4996)

namespace Constants {
    constexpr int MaxLogMessageLength = 100;
	constexpr int MaxMessagesCount = 100;
    constexpr int MaxTimestampLength = 20;
    constexpr int ValidTimestampLength = 8;
    constexpr int MinHours = 0;
    constexpr int MaxHours = 23;
    constexpr int MinMinutes = 0;
    constexpr int MaxMinutes = 59;
    constexpr int MinSeconds = 0;
    constexpr int MaxSeconds = 59;
}

namespace Logs {
    enum class MessageType {
        Info,
        Warning,
        Error,
        Debug
	};

    MessageType parseCharToMessageType(char messageType) {
        switch (messageType) {
            case 'I': return MessageType::Info;
            case 'W': return MessageType::Warning;
            case 'E': return MessageType::Error;
            case 'D': return MessageType::Debug;
        }
    }

    char parseMessageTypeToChar(MessageType messageType) {
        switch (messageType) {
            case MessageType::Info: return 'I';
            case MessageType::Warning: return 'W';
            case MessageType::Error: return 'E';
            case MessageType::Debug: return 'D';
        }
	}

    bool validateTimestamp(const char* timestamp) {
        if (std::strlen(timestamp) != Constants::ValidTimestampLength) return false;
        if (timestamp[2] != ':' || timestamp[5] != ':') return false;

        for (int i = 0; i < Constants::ValidTimestampLength; i++) {
            if (i == 2 || i == 5) continue;

            if (!std::isdigit(timestamp[i])) return false;
        }

        int hours = (timestamp[0] - '0') * 10 + (timestamp[1] - '0');
        int minutes = (timestamp[3] - '0') * 10 + (timestamp[4] - '0');
        int seconds = (timestamp[6] - '0') * 10 + (timestamp[7] - '0');

        if (
            hours < Constants::MinHours || hours > Constants::MaxHours || 
            minutes < Constants::MinMinutes || minutes > Constants::MaxMinutes || 
            seconds < Constants::MinSeconds || seconds > Constants::MaxSeconds) {
            return false;
        }

		return true;
	}

    int parseTimestampToInt(const char* timestamp) {
        if (!validateTimestamp(timestamp)) return -1;

		int hours = (timestamp[0] - '0') * 10 + (timestamp[1] - '0');
        int minutes = (timestamp[3] - '0') * 10 + (timestamp[4] - '0');
        int seconds = (timestamp[6] - '0') * 10 + (timestamp[7] - '0');
		return hours * 60 * 60 + minutes * 60 + seconds;
	}

    struct Log {
    private:
        struct Message {
            int timestamp = 0;
            MessageType type;
            char timestampText[Constants::ValidTimestampLength + 1];
            char text[Constants::MaxLogMessageLength];

            void print(std::ostream& os = std::cout) const {
                std::print(os, "Time: {}; ", timestampText);
                std::print(os, "Message type: {}; ", parseMessageTypeToChar(type));
                std::print(os, "Message: {}; ", text);
                std::println(os);
            }
        };

		Message messages[Constants::MaxMessagesCount];
        int messageCount = 0;
		int infoMessagesCount = 0;
		int warningMessagesCount = 0;
		int errorMessagesCount = 0;
		int debugMessagesCount = 0;

        void updateMessageCounts(const MessageType& type) {
            switch (type) {
                case MessageType::Info: infoMessagesCount++; break;
                case MessageType::Warning: warningMessagesCount++; break;
                case MessageType::Error: errorMessagesCount++; break;
                case MessageType::Debug: debugMessagesCount++; break;
            }
		}

        void addMessage(const Message& message) {
            if (messageCount < Constants::MaxMessagesCount) {
                messages[messageCount] = message;
                messageCount++;

                updateMessageCounts(message.type);
            }
        }

        void readMessage() {
            Message message;

            char timestampText[Constants::MaxTimestampLength + 1];
            std::cin >> timestampText;
            message.timestamp = parseTimestampToInt(timestampText);
			strcpy(message.timestampText, timestampText);

            char messageTypeChar;
            std::cin >> messageTypeChar;
            message.type = parseCharToMessageType(messageTypeChar);

			std::cin.ignore();

            char messageText[Constants::MaxLogMessageLength];
            std::cin.getline(messageText, Constants::MaxLogMessageLength);
            std::strcpy(message.text, messageText);

            addMessage(message);
        }

        void sortMessages() {
            for (int i = 0; i < messageCount - 1; i++) {
                for (int j = 0; j < messageCount - i - 1; j++) {
                    if (messages[j].timestamp > messages[j + 1].timestamp) {
                        std::swap(messages[j], messages[j + 1]);
                    }
                }
            }
		}

    public:
        void readMessages(int messageCount) {
            for (int i = 0; i < messageCount; i++) {
                readMessage();
            }

			sortMessages();
        }

        void printMessages() const {
            for (int i = 0; i < messageCount; i++) {
                messages[i].print();
			}
        }

        void printMessagesByType(MessageType type) const {
            for (int i = 0; i < messageCount; i++) {
                if (messages[i].type == type) {
                    messages[i].print();
                }
            }
		}

        void printEarliestAndLatestMessage() const {
            if (messageCount > 0) {
                std::println("Earliest message:");
                messages[0].print();

                std::println("Latest message:");
				messages[messageCount - 1].print();
            }
		}

        void printMessagesInTimeRange(const char* startTime, const char* endTime) const {
            int startTimestamp = parseTimestampToInt(startTime);
            int endTimestamp = parseTimestampToInt(endTime);

            for (int i = 0; i < messageCount; i++) {
                if (messages[i].timestamp >= startTimestamp && messages[i].timestamp <= endTimestamp) {
                    messages[i].print();
                }
            }
        }

        void printStats() const {
            std::println("Total messages: {}", messageCount);
            std::println("Info messages: {}", infoMessagesCount);
            std::println("Warning messages: {}", warningMessagesCount);
            std::println("Error messages: {}", errorMessagesCount);
            std::println("Debug messages: {}", debugMessagesCount);
        }
    };
}

int main()
{
	using namespace Logs;

    int n;
	std::cin >> n;

	Log log;
	log.readMessages(n);

    log.printStats();
    std::println();

    log.printMessages();
    std::println();

	log.printEarliestAndLatestMessage();
    std::println();

    log.printMessagesInTimeRange("09:00:00", "17:00:00");
    std::println();

	log.printMessagesByType(MessageType::Error);
    std::println();
}
