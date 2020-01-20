#include <napi.h>
#include <windows.h>

namespace functionexample {
    void sendKeys(const std::string &inputString);
    void SendKeysWrapped(const Napi::CallbackInfo& info);

    Napi::Object Init(Napi::Env env, Napi::Object exports);
}
