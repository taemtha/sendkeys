
#define WINVER 0x0500
#include "sendkeys.h"

void functionexample::sendKeys(const std::string &inputString)
{
    std::for_each(inputString.begin(), inputString.end(), [](char const &character) {
        INPUT ip;

        ip.type = INPUT_KEYBOARD;
        ip.ki.wScan = 0;
        ip.ki.time = 0;
        ip.ki.dwExtraInfo = 0;
        
        ip.ki.wVk = 0;
        ip.ki.wScan = character;
        ip.ki.dwFlags = KEYEVENTF_UNICODE;

        SendInput(1, &ip, sizeof(INPUT));

        ip.ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
        SendInput(1, &ip, sizeof(INPUT));
    });
}

void functionexample::SendKeysWrapped(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsString())
    {
        Napi::TypeError::New(env, "String expected").ThrowAsJavaScriptException();
    }

    Napi::String inputString = info[0].As<Napi::String>();
    functionexample::sendKeys(inputString.Utf8Value());
    
}

Napi::Object functionexample::Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("sendKeys", Napi::Function::New(env, functionexample::SendKeysWrapped));
    return exports;
}