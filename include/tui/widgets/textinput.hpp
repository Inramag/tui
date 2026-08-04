#pragma once

#include <tui/widget.hpp>

#include <tui/scene.hpp>

class TextInput : public Widget {
public:
    TextInput(std::string _name, std::string _text = "");
    TextInput(std::string _name, std::wstring _text = L"");
    TextInput(std::wstring _name, std::string _text = "");
    TextInput(std::wstring _name, std::wstring _text = L"");
    ~TextInput() override = default;

    std::wstring name;

    std::wstring get() const;

protected:
    std::wstring render() const override;

private:
    std::wstring text;
    std::wstring buff;

    Scene* parent{};
    Scene scene;
};