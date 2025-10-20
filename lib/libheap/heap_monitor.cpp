#include "heap_monitor.hpp"

#undef new

#include <cstdlib>
#include <iostream>

namespace fri {

namespace details {

HeapMonitor::~HeapMonitor() {
    if (m_allocations.empty()) {
        return;
    }

    std::map<std::string, int> leaks;
    for (const auto &[p, loc] : m_allocations) {
        ++leaks[loc];
    }

    std::cerr << "\n\n~~~\nDetected memory leaks!\n";
    for (const auto &[loc, count] : leaks) {
        std::cerr << "  " << loc << "\t" << count << "x" << "\n";
    }
    std::cerr << "\n";
}

void HeapMonitor::logAllocation(void *p, std::string file, int line) {
    const std::intptr_t ip = reinterpret_cast<std::intptr_t>(p);
    std::string loc = file + ":" + std::to_string(line);
    (void)m_allocations.try_emplace(ip, std::move(loc));
}

void HeapMonitor::logDeletion(void *p) {
    (void)m_allocations.erase(reinterpret_cast<std::intptr_t>(p));
}

} // namespace details

} // namespace fri

void *operator new (std::size_t sz, const char *file, int line) {
    void *p = std::malloc(sz);
    ::fri::details::HeapMonitor::getInstance().logAllocation(p, file, line);
    return p;
}

void operator delete (void *p) noexcept {
    ::fri::details::HeapMonitor::getInstance().logDeletion(p);
    std::free(p);
}

void operator delete (void *p, std::size_t n) noexcept {
    (void)n;
    ::fri::details::HeapMonitor::getInstance().logDeletion(p);
    std::free(p);
}
