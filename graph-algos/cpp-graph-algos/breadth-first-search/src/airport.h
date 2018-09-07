#ifndef ITEM_H
#define ITEM_H

class Airport
{
private:
    std::string city;
    std::string code;

public:
    Airport(std::string city, std::string code)
    {
        this->city = city;
        this->code = code;
    }

    std::string get_city() { return city; }
    std::string get_code() { return code; }

    void set_city(std::string city) { this->city = city; }
    void set_code(std::string code) { this->code = code; }
};

#endif // ITEM_H
