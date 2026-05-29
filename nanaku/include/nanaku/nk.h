#ifndef NANAKU_NK_H
#define NANAKU_NK_H

struct nkVersion
{
    const char* name;
    unsigned char major;
    unsigned char minor;
    unsigned char patch;
    void* user;
};
#define NK_VERSION \
{ \
    .name = "Nanase Kurumi", \
    .major = 1, \
    .minor = 1, \
    .patch = 1, \
    .user = NULL \
}
#define NK_VERSION_TO_UINT(MAJOR, MINOR, PATCH) \
    (((uint32_t)(MAJOR) << 16) | ((uint32_t)(MINOR) << 8) | (uint32_t)(PATCH))
#define NK_UINT_TO_MAJOR(VERSION) (((VERSION) >> 16) & 0xFF)
#define NK_UINT_TO_MINOR(VERSION) (((VERSION) >> 8) & 0xFF)
#define NK_UINT_TO_PATCH(VERSION) ((VERSION) & 0xFF)

#endif
