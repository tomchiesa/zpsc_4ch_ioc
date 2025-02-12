
#include "devcommon.h"

int parse_link(Priv* priv, const char* link, int direction)
{
    std::istringstream strm(link);

    std::string name;
    unsigned int block;
    unsigned long offset = 0;

    strm >> name >> block;
    if(!strm.eof())
        strm >> offset;
    if(strm.bad()) {
        fprintf(stderr, "%s: Error Parsing: '%s'\n",
                priv->prec->name, link);
        return 1;
    }

    priv->psc = PSC::getPSC(name);
    if(!priv->psc) {
        fprintf(stderr, "%s: PSC '%s' not found\n",
                priv->prec->name, name.c_str());
        return 1;
    }

    priv->bid = block;
    priv->offset = offset;

    Guard(priv->psc->lock);

    if(direction)
        priv->block = priv->psc->getSend(block);
    else
        priv->block = priv->psc->getRecv(block);

    if(!priv->block) {
        fprintf(stderr, "%s: can't get block %u from PSC '%s'\n",
                priv->prec->name, block, name.c_str());
        return 1;
    }
    return 0;
}

