/* alloc.c */
#include "alloc.h"

extern heap *memspace;

void *alloc(int32 bytes) {
    word words;
    header *hdr;
    void *mem;

    words = (!(bytes % 4)) ?
            bytes/4 :
        (bytes/4) + 1;
    
    mem = $v memspace;
    hdr = $h mem;

    hdr->w = 1;

    (!(hdr->w)) ? ({
        printf("empty\n");
        exit(0);
    })
    : ({
        printf("bla\n");
        exit(0);
    });

    return $v 0;
}

int main(int argc, char *argv[]) {
    alloc(7);

    return 0;
}