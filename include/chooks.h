#ifndef LIBCHOOKS_CHOOKS_H
# define LIBCHOOKS_CHOOKS_H

# define _GNU_SOURCE
# include <stdio.h>
# include <dlfcn.h>
# include <sys/types.h>

typedef void (*main_hook_t)(void **args, void *retval);
typedef void (*pre_hook_t)(void **args);
typedef void (*post_hook_t)(void **args, void *retval);

#define MAX_HOOKS 8

typedef struct {
  const char  *func_name;
  void        *real;
  main_hook_t main;
  pre_hook_t  pre[MAX_HOOKS];
  int         pre_count;
  post_hook_t post[MAX_HOOKS];
  int         post_count;
} hook_info_t;

# define ARGS_COUNT(...) ARGS_COUNT_HELPER(__VA_ARGS__,  9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
# define ARGS_COUNT_HELPER(_1, _2, _3, _4, _5, _6, _7, _8, _9, N, ...) N

# define SIG_0
# define SIG_1(T1) T1 _1
# define SIG_2(T1, T2) T1 _1, T2 _2
# define SIG_3(T1, T2, T3) T1 _1, T2 _2, T3 _3
# define SIG_4(T1, T2, T3, T4) T1 _1, T2 _2, T3 _3, T4 _4
# define SIG_5(T1, T2, T3, T4, T5) T1 _1, T2 _2, T3 _3, T4 _4, T5 _5
# define SIG_6(T1, T2, T3, T4, T5, T6) T1 _1, T2 _2, T3 _3, T4 _4, T5 _5, T6 _6
# define SIG_7(T1, T2, T3, T4, T5, T6, T7) T1 _1, T2 _2, T3 _3, T4 _4, T5 _5, T6 _6, T7 _7
# define SIG_8(T1, T2, T3, T4, T5, T6, T7, T8) T1 _1, T2 _2, T3 _3, T4 _4, T5 _5, T6 _6, T7 _7, T8 _8
# define SIG_9(T1, T2, T3, T4, T5, T6, T7, T8, T9) T1 _1, T2 _2, T3 _3, T4 _4, T5 _5, T6 _6, T/ _7, T8 _8, T9 _9

# define CALL_0
# define CALL_1 _1
# define CALL_2 _1, _2
# define CALL_3 _1, _2, _3
# define CALL_4 _1, _2, _3, _4
# define CALL_5 _1, _2, _3, _4, _5
# define CALL_6 _1, _2, _3, _4, _5, _6
# define CALL_7 _1, _2, _3, _4, _5, _6, _7
# define CALL_8 _1, _2, _3, _4, _5, _6, _7, _8
# define CALL_9 _1, _2, _3, _4, _5, _6, _7, _8, _9

# define ARRAY_0 (void *[1]){ NULL }
# define ARRAY_1 (void *[1]){ (void *)&_1 }
# define ARRAY_2 (void *[2]){ (void *)&_1, (void *)&_2 }
# define ARRAY_3 (void *[3]){ (void *)&_1, (void *)&_2, (void *)&_3 }
# define ARRAY_4 (void *[4]){ (void *)&_1, (void *)&_2, (void *)&_3, (void *)&_4 }
# define ARRAY_5 (void *[5]){ (void *)&_1, (void *)&_2, (void *)&_3, (void *)&_4, (void *)&_5 }
# define ARRAY_6 (void *[6]){ (void *)&_1, (void *)&_2, (void *)&_3, (void *)&_4, (void *)&_5, (void *)&_6 }
# define ARRAY_7 (void *[7]){ (void *)&_1, (void *)&_2, (void *)&_3, (void *)&_4, (void *)&_5, (void *)&_6, (void *)&_7 }
# define ARRAY_8 (void *[8]){ (void *)&_1, (void *)&_2, (void *)&_3, (void *)&_4, (void *)&_5, (void *)&_6, (void *)&_7, (void *)&_8 }
# define ARRAY_9 (void *[9]){ (void *)&_1, (void *)&_2, (void *)&_3, (void *)&_4, (void *)&_5, (void *)&_6, (void *)&_7, (void *)&_8, (void *)&_9 }

#define GLUE(A, B) A##B
#define EVAL_GLUE(A, B) GLUE(A, B)

# define MAKE_SIG(Count, Types) EVAL_GLUE(SIG_, Count) Types
# define MAKE_CALL(Count) EVAL_GLUE(CALL_, Count)
# define MAKE_ARRAY(Count) EVAL_GLUE(ARRAY_, Count)

# define INIT_HOOK(RetType, FuncName, ArgTypes)                                \
__attribute__((weak)) hook_info_t FuncName##_hook_info = {                     \
  .func_name = #FuncName,                                                      \
	.real = NULL,                                                                \
	.main = NULL,                                                                \
  .pre = NULL,                                                                 \
  .pre_count = 0,                                                              \
  .post = NULL,                                                                \
  .post_count = 0 };                                                           \
                                                                               \
__attribute__((weak))                                                          \
RetType FuncName ( MAKE_SIG( ARGS_COUNT ArgTypes, ArgTypes ) ) {               \
  static RetType (*real_func) ArgTypes = NULL;                                 \
  if (!FuncName##_hook_info.real) {                                            \
		FuncName##_hook_info.real = dlsym(RTLD_NEXT, #FuncName);                   \
  }                                                                            \
  void *args = MAKE_ARRAY(ARGS_COUNT ArgTypes);                                \
  for (int i = 0; i < FuncName##_hook_info.pre_count; i++) {                   \
    if (FuncName##_hook_info.pre[i]) {                                         \
      FuncName##_hook_info.pre[i](args);                                       \
    }                                                                          \
  }                                                                            \
  RetType result;                                                              \
  if (!FuncName##_hook_info.main) {                                            \
		__typeof__(FuncName) *call_real = (__typeof__(FuncName) *)FuncName##_hook_info.real; \
    result = call_real ( MAKE_CALL( ARGS_COUNT ArgTypes ) );                   \
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

#endif /* !LIBCHOOKS_CHOOKS_H */
