#pragma once
#include <ios>
#include <sstream>

enum class Error
{
    NoError,
    CorruptedArchive
};

class Serializer
{
    static constexpr char Separator = ' ';
    std::ostream& out_;

    template <class T>
    Error process(T&& value) {
        return serialize(value);
    }

    template <class T, class... Args>
    Error process(T&& value, Args&&... args) {
        return (process(value) == Error::CorruptedArchive) ? Error::CorruptedArchive : process(std::forward<Args>(args)...);
    }

    Error serialize(bool value) {
        out_ << std::boolalpha << value << Separator;
        return (out_) ? Error::NoError : Error::CorruptedArchive;
    }

    Error serialize(uint64_t value) {
        out_ << value << Separator;
        return (out_) ? Error::NoError : Error::CorruptedArchive;
    }

public:
    explicit Serializer(std::ostream& out)
        : out_(out)
    {
    }

    template <class T>
    Error save(T& object)
    {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT... args)
    {
        return process(args...);
    }
};


class Deserializer
{
private:
    std::istream& in_;

    template <class T>
    Error process(T& value) {
        return deserialize(value);
    }

    template <class T, class... Args>
    Error process(T& value, Args&&... args) {
        return (process(value) == Error::CorruptedArchive) ? Error::CorruptedArchive : process(std::forward<Args>(args)...);
    }

    Error deserialize(bool& value) {
        in_ >> std::boolalpha >> value;
        return in_ ? Error::NoError : Error::CorruptedArchive;
    }

    Error deserialize(uint64_t& value) {
        std::string s;

        in_ >> s;
        if (s.length() > 0 && std::all_of(s.begin(), s.end(), isdigit)) {
            value = std::stoi(s);
            return Error::NoError;
        }
        return Error::CorruptedArchive;
    }

public:
    explicit Deserializer(std::istream& in)
        : in_(in)
    {
    }

    template <class T>
    Error load(T& object) {
        return object.deserialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&&... args) {
        return process(args...);
    }
};
