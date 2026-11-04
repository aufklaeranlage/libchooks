#ifndef CHOOKS_DYNAMIC_H
# define CHOOKS_DYNAMIC_H

# include "utils.h"

# include <stdio.h>
# include <dlfcn.h>
# include <sys/types.h>

typedef void (*main_hook_t)(void **args, void *retval);
typedef void (*pre_hook_t)(void **args);
typedef void (*post_hook_t)(void **args, void *retval);

#define MAX_HOOKS 8

typedef struct {
  const char  *func_name;
  main_hook_t main;
  pre_hook_t  pre[MAX_HOOKS];
  int         pre_count;
  post_hook_t post[MAX_HOOKS];
  int         post_count;
} hook_info_t;

# define MAKE_SIG(Count, Types) EVAL_GLUE(SIG_, Count) Types
# define MAKE_CALL(Count) EVAL_GLUE(CALL_, Count)
# define MAKE_ARRAY(Count) EVAL_GLUE(ARRAY_, Count)

# define INIT_HOOK(RetType, FuncName, ArgTypes)                                \
__attribute__((weak)) hook_info_t FuncName##_hook_info = {                     \
  .func_name = #FuncName,                                                      \
  .main = NULL,                                                                \
  .pre = NULL,                                                                 \
  .pre_count = 0,                                                              \
  .post = NULL,                                                                \
  .post_count = 0 };                                                           \
                                                                               \
__attribute__((weak)) RetType (*real_##FuncName) ArgTypes = NULL;   \
                                                                               \
__attribute__((weak))                                                          \
RetType FuncName ( MAKE_SIG( ARGS_COUNT ArgTypes, ArgTypes ) ) {               \
  static RetType (*real_func) ArgTypes = NULL;                                 \
  if (!real_##FuncName) {                                                      \
    real_##FuncName = dlsym(RTLD_NEXT, #FuncName);        \
  }                                                                            \
  void *args = MAKE_ARRAY(ARGS_COUNT ArgTypes);                                \
  for (int i = 0; i < FuncName##_hook_info.pre_count; i++) {                   \
    if (FuncName##_hook_info.pre[i]) {                                         \
      FuncName##_hook_info.pre[i](args);                                       \
    }                                                                          \
  }                                                                            \
  RetType result;                                                              \
  if (!FuncName##_hook_info.main) {                                            \
    result = real_##FuncName ( MAKE_CALL( ARGS_COUNT ArgTypes ) );             \
  } else {                                                                     \
    FuncName##_hook_info.main(args, (void*)&result);                           \
  }                                                                            \
  for (int i = 0; i < FuncName##_hook_info.post_count; i++) {                  \
    if (FuncName##_hook_info.post[i]) {                                        \
      FuncName##_hook_info.post[i](args, (void*)&result);                      \
    }                                                                          \
  }                                                                            \
  return result;                                                               \
}

int register_pre_hook(hook_info_t *info, pre_hook_t hook);

int register_post_hook(hook_info_t *info, post_hook_t hook);

int register_main_hook(hook_info_t *info, main_hook_t hook);

# define REGISTER_MAIN_HOOK(TargetFunc, HookFunc) \
	register_main_hook(&TargetFunc##_hook_info, HookFunc)

# define REGISTER_PRE_HOOK(TargetFunc, HookFunc) \
  register_pre_hook(&TargetFunc##_hook_info, HookFunc)

# define REGISTER_POST_HOOK(TargetFunc, HookFunc) \
  register_post_hook(&TargetFunc##_hook_info, HookFunc)

#endif /* !CHOOKS_DYNAMIC_H */
