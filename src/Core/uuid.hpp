#ifndef UUID_H
#define UUID_H

#include <cstdint>

class UUID
{
    public:
        UUID();
        UUID(uint64_t uuid);
        UUID(const UUID&) = default;

    private:
        uint64_t m_UUID;
};

#endif