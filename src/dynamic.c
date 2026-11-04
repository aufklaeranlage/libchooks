#include "chooks/dynamic.h"

int register_main_hook(hook_info_t *info, main_hook_t hook)
{
  if (info->main == NULL) {
    info->main = hook;
  } else {
    fprintf(stderr, "[libchooks] Main-Hook already set for %s\n", info->func_name);
    return 0;
  }
  return 1;
}

int register_pre_hook(hook_info_t *info, pre_hook_t hook)
{
  if (info->pre_count < MAX_HOOKS) {
    info->pre[info->pre_count++] = hook;
  } else {
    fprintf(stderr, "[libchooks] Pre-Hook limit reached for %s\n", info->func_name);
    return 0;
  }
  return 1;
}

int register_post_hook(hook_info_t *info, post_hook_t hook)
{
  if (info->post_count < MAX_HOOKS) {
    info->post[info->post_count++] = hook;
  } else {
    fprintf(stderr, "[libchooks] Post-Hook limit reached for %s\n", info->func_name);
    return 0;
  }
  return 1;
}
