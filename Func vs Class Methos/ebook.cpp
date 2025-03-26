#include <cstdint>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

class Book {
private:
    std::unordered_map<int, int> pages_for_users_; // max page for each user. user_id, max_page.
    std::map<int, int> users_for_pages_; // number of users read page. page_number, number of users.

public:
    void Read(int user_id, int page_count) {
        auto old_page = pages_for_users_[user_id];
        if (users_for_pages_[old_page] == 1) {
            users_for_pages_.erase(old_page);
        }
        else if (users_for_pages_[old_page] > 1) {
            users_for_pages_[old_page] -= 1;
        }
        users_for_pages_[page_count] += 1;
        pages_for_users_[user_id] = page_count;
    }

    double Cheer(int user_id) {
        if (pages_for_users_.find(user_id) == pages_for_users_.end()) {
            return 0.;
        }
        else {
            auto users_quantity = pages_for_users_.size(); // number of users
            if (users_quantity == 1) {
                return 1.;
            }
            else {
                auto user_page = pages_for_users_[user_id];
                auto max_users_for_pages_it = users_for_pages_.find(user_page);
                if (max_users_for_pages_it == users_for_pages_.begin()) {
                    return 0.;
                }
                int users_less_page = 0;
                auto it = users_for_pages_.begin();
                while (it != max_users_for_pages_it) {
                    users_less_page += it->second;
                    ++it;
                }
                return users_less_page * 1. / (users_quantity - 1);
            }
        }
    }
};

int main() {
    Book book;
    int32_t requests;
    std::cin >> requests;
    std::cin.ignore();
    for (int32_t i = 0; i < requests; ++i) {
        std::string request;
        std::getline(std::cin, request);
        auto space_pos = request.find_first_of(" ");
        std::string request_type = request.substr(0, space_pos);
        if (request_type == "CHEER") {
            uint32_t user_id = std::stoi(request.substr(space_pos + 1));
            auto result = book.Cheer(user_id);
            std::cout << std::setprecision(6) << result << "\n";
        } else if (request_type == "READ") {
            auto second_space_pos = request.find_first_of(" ", space_pos + 1);
            auto user_id = std::stoi(request.substr(space_pos, space_pos - second_space_pos));
            auto page = std::stoi(request.substr(second_space_pos));
            book.Read(user_id, page);
        }
    }
}