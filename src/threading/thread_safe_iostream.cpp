#include "threading/thread_safe_iostream.hpp"

thread_local ThreadSafeIOStream threadSafeCout;

ThreadSafeIOStream::ThreadSafeIOStream() : prefix_("") {}

void ThreadSafeIOStream::setPrefix(const std::string& prefix) {
    std::lock_guard<std::mutex> lock(mtx_);
    prefix_ = prefix;
}
