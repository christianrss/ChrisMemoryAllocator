/* alloc.c */
#include "alloc.h"

extern heap *memspace;

void *mkalloc(word words, header *hdr) {
    void *ret, *bytesin;
    word wordsin;

    bytesin = ($v (($v hdr) - memspace));
    wordsin = (((word)bytesin)/4)+1;
    if (words > (Maxwords-wordsin))
        reterr(ErrNoMem);
     
    hdr->w = words;
    hdr->alloced = true;
    ret = ($v hdr)+4;

    return ret;
}

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
        if (words > Maxwords)
            reterr(ErrNoMem);

        mem = mkalloc(words, hdr);
        if(!mem)
            return $v 0;

        return mem;
    })
    : ({
        (void)0;
    });

    return $v 0;
}

int main(int argc, char *argv[]) {
    int8 *p;

    p = alloc(7);
    printf("0x%x\n", $i p);

    return 0;
}