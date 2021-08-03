#include "cengine/util/log.h"

int
main(void)
{
    ce_logi("Hi :)");
    ce_loge("Uh oh...");

    ce_logw("Warning");

    ce_logf("Dead");
    ce_logi("Shouldn't reach here");
}
