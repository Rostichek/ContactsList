#pragma once
#include <vector>
#include <string>
#include <memory>

class ContactListProvider
{
public:
    struct Contact {
        std::shared_ptr<std::string> name;
        size_t id;
    };

public:
    ContactListProvider() = default;

    void call(size_t id) const {}

    const std::vector<Contact>& GetContactList() const { return contacts; };

private:
    std::vector<Contact> contacts = {
        { std::make_shared<std::string>("Kevin Green"), 0 },
        { std::make_shared<std::string>("John Bob"), 1 },
        { std::make_shared<std::string>("Vlad"), 2 },
        { std::make_shared<std::string>("Cheap pizza"), 3 }
    };
};
